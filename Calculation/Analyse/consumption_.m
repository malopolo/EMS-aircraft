function [chydro, cair, Batt_SOC, Batt_SOH] = consumption_(out)
    Ifc = out.FC.Ifc.Data;
    t = out.tout;
    N = 50; % Number of cells
    F = 96485; % Faraday constant
    nf = N/F;
    temp = nf*Ifc;
    
    chydro = trapz(t,temp);
    cair = 0;
    Batt_SOC = out.Batt.SOC____.Data(end);
    
    batt_curr = out.Batt.Current__A_.Data;
%     for i=1:length(out.Batt.Current__A_.Data)
%        if batt_curr(i) <0
%            batt_curr(i) = 0;
%        end
%     end
    Batt_SOH = trapz(t,batt_curr)/14/60/60; % 14 = rated capacity
end
