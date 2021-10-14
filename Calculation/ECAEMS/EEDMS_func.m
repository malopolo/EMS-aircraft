function [Pfc, Pbatt,output] = EEDMS_func(SOC,Pout_required,old_Pfc,Ts)
    Pbatt_min=-200; Pbatt_max=1000;
    SOC_min=40; SOC_max=90;
%     if Pout_required > 0 || SOC < SOC_min
%         Pfc_min=150;
%     else
%         Pfc_min = 0;
%     end
    Pfc_min = 0;
    Pfc_max=1100;
    deltaPfc = 100; % sqrt(deltaPfc/Ts)+old_Pfc
    
    %define Matrix A
%     A = [1,0,0];
    A = [1,0,0;-1,0,0];
    
    %define Matrix b
%     b = [(-deltaPfc*Ts+old_Pfc);(-deltaPfc*Ts-old_Pfc)];
    b = [(-deltaPfc+old_Pfc);(-deltaPfc-old_Pfc)];
    
    %define Matrix Aeq
    Aeq=[0 1 0;1 0 1];
    
    %define Matrix beq
    mu=0.6;
    beq=[1-2*mu*((SOC-0.5*(SOC_max+SOC_min))/(SOC_max+SOC_min)); Pout_required/0.9];
    
    %define boundary conditions
    lb=[Pfc_min, 0, Pbatt_min];
    ub=[Pfc_max, 100, Pbatt_max];
    
    %define initial conditions
    x0=[1000, 0.1, 500];
    
    options = optimoptions('fmincon','Algorithm','sqp',...
        'Display','off','MaxFunctionEvaluations',500,'MaxIterations',100,...
        'StepTolerance',1e-4,'ConstraintTolerance',1e-4);
%     [y,fval] = fmincon(@(x)cost_func(x,Vfc,Ifc_in,Ibatt_in,SOC),x0,A,b,Aeq,beq,lb,ub,[],options);
    [y] = fmincon(@(x)cost_func_2(x,Ts),x0,A,b,Aeq,beq,lb,ub,[],options);
    
    Pfc = y(1);
    Pbatt = Pout_required - Pfc;

end
function f = cost_func_2(x,Ts)
   f = (x(1) + x(2)*x(3))*Ts; 
end

% function f = cost_func(x,Vfc,Ifc_in,Ibatt_in,SOC,Ts)
%     DT=Ts;
%     do = 0.5e-4;
%     alpha = 4;
%     FCcost = 525;
%     Hcost = 2;
%     BATcost = 640;
%     Pfc_nom = 400;
%     Ibatt_nom = 2;
%     Q = 15;
%     dfc = (do/3600)*(1+alpha/(Pfc_nom^2)*(Vfc*Ifc_in-Pfc_nom)^2);
%     dbat = (1/Q)*abs(weight_func_1(SOC)*weight_func_2(Ibatt_in)*Ibatt_in);
%     mfc_deg = dfc * FCcost / Hcost;
%     mbat_deg = dbat * BATcost / Hcost;
%     f = (x(1)+x(2)*x(3)+ mfc_deg + mbat_deg)*DT;
%     
%     fc_cost = 
%     batt_cost = 
%     h2_cost = 
%     
%     efc = fc_cost * Pfc_nom * dfc(old_dfc,Ts,Pfc_nom,Vfc*Ifc_in);
%     eb = batt_cost * Ebatt_nom * dbatt(old_dbatt,Ts,SOC,Ibatt_in,Ibatt_nom,Qbatt_max);
%     eh2 = h2_cost * dh2(old_dh2,Ts,Ifc_in);
%     
%     f = efc + eb + eh2;
% end
% 
% function out = weight_func_1(SOC)
%     out = 1+3.25*(1-SOC)^2;
% end
% 
% function out = weight_func_2(Ibatt,Ibatt_nom)
%     if Ibatt >= 0
%         out = 1+0.45*Ibatt/Ibatt_nom;
%     else
%         out = 1+0.55*abs(Ibatt)/Ibatt_nom;
%     end
% end
% 
% function d = dh2(old_dh2,Ts,N,F,Ifc)
%    d = old_dh2 + Ts*(N/F*Ifc); 
% end
% 
% function d = dbatt(old_dbatt,Ts,SOC,Ibatt_in,Ibatt_nom,Qbatt_max)
%     d = old_dbatt + Ts*(abs(weight_func_1(SOC)*weight_func_2(Ibatt_in,Ibatt_nom)*Ibatt_in)/Qbatt_max);
% end
% 
% function d = dfc(old_dfc,Ts,Pfc_nom,Pfc)
%     delta = 0.5e-4;
%     alpha = 4;
%     d = old_dfc + Ts*(delta/3600*(1+(alpha/(Pfc_nom^2))*(Pfc-Pfc_nom).^2));
% end
% 
% 
