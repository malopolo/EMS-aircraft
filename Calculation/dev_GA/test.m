function model_res = test(fisi)
    model = 'to_del';
    %% Set data
    % Ts = 1e-4;
    SimTime = 85; % Max simulation time
    SOC_init = 80;
    set_param('to_del/Fuzzy Logic Controller','FIS','fisi');
    %start sim
    model_res = sim(model,'StartTime','0','StopTime',num2str(SimTime));
    
end