a = 0; b = 1;
c = 0; d = 1;
m = 100;
n = 100;

hx = (b - a) / m;
hy = (d - c) / n;


I = 0;

for i = 0:m
    x = a + i * hx;
    wx = 1;
    if i == 0 || i == m
        wx = 0.5;
    end
    for j = 0:n
        y = c + j * hy;
        wy = 1;
        if j == 0 || j == n
            wy = 0.5;
        end
        I = I + wx * wy * exp(-(x + y));
    end
end

I = I * hx * hy;

disp(num2str(I));
