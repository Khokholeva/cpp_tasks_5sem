import matplotlib.pyplot as plt

a = open("gauss_times_d.txt").readlines()
n = int(a[0])
data = [list(map(float, s.split())) for s in a[1:]]
x = [el[0] for el in data]
y_for = [el[3] for el in data]
y_low = [el[4] for el in data]
plt.scatter(x, y_for, color='red', label="Параллельно for", s=2)
plt.scatter(x, y_low, color='blue', label="Пфраллельно низкого уровня", s=2)
plt.legend()
plt.savefig("gauss_d.png")
plt.show()

