function [Fit, Pop] = fast_init(PopSize,ChromosomeSize,VarMax,VarMin,fisi,model,add_fuzzy_first_row,Ts,Method)
    % init the pop with random values (width = VarMax/2)
    Pop_ = rand(PopSize,ChromosomeSize) * (VarMax - VarMin) + VarMin;
%     Pop_(:,1:2:end) = Pop_(:,1:2:end)/2;
    
    if strcmp(add_fuzzy_first_row, 'fuzzy_to_improve')
        Pop_(1,:) = fast_get_fit_value('fuzzy_to_impr.fis',ChromosomeSize);
        Pop_(2,:) = fast_get_fit_value('fuzzy_to_improve_2.fis',ChromosomeSize);
        Pop_(3,:) = fast_get_fit_value('best_sol.fis',ChromosomeSize);
        Pop_(4,:) = fast_get_fit_value('fuzzy_1.fis',ChromosomeSize);
    end
    
    % get the fitness value of each pop member
    Fit_ = fast_fitness(Pop_,fisi,model,Ts,Method);
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    % sort the pop depending on the fitness values
    Pop = Pop_(Indx,:);
end