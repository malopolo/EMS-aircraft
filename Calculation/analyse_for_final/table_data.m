function [table_power] = table_data(data,gcf,name_file,dir_,sav)
    row_names = {'gcf','Pfc_in','Pbatt_in','Ppv_in','Vdc_real','SOC_batt',...
        'RMSE_power','RMSE_voltage','error_power','error_voltage',...
        'dVdc','exec time', 'Percentage time','hydrogen consumption'};
            N = 50; % Number of cells
        F = 96485; % Faraday constant
    col = zeros(14,1);
    col(1) = gcf;
    col(2) = round(mean(data.Pfc_in.signals.values),2);
    col(3) = round(mean(data.Pbatt_in.signals.values),2);
    col(4) = round(mean(data.Ppv_in.signals.values),2);
    col(5) = round(mean(data.Vdc_real.signals.values),2);
    col(6) = round(data.SOC_batt.signals.values(end),2);
    col(7) = round(sqrt(mean(data.RMSE_power.signals.values)),2);
    col(8) = round(sqrt(mean(data.RMSE_voltage.signals.values)),2);
    col(9) = round(mean(data.error_power.signals.values),2);
    col(10) = round(mean(data.error_voltage.signals.values),2);
    col(11) = trapz(data.tout(2:end),diff(data.Vdc_real.signals.values))*1e3;
    col(12) = data.SimulationMetadata.TimingInfo.ExecutionElapsedWallTime;
    col(13) = data.SimulationMetadata.TimingInfo.ExecutionElapsedWallTime/data.tout(end)*100;
    col(14) = trapz(data.tout,N/F*data.Ifc.signals.values);
%     col = sgolayfilt(col,2,1001);
    table_power = array2table(col,'RowNames',row_names);
    if strcmp(sav,'save')
        writetable(table_power,strcat(dir_,'\',name_file,'.csv'),'Delimiter',',','QuoteStrings',true)
    end
end
