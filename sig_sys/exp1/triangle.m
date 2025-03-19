function yanghui_triganle(n)
triangle = zeros(n, n);
for i = 1:n
    for j = 1:i
        if j== 1 || j == i
            triangle(i, j) = 1;
        else
            triangle(i, j) = triangle(i-1, j-1) + triangle(i-1, j);
        end
    end
end

for i = 1:n
    % 前导空格
    fprintf(repmat(' ',1 , n - i));
    for j = 1:i
        fprintf('%d ', triangle(i, j));
    end
    fprintf('\n');
end
end

yanghui_triganle(10)