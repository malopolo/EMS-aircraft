function [rmse_p, rmse_v,error_p,error_v] = error_sim(var)
    % rmse
    out = var.out;
    ep = out.RMSE_power.Data;
    ev = out.RMSE_voltage.Data;
    t = out.RMSE_voltage.Time;
    
    
    
    for i = 1:length(t)
        if ~isfinite(ev(i)) || ev(i) > 100
            ev(i) = 0;
        end
    end

    rmse_p = sqrt(mean(ep,'omitnan'));
    rmse_v = sqrt(mean(ev,'omitnan'));
    
    % error
    error_p = mean(out.error_power.Data);
    error_v = mean(out.error_voltage.Data);
end
