%% Start Program
clc
clear
close all;

%% GA Parameters
NumGeneration = 1;
PopSize = 3;
ChromosomeSize = 22;
CrossPercent = 70; % crossover probability x100
MutatPercent = 20; % mutation probability x100
ElitPercent = 100 - CrossPercent - MutatPercent;

% select the number of crossover / mutation / elitism operation
CrossNum = round(CrossPercent/100*PopSize);
if mod(CrossNum,2) CrossNum = CrossNum - 1; end
MutatNum = round(MutatPercent/100*PopSize);
ElitNum = PopSize - CrossNum - MutatNum;




%% Boundaries of each MFs parameters
VarMin = 0; % min value of each member of the pop
VarMax = 1;  % max value of each memeber of the pop


%% Global parameters
file = load('load_oc_without_noise.mat');
fuzzy_to_improve_1 = readfis('fuzzy_to_improve_1.fis');
C_sc = 1;
t = file.load_oc_without_noise(1,:);
w = file.load_oc_without_noise(2,:);

%% Initialize Population
tic
[Fit, Pop] = init(PopSize,ChromosomeSize,VarMax,VarMin,fuzzy_to_improve_1, 'fuzzy_to_improve');
toc

%% Main Loop
MeanMat = [];
MinMat = [];
it=0;

tic
%% Loop
for Iter = 1:NumGeneration
    %% Elitism
    ElitPop = Pop(1:ElitNum,:); % select the top x% of the pop
    
    %% Cross Over
    CrossPop = [];
    ParentIndexes = SelectParents_Fcn(PopSize,CrossNum,1);
    
    % random permutation and get the number of cross selected
    for ii = 1:CrossNum/2
        Par1Indx = ParentIndexes(ii*2-1);
        Par2Indx = ParentIndexes(ii*2);
        
        Par1 = Pop(Par1Indx,:); % get the selected parent 1
        Par2 = Pop(Par2Indx,:); % get the selected parent 2
        
        [Off1 Off2] = MyCrossOver_Fcn(Par1,Par2,1);
        % make the crossover (random choice of the two parts)
        CrossPop = [CrossPop ; Off1 ; Off2];
        % CrossPop = new offset pop
    end
    
    %% Mutation
    MutatPop = rand(MutatNum,ChromosomeSize) * (VarMax - VarMin) + VarMin;
    % random mutation pop
    
    
    %% New Population
    Pop = [ElitPop ; CrossPop ; MutatPop];
    % new pop
    
    % get the fitness value of each pop member
    Fit_ = fitness(Pop,fuzzy_to_improve_1,'sim');
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    varcost=var(Fit);
    z=0;
    for ii=1:PopSize
        z=Fit(ii)+z;
    end
    mean1=z/PopSize;
    ma=max(Fit);
    mi=min(Fit);
    mean=1-((mean1-mi)/(ma-mi));
    Pop = Pop(Indx,:);
    % Select the population depending on the best cost
    
    
    %% Algorithm Progress
    disp(strcat('------------------', Iter,'/', NumGeneration, '------------------'))
    BestC = Fit(1); % just display the best cost
    MinMat(Iter) = BestC; % save the best cost
    best=1-(BestC/ma);
    
    
%     %% What ?
%     temp=evalfis(fismat,[Iter;best;varcost;mean]);
%     
%     % most important part
%     MutatPercent = temp(1);
%     CrossPercent = temp(2);
%     PopSize= temp(3);
    
    it=it+1;
    semilogy(Iter,MinMat(Iter),'r.')
    hold on
end
% ylim([0 5])
%% Results
BestSolution = Pop(1,:)
BestCost = Fit(1,:)

%% End Program
toc
