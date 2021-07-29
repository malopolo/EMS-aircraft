function [mep, mev] = error_(out)
    ep = out.RMSE_power.Data;
    ev = out.RMSE_voltage.Data;
    t = out.RMSE_voltage.Time;
    
    % ep = RMSE_power.Data;
    % ev = RMSE_voltage.Data;
    % t = RMSE_voltage.Time;
    
    for i = 1:length(t)
        if ~isfinite(ev(i)) || ev(i) > 100
            ev(i) = 0;
        end
    end
    
    clf
    figure(1)
    plot(t,ep);
    hold on;
    plot(t,ev);
    legend('Power error','Voltage error');
    title('Error graph');
    ylabel('Mean Square Error (%)');
    xlabel('Time (s)');
    
    mep = mean(ep,'omitnan');
    mev = mean(ev,'omitnan');
end
