clc; clear;

% 读取语音信号
[x, fs] = audioread('voice.wav');
x = x(:,1); % 若是立体声，仅取左声道

% 绘制时域波形
t = (0:length(x)-1)/fs;
figure;
plot(t, x); xlabel('Time (s)'); ylabel('Amplitude');
title('原始语音信号时域波形'); grid on;

% 绘制频谱
N = length(x);
X = fft(x);
f = (0:N-1)*(fs/N);
figure;
plot(f, 20*log10(abs(X)+1e-6)); xlim([0 fs/2]);
xlabel('Frequency (Hz)'); ylabel('Magnitude (dB)');
title('原始语音信号频谱'); grid on;


% 低通参数
fp = 1000;
fs_stop = 1200;
delta_p = (10^(1/20)-1)/(10^(1/20)+1);
delta_s = 10^(-100/20);
delta = min(delta_p, delta_s);
A = -20*log10(delta);

% 归一化频率（0~1）
wp = fp/(fs/2);
ws = fs_stop/(fs/2);
Dw = ws - wp;

% Kaiser窗参数估算
if A > 50
    beta = 0.1102*(A - 8.7);
elseif A >= 21
    beta = 0.5842*(A - 21)^0.4 + 0.07886*(A - 21);
else
    beta = 0;
end

N_lp = ceil((A - 8) / (2.285 * Dw * pi));  % 滤波器阶数
if mod(N_lp,2)==0
    N_lp = N_lp + 1;  % 保证奇数
end

% 理想低通滤波器（自定义sinc实现）
wc = (fp + fs_stop)/2 / (fs/2) * pi;
n = -(N_lp-1)/2:(N_lp-1)/2;

% 自定义sinc实现
hd = zeros(size(n));
for i = 1:length(n)
    if n(i) == 0
        hd(i) = wc/pi;  % sinc(0) = 1
    else
        hd(i) = wc/pi * sin(wc*n(i))/(wc*n(i));  % sinc(x) = sin(x)/x
    end
end

% Kaiser窗函数
w = zeros(size(n));
for i = 1:length(n)
    arg = beta * sqrt(1 - (2*n(i)/(N_lp-1))^2);
    w(i) = besseli(0, arg) / besseli(0, beta);
end
h_lp = hd .* w;


% 高通参数
fs_stop = 4800;
fp = 5000;
wp = fp/(fs/2);
ws = fs_stop/(fs/2);
Dw = wp - ws;

delta_p = (10^(1/20)-1)/(10^(1/20)+1);
delta_s = 10^(-100/20);
delta = min(delta_p, delta_s);
A = -20*log10(delta);

% Kaiser参数
if A > 50
    beta = 0.1102*(A - 8.7);
elseif A >= 21
    beta = 0.5842*(A - 21)^0.4 + 0.07886*(A - 21);
else
    beta = 0;
end

N_hp = ceil((A - 8) / (2.285 * Dw * pi));
if mod(N_hp,2)==0
    N_hp = N_hp + 1;
end

% 理想高通 = δ[n] - 低通
wc = (fs_stop + fp)/2 / (fs/2) * pi;
n = -(N_hp-1)/2:(N_hp-1)/2;

% 自定义delta函数 - 低通
hd = zeros(size(n));
for i = 1:length(n)
    if n(i) == 0
        hd(i) = 1 - wc/pi;  % δ(0) - sinc(0)*wc/pi
    else
        hd(i) = 0 - wc/pi * sin(wc*n(i))/(wc*n(i));  % 0 - sinc(x)*wc/pi
    end
end

% Kaiser窗
w = zeros(size(n));
for i = 1:length(n)
    arg = beta * sqrt(1 - (2*n(i)/(N_hp-1))^2);
    w(i) = besseli(0, arg) / besseli(0, beta);
end
h_hp = hd .* w;


y_lp = conv(x, h_lp, 'same');
y_hp = conv(x, h_hp, 'same');


% 时域对比
figure;
subplot(3,1,1); plot(t, x); title('原始语音');
subplot(3,1,2); plot(t, y_lp); title('低通滤波后');
subplot(3,1,3); plot(t, y_hp); title('高通滤波后');

% 频谱对比
N = length(x);
X = fft(x, N);
Y_lp = fft(y_lp, N);
Y_hp = fft(y_hp, N);
f = (0:N-1)*(fs/N);

figure;
subplot(3,1,1); plot(f, 20*log10(abs(X)+1e-6)); xlim([0 fs/2]); title('原始语音频谱');
subplot(3,1,2); plot(f, 20*log10(abs(Y_lp)+1e-6)); xlim([0 fs/2]); title('低通滤波后频谱');
subplot(3,1,3); plot(f, 20*log10(abs(Y_hp)+1e-6)); xlim([0 fs/2]); title('高通滤波后频谱');

