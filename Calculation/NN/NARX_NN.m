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
        tt = temp_t(1):1e-2:temp_t(end);
        temp_w = cl_inputs(i,idx);
        w = [w fixpt_interp1(temp_t,temp_w,tt,float('single'),[],float('single'),...
            [],'Floor')];
        c = [c repelem(label,length(tt))];
        t = [t tt];
    end
    inputs = [inputs; w];
    outputs = [outputs; c];
    [Aval, ~, indAval] = unique(c);
    Avalnew = [1; 2; 3; 4];
    Anew = Avalnew(indAval);
    c_n = reshape(Anew, size(c));
    outputs_number = [outputs_number; c_n];
    inputs_cell_arr{i} = smoothdata(w,'movmean','SmoothingFactor',0.01);
    outputs_cell_arr{i} = c;
    outputs_number_cell_arr{i} = c_n;
end



%% variations
var_w = {};
var_c = {};
for k=1:length(inputs_cell_arr)-25    
    % narx nn
    temp = num2cell(inputs_cell_arr{k},1);
    var_w = [var_w temp];
    temp_out = outputs_cell_arr{k};
    [Aval, ~, indAval] = unique(outputs_cell_arr{k});
    Avalnew = [1; 2; 3; 4];
    Anew = Avalnew(indAval);
    temp_out = reshape(Anew, size(temp_out));
    temp = num2cell(temp_out,1);
    var_c = [var_c temp];

end
test_var_w = cell2mat(var_w);
test_var_c = cell2mat(var_c);









%% train the narx
% Solve an Autoregression Problem with External Input with a NARX Neural Network
% Script generated by Neural Time Series app
% Created 16-Sep-2021 15:21:59
%
% This script assumes these variables are defined:
%
%   var_w - input time series.
%   var_c - feedback time series.

% X = var_w;
% T = var_c;
X = var_w(1:10:end);
T = var_c(1:10:end);

% Choose a Training Function
% For a list of all training functions type: help nntrain
% 'trainlm' is usually fastest.
% 'trainbr' takes longer but may be better for challenging problems.
% 'trainscg' uses less memory. Suitable in low memory situations.
% trainFcn = 'trainlm';  % Levenberg-Marquardt backpropagation.
trainFcn = 'trainscg';

% Create a Nonlinear Autoregressive Network with External Input
inputDelays = 1:10;
feedbackDelays = 1:10;
hiddenLayerSize = 10;
net = narxnet(inputDelays,feedbackDelays,hiddenLayerSize,'open',trainFcn);

% Choose Input and Feedback Pre/Post-Processing Functions
% Settings for feedback input are automatically applied to feedback output
% For a list of all processing functions type: help nnprocess
% Customize input parameters at: net.inputs{i}.processParam
% Customize output parameters at: net.outputs{i}.processParam
% net.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
% net.inputs{2}.processFcns = {'removeconstantrows','mapminmax'};

% Prepare the Data for Training and Simulation
% The function PREPARETS prepares timeseries data for a particular network,
% shifting time by the minimum amount to fill input states and layer
% states. Using PREPARETS allows you to keep your original time series data
% unchanged, while easily customizing it for networks with differing
% numbers of delays, with open loop or closed loop feedback modes.
[x,xi,ai,tt] = preparets(net,X,{},T);

% Setup Division of Data for Training, Validation, Testing
% For a list of all data division functions type: help nndivision
net.divideFcn = 'dividerand';  % Divide data randomly
net.divideMode = 'time';  % Divide up every sample
net.divideParam.trainRatio = 80/100;
net.divideParam.valRatio = 10/100;
net.divideParam.testRatio = 10/100;

% Choose a Performance Function
% For a list of all performance functions type: help nnperformance
net.performFcn = 'mse';  % Mean Squared Error

% Choose Plot Functions
% For a list of all plot functions type: help nnplot
net.plotFcns = {'plotperform','plottrainstate', 'ploterrhist', ...
    'plotregression', 'plotresponse', 'ploterrcorr', 'plotinerrcorr'};

% Train the Network
% net.trainParam.showWindow = 0;
[net,tr] = train(net,x,tt,xi,ai);

% Test the Network
y = net(x,xi,ai);
e = gsubtract(tt,y);
performance = perform(net,tt,y)

