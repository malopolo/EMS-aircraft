%% Function to get the fitness value of each member of the pop
% Each memember needs to be evaluated during a specific power profile
function Fit = new_fitness(Pop,fisi,Ts,Method,Pout,SimTime,SOC_batt_arr)
    len = height(Pop);
    Fit = zeros(len,1);
    
            %% Constant
        Vdc_wanted = 72;
        Ifc = 0.001;
        Ibatt = 0;
        Ppv_out = 140;
            power_fc = zeros(1,SimTime/Ts);
        current_fc = zeros(1,SimTime/Ts);
        voltage_fc = zeros(1,SimTime/Ts);
        current_batt = zeros(1,SimTime/Ts);
        voltage_batt = zeros(1,SimTime/Ts);
        soc_batt = zeros(1,SimTime/Ts);
        time_vector = 0:Ts:SimTime-Ts;
    if Method == 1
        [BATTdata,FCdata,PVdata,SCdata] = init_sources(Ts,SOC_batt_arr(1));
        
        %% start the fitness evaluation
        for i = 1:len
            % change the fuzzy (here we just change the fuzzy mfs)
            new_fis = new_change_mfs_fis(Pop(i,:),fisi,1);
            
            
            
            % get the results and compute the cost function
            Fit(i,1) = simple_powertrain_fuzzy(Ts, SimTime, BATTdata,FCdata, power_fc,current_fc,...
                voltage_fc,current_batt,voltage_batt,soc_batt,Pout,Ppv_out,time_vector,...
                new_fis);
        end
        
    else

        for j=1:length(SOC_batt_arr)
        [BATTdata,FCdata,PVdata,SCdata] = init_sources(Ts,SOC_batt_arr(j));
        
        %% start the fitness evaluation
        for i = 1:len
            % change the fuzzy (here we just change the fuzzy mfs)
            new_fis = new_change_mfs_fis(Pop(i,:),fisi,1);
            

            % get the results and compute the cost function
            Fit(i,1) = Fit(i,1)+simple_powertrain_fuzzy(Ts, SimTime, BATTdata,FCdata, power_fc,current_fc,...
                voltage_fc,current_batt,voltage_batt,soc_batt,Pout,Ppv_out,time_vector,...
                new_fis);
        end
        end
    end
    %     Fit
    
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