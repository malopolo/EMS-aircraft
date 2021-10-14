function [Batt] = battery_model(current,Batt)

    format long
    %% init states
    old_i_filter = Batt.old_i_filter;
    old_old_var = Batt.old_old_var;
    old_var = Batt.old_var;
    old_res = Batt.old_res;
    old_it_sat = Batt.old_it_sat;
    old_current = current;
    
    %% start
%     if Batt.init == 0
%         i_filter = old_current + (old_current - old_i_filter)*Batt.B_;
%     else
%         i_filter = 0;
%     end

    if Batt.init == 0
        old_var = 1;
        old_old_var = 1;
    end
    i_filter = old_current + (old_current - old_i_filter)*Batt.B_;
    var = i_filter>0;
    
    
%     if old_old_var ~= old_var
%         old_current = old_it_sat*3600;
%     end
    
    res = old_res+Batt.Ts*old_current;
    
%     if var ~= old_var && Batt.init == 0
%         res = 0;
%     end
    
    if var ~= old_var && var > 0
       res = old_it_sat*3600; 
    end
    % init first res
    if Batt.init == 1
        res = old_res;
    end
    
    old_old_var = old_var;
    old_var = var;
    old_res = res;
    
    if res > Batt.Qmax*3600
        res = Batt.Qmax*3600;
    end
    
%     i_filter
    
    it_SC = res/3600;
    it_sat = it_SC;
    
    if it_sat > Batt.Qc*0.9999
        it_sat = Batt.Qc*0.9999;
    elseif it_sat < 0
        it_sat = 0;
    end
    
    if Batt.Qc*0.9999*(1+1e-6)/Batt.lambda/0.9999 <= it_sat
        it_sat = Batt.Qc*0.9999;
    end
    
    if it_SC > Batt.Qc*0.9999
        it_SC = 0.9999;
    elseif it_SC < 0.9999*Batt.Qc*(1-1e-3)*0.9999
        it_SC = 0.9999*Batt.Qc*(1-1e-3)*0.9999;
    end
    
    i_other = Batt.A* exp(-Batt.B*it_sat);
    if it_sat > Batt.Qmax/Batt.lambda
        i_other = Batt.Qmax/Batt.lambda;
    end
    i_other = max(-Inf,i_other);
    

%     discharge = - var*Batt.K*i_filter*Batt.Qc/(Batt.Qc-it_sat)
%     charge = - (1-var)*Batt.K*i_filter*Batt.Qc/(it_SC+Batt.Qc*Batt.kc) % charge
%     expp = i_other
    E1 = Batt.E0 - Batt.K*Batt.Qc/(Batt.Qc-it_sat)*it_sat ...
        - var*Batt.K*i_filter*Batt.Qc/(Batt.Qc-it_sat) ...
        - (1-var)*Batt.K*i_filter*Batt.Qc/(it_SC+Batt.Qc*Batt.kc) ...
        + i_other ...
        - it_sat*Batt.C;
    
    if E1 > 2*Batt.E0
        E1 = 2*Batt.E0;
    elseif E1 < old_current*Batt.R
        E1 = old_current*Batt.R;
    end
    
    voltage = E1;
%     ouput_voltage = E1 - old_current * Batt.R;
    
    SOC = 100*(1-it_sat/(Batt.Qc/Batt.lambda));
    if SOC > 100
        SOC = 1;
    elseif SOC < 0
        SOC = 0;
    end
    
    Batt.voltage = voltage;
%     Batt.ouput_voltage = ouput_voltage;
    Batt.SOC = SOC;
        
    %% save states
    Batt.old_i_filter = i_filter;
    Batt.old_old_var = old_old_var;
    Batt.old_var = old_var;
    Batt.old_res = old_res;
    Batt.old_it_sat = old_it_sat;
    Batt.old_current = old_current;
    Batt.init = 0;
end

