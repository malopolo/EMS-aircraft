function bus_curve(data,titlle)
    clf;
    var = data.out;
    t = var.tout;
    figure;
    wanted = var.LOAD.signals.values(:,2);
    real = var.LOAD.signals.values(:,1);
    plot(t,wanted);
    hold on;
    plot(t,real);
    legend('Wanted DC bus voltage','Real DC bus voltage');
    ylabel('Voltage (Volts)');
    xlabel('Time (s)');
    ylim([wanted(1)-2 wanted(1)+2]);
    title(strcat(titlle,' - dc bus voltage curves'));
end