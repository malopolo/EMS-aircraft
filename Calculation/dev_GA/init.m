function [Fit, Pop] = init(PopSize,ChromosomeSize,VarMax,VarMin,fisi,model_to_use,add_fuzzy_first_row,projectpath)
    % init the pop with random values
    Pop_ = rand(PopSize,ChromosomeSize) * (VarMax - VarMin) + VarMin;
    if strcmp(add_fuzzy_first_row, 'fuzzy_to_improve')
        Pop_(1,:) = get_fit_value('fuzzy_to_impr.fis',ChromosomeSize);
        Pop_(2,:) = get_fit_value('fuzzy_to_improve_2.fis',ChromosomeSize);
    end
    % get the fitness value of each pop member
    Fit_ = fitness(Pop_,fisi,model_to_use,projectpath);
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    % sort the pop depending on the fitness values
    Pop = Pop_(Indx,:);
end