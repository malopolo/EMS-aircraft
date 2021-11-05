clf
%% GA Parameters
NumGeneration = 100;
PopSize = 100;
ChromosomeSize = 22;
CrossPercent = 70; % crossover probability x100
MutatPercent = 20; % mutation probability x100
ElitPercent = 100 - CrossPercent - MutatPercent;
% Method of implementation
Method = 2;

% select the number of crossover / mutation / elitism operation
CrossNum = round(CrossPercent/100*PopSize);
if mod(CrossNum,2)
    CrossNum = CrossNum - 1;
end
MutatNum = round(MutatPercent/100*PopSize);
ElitNum = PopSize - CrossNum - MutatNum;


%% Boundaries of each MFs parameters
VarMin = 0; % min value of each member of the pop
VarMax = 1;  % max value of each memeber of the pop
% max width is VarMax/2


%% Global parameters
fuzzy_to_improve_1 = readfis('fuzzy_to_improve_1.fis');
Tss = 1;
Pout = w(1:Tss/1e-3:SimTime/1e-3);
SimTime = t(end);
SOC_batt_arr = [80 85 75];

%% Start the GA
%% Initialize Population
inittime = tic;
[Fit_, Pop] = new_init(PopSize,ChromosomeSize,VarMax,VarMin,...
    fuzzy_to_improve_1, 'fuzzy_to_improve',Tss,Method,Pout,SimTime,SOC_batt_arr);
[Fit,Indx] = sort(Fit_);
disp(strcat('------------------ init phase ended, time : ', num2str(toc(inittime)) , ' Best Cost : ' , num2str(Fit(1,:)), ' Mean Cost : ' , num2str(mean(Fit)),  ' ------------------'))


%% Main Loop
MinMat = zeros(NumGeneration,1);

looptime = tic;
for Iter = 1:NumGeneration
    inlooptime = tic;
    %% Elitism
    ElitPop = Pop(1:ElitNum,:); % select the top x% of the pop
    
    %% Cross Over
    CrossPop = zeros(CrossNum, ChromosomeSize);
    ParentIndexes = fast_SelectParents_Fcn(PopSize,CrossNum,1);
    
    %% change to make it newer
    % random permutation and get the number of cross selected
    for ii = 1:CrossNum/2
        Par1Indx = ParentIndexes(ii*2-1);
        Par2Indx = ParentIndexes(ii*2);
        
        Par1 = Pop(Par1Indx,:); % get the selected parent 1
        Par2 = Pop(Par2Indx,:); % get the selected parent 2
        
        % make the crossover (random choice of the two parts)
        [CrossPop(ii*2-1,:),CrossPop(ii*2,:)] = fast_MyCrossOver_Fcn(Par1,Par2,1);
    end
    
    %% Mutation (width = VarMax/2)
    MutatPop = round(rand(MutatNum,ChromosomeSize),5) * (VarMax - VarMin) + VarMin;
    
    
    %% New Population
    % chose the pop
    Pop = [ElitPop ; CrossPop ; MutatPop];
    
    % get the fitness value of each pop member
    Fit_ = new_fitness(Pop,fuzzy_to_improve_1,Tss,Method,Pout,SimTime,SOC_batt_arr);
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    % Select the population depending on the best cost
    Pop = Pop(Indx,:);
    
    
    
    %% Algorithm Progress
    disp(strcat('------------------', int2str(Iter),'/', int2str(NumGeneration), ' time : ', num2str(toc(inlooptime)) , ' Best Cost : ' , num2str(Fit(1,:)), ' Mean Cost : ' , num2str(mean(Fit)),  ' ------------------'))
    MinMat(Iter) = Fit(1); % save the best cost
    
    % draw the semi log figure
    semilogy(Iter,MinMat(Iter),'r.')
    hold on
end

%% Results
Pop
BestSolution = Pop(1,:)
BestCost = Fit(1,:)

%% End Program
toc(looptime)

%% Save Best Solution
save_fuzzy(BestSolution,fuzzy_to_improve_1,strcat('fuzzy_for_final_',num2str(Method)));


