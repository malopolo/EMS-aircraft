function [out] = filter_sgo(out)
    val = 1001;
    out.Pfc_in.signals.values = sgolayfilt(out.Pfc_in.signals.values,2,val);
    out.Pbatt_in.signals.values = sgolayfilt(out.Pbatt_in.signals.values,2,val);
    out.Ppv_in.signals.values = sgolayfilt(out.Ppv_in.signals.values,2,val);
    out.Vdc_real.signals.values = sgolayfilt(out.Vdc_real.signals.values,2,val);
    out.SOC_batt.signals.values = sgolayfilt(out.SOC_batt.signals.values,2,val);
    out.RMSE_power.signals.values = sgolayfilt(out.RMSE_power.signals.values,2,val);
    out.RMSE_voltage.signals.values = sgolayfilt(out.RMSE_voltage.signals.values,2,val);
    out.error_power.signals.values = sgolayfilt(out.error_power.signals.values,2,val);
    out.error_voltage.signals.values = sgolayfilt(out.error_voltage.signals.values,2,val);
    out.Vdc_real.signals.values = sgolayfilt(out.Vdc_real.signals.values,2,val);
    out.Ifc.signals.values = sgolayfilt(out.Ifc.signals.values,2,val);
    out.Pout_real.signals.values = sgolayfilt(out.Pout_real.signals.values,2,val);
end

