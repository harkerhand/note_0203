import numpy as np
from scipy.optimize import minimize

# 定义测试函数
def rastrigin(x):
    return 10 * len(x) + sum(xi**2 - 10 * np.cos(2 * np.pi * xi) for xi in x)

def ackley(x):
    a, b, c = 20, 0.2, 2*np.pi
    x = np.array(x)
    d = len(x)
    return -a * np.exp(-b * np.sqrt(sum(x**2) / d)) - np.exp(sum(np.cos(c*x)) / d) + a + np.exp(1)

def beale(x):
    x1, x2 = x
    return (1.5 - x1 + x1*x2)**2 + (2.25 - x1 + x1*x2**2)**2 + (2.625 - x1 + x1*x2**3)**2

def booth(x):
    x1, x2 = x
    return (x1 + 2*x2 - 7)**2 + (2*x1 + x2 - 5)**2

def levy(x):
    w = [(xi - 1) / 4 + 1 for xi in x]
    term1 = np.sin(np.pi * w[0])**2
    term3 = (w[-1] - 1)**2 * (1 + np.sin(2 * np.pi * w[-1])**2)
    term2 = sum((w_i - 1)**2 * (1 + 10 * np.sin(np.pi * w_i + 1)**2) for w_i in w[:-1])
    return term1 + term2 + term3

# 测试函数配置
functions = [
    ("Rastrigin", rastrigin, [0, 0], [0, 0]),
    ("Ackley", ackley, [2, 2], [0, 0]),
    ("Beale", beale, [1, 1], [3, 0.5]),
    ("Booth", booth, [0, 0], [1, 3]),
    ("Levy", levy, [0, 0], [1, 1])
]

# 执行优化
results = []
for name, func, x0, true_min in functions:
    res = minimize(func, x0, method='L-BFGS-B')
    results.append((name, res.fun, res.x, true_min, np.linalg.norm(res.x - true_min)))

# 输出结果
for name, val, x_opt, x_true, err in results:
    print(f"\n{name} Function:")
    print(f"  Found Min Value: {val:.6f}")
    print(f"  Found Point:     {x_opt}")
    print(f"  True Point:      {x_true}")
    print(f"  Distance to True: {err:.6e}")