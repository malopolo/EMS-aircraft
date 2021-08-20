% %% Get current folder and add all folders to the path
% currentpath = pwd;
% currentfolder = strsplit(currentpath,filesep);
% while ((~strcmp(currentfolder{end}, 'EMS-aircraft')) && ...
%         (~strcmp(currentfolder{end}, 'EMS-aircraft-main')) && ...
%         ~isempty(currentfolder{end}))
%     currentpath = fileparts(currentpath);
%     currentfolder = strsplit(currentpath,filesep);
% end
% projectpath = currentpath;
% addpath(genpath(projectpath));
% 
% %%
% file = load('load_oc_without_noise.mat');
% C_sc = 1;
% Ts = 1e-3;
% t = file.load_oc_without_noise(1,:);
% w = file.load_oc_without_noise(2,:);
%%
tic
Ts = 1e-3;
model = strcat(projectpath,'\Main\fast_powertrain.slx');
load_system(model);
set_param(gcs,'FastRestart','off');
set_param(gcs,'StartTime','0','StopTime',num2str(60));
% sss = sim(model,'StartTime','0','StopTime',num2str(60));
set_param(gcs,'FastRestart','on');
sss = sim(model);
toc