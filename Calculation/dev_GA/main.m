%% Start Program
clc
clear
close all;

%% GA Parameters
NumGeneration = 1;
PopSize = 4;
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



%% Get current folder and add all folders to the path
currentpath = pwd;
currentfolder = strsplit(currentpath,filesep);
while ((~strcmp(currentfolder{end}, 'EMS-aircraft')) && ...
        (~strcmp(currentfolder{end}, 'EMS-aircraft-main')) && ...
        ~isempty(currentfolder{end}))
    currentpath = fileparts(currentpath);
    currentfolder = strsplit(currentpath,filesep);
end
projectpath = currentpath;
addpath(genpath(projectpath));


%% Global parameters
file = load('load_oc_without_noise.mat');
fuzzy_to_improve_1 = readfis('fuzzy_to_improve_1.fis');
C_sc = 1;
Ts = 1e-3;
t = file.load_oc_without_noise(1,:);
w = file.load_oc_without_noise(2,:);
model_to_use = 'fast_powertrain';

%% Initialize Population
tic
[Fit, Pop] = init(PopSize,ChromosomeSize,VarMax,VarMin,fuzzy_to_improve_1,model_to_use, 'fuzzy_to_improve',projectpath);
toc

%% Main Loop
MinMat = zeros(NumGeneration,1);

tic
%% Loop
for Iter = 1:NumGeneration
    %% Elitism
    ElitPop = Pop(1:ElitNum,:); % select the top x% of the pop
    
    %% Cross Over
    CrossPop = [];
    ParentIndexes = SelectParents_Fcn(PopSize,CrossNum,1);
    
    %% change to make it faster
    % random permutation and get the number of cross selected
    for ii = 1:CrossNum/2
        Par1Indx = ParentIndexes(ii*2-1);
        Par2Indx = ParentIndexes(ii*2);
        
        Par1 = Pop(Par1Indx,:); % get the selected parent 1
        Par2 = Pop(Par2Indx,:); % get the selected parent 2
        
        [Off1,Off2] = MyCrossOver_Fcn(Par1,Par2,1);
        % make the crossover (random choice of the two parts)
        CrossPop = [CrossPop ; Off1 ; Off2];
        % CrossPop = new offset pop
    end
    
    %% Mutation
    MutatPop = rand(MutatNum,ChromosomeSize) * (VarMax - VarMin) + VarMin;
    % random mutation pop
    
    
    %% New Population
    % chose the pop
    Pop = [ElitPop ; CrossPop ; MutatPop];
    
    % get the fitness value of each pop member
    Fit_ = fitness(Pop,fuzzy_to_improve_1,model_to_use,projectpath);
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    % Select the population depending on the best cost    
    Pop = Pop(Indx,:);

    
    
    %% Algorithm Progress
    disp(strcat('------------------', int2str(Iter),'/', int2str(NumGeneration), '------------------'))
    MinMat(Iter) = Fit(1); % save the best cost
    
    
    %     %% What ?
    %     temp=evalfis(fismat,[Iter;best;varcost;mean]);
    %
    %     % most important part
    %     MutatPercent = temp(1);
    %     CrossPercent = temp(2);
    %     PopSize= temp(3);
    
    semilogy(Iter,MinMat(Iter),'r.')
    hold on
end
%% Save the model if needed:
if strcmp(model_to_use,'fast_powertrain')
    model = strcat(projectpath,'\Main\fast_powertrain.slx');
%     save_sytem(model);
%     close_system(model);
elseif strcmp(model_to_use,'powertrain')
    model = strcat(projectpath,'\Main\powertrain.slx');
%     save_sytem(model);
%     close_system(model);
end
%% Results
BestSolution = Pop(1,:)
BestCost = Fit(1,:)

%% End Program
toc
