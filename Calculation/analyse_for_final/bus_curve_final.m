function bus_curve_final(data,titlle,dir_,sav,wth)
    %     clf;
    t = data.tout;
    figure;
    wanted = data.Vdc_wanted.signals.values(1)+zeros(1,length(t));
    real = data.Vdc_real.signals.values;
    %     real(3200*1e3:end) = min(72.25,max(71.75,real(3200*1e3:end)));
    plot(t,wanted,'lineWidth',wth);
    hold on;
    plot(t,real,'lineWidth',wth);
    legend('Wanted DC bus voltage','Real DC bus voltage');
    ylabel('Voltage (Volts)');
    xlabel('Time (s)');
    ylim([wanted(1)-0.75 wanted(1)+0.75]);
    title(strcat(titlle,' - dc bus voltage curves'));
    if strcmp(sav,'save')
        savefig(strcat(dir_,'\',titlle,' - dc bus voltage curves.fig'));
        saveas(gcf,strcat(dir_,'\',titlle,' - dc bus voltage curves.png'));
    end
end