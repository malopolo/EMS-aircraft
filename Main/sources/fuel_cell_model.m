function [old_data] = fuel_cell_model(Ifc,old_data)
    %     https://link.springer.com/article/10.1007/s40565-016-0196-5
    %     Modeling and Simulation of a Proton Exchange Membrane Fuel Cell Alongside a Waste Heat Recovery System Based on the Organic Rankine Cycle in MATLAB/SIMULINK Environment
    %     MATHEMATICAL MODELLING FOR PROTON EXCHANGE MEMBRANE FUEL CELL (PEMFC)
    %     https://www.scirp.org/pdf/epe_2020112310053180.pdf#page=17&zoom=100,72,604
    %     H-Series Fuel Cell Stacks
    % https://ieeexplore.ieee.org/document/6243436
    % https://www.scirp.org/journal/paperinformation.aspx?paperid=84317
    format long
    %% States
    E_act=old_data.E_act;
    old_E_act_bl=old_data.old_E_act_bl;
    old_E_act_d=old_data.old_E_act_d;
    old_lim=old_data.old_lim;
%     Efc=old_data.Efc;
    
    %% constants:
    Ts = old_data.Ts;
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
    
    Ifc = min(Inf,max(0.001,Ifc));
    J = Ifc/old_data.A;
    Tc = T-273.15;
    
    PH2Osat = 10^(-2.18+2.95e-2*Tc-9.18e-5*Tc^2+1.44e-7*Tc^3);
    

    P_H2 = 0.5*PH2Osat*(exp(-(1.635*J/T^1.334))*(Pa/PH2Osat)-1);
    P_O2 = PH2Osat*(exp(-(4.192*J/T^1.334))*(Pc/PH2Osat)-1);
    
    
    %% Saturation at start
    if -1.87e-4*log(Ifc) > 0
        k = 0;
    else
        if -1.87e-4*log(Ifc) < -1.2
            k = -1.2;
        else
            k = -1.87e-4*log(Ifc);
        end
    end
    %% Nernst Voltage
    E_Ner = 1.229 + (T-298.15) * (-0.85e-3) + T*R_/nF * log(P_H2*P_O2^0.5);
    
    %% Activation loss
    % Pressure not in Pa ?
    CO2 = (P_O2/(5.08e6))*exp(498/T);
    %     CH2 = (P_H2/(1.09e6))*exp(-77/T);
    %     E_act_steady=-0.9514 + T * (2.86e-3+2.1e-4*log(200)+4.3e-5*log(CH2)+7.4e-5*log(CO2)+k);
    E_act_steady = -0.9514 + 3.12e-3*T + 7.4e-5*T*log(CO2) -1.87e-4*T*log(Ifc);
    
    %% Ohmic loss
    %     E_ohm = - Ifc*(l/((lambda*5.139e-3-3.26e-3)*exp(1268*(1/303-1/T))));
    R_ohm = (l/((lambda*5.139e-3-3.26e-3)*exp(1268*(1/303-1/T))));
    E_ohm = -Ifc*l/old_data.A*(181.6*(1+0.03*(Ifc/old_data.A))+0.062*(T/303)^2*(Ifc/old_data.A)^2.5)/((lambda-0.634-3*(Ifc/old_data.A))*exp(4.18*((T-303)/T)));
    
    %% Concentration loss
    %     if T>= 312.15
    %         E_con = (1.1e-4-1.2e-6*(T-273.15))*exp(8*Ifc/40);
    %     else
    %         E_con = (3.3e-3-8.2e-5*(T-273.15))*exp(8*Ifc/40);
    %     end
    
    %     E_con = 3*R_*T/(2*nF)*log(1-J/JM)-1.5607*R_*T/(2*nF);
    if J/JM < 1
        E_con = 3*R_*T/(2*nF)*log(1-J/JM)-1.5607*R_*T/(2*nF);
    else
        %         E_con = -abs(3*R_*T/(2*nF)*log(complex(1-J/(JM-0.001)))-1.5607*R_*T/(2*nF));
        E_con = 3*R_*T/(2*nF)*log(J/JM)-1.5607*R_*T/(2*nF);
    end
    
    %% with coefficient
    E_con = coeff * E_con;
    E_act_steady = coeff * E_act_steady;
    E_ohm = coeff * E_ohm;
    E_Ner = coeff * E_Ner;
    
    
    %% activation dynamic loss:
    below = -E_act_steady-E_con;
    E_act_d = (Ifc/C_act)*(1-E_act/below);
    %     E_act_d = 0;

    
    %% Fuel utilization
    U_H2 = 60000*Ifc*R_*T*Nfc/(nF*1.16*1*0.9995*Pstd);
    
    %% Air utilization
    U_O2 = 60000*Ifc*R_*T*Nfc/(2*nF*0.0181*1*0.21*Pstd);
    limit = 1;
%     if J/JM >= 1
%         E_con = 0;
%         E_act_steady = 0;
%         E_ohm = 0;
%         E_act_d = 0;
%         E_Ner = -35*Ifc;
%         if E_Ner <= 0
%             E_Ner = 0;
%         end
%         limit = 0;
%     end
    
        
    %% Fuel cell voltage
%     E_act_bl =  (old_E_act_bl + Ts*old_E_act_d);
    E_act_bl =  (old_E_act_bl + Ts*E_act_d);
    old_E_act_d = E_act_d;
    E_act = old_lim *E_act_bl;
    old_lim = limit;
    old_E_act_bl = E_act_bl;
    
%     E_Ner
%     E_ohm
%     E_con
%     E_act
    Efc = abs(Nfc*(E_Ner + E_ohm + E_con - E_act));
%     if Efc <= 0
%         Efc = 0;
%     end
    
    old_data.E_act = E_act ;
    old_data.old_E_act_bl = old_E_act_bl ;
    old_data.old_E_act_d = old_E_act_d;
    old_data.old_lim = old_lim ;
    old_data.Efc = Efc;
end

