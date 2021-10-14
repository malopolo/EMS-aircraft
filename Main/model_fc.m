function [Pin,Pout,old_data] = model_fc(Vdc, Ifc_out, Vdc_ref, ILmax, old_data)
    %MODEL_FC Summary of this function goes here
    %   Detailed explanation goes here
    
    %% static data
    Ts = old_data.Ts;
    % converter data
    L = old_data.L;
    Ca = old_data.Ca;
    
    % Current regulator
    Kpi = old_data.Kpi;
    Kii = old_data.Kii;
    
    % Voltage regulator
    Kpv = old_data.Kpv;
    Kiv = old_data.Kiv;
    
    % fuel cell data
    Ncell = old_data.Ncell;
    eff = old_data.eff;
    T = old_data.T;
    Rohm = old_data.Rohm;
    R_ = old_data.R_;
    Pstd = old_data.Pstd;
    nF = old_data.nF;
    C_act = old_data.C_act;
    Nfc = old_data.Nfc;
    lambda = old_data.lambda;
    l = old_data.l;
    JM = old_data.JM;
    Pa = old_data.Pa;
    Pc = old_data.Pc;
    coeff = old_data.coeff;
    

    
    %% states
    x_k=old_data.x_k;
    e_pre=old_data.e_pre;
    e2_pre=old_data.e2_pre;
    pi_pi=old_data.pi_pi;
    pi_ii=old_data.pi_ii;
    E_act=old_data.E_act;
    old_E_act_bl=old_data.old_E_act_bl;
    old_E_act_d=old_data.old_E_act_d;
    old_lim=old_data.old_lim;
    Efc=old_data.Efc;
    
    
    %% start the function
    R = Vdc/Ifc_out;
    
    % Vdc_ref = given by EMS
    % ILmax = given by EMS
    
