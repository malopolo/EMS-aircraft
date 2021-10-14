function y = opti_fcn(x0,lb,ub,Vin,Vdc,Ifc_out,ILmax,Vdc_ref,data,Hp,Pload_est,Ppv_out,k,TsOpti)
    rng default % For reproducibility
%     gs = GlobalSearch('Display','off','XTolerance',1e-3);
    gs = MultiStart('Display','off','XTolerance',1e-3);
    data.Ts = TsOpti;
    options = optimoptions('fmincon','Algorithm','sqp',...
        'Display','off','MaxFunctionEvaluations',500,'MaxIterations',300,...
        'DiffMinChange',10);
    objfcn = @(x)loop_res_fun(x,Vin,Vdc,Ifc_out,ILmax,Vdc_ref,data,Hp,Pload_est-Ppv_out,k);
    problem = createOptimProblem('fmincon','x0',x0,...
        'objective',objfcn,'lb',lb,'ub',ub,'options',options);
%     y = run(gs,problem);
    y = run(gs,problem,200);
end



function f = loop_res_fun(x,Vin,Vdc,Ifc_out,ILmax,Vdc_ref,data,Hp,Pload_est,k)
    %     coder.extrinsic('res_fun');
    Ptot_fc = 0;
    Ptot_fc_out = 0;
    err = 0;
    Iout = Ifc_out;
%     x
%     Pload_est
    for i=1:Hp
        ILmax = x(1) / Vin;
        Vdc_real = data.x_k(2);
        [Vin,Vout,Iout,Pin,Pout,data] = res_fun(Vdc_real,Iout,ILmax,Vdc_ref,data);
        Vdc_real = data.x_k(2);
        Ifc_out = Pout/Vdc_real;
        if data.x_k(1) > ILmax
            Vdc_ref = 100;
        else
            Vdc_ref = 72;
        end
        Ptot_fc = Ptot_fc + Pin;
        Ptot_fc_out = Ptot_fc_out + Pout;
        if (Pload_est(i) - Pout)/0.9 > 850 || (Pload_est(i) - Pout)/0.9 < -150
            err = err + 3000;
        end
        if Pout < (Pload_est(i) - Pout) && k < 0
            err = err + 3000;
        end
%         Pout
    end
%     if (sum(Pload_est) - Ptot_fc_out)/0.9 > Hp*850
%         err = Hp*(sum(Pload_est) - Ptot_fc_out)/0.9;
%     elseif (sum(Pload_est) - Ptot_fc_out)/0.9 < Hp*(-150)
%         err = -Hp*(sum(Pload_est) - Ptot_fc_out)/0.9;
%     end
%     Ptot_fc_out
%     (sum(Pload_est) - Ptot_fc_out)/0.9
    %     f = Hp*data.Ts * (Ptot_fc*(1-x(2)) + x(2)*sum(Pload_est) + err) %
    %     change for SOC(t)
    f = Hp*data.Ts * (Ptot_fc*(1-k) + k*sum(Pload_est) + err);
    
    
    
end


function [Vin,Vout,Iout,Pin,Pout,new_data] = res_fun(Vdc,Ifc_out,ILmax,Vdc_ref,data)
    %% get data
    Ts = data.Ts;
    % converter data
    L = data.L;
    Ca = data.Ca;
    
    % Current regulator
    Kpi = data.Kpi;
    Kii = data.Kii;
    
    % Voltage regulator
    Kpv = data.Kpv;
    Kiv = data.Kiv;
    
    % fuel cell data
    Ncell = data.Ncell;
    eff = data.eff;
    T = data.T;
    Rohm = data.Rohm;
    R_ = data.R_;
    Pstd = data.Pstd;
    nF = data.nF;
    C_act = data.C_act;
    Nfc = data.Nfc;
    lambda = data.lambda;
    l = data.l;
    JM = data.JM;
    Pa = data.Pa;
    Pc = data.Pc;
    coeff = data.coeff;
    
    
    
    % states
    %     x_k=[Iin;Vdc];
    x_k=data.x_k;
    e_pre=data.e_pre;
    e2_pre=data.e2_pre;
    pi_pi=data.pi_pi;
    pi_ii=data.pi_ii;
    E_act=data.E_act;
    old_E_act_bl=data.old_E_act_bl;
    old_E_act_d=data.old_E_act_d;
    old_lim=data.old_lim;
    Efc=data.Efc;
    
    
    %% start the function
    R = Vdc/Ifc_out;
    x_k(2) = Vdc; %%%%%%%%%%%% changed here
    
    
    
    % Vdc_ref = given by EMS
    % ILmax = given by EMS
    
    %     if x_k(1)<0.001
    %         x_k(1) = 0.001;
    %     end
    
    
    %     Vin = Efc - Rohm * x_k(1);
    Vin = Efc;
    if Vin <= 0
        Vin = 60.484318707027604;
    end
    
    
    %% BOOST PART
    % control part voltage:
    e=(Vdc_ref - x_k(2));
    %     e=(Vdc_ref - Vdc_real);
    pi_pi = min(0.5,max(-0.5,pi_pi + Kiv*Ts*e_pre)); % sat:[-0.5; 0.5]
    out_pi_1 = min(0.5,max(-0.5,Kpv*e + pi_pi)); % sat:[-0.5; 0.5]
    
    sub = max(0.01,eff*Vin); % sat:[0.01; Inf]
    %     temp = min(ILmax,max(0,(out_pi_1+x_k(2)/R)*x_k(2)/sub)); % sat:[0; ILmax]
    temp = min(ILmax,max(0,(out_pi_1+x_k(2)*(1/(5e3)+1/R))*x_k(2)/sub)); % sat:[0; ILmax]
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
    Iout_1 = Vout/Rreal;
    Iout = (Iout_1 - Vout/(5e3));
    
    % works well
    Vout = 72;
%     Vout = Vdc;
    x_k(2) = Vout;
    
%     Iout = Vout/R;
    Iout = x_k(1)*eff;
    
    
    Pin = min(2000,max(-100,  Vin*x_k(1))); % sat:[-100; 2000]
    
    Pout = min(2000,max(-500, Vout*Iout));  % sat:[-500; 2000]
    %     Pout = min(2000,max(-500, 0.9*Pin));  % sat:[-500; 2000]
    
    
    
    %% FC PART
    if x_k(1)<0.001
        x_k(1) = 0.001;
    end
    if x_k(1)>100
        x_k(1) = 100;
    end
    Ifc = x_k(1);
    
    J = Ifc/data.A;
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
    old_E_act_bl = E_act_bl;
    E_act = old_lim *E_act_bl;
    old_lim = limit;
    
    old_lim = limit;
    
    Efc = Ncell*(E_Ner + E_ohm + E_con - E_act)-Rohm*x_k(1);
    if Efc <= 0
        Efc = 0;
    end
    %     Vin = Efc;
    Iin = x_k(1);
    
    %% save states + data
    
    data.x_k= x_k;
    data.e_pre =e;
    data.e2_pre = e2;
    data.pi_pi = pi_pi ;
    data.pi_ii = pi_ii ;
    data.E_act = E_act ;
    data.old_E_act_bl = old_E_act_bl ;
    data.old_E_act_d = old_E_act_d;
    data.old_lim = old_lim ;
    data.Efc = Efc;
    
    
    new_data = data;
    
    
    %% compute the new value of limit / E_act / ... based on previous values
end
