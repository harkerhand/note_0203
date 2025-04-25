function X = myFFT(x)
    % myFFT 基于按时间抽取法的基2快速傅里叶变换实现
    % 输入：x - 长度为2的幂的复数序列
    % 输出：X - 傅里叶变换结果
    
    N = length(x);
    if log2(N) ~= floor(log2(N))
        error('输入长度必须为2的幂');
    end

    % 位倒序排序
    j = 0:(N-1);
    rev = bitrevorder(j+1);
    x = x(rev);

    % FFT迭代计算
    for s = 1:log2(N)
        m = 2^s;
        wm = exp(-2*pi*1i/m);
        for k = 1:m:N
            for j = 0:(m/2 - 1)
                t = wm^j * x(k + j + m/2);
                u = x(k + j);
                x(k + j) = u + t;
                x(k + j + m/2) = u - t;
            end
        end
    end
    X = x;
end


clc; clear;

disp('--- FFT频谱分析实验 ---');
N = input('请输入采样点数N（必须为2的幂）: ');
Ts = input('请输入采样间隔Ts: ');
Fs = 1 / Ts;

f = input('请输入信号频率f: ');
t = (0:N-1) * Ts;
x = sin(2 * pi * f * t);  % 纯正弦波信号

add_zeros = input('是否补零至64点？(1-是, 0-否): ');
if add_zeros
    x = [x, zeros(1, 64 - length(x))];
    N = 64;
end

% 调用自定义FFT
X = myFFT(x);

% 频谱归一化幅度
magX = abs(X) / max(abs(X));  

% 绘图
f_axis = (0:N-1) * Fs / N;
stem(f_axis, magX, 'filled');
title('归一化幅度频谱');
xlabel('频率 (Hz)');
ylabel('|X(k)|');
grid on;
