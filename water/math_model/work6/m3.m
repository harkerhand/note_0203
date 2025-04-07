f = @(t, Y) [Y(2);
    -t * Y(1) + exp(t) * Y(2) + 3 * sin(2 * t)];

tspan = [3.9 4];                % 时间区间很短
Y0 = [8; 2];                    % 初值 y(3.9) = 8, y'(3.9) = 2

[t, Y] = ode45(f, tspan, Y0);  % 求解

% 绘图
plot(t, Y(:,1), 'b-', 'LineWidth', 2);
xlabel('时间 t');
ylabel('解 y(t)');
title('例3：二阶微分方程的特解');
grid on;
