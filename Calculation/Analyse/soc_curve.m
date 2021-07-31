function soc_curve(data,titlle)
    clf;
    var = data.out;
    t = var.tout;
    figure;    
    plot(t,var.Batt.signals.values(:,6));
    legend('SOC');
    ylabel('SOC (%)');
    xlabel('Time (s)'); 
    title(strcat(titlle,' - SOC curve'));
end