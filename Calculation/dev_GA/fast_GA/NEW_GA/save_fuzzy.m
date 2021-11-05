function save_fuzzy(Pop,fis,name)
    count = 0;
    for i = 1:length(fis.Inputs)
        for j = 1:length(fis.Inputs(i).MembershipFunctions)
            count = count + 2;
            fis.Inputs(i).MembershipFunctions(j).Parameters = [Pop(count-1) Pop(count)];
        end
    end
    for i = 1:length(fis.Outputs)
        for j = 1:length(fis.Outputs(i).MembershipFunctions)
            count = count + 2;
            fis.Outputs(i).MembershipFunctions(j).Parameters = [Pop(count-1) Pop(count)];
        end
    end
    writeFIS(fis,strcat(name,'.fis'));
end