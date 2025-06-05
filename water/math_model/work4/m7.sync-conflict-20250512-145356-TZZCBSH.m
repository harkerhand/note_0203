function y = f(x)
y = exp(1) ^ (-x ^ 2);
end

function y = sipson(f, a, b, m)
n = 2 * m;
h = (b - a) / n;
sum1 = 0;
for i=0:m-1
    sum1 = sum1 + f(a + (2 * i + 1) * h);
end
sum2 = 0;
for i=1:m-1
    sum2 = sum2 + f(a + 2 * i * h);
end

y = h / 3 * (f(a) + f(b) + 4 * sum1 + 2 * sum2);

end

out = sipson(@f, 0, 10, 10);
disp(out);

