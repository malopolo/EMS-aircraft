function [f,new_fc_func,new_batt_func,new_h2_func] = one_global_cost_function(a,b,Pfc,Ifc_in,Ibatt_in,...
        SOC,old_fc_func,old_batt_func,old_h2_func,size_sample,current_soc,current_Pfc)
    Ibatt_nom = 2;
    Pfc_nom = 400;
    Q = 15;
    Ebatt_nom = Q*48;
    N = 50;
    F = 96485;
    
    fc_cost = 525;
    batt_cost = 640;
    h2_cost = 2/1000;
    
    [delta_fc,new_fc_func] = dfc(a,b,Pfc_nom,Pfc,old_fc_func,size_sample);
    [delta_bat,new_batt_func] = dbatt(a,b,SOC,Ibatt_in,Ibatt_nom,Q,old_batt_func,size_sample);
    [delta_h2,new_h2_func] = dh2(a,b,N,F,Ifc_in,old_h2_func,size_sample);
    %     efc = fc_cost * Pfc_nom * dfc(t,Pfc_nom,Pfc);
    %     eb = batt_cost * Ebatt_nom * dbatt(t,SOC,Ibatt_in,Ibatt_nom,Q);
    %     eh2 = h2_cost * dh2(t,N,F,Ifc_in);
    efc = fc_cost * delta_fc;
    eb = batt_cost * delta_bat;
    eh2 = h2_cost * delta_h2;

    %     f = efc + eb + eh2;

    f = Pfc_nom*efc/1000 + Ebatt_nom*eb/2500 + eh2;
    
end


% https://fr.mathworks.com/help/matlab/ref/trapz.html
% f(x_n) = 0
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
    out = zeros(1,length(Ibatt));
    for i=1:length(Ibatt)
        if Ibatt(i) >= 0
            out(i) = 1+0.45*Ibatt(i)/Ibatt_nom;
        else
            out(i) = 1+0.55*abs(Ibatt(i))/Ibatt_nom;
        end
    end
    
    
end

function [d,new_h2_func] = dh2(a,b,N,F,Ifc,old_h2_func,size_sample)
    new_h2_func = (N/F).*Ifc;
    d = (b-a)/2/(size_sample)*(new_h2_func + 2*old_h2_func);
end

function [d,new_batt_func] = dbatt(a,b,SOC,Ibatt_in,Ibatt_nom,Qbatt_max,old_batt_func,size_sample)
    new_batt_func = abs(weight_func_1(SOC).*weight_func_2(Ibatt_in,Ibatt_nom).*Ibatt_in);
    d = (b-a)/2/(size_sample)*(new_batt_func + 2*old_batt_func);
    d = d/Qbatt_max/3600;
end

function [d,new_fc_func] = dfc(a,b,Pfc_nom,Pfc,old_fc_func,size_sample)
    %     delta = 0.5e-4;
    delta = 1/2;
    alpha = 4;
    new_fc_func = delta/3600*(1+(alpha/(Pfc_nom^2))*(Pfc-Pfc_nom).^2);
    d = (b-a)/2/(size_sample)*(new_fc_func + 2*old_fc_func);
end