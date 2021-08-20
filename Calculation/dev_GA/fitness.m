%% Function to get the fitness value of each member of the pop
% Each memember needs to be evaluated during a specific power profile
function Fit = fitness(Pop,fisi,model_type,projectpath)
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
    elseif strcmp(model_type,'powertrain')
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
            [DIfc, mh2, error_power, SOC] = get_results_from_sim(model,model_type);
            
            % compute the cost function and get the results
            Fit(i,1) = cost_function(DIfc, mh2, error_power, SOC);
        end
    elseif strcmp(model_type,'fast_powertrain')
        %% Open file (if needed) / set model path
        model = strcat(projectpath,'\Main\fast_powertrain.slx');
        load_system(model);
        SOC_init = 80;
        SimTime = 60; % Max simulation time
        set_param('fast_powertrain/Fuzzy Logic Controller','FIS',"'fuzzy_to_improve_1.fis'");
        set_param('fast_powertrain/Battery','SOC', string(SOC_init));
        warning('off','all');
        set_param('fast_powertrain','StartTime','0','StopTime',num2str(SimTime));
%         set_param('fast_powertrain','FastRestart','on');
        %% start the fitness evaluation
        for i = 1:len
            % change the fuzzy (here we just change the fuzzy mfs)
            fast_change_mfs_fis(Pop(i,:),fisi);
            
            % compute the model / sim
            [DIfc, mh2, error_power, SOC] = get_results_from_sim(model,model_type);
            
            % compute the cost function and get the results
            Fit(i,1) = cost_function(DIfc, mh2, error_power, SOC);
        end
%         set_param('fast_powertrain','FastRestart','off');
    end
end