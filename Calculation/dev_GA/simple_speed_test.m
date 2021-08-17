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

%%
tic
Ts = 1e-3;
model = strcat(projectpath,'\Main\fast_powertrain.slx');
open_system(model);
sss = sim(model,'StartTime','0','StopTime',num2str(60));
toc