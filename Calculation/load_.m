%% get array in correct way
%clc
x = [0,0,0,1500,1550,1475,1480,1550,1525,1475,1500,1250,950,1000,1050,1075,950,975,1000,1000,1000,1000,1000,1000,1000,1000,1250,1500,1550,1475,1480,1550,1525,1475,1500,0,0,0,0,0];
x = x; % [0,0,50,500,1000,1250,1250,1000,750,750,750];
length(x)
breakpoints_ = linspace(0,60,length(x));
temp = sprintf('%d,', x);
temp(end) = [];
fff = strcat('[',temp,']')
temp = sprintf('%d,', breakpoints_);
temp(end) = [];
bbb = strcat('[',temp,']')

% clipboard('copy',x);
clipboard('copy',breakpoints_);