dir_ = 'C:\Users\maloc\OneDrive\Documents\CHINE\Thèse\Thesis FINAL\Pictures\EMS';
% addpath(genpath(dir_));
% datt = 'constant low-range flight - dc bus voltage curves';
% datt = 'constant mid-range flight - power curves';
datt = 'constant mid-range flight - dc bus voltage curves';
Files=dir(dir_);
for k=1:length(Files)
    FileNames=Files(k).name;
    files_in=dir(strcat(dir_,'\',FileNames));
    for i=1:length(files_in)
        curve_to_change=files_in(i).name;
        if contains(curve_to_change,'.fig')
            if (contains(curve_to_change,'low-range') || contains(curve_to_change,'mid-range')) ...
                    && ~contains(curve_to_change,'SOC') && ~contains(curve_to_change,'filtered')
                clf
                fig = openfig(curve_to_change);
                h = findobj(fig,'Type','line');
                x1=h(2).XData;
                y1=h(2).YData;
                x2=h(1).XData;
                y2=h(1).YData;
                m = figure;
                plot(x1,sgolayfilt(y1,2,1001),'LineWidth',1)
                hold on
                plot(x2,sgolayfilt(y2,2,1001),'LineWidth',1)
                
                if contains(curve_to_change,'voltage')
                    ylim([71 73])
                    legend('Wanted DC bus voltage','Real DC bus voltage');
                elseif contains(curve_to_change,'output')
                    legend('Pout required','Pout real');
                else
                    legend('Pfc','Pbatt');
                end
                
                titt = strcat(curve_to_change(1:end-4),' - filtered');
                title(titt);
                xlabel('Time (s)');
                ylabel('Voltage (V)');
                
                
%                 set(fig, 'Visible', 'on');
                saveas(m,[dir_ '\' FileNames '\' titt '.fig']);
                saveas(m,[dir_ '\' FileNames '\' titt '.png']);
                close all;
            end
        end
    end
end

% fig = openfig(strcat(datt,'.fig'));
% h = findobj(fig,'Type','line');
% x1=h(1).XData;
% y1=h(1).YData;
% x2=h(2).XData;
% y2=h(2).YData;
% figure
% plot(x1,sgolayfilt(y1,2,1001))
% hold on
% plot(x2,sgolayfilt(y2,2,1001))
% % ylim([71 73])
% title(datt);
% xlabel('Time (s)');
% ylabel('Voltage (V)');
%
%
% set(fig, 'Visible', 'on');

