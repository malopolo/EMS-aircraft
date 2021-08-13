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
model = 'to_del';
load_system(model);
Pop = rand(2,22) * (1 - 0) + 0;
fuzz = readfis('fuzzy_to_improve_1.fis');
w = 0.5;
t = 0.5;
for i = 1:2
    fuzzy = change_mfs_fis(Pop(i,:),fuzz);
    m = test(fuzzy);
    disp(m)
end
