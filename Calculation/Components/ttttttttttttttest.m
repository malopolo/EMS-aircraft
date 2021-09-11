mm = round(netNN(str2double(to_try.power)'),0);
cat_snn = [];
for i=1:length(mm)
    if mm(i) == 0
        j = "takeoff";
    elseif mm(i) == 1
        j = "climb";
    elseif mm(i) == 2
        j = "cruise";
    else 
        j = "descend";
    end
    cat_snn = [cat_snn categorical(j)];
end
cat_snn