%     if x_k(1)<0.001
%         x_k(1) = 0.001;
%     end
    
    Vin = Efc - Rohm * x_k(1);
    
    
    %% BOOST PART
    % control part voltage:
    e=(Vdc_ref - x_k(2));
    %     e=(Vdc_ref - Vdc_real);
    pi_pi = min(0.5,max(-0.5,pi_pi + Kiv*Ts*e_pre)); % sat:[-0.5; 0.5]
    out_pi_1 = min(0.5,max(-0.5,Kpv*e + pi_pi)); % sat:[-0.5; 0.5]
    
    sub = max(0.01,eff*Vin); % sat:[0.01; Inf]
    temp = min(ILmax,max(0,(out_pi_1+x_k(2)/R)*x_k(2)/sub)); % sat:[0; ILmax]
    %     temp = (out_pi_1+Vdc_real/R)*Vdc_real/sub;
    
    
    % control part current
    e2 = temp - x_k(1);
    %     e2 = temp - iL;
    pi_ii = min(50,max(-50,pi_ii + Kii*Ts*e2_pre)); % sat:[-50; 50]
    out_pi_2 = min(50,max(-50,Kpi*e2 + pi_ii)); % sat:[-50; 50]

    sub_2 = max(0.01,x_k(2)); % sat:[0.01; Inf]
    %     sub_2 = max(0.01,Vdc_real);
    d = min(1,max(0,1-(Vin-out_pi_2)/sub_2)); % sat:[0; 1]
    
    
    
    A = [-0.002/L -(1-d)/L;(1-d)*eff/Ca*R/(R+0.002) -1/((R+0.002)*Ca)];
    B = [1/L; 0];
    C = [1 0];
    D = 0;
    
    % continuous to discrete (exact)
    %     Ai = expm(Ts*A);
    %     Bi = inv(A)*(Ai - eye(2))*B;
    
    % approx : (https://en.wikipedia.org/wiki/Discretization)
    Ai = eye(2)+A*Ts;
    Bi = Ts*B;
    
    x_k1 = Ai*x_k+Bi*Vin;
    y = C*x_k;

    
    %% Outputs
    x_k = x_k1;
    %     x_k(2) = Vdc_real;
    %     x_k(1) = iL;
%     if x_k(1) < 0.001
%         x_k(1) = 0.001;
%     end
    
    Vout = x_k(2);
    Rreal = R+0.002;
    iout_1 = Vout/Rreal;
    iout = (iout_1 - Vout/(5e3));
    
    % works well
    Vout = 72;
    x_k(2) = Vout;
    iout = Vout/R;
    
    
    Pin = min(2000,max(-100,  Vin*x_k(1))); % sat:[-100; 2000]
    
%     Pout = min(2000,max(-500, Vout*iout));  % sat:[-500; 2000]
    Pout = min(2000,max(-500, 0.9*Pin));  % sat:[-500; 2000]
    
    
    
    %% FC PART
    Ifc = x_k(1);
    if Ifc<0.001
        Ifc = 0.001;
    end
    
    J = Ifc/old_data.A;
    Tc = T-273.15;
    
    PH2Osat = 10^(-2.18+2.95e-2*Tc-9.18e-5*Tc^2+1.44e-7*Tc^3);
    
    P_H2 = 0.5*PH2Osat*(exp(-(1.635*J/T^1.334))*(Pa/PH2Osat)-1);
    P_O2 = PH2Osat*(exp(-(4.192*J/T^1.334))*(Pc/PH2Osat)-1);
    
    
    % Saturation at start
    if -1.87e-4*log(Ifc) > 0
        k = 0;
    else
        if -1.87e-4*log(Ifc) < -1.2
            k = -1.2;
        else
            k = -1.87e-4*log(Ifc);
        end
    end
    
    % Nernst Voltage
    E_Ner = 1.229 + (T-298.15) * (-0.85e-3) + T*R_/nF * log(P_H2*P_O2^0.5);
    
    % Activation loss
    % Pressure not in Pa ?
    CO2 = (P_O2/(5.08e6))*exp(498/T);
    CH2 = (P_H2/(1.09e6))*exp(-77/T);
    E_act_steady=-0.9514 + T * (2.86e-3+2e-4*log(200)+4.3e-5*log(CH2)+7.4e-5*log(CO2)+k);
    %     E_act_steady = -0.9514 + 3.12e-3*T + 7.4e-5*T*log(CO2) -1.87e-4*T*log(Ifc);
    
    % Ohmic loss
    E_ohm = - Ifc*(l/((lambda*5.139e-3-3.26e-3)*exp(1268*(1/303-1/T))));
    R_ohm = (l/((lambda*5.139e-3-3.26e-3)*exp(1268*(1/303-1/T))));
    
    % Concentration loss
    %     if T>= 312.15
    %         E_con = (1.1e-4-1.2e-6*(T-273.15))*exp(8*Ifc/40);
    %     else
    %         E_con = (3.3e-3-8.2e-5*(T-273.15))*exp(8*Ifc/40);
    %     end
    
    if J/JM < 1
        E_con = 3*R_*T/(2*nF)*log(1-J/JM)-1.5607*R_*T/(2*nF);
    else
        %         E_con = -abs(3*R*T/(2*nF)*log(complex(1-J/(JM-0.001)))-1.5607*R*T/(2*nF));
        E_con = 3*R_*T/(2*nF)*log(J/JM)-1.5607*R_*T/(2*nF);
    end
    
    % with coefficient
    E_con = coeff * E_con;
    E_act_steady = coeff * E_act_steady;
    E_ohm = coeff * E_ohm;
    E_Ner = coeff * E_Ner;
    
    
    % activation dynamic loss:
    below = -E_act_steady-E_con;
    E_act_d = (Ifc/C_act)*(1-E_act/below);
    
    % Fuel utilization
    U_H2 = 60000*Ifc*R_*T*Nfc/(nF*1.16*1*0.9995*Pstd);
    
    % Air utilization
    U_O2 = 60000*Ifc*R_*T*Nfc/(2*nF*0.0181*1*0.21*Pstd);
    limit = 1;
    if J/JM >= 1
        E_con = 0;
        E_act_steady = 0;
        E_ohm = 0;
        E_act_d = 0;
        E_Ner = -35*Ifc;
        if E_Ner <= 0
            E_Ner = 0;
        end
        limit = 0;
    end
    
    
    % Efc
    
    E_act_bl =  (old_E_act_bl + Ts*old_E_act_d);
    old_E_act_d = E_act_d;
    E_act = old_lim *E_act_bl;
    
    old_lim = limit;
    
    Efc = Ncell*(E_Ner + E_ohm + E_con - E_act)-Rohm*x_k(1);
    if Efc <= 0
        Efc = 0;
    end
    
    
    %% save states
    old_data.x_k= x_k;
    old_data.e_pre =e;
    old_data.e2_pre = e2;
    old_data.pi_pi = pi_pi ;
    old_data.pi_ii = pi_ii ;
    old_data.E_act = E_act ;
    old_data.old_E_act_bl = old_E_act_bl ;
    old_data.old_E_act_d = old_E_act_d;
    old_data.old_lim = old_lim ;
    old_data.Efc = Efc;
end

