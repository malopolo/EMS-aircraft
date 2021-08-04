function [col] = consumption(sim)
    sz_sim = size(sim);
    col = zeros(sz_sim(1),5);
    for i = 1:sz_sim(1)
        t = sim(i).tout;
        N = 50; % Number of cells
        F = 96485; % Faraday constant
        nf = N/F;
        temp = nf*sim(i).FC.signals.values(:,4); % Ifc * N / F

        col(i,1) = trapz(t,temp);

        col(i,2) = sim(i).Batt.signals.values(end,6);

        col(i,3) = 1-trapz(t,sim(i).Batt.signals.values(:,3))/15/60/60; % 15 = rated capacity

        col(i,4) = 1- sim(i).Batt.signals.values(end,7);
        
        
        col(i,5) = sim(i).real_time_sim;
    end
end
