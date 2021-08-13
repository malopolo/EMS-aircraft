function [Off1, Off2] = MyCrossOver_Fcn(Par1,Par2,CrossMethod)

switch CrossMethod
    case 1
        Beta1 = rand;
        Beta2 = rand;
        
        Off1 = Beta1*Par1 + (1-Beta1)*Par2;
        Off2 = Beta2*Par1 + (1-Beta2)*Par2;
    case 2
        
    case 3
        
end