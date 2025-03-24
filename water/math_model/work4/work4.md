## 6

**公式**：


$$
\int_{a}^{b} f(x) \, dx \approx \frac{h}{3} \left[ f(x_0) + 4 \sum_{\text{odd}} f(x_i) + 2 \sum_{\text{even}} f(x_i) + f(x_n) \right]
$$

**代码**:

```matlab
function y = f(x)
y = 1 / ((1 + x^2) * x ^ 2);
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

out = sipson(@f, 1, sqrt(3), 10000);
disp(out);
```

**运行结果**：

```text
>> m6
    0.1609
```

## 7

**近似公式**：

$$
\int_{a}^{+\infty} f(x) \, dx \approx \int_{a}^{L} f(x) \, dx
$$
其中，L足够大使f(L)足够小 且 f(x) 趋近于0

**代码**：

```matlab
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
```

**运行结果**：

```text
>> m7
    0.8862
```

## 8

**公式：**

将区间 `[a, b]` 和 `[c, d]` 分别划分为 $ m $ 和 $ n $ 个小区间。

步长：

$$
h_x = \frac{b - a}{m}, \quad h_y = \frac{d - c}{n}
$$

公式为：

$$
I \approx h_x h_y \sum_{i=0}^{m} \sum_{j=0}^{n} w_i w_j f(x_i, y_j)
$$

其中：

- $ x_i = a + i h_x $
- $ y_j = c + j h_y $
- **权重 $ w_i, w_j = 0.5 $ 当 $ i = 0 $ 或 $ i = m $，其余为 1**

**代码**：

```matlab
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
```

**运行结果**：

```text
>> m8
    0.39958
```