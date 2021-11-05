function [d,iconv,Vconv,controllerData] = boost_regulator(Esource,Rsource,...
        controllerData,Vdc_ref,ILmax,Vdc,idc,iL)
    %% states
    
    e_pre = controllerData.e_pre;
    e2_pre = controllerData.e2_pre;
    pi_pi = controllerData.pi_pi;
    pi_ii = controllerData.pi_ii;
    
    
    %% constant 
    Ts = controllerData.Ts;
    eff = controllerData.eff;
    
    Kpv = controllerData.Kpv;
    Kiv = controllerData.Kiv;
    
    Kpi = controllerData.Kpi;
    Kii = controllerData.Kii;
    
    %% start the function
    Vin = Esource - Rsource * iL;
    
    
    %% BOOST PART
    % voltage control part :
    e=(Vdc_ref - Vdc);
    pi_pi = min(0.5,max(-0.5,pi_pi + Kiv*Ts*e_pre)); % sat:[-0.5; 0.5]
    out_pi_1 = min(0.5,max(-0.5,Kpv*e + pi_pi)); % sat:[-0.5; 0.5]
    
    sub = max(0.01,eff*Vin); % sat:[0.01; Inf]
    temp = min(ILmax,max(0,(out_pi_1+idc)*Vdc/sub)); % sat:[0; ILmax]
    
    
    % current control part :
    e2 = temp - iL;
    pi_ii = min(50,max(-50,pi_ii + Kii*Ts*e2_pre)); % sat:[-50; 50]
    out_pi_2 = min(50,max(-50,Kpi*e2 + pi_ii)); % sat:[-50; 50]

    sub_2 = max(0.01,Vdc); % sat:[0.01; Inf]
    d = min(1,max(0,1-(Vin-out_pi_2)/sub_2)); % sat:[0; 1]
    
    
    %% output
    Vconv = controllerData.old_Vconv;
    iconv = controllerData.old_iconv;
    
    % states
    controllerData.old_Vconv = (1-d)*Vdc;
    controllerData.old_iconv = (1-d)*eff*iL;
    controllerData.e_pre = e_pre;
    controllerData.e2_pre = e2_pre;
    controllerData.pi_pi = pi_pi;
    controllerData.pi_ii = pi_ii;
end

