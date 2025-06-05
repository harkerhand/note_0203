function X = myFFT(x)
% 按时间抽取的基2 FFT算法
N = length(x);
% 位反转置换
X = myBitRevOrder(x);
% 迭代计算FFT
for s = 1:log2(N)
    m = 2^s;
    w_m = exp(-1i * 2 * pi / m);
    for k = 0:m:(N-1)
        for j = 0:(m/2 - 1)
            tw = w_m^j;
            idx1 = k + j + 1;
            idx2 = k + j + m/2 + 1;
            temp = X(idx2) * tw;
            X(idx2) = X(idx1) - temp;
            X(idx1) = X(idx1) + temp;
        end
    end
end
end

function x = myBitRevOrder(x)
% 手动实现位反转排列
N = length(x);
n = log2(N);
indices = 0:N-1;
rev_indices = bin2dec(fliplr(dec2bin(indices, n))) + 1;
x = x(rev_indices);
end