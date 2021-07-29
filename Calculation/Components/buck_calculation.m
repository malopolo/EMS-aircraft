function [L,C] = buck_calculation(Vin,Vout,fs,DV,P)
    mat_ripple = 0.2:0.1:0.4;
    
    L = zeros(length(mat_ripple),length(Vout),length(P));
    C = zeros(length(mat_ripple),length(Vout),length(P));
    for j= 1:length(mat_ripple)
        for k = 1:length(Vout)
            for i= 1:length(P)
                Iout_max = P(i)/Vout(k);
                DIL = mat_ripple(j)*Iout_max;
                L(j,k,i) = Vout(k)*(Vin-Vout(k))/(DIL*fs*Vin);
                C(j,k,i) = DIL/(8*fs*DV);
            end
        end
    end
end
