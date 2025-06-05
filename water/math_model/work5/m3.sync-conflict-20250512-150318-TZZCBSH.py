import numpy as np
from scipy import interpolate
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
# 数据
x = np.array([0,30,50,70,80,90,120,148,170,180,202,212,230,248,268,271,280,290,300,312,320,340,360,372,382,390,416,430,478,440,420,380,360,340,320,314,280,240,200])
y = np.array([80,64,47,42,48,66,80,120,121,138,160,182,200,208,212,210,200,196,188,186,200,184,188,200,202,240,246,280,296,308,334,328,334,346,356,360,392,390,400])

# 创建一个时间序列
t = np.arange(len(x))

# 使用三次样条插值
cs = interpolate.CubicSpline(t, np.c_[x, y])

# 生成插值曲线的坐标
t_fine = np.linspace(0, len(x)-1, 500)
x_fine, y_fine = cs(t_fine).T

# 绘制原始数据点和插值曲线
plt.figure(figsize=(10, 6))
plt.scatter(x, y, color='red', label='原始数据点')
plt.plot(x_fine, y_fine, 'b-', label='插值曲线')
plt.title('三次样条插值')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.legend()
plt.axis('equal')  # Equal scaling for x and y
plt.show()

# 计算插值曲线的长度
length = np.sum(np.sqrt(np.diff(x_fine)**2 + np.diff(y_fine)**2))
print('插值曲线的长度为：', length)