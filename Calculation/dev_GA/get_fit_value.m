function popi = get_fit_value(file,size_pop)
    fis = readfis(file);
    popi = zeros(1,size_pop);
    count = 1;
    for i = 1:length(fis.Inputs)
        for j = 1:length(fis.Inputs(i).MembershipFunctions)
            temp = fis.Inputs(i).MembershipFunctions(j).Parameters;
            popi(count) = temp(1);
            popi(count+1) = temp(2);
            count = count+2;
        end
    end
    for i = 1:length(fis.Outputs)
        for j = 1:length(fis.Outputs(i).MembershipFunctions)
            temp = fis.Outputs(i).MembershipFunctions(j).Parameters;
            popi(count) = temp(1);
            popi(count+1) = temp(2);
            count = count+2;
        end
    end
end