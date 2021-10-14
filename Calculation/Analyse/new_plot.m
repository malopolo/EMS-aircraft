function [outputArg1,outputArg2] = new_plot(time_vector,data,tit,xtit,ytit)
    plot(time_vector,data);
    title(tit);
    xlabel(xtit);
    ylabel(ytit);
end

