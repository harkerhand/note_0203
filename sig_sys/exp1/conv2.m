clear; clc;

% 定义矩阵
A = [0 1 0;
    1 1 1;
    0 1 0];

% 自身卷积
B = conv2(A, A);

% 显示结果
disp('卷积结果：');
disp(B);

% 可视化
figure;
[rows, cols] = size(B);
hold on;
imagesc(B);
colorbar;
for i = 1:rows
    for j = 1:cols
        text(j, i, num2str(B(i,j)), 'HorizontalAlignment', 'center', 'Color', 'k');
    end
end
title('卷积结果');
axis equal tight;
hold off;
