function [col] = mean_power(sim)
    col = zeros(numel(sim),7);
    for i = 1:numel(sim)
        tabin = mean(sim(i).out.compar_in.signals.values);
        tabout = mean(sim(i).out.compar_out.signals.values);
        col(i,1) = tabin(3);
        col(i,2) = tabout(3);
        col(i,3) = tabin(4);
        col(i,4) = tabout(4);
        col(i,5) = tabin(5);
        col(i,6) = tabout(5);
        col(i,7) = mean(sim(i).out.SC.signals.values(:,1));
    end
end
