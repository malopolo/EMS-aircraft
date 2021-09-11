function [profile, leg,t] = cruise(Ts, nbpoints, PrePow, MinCruisePow, minT)
    u = "cruise";
    % power def
    mxp = MinCruisePow + randi(200);

    % little desc
    desc = randi(10)/100;
    F1 = linspace(PrePow,mxp,desc*nbpoints);
    % cruise
    F2 = linspace(mxp,mxp,(1-desc)*nbpoints);
    profile = [F1, F2];
    leg = repelem(u,length(profile));
    t = linspace(minT,minT+Ts,length(profile));