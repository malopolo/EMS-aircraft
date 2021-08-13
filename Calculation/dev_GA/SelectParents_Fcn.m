function ParIndexes = SelectParents_Fcn(PopSize,SelectionNum,SelMethod)
    switch SelMethod
        % random selection
        case 1
            R = randperm(PopSize); 
            ParIndexes = R(1:SelectionNum);
    end
end