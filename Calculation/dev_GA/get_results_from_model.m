function data = get_results_from_model(fisi,time,power_profile)
    SOC_ini = 80;
    count = 0;
    mH2 = 0;
    %         conv_eff = 0.9;
    %         power_from_pv = 145/1500;
    %         power_profile = power_profile-power_from_pv;
    %         Dpfc_bound = 0.1*1100;
    %         SOC_bounds = [0.5 0.9];
    %
    %         Pfc_com = zeros(1,length(time));
    %
    %         for i = 1:length(time)
    %             % power_profile is put between 0 and 1
    %             % SOC as well
    %             % eval fis with power_profile and current SOC
    %             Pfc_com(i) = evalfis(fisi,[power_profile(i) SOC]);
    %             % get new SOC
    %             Pbatt = ...;
    %             SOC = compute_SOC(Pbatt,SOC);
    %             % check if conditions have been respected (boundaries)
    %             if i == 1
    %                 DPfc = Pfc_com(i);
    %             else
    %                 DPfc = Pfc_com(i) - Pfc_com(i-1);
    %             end
    %             if DPfc > Dpfc_bound || DPfc < -Dpfc_bound
    %                 count = count+1;
    %             end
    %             if SOC < SOC_bounds(1) || SOC > SOC_bounds(2)
    %                 count = count+1;
    %             end
    %
    %             % Need Ifc
    %             mH2 = mH2 + h2_consumption(Ifc);
    %             % if not just add a weight ratio to the cost of each param
    %
    %         end
    Ifc = 0;
    
    % compute the hydrogen consumption
    data = h2_consumption(Ifc,t,1);
    % return the value of currents / SOC / consumption
    
end