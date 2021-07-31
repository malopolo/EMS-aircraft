function [col] = mean_error(sim)
    col = zeros(numel(sim),4);
    for i = 1:numel(sim)
        rmse_p = sim(i).out.RMSE_power.Data;
        rmse_v = sim(i).out.RMSE_voltage.Data;
        t = sim(i).out.RMSE_voltage.Time;
        ep = sim(i).out.error_power.Data;
        ev =sim(i).out.error_voltage.Data;

        for j = 1:length(t)
            if ~isfinite(ev(j)) || ev(j) > 100
                ev(j) = 0;
            end
            if ~isfinite(ep(j)) || ep(j) > 100
                ep(j) = 0;
            end
        end

        col(i,1) = sqrt(mean(rmse_p,'omitnan'));
        col(i,2) = sqrt(mean(rmse_v,'omitnan'));
        col(i,3) = mean(ep);
        col(i,4) = mean(ev);
    end
end
