S = readmatrix('solar_data.xlsx');
irradiance = rot90(S(:,1));
irradiance = irradiance ./ max(irradiance);
breakpoints_ = linspace(0,length(irradiance),43200);
% 6 -> 18h
% get a sample from a sample time
Ts = 60;


tot = round(Ts/length(breakpoints_) * length(irradiance));
mat_ = irradiance(1,round(length(irradiance)/2)-round(tot/2):round(length(irradiance)/2)+round(tot/2));
b_ = linspace(0,Ts,length(mat_));


temp = sprintf('%d,', mat_);
temp(end) = [];
fff = strcat('[',temp,']')
clipboard('copy',fff);
fff = strcat('[',temp,']')
temp = sprintf('%d,', b_);
temp(end) = [];
bbb = strcat('[',temp,']')


