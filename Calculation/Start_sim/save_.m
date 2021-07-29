function save_(out_,folder,batt_soc,strategy,Time)
    out = out_;
    save(strcat(folder,'\B',string(batt_soc),'_',strategy,'_',num2str(Time),'.mat'),'out');
end