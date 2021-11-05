fis = readfis('fis_thesis_solo.fis');
plotmf(fis,'input',1);
savefig('Pdemand.fig')
saveas(gcf,'Pdemand.png')

plotmf(fis,'input',2);
savefig('SOC.fig')
saveas(gcf,'SOC.png')

plotmf(fis,'output',1);
savefig('Pfc_demand.fig')
saveas(gcf,'Pfc_demand.png')

gensurf(fis)
savefig('surf_fis_thesis_solo.fig')
saveas(gcf,'surf_fis_thesis_solo.png')
