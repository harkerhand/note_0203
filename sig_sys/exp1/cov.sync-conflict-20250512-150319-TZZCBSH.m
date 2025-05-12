function y = my_cov(x, h)
len_x = length(x);
len_h = length(h);
len_y = len_x + len_h - 1;
y = zeros(1, len_y);

% 计算卷积
for n = 1:len_y
    for k = 1:len_h
        if n-k+1 > 0 && n-k+1 <= len_x
            y(n) = y(n) + x(n-k+1) * h(k);
        end
    end
end
end


%% ========== Case 1 ==========
x1 = 1:10; % x(n) = [1,2,3,...,10]
h1 = [1, 1]; % h(n) = [1,1]
y1 = my_cov(x1, h1);
figure;
stem(0:length(y1)-1, y1, 'filled');
title('Case 1: x(n) = [1:10], h(n) = [1,1]');
xlabel('n'); ylabel('y(n)');
grid on;

%% ========== Case 2 ==========
x2 = [1,2,3,9,4,5,6,0,7,8]; % x(n) = [1,2,3,9,4,5,6,0,7,8]
h2 = [-1, 2, -1]; % h(n) = [-1,2,-1]

y2 = my_cov(x2, h2); % 计算卷积

figure;
stem(0:length(y2)-1, y2, 'filled');
title('Case 2: x(n) = [1,2,3,9,4,5,6,0,7,8], h(n) = [-1,2,-1]');
xlabel('n'); ylabel('y(n)');
grid on;

%% ========== Case 3 ==========
x3 = 1:10; % x(n) = [1,2,3,...,10]
h3 = 1:10; % h(n) = [1,2,3,...,10]

y3 = my_cov(x3, h3); % 计算卷积

figure;
stem(0:length(y3)-1, y3, 'filled');
title('Case 3: x(n) = [1:10], h(n) = [1:10]');
xlabel('n'); ylabel('y(n)');
grid on;