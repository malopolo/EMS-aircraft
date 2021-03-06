%% Function to get the cost value of each pop member (each fuzzy set)
function Cost = cost_function(DIfc, mh2, error_power, SOC)
    w = 0.03;
    
    J1 = sum(DIfc.^2);
    
    J2 = sum(mh2);
    
    SOC = SOC/100;
    if SOC < 0.5
        Jp1 = 0.5-SOC;
    elseif SOC > 0.9
        Jp1 = SOC - 0.9;
    else
        Jp1 = 0;
    end
    
    Jp2 = sum(error_power) / height(error_power);
    
    % Cost return
    Cost = J1 + w*J2 + Jp1 + Jp2;
end