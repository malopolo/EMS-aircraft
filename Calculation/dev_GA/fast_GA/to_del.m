Par1 = MutatPop;
Par2 = MutatPop2;
Beta1 = rand;
Beta2 = rand;

Off11 = Beta1*Par1(1:end/2) + (1-Beta1)*Par2(1:end/2);
Off12 = Beta1*Par1(end/2+1:end) + (1-Beta1)*Par2(end/2+1:end);
Off1 = [Off11 Off12];

Off21 = Beta2*Par1(1:end/2) + (1-Beta2)*Par2(1:end/2);
Off22 = Beta2*Par1(end/2+1:end) + (1-Beta2)*Par2(end/2+1:end);
Off2 = [Off21 Off22];
