function [Esc,SCdata] = sc_model(Isc,SCdata)
    % Forward Euler
    SCdata.deltaI = SCdata.deltaI + SCdata.Ts*SCdata.old_input_deltaI;
    SCdata.old_input_deltaI = (-Isc - SCdata.Iself_dis);
    
    temp = SCdata.deltaI + SCdata.Qinit;
    SCdata.SOC = 100*(temp/SCdata.C/SCdata.Vrated);
    
    temp1 = max(0.001,temp);
    temp2 = SCdata.beta/temp1 * asinh(SCdata.lambda*temp1) + SCdata.alpha;
    Esc = temp1*temp2;
    
    C_bis = 1/temp2;
    if abs(SCdata.old_Isc) < 0.05
        SCdata.old_self_dis_part = SCdata.old_self_dis_part + SCdata.Ts*SCdata.old_input_self_dis_part;
        SCdata.old_input_self_dis_part = 1;
    else
        SCdata.old_self_dis_part = 0;
        SCdata.old_input_self_dis_part = 0;
    end
    SCdata.old_Isc = -Isc;
    
    if SCdata.old_self_dis_part> 0 && SCdata.old_self_dis_part<=10
        temp = SCdata.a1;
    elseif SCdata.old_self_dis_part>10 && SCdata.old_self_dis_part<=100
        temp = SCdata.a2;
    elseif SCdata.old_self_dis_part>100
        temp = SCdata.a3;
    else
        temp = 0;
    end
    
    temp3 = 1/C_bis/SCdata.Rdc;
    

    SCdata.Iself_dis = SCdata.old_Iself_dis + SCdata.Ts*SCdata.old_input_Iself_dis;
    SCdata.old_input_Iself_dis = temp3*(SCdata.old_Iself_dis - temp);
    SCdata.old_Iself_dis = SCdata.Iself_dis;
end

