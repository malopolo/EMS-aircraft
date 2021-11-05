function [gcf] = simple_powertrain(Ts, SimTime, BATTdata,FCdata, power_fc,current_fc,...
        voltage_fc,current_batt,voltage_batt,soc_batt,Pout,Ppv_out,time_vector,...
        fc_power_array,soc)
    
    %% for DP
    Ifc = 0.001;
    Ibatt = 0;
    Pfc = 0;
    tic
    for i=1:1:SimTime/Ts
        
        [BATTdata] = battery_model(Ibatt,BATTdata);
        [FCdata] = fuel_cell_model(Ifc,FCdata);
        
        Pout_required = Pout(i)-Ppv_out;
        if i > 1 && ~mod(i,1/Ts)
            [~,index] = min(abs(soc-BATTdata.SOC));
            Pfc = max(0,min(1100,fc_power_array(index,i*Ts)));
        end
        Pbatt = Pout_required/0.9 - Pfc;
        
        Ifc = Pfc/FCdata.Efc;
        
        % arrays
        voltage_fc(i) = FCdata.Efc;
        current_fc(i) = Ifc;
        power_fc(i) = Ifc*FCdata.Efc;
        
        
        %% batt
        Res_batt = (BATTdata.voltage ^2)/Pbatt-BATTdata.R;
        
        % current
        Ibatt = BATTdata.voltage/(BATTdata.R+Res_batt);
        BATTdata.ouput_voltage = BATTdata.voltage*Res_batt/(BATTdata.R+Res_batt);
        
        % arrays
        voltage_batt(i) = BATTdata.ouput_voltage;
        current_batt(i) = Ibatt;
        soc_batt(i) = BATTdata.SOC;
    end
    
    gcf = global_cost_funciton(power_fc,current_fc,current_batt,soc_batt,time_vector);
end

