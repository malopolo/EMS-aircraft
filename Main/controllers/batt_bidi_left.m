function [iL,Vc] = batt_bidi_left(iL,VL,Vc,Ebatt,Rbatt,Rconv,L,C,Ts)
    iL = (L*iL+dT*(Vc-VL))/L;
    Vc = (C*Vc-Ebatt*Ts/(Rbatt+Rconv)+iL*Ts)/(C-Ts/(Rbatt+Rconv));
end

