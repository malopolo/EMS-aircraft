function [col] = mean_error(sim)
    sz_sim = size(sim);
    col = zeros(sz_sim(1),4);
    for i = 1:sz_sim(1)
        rmse_p = sim(i).RMSE_power.Data;
        rmse_v = sim(i).RMSE_voltage.Data;
        t = sim(i).RMSE_voltage.Time;
        ep = sim(i).error_power.Data;
        ev =sim(i).error_voltage.Data;

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
