function [index_values] = closest_value(base_arr,check_arr)
    lcheck = length(check_arr);
    index_values = zeros(lcheck,1);
    for ni = 1 : lcheck
        [~, index_values(ni)] = min(abs(base_arr-check_arr(ni)));
    end
%     real_index = unique(index_values);
%     next_soc = base_arr(index_values);
end

