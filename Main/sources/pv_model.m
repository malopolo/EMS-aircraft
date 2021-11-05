% https://hal.archives-ouvertes.fr/hal-01351308/document
% PV -> autre -> Matlab sim model
% PV -> autre -> PV panel
% PV -> autre -> PV module
% https://environmentalsystemsresearch.springeropen.com/articles/10.1186/s40068-015-0047-9
% https://iopscience.iop.org/article/10.1088/1757-899X/114/1/012137/pdf
function [ID,PVdata] = pv_model(I_PV,V_PV,PVdata)
    %% Constants    
    a = PVdata.a;
    Tc_STC = 25 + 273.15;
    G_STC = 1000;
    TempCell_K = PVdata.TempCell_C+273.15;
    k = PVdata.k;
    k_ = PVdata.k_;
    q = PVdata.q;
    Eg_ref = PVdata.Eg_ref;
    
    %% Functions
    Vt = k/q*TempCell_K;
    IPH = ((TempCell_K-Tc_STC)*PVdata.alpha+PVdata.IPH_STC)*PVdata.para_string*PVdata.Irradiance/G_STC;
    Ish = (V_PV + I_PV*PVdata.Rs)/PVdata.Rp;
    Irs = PVdata.IPH_STC/(exp(q*PVdata.Voc/(PVdata.Ncell*k*PVdata.a*TempCell_K))-1);
    Is = Irs * (TempCell_K/Tc_STC)^3*exp((Eg_ref/(k_*a))*(1/TempCell_K - 1/Tc_STC));
    Id = PVdata.para_string * Is * (exp((V_PV/PVdata.serie_string+I_PV*PVdata.Rs/PVdata.para_string)/(PVdata.a*Vt*PVdata.Ncell))-1);
    
    %% Output
    ID = IPH * PVdata.para_string - Ish - Id;
end

