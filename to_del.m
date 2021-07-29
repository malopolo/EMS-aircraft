currentpath = pwd;
currentfolder = strsplit(currentpath,filesep);
size(currentfolder)
while ~strcmp(currentfolder{end}, 'EMS-aircraft')
    currentpath = fileparts(currentpath)
    currentfolder = strsplit(currentpath,filesep)
    size(currentfolder)
end
% 
% projectpath = currentpath
% while ~strcmp(currentfolder{end}, 'EMS-aircraft')
%     currentpath = fileparts(currentpath)
%     currentfolder = strsplit(currentpath,filesep)
% end
