import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 拟合大气压强与高度的关系
# 1. 数据
# 高度
h = np.array([0, 300, 600, 1000, 1500, 2000])
# 大气压强
p = np.array([0.9689, 0.9322, 0.8969, 0.8519, 0.7989, 0.7491])

# 2. 拟合
# 指数拟合
# p = exp(a + b * h)
# ln(p) = a + b * h
# y = ln(p), x = h
y = np.log(p)
x = h
# 求解线性方程
A = np.vstack([x, np.ones(len(x))]).T
b, a = np.linalg.lstsq(A, y, rcond=None)[0]

# 理论公式
# P = 1.0332 * e ^ - (x + 500)/7756

# 计算每隔100m的压强值，并与理论公式比较
h_dense = np.arange(0, 2001, 100)  # 0到2000米，每隔100米

# 拟合模型计算的压强值
p_fit = np.exp(b * h_dense + a)

# 理论模型计算的压强值
p_theory = 1.0332 * np.exp(-(h_dense + 500) / 7756)

# 创建结果表格
results = np.column_stack((h_dense, p_fit, p_theory, np.abs(p_fit - p_theory)))
print("\n高度(m)  拟合值    理论值    差值")
print("------------------------------")
for row in results:
    print(f"{int(row[0]):4d}    {row[1]:.4f}  {row[2]:.4f}  {row[3]:.4f}")

# 计算均方误差
mse = np.mean((p_fit - p_theory)**2)
print(f"\n均方误差: {mse:.6f}")

# 可视化拟合结果与理论模型的对比
plt.figure(figsize=(10, 6))
plt.plot(h, p, 'o', label='原始数据点', markersize=8)
plt.plot(h_dense, p_fit, 'r-', label='拟合模型')
plt.plot(h_dense, p_theory, 'g--', label='理论模型')
plt.xlabel('高度 h (m)')
plt.ylabel('压强 p')
plt.title('压强与高度关系：拟合模型与理论模型对比')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.show()