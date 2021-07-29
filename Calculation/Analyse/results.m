function [] = results(PI,SMC,FUZZY)
%     t = linspace(0,PI.tout,length(PI.tout));
t = PI.tout;
    %     figure(1);
    %     plot(t,PI.error.power);
    %     hold on;
    %     plot(t,SMC.error.power);
    %     hold on;
    %     plot(t,FUZZY.error.power);
    %
    %     figure(2);
    %     plot(t,PI.error.voltage);
    %     hold on;
    %     plot(t,SMC.error.voltage);
    %     hold on;
    %     plot(t,FUZZY.error.voltage);
    %
    %     figure(3);
    %     plot(t,PI.bus.power);
    %     hold on;
    %     plot(t,SMC.bus.power);
    %     hold on;
    %     plot(t,FUZZY.bus.power);
    %
    %     figure(4);
    %     plot(t,PI.bus.voltage);
    %     hold on;
    %     plot(t,SMC.bus.voltage);
    %     hold on;
    %     plot(t,FUZZY.bus.voltage);
    
    clf;
    figure(5);
    plot(t,PI.compar_out.P_out_required.data);
        hold on;
    plot(t,PI.compar_out.P_out_real.data);
    plot(t,PI.compar_out.P_fc_out.data);
    plot(t,PI.compar_out.P_batt_out.data);
    plot(t,PI.compar_out.P_pv_out.data);
    legend('Pout required','Pfc out','Pbatt out', 'Ppv out');
    title('PI power curves');
    ylabel('Power (Watts)');
    xlabel('Time (s)');

    
        figure(6);
    plot(t,SMC.compar_out.P_out_required.data);
        hold on;
    plot(t,SMC.compar_out.P_out_real.data);
    plot(t,SMC.compar_out.P_fc_out.data);
    plot(t,SMC.compar_out.P_batt_out.data);
    plot(t,SMC.compar_out.P_pv_out.data);
        legend('Pout required','Pfc out','Pbatt out', 'Ppv out');
    title('SMC power curves');
    ylabel('Power (Watts)');
    xlabel('Time (s)');
    
        figure(7);
    plot(t,FUZZY.compar_out.P_out_required.data);
        hold on;
    plot(t,FUZZY.compar_out.P_out_real.data);
    plot(t,FUZZY.compar_out.P_fc_out.data);
    plot(t,FUZZY.compar_out.P_batt_out.data);
    plot(t,FUZZY.compar_out.P_pv_out.data);
        legend('Pout required','Pfc out','Pbatt out', 'Ppv out');
    title('FUZZY power curves');
    ylabel('Power (Watts)');
    xlabel('Time (s)');
        
        figure(8);
    plot(t,PI.voltage.wanted.data);
        hold on;
    plot(t,PI.voltage.real.data);
    legend('Wanted DC bus voltage','Real DC bus voltage');
    title('PI DC bus voltage curves');
    ylabel('Voltage (Volts)');
    xlabel('Time (s)');

        
        figure(9);
    plot(t,SMC.voltage.wanted.data);
    hold on;
    plot(t,SMC.voltage.real.data);
        legend('Wanted DC bus voltage','Real DC bus voltage');
    title('SMC DC bus voltage curves');
    ylabel('Voltage (Volts)');
    xlabel('Time (s)');
        
        figure(10);
    plot(t,FUZZY.voltage.wanted.data);
        hold on;
    plot(t,FUZZY.voltage.real.data);
        legend('Wanted DC bus voltage','Real DC bus voltage');
    title('FUZZY DC bus voltage curves');
    ylabel('Voltage (Volts)');
    xlabel('Time (s)');

end