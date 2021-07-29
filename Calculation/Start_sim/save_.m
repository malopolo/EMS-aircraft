function save_(out_,folder,name,Time)
    out = out_;
    save(strcat(folder,'\',name,'_',num2str(Time),'.mat'),'out');
end