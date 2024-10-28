import matplotlib.pyplot as plt

a = open("gauss_times_a.txt").readlines()
n = int(a[0])
data = [list(map(float, s.split())) for s in a[1:]]
x = [el[0] for el in data]
y_base = [el[1] for el in data]
y_sect = [el[2] for el in data]
y_for = [el[3] for el in data]
y_low = [el[4] for el in data]
plt.scatter(x, y_base, color='black', label="Последовательно", s=1)
plt.scatter(x, y_sect, color='red', label="Параллельно, 2 секции", s=1)
plt.scatter(x, y_for, color='green', label="Параллельно for", s=1)
plt.scatter(x, y_low, color='blue', label="Пфраллельно низкого уровня", s=1)
plt.legend()
plt.savefig("gauss_a.png")
plt.show()

