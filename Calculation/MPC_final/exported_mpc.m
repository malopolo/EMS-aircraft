function [Vfc_conv,Ifc_boost,f] = exported_mpc(Vfc ,Ifc ,Vdc,Ifc_out,ILmax,Vdc_ref,Ipv_out,SOC,time_data,...
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
    Hp = 0.5;
    TsOpti = Hp;
%     TsOpti = Ts*1e3;
    
    %     Ts = 1e-3; %     Hp = 20; %     TsOpti = Ts*1e3;
    
    
    
    
    %% approximation of states of the FC part
    %     [Vin,Vout,Iout,Pin,Pout,FCdata] = fc_powertrain_fun(Vdc,Ifc_out,ILmax,Vdc_ref,FCdata);
    %     Rout = Vdc/Ifc_out;
    %     Iin = FCdata.x_k(1);
    %     Vout = FCdata.x_k(2);
    
    SOC_k = SOC;
    [f,new_fc_func,new_batt_func,new_h2_func] = one_global_cost_function(0,time_data/Ts,Pfc_k,Ifc_in_k,Ibatt_in_k,...
        SOC_k,old_fc_func,old_batt_func,old_h2_func,time_data/Ts);
    old_fc_func = old_fc_func+new_fc_func;
    old_batt_func = old_batt_func+new_batt_func;
    old_h2_func = old_h2_func+new_h2_func;
    f = f*Ts;
    
    %% FC control
    % FC converter operates ?
    currind = time_data/Ts;
    
    len = length(Pload_full);
    
    %% fonctionne bien
    if mod((time_data/TsOpti),Hp) == 0
        dPfc = 100;
        Ppv_out = Ipv_out*Vdc;
        Pfc_grid = min(1100,max(0,(Pfc_k-dPfc):0.1:(Pfc_k+dPfc)));
        
%         Pbatt_grid = (Pwanted-Ppv_out-Pfc_grid*0.9)/0.9;
        Pbatt_grid = (Pout_real-Ppv_out-Pfc_grid*0.9)/0.9;
        
        
        dsoc_grid = TsOpti/Ts*feval(mdl_dsoc,Pbatt_grid); % delta soc grid (possible)
        soc_grid = SOC + dsoc_grid;
        
        Ifc_in = feval(mdl_ifc,Pfc_grid); % function of Pfc
        Ibatt_in = feval(mdl_ibatt,Pbatt_grid,soc_grid); % function of Pbatt and SOC
        
        
        [gcf,~,~,~] = one_global_cost_function(0,time_data/Ts,Pfc_grid,Ifc_in,Ibatt_in,...
            soc_grid,old_fc_func,old_batt_func,old_h2_func,time_data/Ts);
        [~,ind] = min([gcf]);
        Pfc = Pfc_grid(ind);
        
    else
        Pfc = Pfc_command_pre;
    end
    Pfc_command_pre = Pfc;
    %%
    
    
    %     if mod((time_data/TsOpti),Hp/2) == 1 && len(1)-currind > TsOpti/Ts*Hp
    %
    %         Ppv_out = Ipv_out*Vdc;
    %
    %         Pfc_command_min=0;
    %         Pfc_command_max=1100;
    %         SOC_min=40; SOC_max=90;
    %
    %         size_step = 0:TsOpti/Ts:TsOpti/Ts*Hp;
    %         currtime = round(currind+size_step);
    %         Pload_est = Pload_full(currtime(1:Hp));
    %
    %
    %         Ifc_out = Pout/Vdc;
    %
    %         y = opti_fcn(x0,lb,ub,Vin,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,Hp,Pload_est,Ppv_out,k,TsOpti);
    %
    %         Pfc=y(1);
    %
    %     else
    %         Pfc = Pfc_command_pre;
    %     end
    %     Pfc_command_pre = Pfc;
    
    %     Ifc_boost = min(1100,max(0,Pfc))/Vin;
    Ifc_boost = min(1100,max(0,Pfc))/Vfc;
    
    % Converter command output voltage
    Vfc_conv = Vdc_ref;
    %     if Iin < Ifc_boost
    if Ifc < Ifc_boost
        Vfc_conv = 100;
    end
    
    
end

