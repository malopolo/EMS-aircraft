function [current,voltage,E1, old_i_filter, old_old_var,old_var, old_res, old_it_sat,old_current, SOC] = model_batt(Batt,current, Load,old_i_filter, old_old_var,old_var, old_res, old_it_sat,old_current)
    % num = [A_];
    % denum = [1 B_];
    % filter = tf(num,denum,Batt.Ts);
    % current = zeros(1,10*1/Batt.Ts)+10;
    % [y,t] = lsim(filter,current);
    % % same :
    % for i=Batt.Ts:Batt.Ts:10
    %     out = Batt.A_*curr-Batt.B_*old_i_filter;
    %     ttt = [ttt out];
    %     old_i_filter = out;
    % end
    
    
    i_filter = Batt.A_*current-Batt.B_*old_i_filter;
    var = i_filter>0;
    
    
    if old_old_var ~= old_var
        old_current = old_it_sat*3600;
    end
    
    res = old_res+1*Batt.Ts*old_current;
    
    if var ~= old_var
        res = 0;
    end
    
    
    
    old_old_var = old_var;
    old_var = var;
    old_res = res;
    
    if res > Batt.Qmax*3600
        res = Batt.Qmax*3600;
    end
    
    
    
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
    
    
    E1 = Batt.E0 - Batt.K*Batt.Qc/(Batt.Qc-it_sat)*it_sat ...
        - var*Batt.K*i_filter*Batt.Qc/(Batt.Qc-it_sat) ...
        - (1-var)*Batt.K*i_filter*Batt.Qc/(it_SC+Batt.Qc*Batt.kc) ...
        + i_other ...
        - it_sat*Batt.C;
    
    if E1 > 2*Batt.E0
        E1 = Batt.E0;
    elseif E1 < old_current*Batt.R
        E1 = old_current*Batt.R;
    end
    
    voltage = E1;
    E1 = E1 - current * Batt.R;
    old_current = current;
    current = voltage*Load/(Batt.R+Load);
    
    SOC = 100*(1-it_sat/(Batt.Qc/Batt.lambda));
    if SOC > 100
        SOC = 1;
    elseif SOC < 0
        SOC = 0;
    end
end