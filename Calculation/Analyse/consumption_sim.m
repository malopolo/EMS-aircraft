function [chydro, Batt_SOC, Batt_SOH,age] = consumption_sim(var)
    out = var.out;
    
    Ifc = out.FC.signals.values(:,4);
    t = out.tout;
    N = 50; % Number of cells
    F = 96485; % Faraday constant
    nf = N/F;
    temp = nf*Ifc;
    
    chydro = trapz(t,temp);
    Batt_SOC_temp = out.Batt.signals.values(:,6);
    Batt_SOC = Batt_SOC_temp(end);
    
    batt_curr =  out.Batt.signals.values(:,3);
    Batt_SOH = 1-trapz(t,batt_curr)/15/60/60; % 15 = rated capacity
    
    age_temp = out.Batt.signals.values(:,7);
    age = 1-age_temp(end);
end
