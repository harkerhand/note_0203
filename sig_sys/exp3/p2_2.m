clc; clear;

% ----------- 参数设置 -----------
N = 33;
M = (N - 1) / 2;
wc = 0.5 * pi;  % 截止频率

wc_index = round(wc * N / (2 * pi));  % 对应频率采样点索引

% ---------- 构造三种情况的频率响应 ----------
case_labels = ["无过渡点", "1个过渡点", "2个过渡点"];
Hd_cases = zeros(N, 3);

Hd_cases(1:wc_index, 1) = 1;                              % 无过渡点
Hd_cases(1:wc_index-1, 2) = 1; Hd_cases(wc_index, 2) = 0.5;  % 一个过渡点
Hd_cases(1:wc_index-2, 3) = 1; Hd_cases(wc_index-1, 3) = 0.75; Hd_cases(wc_index, 3) = 0.25; % 两个过渡点

% ---------- 计算并绘制频率响应 ----------
NFFT = 1024;
omega = linspace(0, pi, NFFT/2 + 1);
colors = {'b', 'r', 'g'};


% 图：线性尺度，放大通带边缘
figure;
for i = 1:3
    Hd = Hd_cases(:, i).';
    k = 0:N-1;
    omega_k = 2*pi*k/N;
    Hd = Hd .* exp(-1j * omega_k * M);
    h = real(ifft(Hd));
    h = 0.5 * (h + fliplr(h));
    H_f = fft(h, NFFT);
    H_f = H_f(1:NFFT/2 + 1);
    plot(omega/pi, abs(H_f), colors{i}, 'LineWidth', 1.3); hold on;
end

plot([wc/pi wc/pi], [0 1.2], 'k--');  % 截止频率线
legend([case_labels, "\omega_c"], 'Location', 'best');
title('幅频响应比较（线性尺度，通带边缘）');
xlabel('\omega / \pi'); ylabel('|H(e^{j\omega})|');
xlim([0.3 0.7]); ylim([0 1.2]);
grid on; hold off;
