function [DIfc, mh2, error_power, SOC, Pfc] = fast_get_results_from_sim(model_res,model_type)
    count = 0;
    
    %% start sim
    if strcmp(model_type, 'powertrain')
        Ifc = model_res.FC.signals.values(:,4);
    else
        Ifc = model_res.FC.signals.values(:,1);
        Vfc = model_res.FC.signals.values(:,2);
    end
    t = model_res.tout;
    
    %     bus_curve(model_res,'');
    %     power_curve(model_res,'');
    
    % compute the hydrogen consumption
    mh2 = fast_h2_consumption(Ifc,t,1);
    
    % differences between adjacent elements = slope
    DIfc = diff(Ifc);
    
    % return the diff with power
    error_power = model_res.error_power.data;
    % Replace all inf / Nan value by 0
    error_power(isinf(error_power)|isnan(error_power)) = 0;
    
    % SOC
    SOC = model_res.Batt.signals.values(end,1);
    
    % Pfc
    Pfc = Ifc .* Vfc;
end