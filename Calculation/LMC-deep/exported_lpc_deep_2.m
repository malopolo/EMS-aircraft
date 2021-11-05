function [Vfc_conv,Ifc_boost,f] = exported_lpc_deep_2(Vfc ,Ifc ,Vdc,Ifc_out,ILmax,Vdc_ref,Ipv_out,SOC,time_data,...
        Pfc_k,Ifc_in_k,Ibatt_in_k,Pout_real,Pwanted)
    %% init data
    persistent mdl_dsoc mdl_ibatt mdl_ifc FCdata ...
        Pload_full Pfc_command_pre old_fc_func old_batt_func old_h2_func
%     if isempty(mdl_ifc)
    if time_data == 0
        currentpath = pwd;
        currentfolder = strsplit(currentpath,filesep);
        while ((~strcmp(currentfolder{end}, 'EMS-aircraft')) && ...
                (~strcmp(currentfolder{end}, 'EMS-aircraft-main')) && ...
                ~isempty(currentfolder{end}))
            currentpath = fileparts(currentpath);
            currentfolder = strsplit(currentpath,filesep);
        end
        projectpath = currentpath;
        addpath(genpath(projectpath));
        
        [~,FCdata,~,~] = init_sources(1e-3,80);
        FCdata.x_k = [-0.014465353509422;72];
        FCdata.Efc = 63.508550469803609;
        
        temp = open('mdl_dsoc.mat');
        mdl_dsoc = temp.mdl_dsoc;
        temp = open('mdl_ibatt.mat');
        mdl_ibatt = temp.mdl_ibatt;
        temp = open('mdl_ifc.mat');
        mdl_ifc = temp.mdl_ifc;
        
        Pload_full = evalin('base', 'w');
        
        Pfc_command_pre = 400;
        
        old_fc_func = 0;
        old_batt_func = 0;
        old_h2_func = 0;
        f = 0;
    end

    
    %% start opti
    Ts = 1e-3;
    Hp = 1;
    TsOpti = Hp;
%     TsOpti = Ts*1e3;
    

    Tot_sample = 2;
    Num_sample = 2;
    
    
    %% approximation of states of the FC part
    [Vin,Vout,Iout,Pin,Pout,FCdata] = fc_powertrain_fun(Vdc,Ifc_out,ILmax,Vdc_ref,FCdata);
    Rout = Vdc/Ifc_out;
    Iin = FCdata.x_k(1);
    Vout = FCdata.x_k(2);
    
    SOC_k = SOC;
    [f,new_fc_func,new_batt_func,new_h2_func] = one_global_cost_function(0,time_data/Ts,Pfc_k,Ifc_in_k,Ibatt_in_k,...
        SOC_k,old_fc_func,old_batt_func,old_h2_func,time_data/Ts);
    old_fc_func = old_fc_func+new_fc_func;
    old_batt_func = old_batt_func+new_batt_func;
    old_h2_func = old_h2_func+new_h2_func;
    f = f*Ts;
    
    %% FC control
    % FC converter operates ?

    %% fonctionne bien
    if mod((time_data/TsOpti),Hp) == 0 && time_data > Ts
        x0 = Pfc_command_pre;
        dPfc = 100;
%         lb = [0];
%         ub = [1100];
        lb = [max(0,x0-dPfc)];
        ub = [min(1100,x0+dPfc)];
        
        Pfc = opti_fc_lmc_deep_2(Ts,Tot_sample,Num_sample,x0,lb,ub,SOC,Pwanted,@fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
        @one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc);
    else
        Pfc = Pfc_command_pre;
    end
    Pfc_command_pre = Pfc;

    Ifc_boost = min(1100,max(0,Pfc))/Vfc;
    
    % Converter command output voltage
    Vfc_conv = Vdc_ref;

    if Ifc < Ifc_boost
        Vfc_conv = 100;
    end
    
    
end

