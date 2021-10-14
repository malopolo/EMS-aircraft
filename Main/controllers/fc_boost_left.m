function [iL] = fc_boost_left(Efc, VL, iL,Rconv,L,Ts)
    iL = (L*iL + Ts*(Efc-VL))/(Ts*Rconv+L);
end