% Recalculate Training, Validation and Test Performance
trainTargets = gmultiply(tt,tr.trainMask);
valTargets = gmultiply(tt,tr.valMask);
testTargets = gmultiply(tt,tr.testMask);
trainPerformance = perform(net,trainTargets,y)
valPerformance = perform(net,valTargets,y)
testPerformance = perform(net,testTargets,y)

% View the Network
view(net)

% Plots
% Uncomment these lines to enable various plots.
%figure, plotperform(tr)
%figure, plottrainstate(tr)
%figure, ploterrhist(e)
%figure, plotregression(t,y)
%figure, plotresponse(t,y)
%figure, ploterrcorr(e)
%figure, plotinerrcorr(x,e)

% Closed Loop Network
% Use this network to do multi-step prediction.
% The function CLOSELOOP replaces the feedback input with a direct
% connection from the output layer.
netc = closeloop(net);
netc.name = [net.name ' - Closed Loop'];
view(netc)
[xc,xic,aic,tc] = preparets(netc,X,{},T);
yc = netc(xc,xic,aic);
closedLoopPerformance = perform(net,tc,yc)

% Multi-step Prediction
% Sometimes it is useful to simulate a network in open-loop form for as
% long as there is known output data, and then switch to closed-loop form
% to perform multistep prediction while providing only the external input.
% Here all but 5 timesteps of the input series and target series are used
% to simulate the network in open-loop form, taking advantage of the higher
% accuracy that providing the target series produces:
numTimesteps = size(x,2);
knownOutputTimesteps = 1:(numTimesteps-5);
predictOutputTimesteps = (numTimesteps-4):numTimesteps;
X1 = X(:,knownOutputTimesteps);
T1 = T(:,knownOutputTimesteps);
[x1,xio,aio] = preparets(net,X1,{},T1);
[y1,xfo,afo] = net(x1,xio,aio);
% Next the the network and its final states will be converted to
% closed-loop form to make five predictions with only the five inputs
% provided.
x2 = X(1,predictOutputTimesteps);
[netc,xic,aic] = closeloop(net,xfo,afo);
[y2,xfc,afc] = netc(x2,xic,aic);
multiStepPerformance = perform(net,T(1,predictOutputTimesteps),y2)
% Alternate predictions can be made for different values of x2, or further
% predictions can be made by continuing simulation with additional external
% inputs and the last closed-loop states xfc and afc.

% Step-Ahead Prediction Network
% For some applications it helps to get the prediction a timestep early.
% The original network returns predicted y(t+1) at the same time it is
% given y(t+1). For some applications such as decision making, it would
% help to have predicted y(t+1) once y(t) is available, but before the
% actual y(t+1) occurs. The network can be made to return its output a
% timestep early by removing one delay so that its minimal tap delay is now
% 0 instead of 1. The new network returns the same outputs as the original
% network, but outputs are shifted left one timestep.
nets = removedelay(net);
nets.name = [net.name ' - Predict One Step Ahead'];
view(nets)
[xs,xis,ais,ts] = preparets(nets,X,{},T);
ys = nets(xs,xis,ais);
stepAheadPerformance = perform(nets,ts,ys)

% Deployment
% Change the (false) values to (true) to enable the following code blocks.
% See the help for each generation function for more information.
if (false)
    % Generate MATLAB function for neural network for application
    % deployment in MATLAB scripts or with MATLAB Compiler and Builder
    % tools, or simply to examine the calculations your trained neural
    % network performs.
    genFunction(net,'myNeuralNetworkFunction');
    y = myNeuralNetworkFunction(x,xi,ai);
end
if (false)
    % Generate a matrix-only MATLAB function for neural network code
    % generation with MATLAB Coder tools.
    genFunction(net,'myNeuralNetworkFunction','MatrixOnly','yes');
    x1 = cell2mat(x(1,:));
    x2 = cell2mat(x(2,:));
    xi1 = cell2mat(xi(1,:));
    xi2 = cell2mat(xi(2,:));
    y = myNeuralNetworkFunction(x1,x2,xi1,xi2);
end
if (true)
    % Generate a Simulink diagram for simulation or deployment with.
    % Simulink Coder tools.
    netc = closeloop(net);
    gensim(netc,1e-1);
end
