function [iL,Vc] = pv_boost_left(iL,VL,Vc,Rconv,C,L,Ts)
    Vc = (i1 - iL)*Ts/C+Vc;
    iL = (L*iL+Ts*(Vc-VL))/(Ts*Rconv+L);
end

