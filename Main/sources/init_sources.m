function [BATTdata,FCdata,PVdata,SCdata] = init_sources(Ts)
    %     BatteryParam(48 = ;15 = ;15 = ;36 = ;55.8714 = ;6.5217 = ;0.032 = ;13.5652 = ;[51.8585 0.736957] = ;gcb = ;0)
    %% BATTdataery FCdata initialization
    BATTdata.Batt_Tr = 20;
    BATTdata.Ts = Ts;
    BATTdata.E0 = 52.049232061865339;
    BATTdata.R = 0.032;
    BATTdata.Qmax = 15.51;
    BATTdata.Qc = 15.51;
    BATTdata.K = 0.023973807375425;
    BATTdata.kc = 0.1;
    BATTdata.kcsat = 0.1;
    BATTdata.A = 4.030846226964528;
    BATTdata.B = 4.070796460176990;
    BATTdata.C = 0;
    BATTdata.lambda = 1.034;
    BATTdata.current = 10;
    BATTdata.B_ = -exp(-Ts/(BATTdata.Batt_Tr/3));
    BATTdata.A_ = 1+BATTdata.B;
    
    BATTdata.voltage = 0;
    BATTdata.ouput_voltage = 0;
    BATTdata.SOC = 80;
    
    
    % states
    BATTdata.old_i_filter = 0;
    BATTdata.old_old_var = 0;
    BATTdata.old_var = 1;
    BATTdata.old_res = (1-BATTdata.SOC/100)*BATTdata.Qc*(1/BATTdata.lambda)*3600;
    BATTdata.old_it_sat = 0;
    BATTdata.old_current = 0;
    BATTdata.init = 1;
    
    
    %% FC FCdata initialization
    % variables / states
    FCdata.x_k= [0;0];
    FCdata.e_pre = 0;
    FCdata.e2_pre = 0;
    FCdata.pi_pi = 0;
    FCdata.pi_ii = 0;
    FCdata.E_act = 0;
    FCdata.old_E_act_bl = 0;
    FCdata.old_E_act_d = 0;
    FCdata.old_lim = 1;
    FCdata.Efc = 0;
    
    % static FCdata
    FCdata.Ts = Ts;
    % converter FCdata
    FCdata.L = 2e-3;
    FCdata.Ca = 1e-4;
    FCdata.Cdc = 1;
    
    % regulators FCdata
    FCdata.Ct = FCdata.Ca + FCdata.Cdc;
    FCdata.T_v_bst = 1;
    FCdata.T_i_bst = 1;
    damp = 0.707;
    % Current regulator
    zetai=damp;
    thau_si=FCdata.T_i_bst/10;
    zetawni=(-log(0.05*sqrt(1-zetai^2)))/thau_si;
    FCdata.Kpi=2*FCdata.L*zetawni / 1000;
    wni=zetawni/zetai;
    FCdata.Kii=FCdata.L*wni^2 / 1000;
    
    % Voltage regulator
    zetav=damp;
    thau_sv=FCdata.T_v_bst; %response time
    zetawnv=(-log(0.05*sqrt(1-zetav^2)))/thau_sv;
    FCdata.Kpv=2*FCdata.Ct*zetawnv;
    wnv=zetawnv/zetav;
    FCdata.Kiv=FCdata.Ct*wnv^2;
    clear wnv zetawnv thau_sv zetav wni zetawni thau_si zetai damp
    
    % fuel cell FCdata
    FCdata.eff = 0.9;
    FCdata.T = 303.15;
    FCdata.Rohm = 0.061871;
    FCdata.R_ = 8.3145;
    FCdata.Pstd = 101325;
    FCdata.nF = 2*96485;
    FCdata.C_act = 2;
    FCdata.A = 19.6*4.0;
    FCdata.Nfc = 50;
    FCdata.lambda = 14;
    FCdata.l = 21e-4 * 10^-2;
    FCdata.JM = 45/FCdata.A;
    FCdata.Pa = 1.45;
    FCdata.Pc = 1;
    FCdata.coeff = 1.05;
    
    
    %% PV PVdata initialization
    PVdata.Ts = Ts;
    PVdata.TempCell_C = 25;
    PVdata.Irradiance = 800;
    PVdata.Ncell = 72;
    PVdata.Voc = 44.5;
    PVdata.Isc = 5.54;
    PVdata.Vmp = 37.2;
    PVdata.Imp = 4.97;
    PVdata.alpha_Isc_pc = -0.017;
    PVdata.alpha = PVdata.alpha_Isc_pc*PVdata.Isc/100;
    PVdata.beta = 0;
    PVdata.IPH_STC = PVdata.Isc;
    PVdata.I_0 = 2.39143e-10;
    PVdata.a = 0.96618;
    PVdata.n = PVdata.a;
    PVdata.Rp = 113.762;
    PVdata.Rs = 0.32122;
    PVdata.para_string = 1;
    PVdata.serie_string = 1;
    PVdata.k = 1.3806e-23; % Boltzman constant (J/K)
    PVdata.k_ = 8.617333262145e-5; % Boltzman constant (eV/K)
    PVdata.q = 1.602e-19; % Elementary charge on an electron (C)
    PVdata.Eg0 = 1.121;
    PVdata.Eg_ref = PVdata.Eg0*PVdata.q; % Band gap for silicon (eV)
    
    
    %% SC SCdata initialization
    SCdata.Ts = Ts;
    SCdata.C = 1;
    SCdata.Rdc = 150e-3;
    SCdata.Vrated = 72;
    SCdata.Ns = 50;
    SCdata.Np = 1;
    SCdata.Vinit = 72;
    SCdata.T = 25;
    SCdata.Nc = 1;
    SCdata.r = 1e-9;
    SCdata.epsilon = 6.0208e-10;
    SCdata.Ich = 10;
    SCdata.Ioc = 10;
    SCdata.Vstern = [0.161 2.7 7.8];
    SCdata.Vself = [48 47.8 47.06 44.65];
    SCdata.Qinit = 63.43;
    SCdata.alpha = 0.996594853675680;
    SCdata.beta = 2.569260646723565;
    SCdata.lambda = 0.241055190586378;
    SCdata.a1 = -0.130000000000000;
    SCdata.a2 = 0.008222222222222;
    SCdata.a3 = 0.002677777777778;
    
    % states
    SCdata.deltaI = 0;
    SCdata.old_input_deltaI = 0;
    SCdata.old_self_dis_part = 0;
    SCdata.old_input_self_dis_part = 0;
    SCdata.old_Isc = 0;
    SCdata.Iself_dis = 0;
    SCdata.old_input_Iself_dis = 0;
    SCdata.old_Iself_dis = 0;
end

