function y = test_fcn(myfis,Pload, SOC)
    options = evalfisOptions('NumSamplePoints',10);
    m = evalfis(myfis,[Pload SOC],options);
    y = m(1);