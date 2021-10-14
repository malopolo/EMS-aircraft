%% get path
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

%% get data
load load_to_train
cl_inputs = [];
cl_outputs = [];
tot_w = [];
tot_c = [];
inputs = [];
outputs = [];
outputs_number = [];
inputs_cell_arr = {};
outputs_cell_arr = {};
outputs_number_cell_arr = {};

all_l = cellfun('length',XTrain);
ml = max(all_l);

tot = length(XTrain);
% tot = 1;
l1 = 4;
Ts = 1e-2;
for i=1:tot
    add = ml - all_l(i);
    to_add = zeros(1,add);
    cl_inputs = [cl_inputs; [to_add XTrain{i}]];
    to_add_2 = categorical(repelem("takeoff",add));
    cl_outputs = [cl_outputs;[to_add_2 YTrain{i}]];
    t = [0];
    w = [0];
    c = ["takeoff"];
    classes = unique(cl_outputs);
    for j = 1:l1
        label = classes(j);
        idx = find(cl_outputs(i,:) == label);
        temp_t = idx;
        tt = temp_t(1):Ts:temp_t(end);
        temp_w = cl_inputs(i,idx);
        w = [w fixpt_interp1(temp_t,temp_w,tt,float('single'),[],float('single'),...
            [],'Floor')];
        c = [c repelem(label,length(tt))];
        w =w;
        t = [t tt];
    end
    inputs = [inputs; w];
    outputs = [outputs; c];
    tot_w = [tot_w w];
    tot_c = [tot_c c];
    [Aval, ~, indAval] = unique(c);
    Avalnew = [1; 2; 3; 4];
    Anew = Avalnew(indAval);
    c_n = reshape(Anew, size(c));
    outputs_number = [outputs_number c_n];
    inputs_cell_arr{i} = w(1:1:length(w));
    outputs_cell_arr{i} = c(1:1:length(c));
    outputs_number_cell_arr{i} = c_n;
end

%% variations
var_w = {};
var_c = {};
step = 1;
test_var_w = tot_w(1:step:end);
test_var_c = tot_c(1:step:end);
k = 1;
size_sample = 100000;
for i=1:floor(length(test_var_w)/size_sample)
    next_k = min(size_sample+k,length(test_var_w));
    var_c = [var_c; mat2cell(test_var_c(k:next_k),1)];
    var_w = [var_w; test_var_w(k:next_k)];
    k = next_k;
end
shuffling = randperm(numel(var_w));
var_w(shuffling);
var_c(shuffling);

%% part to make neural net (lstm)
numFeatures = 1;
numHiddenUnits = 100;
numClasses = 4;

layers = [ ...
    sequenceInputLayer(numFeatures)
    lstmLayer(numHiddenUnits,'OutputMode','sequence')
    fullyConnectedLayer(numClasses)
    softmaxLayer
    classificationLayer];

options = trainingOptions('adam', ...
    'MaxEpochs',10, ...
    'GradientThreshold',2, ...
    'Verbose',0, ...
    'Plots','training-progress', 'MiniBatchSize',2);

% net = trainNetwork(inputs_cell_arr,outputs_cell_arr,layers,options);
net = trainNetwork(var_w,var_c,layers,options);
save('net_to_test','net');
%%


outputs = convertCharsToStrings(outputs);


while mod(length(inputs),100)
    inputs = inputs(:,2:end);
    outputs = outputs(:,2:end);
end

%% takeoff part
[Aval, ~, indAval] = unique(outputs);
%% takeoff
Avalnew = [1; 0; 0; 0];
Anew = Avalnew(indAval);
outputs = reshape(Anew, size(outputs));


%% 
inputs_to_try = cell2mat(mat2cell(inputs(1,:), 1, 100.*ones(1,length(inputs(1,:))/100))');
outputs_to_try = cell2mat(mat2cell(outputs(1,:), 1, 100.*ones(1,length(outputs(1,:))/100))');

step = 1000;
inputs_to_test = cell2mat(mat2cell(inputs(2,301:end), 1, step.*ones(1,length(inputs(2,301:end))/step))');
outputs_to_test = cell2mat(mat2cell(outputs(2,301:end), 1, step.*ones(1,length(outputs(2,301:end))/step))');


clf 
figure(1)
plot(1:length(inputs(2,:)),inputs(2,:))
figure(2)
test = [];
for i=1:height(inputs_to_test)
    %     test = [test sim(net, inputs_to_test(i,:)')'];
    test = [test classify(net,inputs_to_test(i,:))];
end
plot(1:length(test),test)
