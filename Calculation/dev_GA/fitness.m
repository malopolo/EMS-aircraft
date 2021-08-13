%% Function to get the fitness value of each member of the pop
% Each memember needs to be evaluated during a specific power profile
function Fit = fitness(Pop,fisi,model_type)
    len = height(Pop);
    Fit = zeros(len,1);
    
    if strcmp(model_type,'mfile')
        %         for i = 1:len
        %             % load the current pop
        %             Popi = Pop(i,:);
        %             % change the fuzzy (here we just change the fuzzy mfs)
        %             fisi = change_mfs_fis(Popi,fisi);
        %             % compute the power profile / soc ...
        %             Cost = get_results_from_model(fisi,time,power_profile,'sim');
        %             % compute the cost function and get the results
        %             %         Cost(i,1) = cost_function(..);
        %         end
    elseif strcmp(model_type,'sim')
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
        
        %% Open file (if needed) / set model path
        model = strcat(projectpath,'\Main\powertrain.slx');
        load_system(model);
        EMS_block  = 'powertrain/EMS';
        SOC_init = 80;
        set_param('powertrain/EMS/Management Variant/FUZZY/Fuzzy Logic Controller','FIS',"'fuzzy_to_improve_1.fis'");
        set_param('powertrain/Battery','SOC', string(SOC_init));
        
        warning('off','all');
        set_param(EMS_block,'ems','FUZZY');
        
        %% start the fitness evaluation
        for i = 1:len
            % change the fuzzy (here we just change the fuzzy mfs)
            change_mfs_fis(Pop(i,:),fisi);
            
            % compute the model / sim
            [DIfc, mh2, error_power, SOC] = get_results_from_sim(model);
            
            % compute the cost function and get the results
            Fit(i,1) = cost_function(DIfc, mh2, error_power, SOC);
        end
    end
end