function f = local_cost_function(Pfc,SOC,Pbatt,Ts)
    mu = 0.6;
    SOC_min=40; SOC_max=90;
    alpha = 1-2*mu*((SOC-0.5*(SOC_max+SOC_min))/(SOC_max+SOC_min));
    f = (Pfc+alpha.*Pbatt).*Ts;
end

