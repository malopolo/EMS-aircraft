function [P_FC, P_PV, P_batt, P_SC] = mean_power_sim(var,side)
    out = var.out;
    if strcmp(side,'in')
%         P_PV = mean(out.PV.signals.values(:,1) .* out.PV.signals.values(:,4));
%         P_FC = mean(out.FC.signals.values(:,1) .* out.FC.signals.values(:,4));
%         P_batt = mean(out.Batt.signals.values(:,1) .* out.Batt.signals.values(:,3));
        P_PV = mean(out.compar_in.signals.values(:,5));
        P_FC = mean(out.compar_in.signals.values(:,3));
        P_batt = mean(out.compar_in.signals.values(:,4));
    else
%         P_PV = mean(out.LOAD.signals.values(:,1) .* out.PV.signals.values(:,5));
%         P_FC = mean(out.LOAD.signals.values(:,1) .* out.FC.signals.values(:,5));
%         P_batt = mean(out.LOAD.signals.values(:,1) .* out.Batt.signals.values(:,5));
        P_PV = mean(out.compar_out.signals.values(:,5));
        P_FC = mean(out.compar_out.signals.values(:,3));
        P_batt = mean(out.compar_out.signals.values(:,4));
    end
    % WARNING : Calculated after 0.2sec
    P_SC = mean(out.SC.signals.values(:,1));
end