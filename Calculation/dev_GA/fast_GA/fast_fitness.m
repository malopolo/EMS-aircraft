%% Function to get the fitness value of each member of the pop
% Each memember needs to be evaluated during a specific power profile
function Fit = fast_fitness(Pop,fisi,model,Ts,Method)
    len = height(Pop);
    Fit = zeros(len,1);
    
    %% start the fitness evaluation
    for i = 1:len
        % change the fuzzy (here we just change the fuzzy mfs)
        fast_change_mfs_fis(Pop(i,:),fisi,Method);
        
        % compute the model / sim
        model_res = sim(model);
%         assignin('base','mood',model_res);
        % extract the data
        [DIfc, mh2, error_power, SOC, Pfc] = fast_get_results_from_sim(model_res,'');
        
        % compute the cost function and get the results
        Fit(i,1) = fast_cost_function(DIfc, mh2, error_power, SOC, Pfc,Ts);
    end
    
    %     %% start the fitness evaluation (parallel)
    %     global fuzzy_test
    %     for i = 1:len
    %         % change the fuzzy (here we just change the fuzzy mfs)
    %         para_fast_change_mfs_fis(Pop(i,:),fisi);
    %         in(i) = Simulink.SimulationInput('fast_powertrain');
    %         in(i) = in(i).setVariable('fuzzy_test',fuzzy_test);
    %     end
    %     simOut = parsim(in);
    %
    %     assignin('base','test',simOut);
    %     for i = 1:len
    %         model_res = simOut(i);
    %
    %         Ifc = model_res.FC.signals.values(:,1);
    %         t = model_res.tout;
    %
    %         %     bus_curve(model_res,'');
    %         %     power_curve(model_res,'');
    %         % compute the hydrogen consumption
    %         mh2 = fast_h2_consumption(Ifc,t,1);
    %
    %         % differences between adjacent elements = slope
    %         DIfc = diff(Ifc);
    %
    %         % return the diff with power
    %         error_power = model_res.error_power.data;
    %         % Replace all inf / Nan value by 0
    %         error_power(isinf(error_power)|isnan(error_power)) = 0;
    %
    %         % SOC
    %         SOC = model_res.Batt.signals.values(end,1);
    %         % compute the cost function and get the results
    %         Fit(i,1) = fast_cost_function(DIfc, mh2, error_power, SOC);
    %     end
end