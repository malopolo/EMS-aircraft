%% Function to get the cost value of each pop member (each fuzzy set)
function Cost = fast_cost_function(DIfc, mh2, error_power, SOC,Pfc,Ts)
    %% Old design
    %     w = 0.03;
    %
    %     J1 = sum(DIfc.^2);
    %
    %     J2 = sum(mh2);
    %
    %     SOC = SOC/100;
    %     if SOC < 0.5
    %         Jp1 = 0.5-SOC;
    %     elseif SOC > 0.9
    %         Jp1 = SOC - 0.9;
    %     else
    %         Jp1 = 0;
    %     end
    %
    %     Jp2 = mean(error_power);
    %
    %     % Cost return
    %     Cost = J1 + w*J2 + Jp1 + Jp2;
    
    %% New design:
    mSOC = 1/SOC; % min = 0.01
    global x_fc_eff fc_eff
    eff = zeros(1,height(Pfc));
    for i= 1:height(Pfc)
        [~, index] = min(abs(x_fc_eff-Pfc(i)));
        eff(i) = fc_eff(index);
    end
    meff = 1/mean(eff); % min = 0.018 ~~
    
    sT = 1/Ts;
    dPfc = circshift(Pfc,-sT) - Pfc;
    n = sum(dPfc(1:(end-sT))>250|dPfc(1:(end-sT))<-250);
    mdPfc = n/height(Pfc);
    
%     dPfc = diff(Pfc);
%     n = sum(dPfc>250*Ts|dPfc<-250*Ts);
%     mdPfc = n/height(Pfc);
%     
    merrpow = mean(error_power);

    Cost = 10*mSOC + meff + mdPfc + merrpow;
end