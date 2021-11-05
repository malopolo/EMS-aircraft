fis = readfis('DP_ANFIS_mid.fis');
plotmf(fis,'input',1);
xlabel('Output Power demand');
savefig('Pdemand_DP_ANFIS_mid.fig')
saveas(gcf,'Pdemand_DP_ANFIS_mid.png')

plotmf(fis,'input',2);
xlabel('Battery SOC value');
savefig('SOC_DP_ANFIS_mid.fig')
saveas(gcf,'SOC_DP_ANFIS_mid.png')

% plotmf(fis,'output',1);
% savefig('Pfc_demand_DP_ANFIS_mid.fig')
% saveas(gcf,'Pfc_demand_DP_ANFIS_mid.png')

[mx,my,mz] = gensurf(fis);
surf(mx,my+20,min(1100,max(0,mz)));
zlim([0 1100])
colorbar
colormap winter;
xlabel('Output Power demand');
ylabel('Battery SOC value');
zlabel('Fuel Cell Power command');
title('ANFIS-DP surface');
savefig('surf_fis_DP_ANFIS_mid.fig')
saveas(gcf,'surf_fis_DP_ANFIS_mid.png')
