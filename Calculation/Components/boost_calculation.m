function [L,C] = boost_calculation(Vin,Vout,fs,DV,P)
    Iout_max = P./Vout;
    mat_ripple = 0.2:0.1:0.4;
    
    L = zeros(length(mat_ripple),length(Vin),length(Iout_max));
    C = zeros(length(mat_ripple),length(Vin),length(Iout_max));
    for j= 1:length(mat_ripple)
        for k = 1:length(Vin)
            for i= 1:length(Iout_max)
                DIL = mat_ripple(j)*Iout_max(i)*Vout/Vin(k);
                L(j,k,i) = Vin(k)*(Vout-Vin(k))/(DIL*fs*Vout);
                C(j,k,i) = Iout_max(i)*(Vout-Vin(k))/(fs*DV*Vout);
            end
        end
        
    end
end
