function soc_curve(data,titlle)
    clf;
    t = data.tout;
    figure;    
    plot(t,data.Batt.signals.values(:,6));
    legend('SOC');
    ylabel('SOC (%)');
    xlabel('Time (s)'); 
    title(strcat(titlle,' - SOC curve'));
end