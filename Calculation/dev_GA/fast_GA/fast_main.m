%% Start Program
clc
clear
close all;

%% GA Parameters
NumGeneration = 30;
PopSize = 60;
ChromosomeSize = 22;
CrossPercent = 70; % crossover probability x100
MutatPercent = 20; % mutation probability x100
ElitPercent = 100 - CrossPercent - MutatPercent;
% Method of implementation
Method = 1;

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
SOC_init = 80;
SimTime = 200; % Max simulation time
% t = file.t_one_c; % breakpoints for load look up table
% w = file.one_c; % load data for look up table
t = file.t_repeated; % breakpoints for load look up table
w = file.c_repeated; % load data for look up table

% fuel cell efficiency
x = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33];
y = [0,24.67,38.67,47.67,52.67,54.83,56.33,57,57.33,57.33,57.33,57.17,57,56.67,56.33,55.83,55.33,55,54.58,54,53.56,53,52.56,52.08,51.67,51.33,50.92,50.42,50,49.6,49.2,48.8,48.4,48];
x = x / (33/1.21);

global x_fc_eff fc_eff
x_fc_eff = linspace(0,1.21,100);
fc_eff = interp1(x, y, x_fc_eff, 'linear'); %// Generate interpolated array



%% Set the model
% load the model
model_to_use = 'fast_powertrain';
model = strcat(projectpath,'\Main\fast_powertrain.slx');
load_system(model);


% set param in model
set_param('fast_powertrain/Fuzzy Logic Controller','FIS',"'fuzzy_to_improve_1.fis'");
set_param('fast_powertrain/Battery','SOC', string(SOC_init));
set_param(model_to_use,'StartTime','0','StopTime',num2str(SimTime));
warning('off','all');

% define the fis file
global fuzzy_test
fuzzy_test = readfis('fuzzy_to_improve_1.fis');
set_param('fast_powertrain/Fuzzy Logic Controller','FIS',"fuzzy_test");

% Enable fast restart
set_param(model_to_use,'FastRestart','off');
save_system(model);




%% Start the GA
%% Initialize Population
inittime = tic;
[Fit, Pop] = fast_init(PopSize,ChromosomeSize,VarMax,VarMin,fuzzy_to_improve_1,model, 'fuzzy_to_improve',Ts,Method);
disp(strcat('------------------ init phase ended, time : ', num2str(toc(inittime)) ,  ' ------------------'))


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
    
    %% change to make it faster
    % random permutation and get the number of cross selected
    for ii = 1:CrossNum/2
        Par1Indx = ParentIndexes(ii*2-1);
        Par2Indx = ParentIndexes(ii*2);
        
        Par1 = Pop(Par1Indx,:); % get the selected parent 1
        Par2 = Pop(Par2Indx,:); % get the selected parent 2
        
        % make the crossover (random choice of the two parts)
        [CrossPop(ii*2-1,:),CrossPop(ii*2,:)] = fast_MyCrossOver_Fcn(Par1,Par2,Method);
    end
    
    %% Mutation (width = VarMax/2)
    MutatPop = rand(MutatNum,ChromosomeSize) * (VarMax - VarMin) + VarMin;
    
    
    %% New Population
    % chose the pop
    Pop = [ElitPop ; CrossPop ; MutatPop];
    
    % get the fitness value of each pop member
    Fit_ = fast_fitness(Pop,fuzzy_to_improve_1,model,Ts,Method);
    
    % sort the fitness matrix
    [Fit,Indx] = sort(Fit_);
    
    % Select the population depending on the best cost
    Pop = Pop(Indx,:);
    
    
    
    %% Algorithm Progress
    disp(strcat('------------------', int2str(Iter),'/', int2str(NumGeneration), ' time : ', num2str(toc(inlooptime)) ,  ' ------------------'))
    MinMat(Iter) = Fit(1); % save the best cost
    
    % draw the semi log figure
    semilogy(Iter,MinMat(Iter),'r.')
    hold on
end
set_param(model_to_use,'FastRestart','off');

%% Results
BestSolution = Pop(1,:)
BestCost = Fit(1,:)

%% End Program
toc(looptime)

%% Save Best Solution
best_sol = readfis('best_sol.fis');
write_bestsol_fis(BestSolution,best_sol);
