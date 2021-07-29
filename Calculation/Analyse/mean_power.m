function [P_FC_in, P_PV_in, P_batt_in, P_SC] = mean_power(out)   
    P_PV_in = mean(out.PV.V_PV.data .* out.PV.I_PV.data);
    P_FC_in = mean(out.FC.Vfc.data .* out.FC.Ifc.data);
    P_batt_in = mean(out.Batt.Voltage__V_.data .* out.Batt.Current__A_.data);
    % Calculated after 0.2sec
    P_SC = mean(out.SC.out.data);
end
