% gcf_4 = out.gcf.signals.values;
% Pfc_in_4 = out.Pfc_in.signals.values;
% Pbatt_in_4 = out.Pbatt_in.signals.values;
% Ppv_in_4 = out.Ppv_in.signals.values;
% t_4 = out.tout;

% gcf_3 = out.gcf.signals.values;
% Pfc_in_3 = out.Pfc_in.signals.values;
% Pbatt_in_3 = out.Pbatt_in.signals.values;
% Ppv_in_3 = out.Ppv_in.signals.values;
% t_3 = out.tout;

gcf_2 = out.gcf.signals.values;
Pfc_in_2 = out.Pfc_in.signals.values;
Pbatt_in_2 = out.Pbatt_in.signals.values;
Ppv_in_2 = out.Ppv_in.signals.values;
t_2 = out.tout;

close all;
figure;
plot(t_4(1:10:end),gcf_4(1:10:end)/10)
hold on 
plot(t_3,gcf_3)
plot(t_2,gcf_2)
legend('gcf_4','gcf_3','gcf_2')

figure;
plot(t_4(1:10:end),Pfc_in_4(1:10:end))
hold on 
plot(t_3,Pfc_in_3)
plot(t_2,Pfc_in_2)
legend('Pfc_4','Pfc_3','Pfc_2')

figure;
plot(t_4(1:10:end),Ppv_in_4(1:10:end))
hold on 
plot(t_3,Ppv_in_3)
plot(t_2,Ppv_in_2)

figure;
plot(gcf_4(1:10:end)/10,Pbatt_in_4(1:10:end))
hold on 
plot(gcf_3,Pbatt_in_3)
plot(gcf_2,Pbatt_in_2)
hold off