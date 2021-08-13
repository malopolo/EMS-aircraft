function [Ifc,t] = model_sim(fisi,model,SOC_init)
%     EMS_block  = 'powertrain/EMS';

    %% Change the fuzzy file
    writeFIS(fisi,'fuzzy_to_improve_1.fis');
    
    %% Set data
    SimTime = 60; % Max simulation time
    %start sim
    model_res = sim(model,'StartTime','0','StopTime',num2str(SimTime));
    Ifc = model_res.FC.signals.values(:,4);
    t = model_res.tout;
end