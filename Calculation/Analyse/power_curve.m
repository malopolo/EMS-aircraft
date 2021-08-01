function power_curve(data,titlle)
    clf;
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
end