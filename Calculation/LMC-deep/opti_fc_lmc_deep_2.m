function y = opti_fc_lmc_deep_2(Ts,Tot_sample,Num_sample,x0,lb,ub,SOC,Pwanted,fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
        one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc)
    
    rng default % For reproducibility
%         gs = GlobalSearch('Display','off','XTolerance',1e-3);
    gs = MultiStart('Display','off','XTolerance',1e-3);

    options = optimoptions('fmincon','Algorithm','sqp',...
        'Display','off','MaxFunctionEvaluations',500,'MaxIterations',20,...
        'DiffMinChange',1);
    
    Ts = Ts*10;
    FCdata.Ts = Ts;
    
    objfcn = @(x)loop_res_fun(x,Ts,Tot_sample,Num_sample,SOC,Pwanted,fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
        one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc);
    
    problem = createOptimProblem('fmincon','x0',x0,...
        'objective',objfcn,'lb',lb,'ub',ub,'options',options);
    
%         y = run(gs,problem);
%     tic
    y = run(gs,problem,15);
%     toc


%     Pfc_grid = 0:10:1100;
%     gcf = zeros(1,length(Pfc_grid));
%     for i=1:length(Pfc_grid)
%         f = loop_res_fun(Pfc_grid(i),Ts,Tot_sample,Num_sample,SOC,Pwanted,fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
%         one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc);
%         gcf(i) = f;
%     end
%     [~,ind] = min([gcf]);
%     y = Pfc_grid(ind)
end


% function f = loop_res_fun(Ts,Tot_sample,Num_sample,SOC,Pwanted,fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
%         one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc)
function f = loop_res_fun(x,Ts,Tot_sample,Num_sample,SOC,Pwanted,fc_powertrain_fun,Vdc,Ifc_out,ILmax,Vdc_ref,FCdata,...
        one_global_cost_function,time_data,old_fc_func,old_batt_func,old_h2_func,mdl_dsoc,mdl_ibatt,mdl_ifc)

    Iout = Ifc_out;
    numm = Tot_sample / Num_sample;
    Vdc_wanted = Vdc_ref;
    
    f = 0;
    for i=Ts:Ts:Tot_sample
        time_data = time_data+i;

        
        if ~mod(i,numm)
            dPfc = 100;
            Pfc_grid = x(1);

            Pbatt_grid = (Pwanted-Pfc_grid*0.9)/0.9;
    %         Pbatt_grid = (Pout_real-Ppv_out-Pfc_grid*0.9)/0.9;


            dsoc_grid = numm/Ts*feval(mdl_dsoc,Pbatt_grid); % delta soc grid (possible)
            soc_grid = SOC + dsoc_grid;

            Ifc_in = feval(mdl_ifc,Pfc_grid); % function of Pfc
            Ibatt_in = feval(mdl_ibatt,Pbatt_grid,soc_grid); % function of Pbatt and SOC

            
            [f_bis,new_fc_func,new_batt_func,new_h2_func] = one_global_cost_function(0,time_data/Ts,x(1),Ifc_in,Ibatt_in,...
                next_soc,old_fc_func,old_batt_func,old_h2_func,time_data/Ts);
            old_fc_func = old_fc_func+new_fc_func;
            old_batt_func = old_batt_func+new_batt_func;
            old_h2_func = old_h2_func+new_h2_func;
            f = f + f_bis*Ts;
        end
    end
end