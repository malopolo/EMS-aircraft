function y = call_lstm(u)
    persistent net classes
    if isempty(net)
        load net_to_test
        classes = categorical(["takeoff","climb","cruise","descend"]);
    end
    
    temp = classify(net,u);
    y = find(temp(end)==classes);
    
    %  y = temp(end);