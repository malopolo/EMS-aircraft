function [d,iconv,Vconv,controllerData] = buck_regulator(Esource,Rsource,controllerData,Vbatt_ref,Vbatt,Ibatt,Ibatt_ref,iL)
    %% states
    e_pre = controllerData.e_pre;
    e2_pre = controllerData.e2_pre;
    pi_pi = controllerData.pi_pi;
    pi_ii = controllerData.pi_ii;
    
    
    %% constant 
    Kpv = controllerData.Kpv;
    Kiv = controllerData.Kiv;
    
    Kpi = controllerData.Kpi;
    Kii = controllerData.Kii;
    
    %% start the function
    Vin = Esource - Rsource * iL;
    
    
    %% BOOST PART
    % voltage control part :
    e=(Vbatt_ref - Vbatt);
    pi_pi = min(1,max(-1,pi_pi + Kiv*Ts*e_pre)); % sat:[-1; 1]
    out_pi_1 = min(1,max(-1,Kpv*e + pi_pi)); % sat:[-1; 1]
    
    temp = min(Ibatt_ref,max(0,out_pi_1-Ibatt)); % sat:[0; Ibatt_ref]
    
    
    % current control part :
    e2 = temp + iL;
    pi_ii = min(1,max(-1,pi_ii + Kii*Ts*e2_pre)); % sat:[-1; 1]
    out_pi_2 = min(1,max(-1,Kpi*e2 + pi_ii)); % sat:[-1; 1]

    sub_2 = max(0.01,Vdc); % sat:[0.01; Inf]
    d = min(1,max(0,(Vin+out_pi_2)/sub_2)); % sat:[0; 1]
    
    
    %% output
    Vconv = controllerData.old_Vconv;
    iconv = controllerData.old_iconv;
    
    % states
    controllerData.old_Vconv = d*Vdc;
    controllerData.old_iconv = d/controllerData.conv_eff*iL;
    controllerData.e_pre = e_pre;
    controllerData.e2_pre = e2_pre;
    controllerData.pi_pi = pi_pi;
    controllerData.pi_ii = pi_ii;
end

