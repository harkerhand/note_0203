f = @(t, i) i * (0.7 - i);       % 定义微分方程
tspan = [0 50];                  % 求解时间范围
i0 = 0.02;                       % 初始条件

[t, i] = ode45(f, tspan, i0);   % 使用 ode45 求解

% 绘图
plot(t, i, 'LineWidth', 2);
xlabel('时间 t');
ylabel('感染者比例 i(t)');
title('例2：SIS模型解 i''(t) = i(0.7 - i)');
grid on;
