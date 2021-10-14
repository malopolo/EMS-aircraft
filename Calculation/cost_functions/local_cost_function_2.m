function f = local_cost_function_2(Pfc,SOC,current_soc,current_Pfc)
    esoc = zeros(1,length(SOC));
    edpfc = zeros(1,length(SOC));
    
    for soc=1:length(SOC)
        if SOC(soc)>90
            esoc(soc) =  (SOC(soc) - current_soc(soc)).^2;
        elseif SOC(soc)<40
            esoc(soc) =  (current_soc(soc) - SOC(soc)).^2;
        else
            esoc(soc) = 0;
        end
    end
    
    dpfc = 100;
    for soc=1:length(SOC)
        if Pfc(soc) > current_Pfc(soc)+dpfc
            edpfc(soc) = (Pfc(soc)-current_Pfc(soc)).^2;
        elseif Pfc(soc) < current_Pfc(soc)-dpfc
            edpfc(soc) = (current_Pfc(soc)-Pfc(soc)).^2;
        else
            edpfc(soc) = 0;
        end
    end
    
%     if find(edpfc) > 0
%         edpfc
%         current_soc
%         SOC
%     end
    f = esoc+edpfc;
end

