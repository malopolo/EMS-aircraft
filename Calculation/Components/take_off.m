function [profile, leg,t] = take_off(Ts, nbpoints, MaxPow, minT)
    u = "takeoff";
    %stationary
    stat = 0.1+randi(30)/100;
    F1 = linspace(0,0,stat*nbpoints);
    % take off
    takeoff = 0.5-stat;
    mxp = MaxPow - randi(100);
    F2 = linspace(0,mxp,takeoff*nbpoints);
    takeoff_cst = 1-takeoff;
    F3 = linspace(mxp,mxp,takeoff_cst*nbpoints);
    profile = [F1 F2 F3];
    leg = repelem(u,length(profile));
    t = linspace(minT,minT+Ts,length(profile));