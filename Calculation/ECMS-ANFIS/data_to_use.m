function [t, w] = data_to_use(X,Y)
    classes = categories(Y{1});
    l1 = numel(classes);
    l2 = length(Y)/2;
    
    tot_time = cell(1,l2);
    tot_data = cell(1,l2);
    
    for i = 1:l2
        t = cell(1,l1);
        w = cell(1,l1);
        for j = 1:l1
            label = classes(j);
            idx = find(Y{i} == label);
            t{j} = idx-idx(1);
            w{j} = X{i}(idx);
            %         if strcmp(label,'cruise')
            %             plot(t{j},w{j})
            %         end
        end
        tot_time{i} = t;
        tot_data{i} = w;
        
    end
    
    t = cell(1,l1);
    w = cell(1,l1);
    
    for j = 1:l1
        temp_t = [0];
        temp_w = [0];
        for i = 1:l2
            tt = 0:1e-1:20;
            ww = zeros(1,20/1e-1+1);
            var_t = [tot_time{i}{j}+temp_t(end)];
            var_t = [var_t var_t(end)+tt];
            var_w = [tot_data{i}{j}+temp_w(end)];
            var_w = [var_w ww];
            temp_t = [temp_t var_t];
            temp_w = [temp_w var_w];
        end
        if j==2
            temp_t = temp_t/5;
        end
        temp_t = temp_t/3;
        ttt = 0:1e-2:temp_t(end);
        www = fixpt_interp1(temp_t,temp_w,ttt,float('single'),[],float('single'),...
            [],'Floor');
        t{j} = ttt;
        w{j} = www;
    end
end