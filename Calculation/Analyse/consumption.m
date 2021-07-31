function [col] = consumption(sim)
    col = zeros(numel(sim),4);
    for i = 1:numel(sim)
        t = sim(i).out.tout;
        N = 50; % Number of cells
        F = 96485; % Faraday constant
        nf = N/F;
        temp = nf*sim(i).out.FC.signals.values(:,4); % Ifc * N / F

        col(i,1) = trapz(t,temp);

        col(i,2) = sim(i).out.Batt.signals.values(end,6);

        col(i,3) = 1-trapz(t,sim(i).out.Batt.signals.values(:,3))/15/60/60; % 15 = rated capacity

        col(i,4) = 1- sim(i).out.Batt.signals.values(end,7);
    end
end
