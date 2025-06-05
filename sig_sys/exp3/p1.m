clc; clear;

% 设计参数
wp = 0.2 * pi;   % 通带截止频率
ws = 0.4 * pi;   % 阻带截止频率
As = 50;         % 阻带最小衰减（dB）

% 选择Blackman窗，满足As ≥ 50 dB
% 经验公式估计所需滤波器长度 N:
delta_omega = ws - wp;
N = ceil(6.6 * pi / delta_omega); % Blackman窗公式经验值
if mod(N,2) == 0
    N = N + 1;  % 保证N为奇数，以便获得对称线性相位
end

n = 0:N-1;
M = (N - 1) / 2;         % 中心点
wc = (wp + ws) / 2;      % 截止频率 (过渡带中点)

% -------- 1. 理想单位脉冲响应 --------
hd = sin(wc * (n - M)) ./ (pi * (n - M));
hd(M+1) = wc / pi;  % 修正n = M处的NaN（除零）

% -------- 2. Blackman窗函数 --------
w = 0.42 - 0.5 * cos(2*pi*n/(N-1)) + 0.08 * cos(4*pi*n/(N-1));

% -------- 3. 实际单位脉冲响应 --------
h = hd .* w;

% -------- 4. 绘图 --------
figure;
subplot(3,2,1);
stem(n, hd, 'filled');
title('理想单位脉冲响应 h_d[n]');
xlabel('n'); ylabel('Amplitude'); grid on;

subplot(3,2,2);
plot(n, w, 'LineWidth', 1.5);
title('Blackman窗函数 w[n]');
xlabel('n'); ylabel('Amplitude'); grid on;

subplot(3,2,3);
stem(n, h, 'filled');
title('实际单位脉冲响应 h[n]');
xlabel('n'); ylabel('Amplitude'); grid on;

% -------- 5. 幅频响应和相频响应 --------
NFFT = 1024;  % FFT点数
H = fft(h, NFFT);  % 计算频率响应
H = H(1:NFFT/2+1);  % 只取前半部分（到Nyquist频率）

% 创建频率向量，替代freqz返回的omega
omega = linspace(0, pi, NFFT/2+1);  % 从0到π的频率向量

% 计算幅度和相位
mag = 20*log10(abs(H) + 1e-10);  % 加小值防止log(0)
phase = angle(H);

subplot(3,2,4);
plot(omega/pi, mag);
title('幅频响应');
xlabel('\omega/\pi'); ylabel('Magnitude (dB)');
axis([0 1 -100 5]); grid on;

subplot(3,2,5);
plot(omega/pi, unwrap(phase));
title('相频响应');
xlabel('\omega/\pi'); ylabel('Phase (radians)');
grid on;

