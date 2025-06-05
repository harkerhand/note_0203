clc; clear;

N_list = [33, 63];
wc = 0.5 * pi;  % 3dB截止频率（rad）

for idx = 1:length(N_list)
    N = N_list(idx);
    M = (N - 1) / 2;  % 对称中心

    % ----- 1. 理想频率响应采样 -----
    k = 0:N-1;
    omega_k = 2 * pi * k / N;

    % 理想低通采样频率响应 Hd(k)
    Hd = double(omega_k <= wc);  % 截止频率处为1，其余为0

    % 确保对称性（避免复杂频率）
    Hd = Hd .* exp(-1j * omega_k * M);  % 增加相位补偿，保证实值对称

    % ----- 2. IFFT 得到 h(n) -----
    h = real(ifft(Hd));  % 保证对称实数序列

    % 强制对称（修正数值误差）
    h = 0.5 * (h + fliplr(h));

    % ----- 3. 手动计算幅频响应（替代freqz）-----
    NFFT = 1024;  % FFT点数
    H_f = fft(h, NFFT);  % 计算频率响应
    H_f = H_f(1:NFFT/2+1);  % 只取前半部分（到Nyquist频率）

    % 创建频率向量，替代freqz返回的omega
    omega = linspace(0, pi, NFFT/2+1);  % 从0到π的频率向量

    % ----- 4. 图像 -----
    figure;
    subplot(3,1,1);
    stem(k, abs(Hd), 'filled');
    title(['理想频率响应采样点 (N = ', num2str(N), ')']);
    xlabel('k'); ylabel('|H_d(k)|'); grid on;

    subplot(3,1,2);
    stem(0:N-1, h, 'filled');
    title(['滤波器系数 h(n) (N = ', num2str(N), ')']);
    xlabel('n'); ylabel('h(n)'); grid on;

    subplot(3,1,3);
    plot(omega/pi, 20*log10(abs(H_f)+1e-6));  % 幅频响应（dB）
    title(['实际滤波器幅频响应 (N = ', num2str(N), ')']);
    xlabel('\omega / \pi'); ylabel('Magnitude (dB)'); grid on;
    ylim([-100 5]);

    % 在幅频图上添加参考线
    hold on;
    plot([wc/pi wc/pi], [-100 5], 'r--');
    text(wc/pi, 0, '\omega_c', 'Color', 'r', 'HorizontalAlignment', 'left');
    hold off;
end

% 添加一个额外的图，比较两个滤波器
figure;
for idx = 1:length(N_list)
    N = N_list(idx);
    M = (N - 1) / 2;

    k = 0:N-1;
    omega_k = 2 * pi * k / N;
    Hd = double(omega_k <= wc);
    Hd = Hd .* exp(-1j * omega_k * M);
    h = real(ifft(Hd));
    h = 0.5 * (h + fliplr(h));

    NFFT = 1024;
    H_f = fft(h, NFFT);
    H_f = H_f(1:NFFT/2+1);
    omega = linspace(0, pi, NFFT/2+1);

    subplot(2,1,1);
    plot(omega/pi, abs(H_f));
    title('两种阶数滤波器幅频响应比较（线性尺度）');
    xlabel('\omega / \pi'); ylabel('|H(e^{j\omega})|');
    ylim([0 1.2]);
    hold on;

    subplot(2,1,2);
    plot(omega/pi, 20*log10(abs(H_f)+1e-6));
    title('两种阶数滤波器幅频响应比较（dB尺度）');
    xlabel('\omega / \pi'); ylabel('Magnitude (dB)');
    ylim([-100 5]);
    hold on;
end

% 添加图例和垂直线
subplot(2,1,1);
plot([wc/pi wc/pi], [0 1.2], 'r--');
legend(['N = ', num2str(N_list(1))], ['N = ', num2str(N_list(2))], '\omega_c', 'Location', 'best');
hold off;

subplot(2,1,2);
plot([wc/pi wc/pi], [-100 5], 'r--');
legend(['N = ', num2str(N_list(1))], ['N = ', num2str(N_list(2))], '\omega_c', 'Location', 'best');
hold off;



