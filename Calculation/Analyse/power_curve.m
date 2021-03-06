function power_curve(data,titlle)
%     clf;
    t = data.tout;
    figure;    
    plot(t,data.compar_out.signals.values(:,1));
        hold on;
    plot(t,data.compar_out.signals.values(:,2));
    plot(t,data.compar_out.signals.values(:,3));
    plot(t,data.compar_out.signals.values(:,4));
    plot(t,data.compar_out.signals.values(:,5));
    legend('Pout required','Pout real','Pfc out','Pbatt out', 'Ppv out');
    ylabel('Power (Watts)');
    xlabel('Time (s)'); 
    title(strcat(titlle,' - power curves'));
    
    figure;
    plot(t,data.compar_in.signals.values(:,3));
        hold on;
    data.compar_in.signals.values(3200*1e3:end,4) = min(0,max(-200,data.compar_in.signals.values(3200*1e3:end,4)));
    plot(t,data.compar_in.signals.values(:,4));
    legend('Pfc','Pbatt');
    ylabel('Power (Watts)');
    xlabel('Time (s)'); 
    title(strcat(titlle,' - power curves'));
    ylim([-500 2000]);
end