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

%% Get the data folder
folder_data = strcat(projectpath,'\Data');

%% Open file (if needed) / set model path
model = strcat(projectpath,'\Main\powertrain.slx');
load_system(model);
model_name = strcat('','powertrain');


%% Get load data for the simulation
fullMatFileName = fullfile(folder_data,  'data.mat');
load(fullMatFileName); % w is loaded (load data)

%% Get the EMS files if needed
fuzzy_1 = readfis(strcat(projectpath,'\EMS\fuzzy_1.fis'));

%% Set data
% Ts = 1e-4;
SimTime = 85; % Max simulation time
SOC_init = 80;


% 3) Create an array of SimulationInput objects and specify the sweep value for each simulation
simIn(1:numSims) = Simulink.SimulationInput(model_name);
idx = 1;
simIn(idx) = simIn(idx).setBlockParameter([model_name '/EMS'], 'ems', 'PI');
simIn(idx) = simIn(idx).setBlockParameter([model_name '/Battery'], 'SOC', num2str(SOC_init+(idx-1)*10));
idx = 2;
simIn(idx) = simIn(idx).setBlockParameter([model_name '/EMS'], 'ems', 'PI');
simIn(idx) = simIn(idx).setBlockParameter([model_name '/Battery'], 'SOC', num2str(SOC_init+(idx-1)*10));


% 4) Simulate the model
simOut = parsim(simIn)

%% close the model to unload the memory
close_system(model);
