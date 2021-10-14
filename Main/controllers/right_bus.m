function [Vdc,Idc,Pdc] = right_bus(ifc,ibatt,ipv,Esc,Rsc,Rconv_fc,Cconv_fc,Rconv_batt,Cconv_batt,Rconv_pv,Cconv_pv,Rout,Vdc)
    Rbis = 1/(1/Rconv_fc+1/Rconv_batt+1/Rconv_pv+1/Rsc+1/Rout);
    
    alpha = dT/(Rbis*(Cconv_fc+Cconv_batt+Cconv_pv)+dT);
    
    Vdc = (ifc+ibatt+ipv+Esc/Rsc)*Rbis*alpha + Vdc * (1-alpha);
    Idc = Vdc/Rout;
    Pdc = Idc*Vdc;
end

