function soc_curve_final(data,titlle,dir_,sav,wth)
    clf;
    t = data.tout;
    figure;
    plot(t,data.SOC_batt.signals.values,'lineWidth',wth);
    legend('SOC');
    ylabel('SOC (%)');
    xlabel('Time (s)');
    title(strcat(titlle,' - SOC curve'));
    if strcmp(sav,'save')
        savefig(strcat(dir_,'\',titlle,' - SOC curve.fig'));
        saveas(gcf,strcat(dir_,'\',titlle,' - SOC curve.png'));
    end
end