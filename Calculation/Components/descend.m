function [profile, leg,t] = descend(Ts, nbpoints, MaxPow, minT)
    u = "descend";
    % descend
    dwn = 0.01+randi(3)/100;
    dwnbis = 0.15+randi(5)/100;
    mxp = 500+randi(100);
    F1 = linspace(MaxPow,mxp,dwn*nbpoints);
    F1bis = linspace(mxp,mxp,dwnbis*nbpoints);
    % max
    
    mxp2 = 500 + 100 + randi(100);
    upp = 0.01+randi(3)/100;
    plateau = 0.25+randi(5)/100;
    F2 = linspace(mxp,mxp2,upp*nbpoints);
    F2bis = linspace(mxp2,mxp2,plateau*nbpoints);
    
    landing = 0.02+randi(5)/100;
    tot = 1-dwn-dwnbis-upp-plateau-landing;
    F3 = [];
    while tot > 0
        new1 = 0.01+randi(2)/100;
        
        if tot-new1 < 0
            new1 = tot;
            tot = 0;
        else
            tot = tot-new1;
        end
        mxp3 = mxp+50-randi(150);
        F3_1 = linspace(mxp2,mxp3,new1*nbpoints);
        if tot == 0
            continue
        end
        new2 = 0.2+randi(10)/100;
        
        if tot-new2 < 0
            new2 = tot;
            tot=0;
        else
            tot = tot-new2;
        end
        mxp2 = mxp3;
        F3_2 = linspace(mxp3,mxp3,new2*nbpoints);       
        F3 = [F3 F3_1 F3_2];
    end
    F4 = linspace(0,0,landing*nbpoints);
    
    profile = [F1 F1bis F2 F2bis F3 F4];
    leg = repelem(u,length(profile));
    t = linspace(minT,minT+Ts,length(profile));