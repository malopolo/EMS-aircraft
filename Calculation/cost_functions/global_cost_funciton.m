function f = global_cost_funciton(Pfc,Ifc_in,Ibatt_in,SOC,t)
    Ibatt_nom = 2;
    Pfc_nom = 400;
    Q = 15;
    Ebatt_nom = Q*48;
    N = 50;
    F = 96485;
    
    fc_cost = 525;
    batt_cost = 640;
    h2_cost = 5.11/1000;
    Pfc_in = Pfc;
    delta_fc = dfc(t,Pfc_nom,Pfc_in);
    delta_bat = dbatt(t,SOC,Ibatt_in,Ibatt_nom,Q);
    delta_h2 = dh2(t,N,F,Ifc_in);
    %     efc = fc_cost * Pfc_nom * dfc(t,Pfc_nom,Pfc_in);
    %     eb = batt_cost * Ebatt_nom * dbatt(t,SOC,Ibatt_in,Ibatt_nom,Q);
    %     eh2 = h2_cost * dh2(t,N,F,Ifc_in);
    efc = fc_cost * delta_fc;
    eb = batt_cost * delta_bat;
    eh2 = h2_cost * delta_h2;
    
%     f = efc + eb + eh2;
%         f = Pfc_nom*efc/1000 + Ebatt_nom*eb/2500 + eh2;
        f = Pfc_nom*efc/1000 + Ebatt_nom*eb/1000 + eh2;
    
    %     pb_inf = find(Pbatt < - 150);
    %     pb_sup = find(Pbatt > 850);
    %     weight_1 = Pbatt(pb_sup)-850;
    %     weight_2 = 150-Pbatt(pb_inf);
    
    %     f = f + length(weight_1)*sum(weight_1) + length(weigth_2)*sum(weigth_2);
    %     f = f + sum(weight_1)/length(weight_1) + sum(weight_2)/length(weight_2);
end

function out = weight_func_1(SOC)
%     out = 1+3.25*(1-SOC(end)/100).^2;
    out = 1+3.25*(1-SOC/100).^2;
end

function out = weight_func_2(Ibatt,Ibatt_nom)
    %     if Ibatt >= 0
    %         out = 1+0.45*Ibatt/Ibatt_nom;
    %     else
    %         out = 1+0.55*abs(Ibatt)/Ibatt_nom;
    %     end
%         if mean(Ibatt) >= 0
%             out = 1+0.45*mean(Ibatt)/Ibatt_nom;
%         else
%             out = 1+0.55*abs(mean(Ibatt))/Ibatt_nom;
%         end

%     out = [];
%     for i=1:length(Ibatt)
%         if Ibatt(i) >= 0
%             outt = 1+0.45*Ibatt(i)/Ibatt_nom;
%         else
%             outt = 1+0.55*abs(Ibatt(i))/Ibatt_nom;
%         end
%         out = [out;outt];
%     end
    if length(Ibatt) > 1
        sss = length(Ibatt);
    else
        sss = height(Ibatt);
    end
    out = zeros(1,sss);
    for i=1:length(Ibatt)
        if Ibatt(i) >= 0
            out(i) = 1+0.45*Ibatt(i)/Ibatt_nom;
        else
            out(i) = 1+0.55*abs(Ibatt(i))/Ibatt_nom;
        end
    end
    

end

function d = dh2(t,N,F,Ifc)
    d = trapz(t,((N/F).*Ifc));
end

function d = dbatt(t,SOC,Ibatt_in,Ibatt_nom,Qbatt_max)
    d = trapz(t,abs(weight_func_1(SOC).*weight_func_2(Ibatt_in,Ibatt_nom).*Ibatt_in))/Qbatt_max/3600;
end

function d = dfc(t,Pfc_nom,Pfc)
    %     delta = 0.5e-4;
    delta = 1/2;
    alpha = 4;
    d = trapz(t,delta/3600*(1+(alpha/(Pfc_nom^2))*(Pfc-Pfc_nom).^2));
end