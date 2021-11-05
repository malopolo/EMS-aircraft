function power_curve_final(data,titlle,dir_,sav,wth)
    %     clf;
    t = data.tout;
    
    figure;
    plot(t,data.Pout_wanted.signals.values,'lineWidth',wth);
    hold on;
    plot(t,data.Pout_real.signals.values,'lineWidth',wth);
    legend('Pout required','Pout real');
    ylabel('Power (Watts)');
    xlabel('Time (s)');
    title(strcat(titlle,' - output power curves'));
    ylim([-500 2000]);
    if strcmp(sav,'save')
        savefig(strcat(dir_,'\',titlle,' - output power curves.fig'));
        saveas(gcf,strcat(dir_,'\',titlle,' - output power curves.png'));
    end
    
    figure;
    plot(t,data.Pfc_in.signals.values,'lineWidth',wth);
    hold on;
    %     data.compar_in.signals.values(3200*1e3:end,4) = min(0,max(-200,data.compar_in.signals.values(3200*1e3:end,4)));
    plot(t,data.Pbatt_in.signals.values,'lineWidth',wth);
    legend('Pfc','Pbatt');
    ylabel('Power (Watts)');
    xlabel('Time (s)');
    title(strcat(titlle,' - power curves'));
    ylim([-500 2000]);
    if strcmp(sav,'save')
        savefig(strcat(dir_,'\',titlle,' - power curves.fig'));
        saveas(gcf,strcat(dir_,'\',titlle,' - power curves.png'));
    end
end