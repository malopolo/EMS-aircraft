function new_SOC = compute_SOC(Pbatt,SOC, DT)
    % Needs the batt current
    Qn = 15*3600;
    new_SOC = SOC + DT*Ibatt/Qn;
end