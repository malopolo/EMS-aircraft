function [profile, leg,t] = climb(Ts, nbpoints, MinPow, MaxPow, minT)
    u = "climb";
    % power def
    mxp = MaxPow - randi(100);
    % climb
    clb = randi(30)/100;
    F1 = linspace(MinPow,mxp,clb*nbpoints);
    % max
    mx = 1-clb;
    F2 = linspace(mxp,mxp,mx*nbpoints);
    profile = [F1 F2];
    leg = repelem(u,length(profile));
    t = linspace(minT,minT+Ts,length(profile));