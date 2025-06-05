% 人机交互输入参数
f = input('输入信号频率（Hz）：');
N = input('输入采样点数：');
T = input('输入采样间隔（s）：');
pad_zero = input('是否补零到64点？(y/n)：', 's');

% 生成信号
n = 0:N-1;
x = sin(2 * pi * f * n * T);

% 补零处理
if lower(pad_zero) == 'y'
    x = [x, zeros(1, 64 - N)];
    N = 64;
end

% 计算FFT
X = myFFT(x);

% 计算幅度谱并归一化
magnitude = abs(X) / N;
freq = (0:N-1) * (1/T) / N;

% 绘制频谱图
stem(freq, magnitude);
xlabel('频率 (Hz)');
ylabel('幅度');
title('幅度频谱');
xlim([0, 1/(2*T)]); % 显示Nyquist频率以内的部分
grid on;

% 输出X(k)值
disp('X(k)值：');
disp(X);