function [DIfc, mh2, error_power, SOC] = get_results_from_sim(model,model_type)
    SOC_ini = 80;
    count = 0;
    mH2 = 0;
    
    %% Set sim time
    SimTime = 60; % Max simulation time
    
    %% start sim
    model_res = sim(model,'StartTime','0','StopTime',num2str(SimTime));
    if strcmp(model_type, 'powertrain')
        Ifc = model_res.FC.signals.values(:,4);
    else
        Ifc = model_res.FC.signals.values(:,1);
    end
    t = model_res.tout;
    assignin('base','tttt',t);
    %     bus_curve(model_res,'');
    %     power_curve(model_res,'');
    % compute the hydrogen consumption
    mh2 = h2_consumption(Ifc,t,1);
    
    % differences between adjacent elements = slope
    DIfc = diff(Ifc);
    
    % return the diff with power
    error_power = model_res.error_power.data;
    % Replace all inf / Nan value by 0
    error_power(isinf(error_power)|isnan(error_power)) = 0;
    
    % SOC
    SOC = model_res.Batt.signals.values(end,1);
    
end