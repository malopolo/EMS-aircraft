function [FCdata,SCdata,PVdata,BATTdata,ifc,ibatt,ipv,Esc,Vdc,Pdc] = ...
        powertrain_MPC(BATTdata,FCdata,PVdata,SCdata,...
        ifc,ibatt,ipv,Esc,Vdc,Rout,iconv)
    
%     [BATTdata,FCdata,PVdata,SCdata] = init_sources(Ts,SOC_init);
    
    
    %% begining
    % First right bus computation
    [Vdc,Idc,Pdc] = right_bus(Ts,ifc,ibatt,ipv,Esc,...
    SCdata.Rdc,FCdata.RRp,FCdata.Ca,BATTdata.CR,PVdata.RRp,PVdata.Ca,Rout,Vdc);
    
    % regulators computation
    [d,iconv_fc,Vconv_fc,controllerData] = boost_regulator(Esource,Rsource,...
        controllerData,Vdc_ref,ILmax,Vdc,iconv_fc,iL);
    
    [d,iconv_pv,Vconv_pv,controllerData] = pv_boost_regulator(Esource,Rsource,...
        controllerData,Vdc_ref,ILmax,Vdc,iconv_pv,iL);
    
    [d,iconv_batt,Vconv_batt,controllerData] = buck_regulator(Esource,Rsource,...
        controllerData,Vbatt_ref,Vbatt,Ibatt,Ibatt_ref,iL);
    
    
    %% Left converters computation
    [iL,Vc] = pv_boost_left(iL,VL,Vc,Rconv,C,L,Ts);
    
    [iL] = fc_boost_left(Efc, VL, iL,Rconv,L,Ts);
    
    [iL,Vc] = batt_bidi_left(iL,VL,Vc,Ebatt,Rbatt,Rconv,L,C,Ts);
    
    
    %% model of sources
    [Esc,SCdata] = sc_model(Isc,SCdata);
    
    [FCdata] = fuel_cell_model(Ifc,FCdata);
    
    [BATTdata] = battery_model(current,BATTdata);
    
    [ID,PVdata] = pv_model(I_PV,V_PV,PVdata);
end

