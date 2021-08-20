function mh2 = fast_h2_consumption(Ifc,t,type)
    N = 50; % Number of cells
    F = 96485; % Faraday constant
    nf = N/F;
    if type == 1
        temp = nf*Ifc'; % Ifc * N / F
        mh2 = trapz(t,temp);
    end
    if type == 2
        A = 19.6*4.0; % Area
        M = 2.02e-3; % Molar mass
        mh2 = M*N*A*Ifc/(2*F);
    end
end