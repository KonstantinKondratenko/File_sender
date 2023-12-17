import matplotlib.pyplot as plt

class dot:
    def __init__(self, val, n):
        self.val = val
        self.n = n
        self.times = [0] * n
        self.res = None

def read(name):
    data = []
    with open(name, "r") as file:
                for line in file:
                    proc_info = {}
                    proc_info['num_proc'], proc_info['time'] = int(line.split()[0]), float(line.split()[1])
                    data.append(proc_info)
    # print(data)
    return data

vals = read('result_no_cache.txt')
degs = [1, 4, 9, 25]
dots = []
for deg in degs:
    dot1 = dot(deg, 5)
    print(dot1.val)
    dots.append(dot1)

    

dots[0].times = [7493.12, 7650.56, 9398.63, 7294.7, 13187.5]
dots[1].times = [6897.47, 7478.44, 10863.7, 7912.3, 10189.6]
dots[2].times = [9896.87, 23116.1, 13990.8, 20934.8, 7714.55]
dots[3].times = [239258.0, 260426.0, 237563.0, 149217.0, 199927.0]

for i in range (4):
    dots[i].res = round(sum(dots[i].times) / len(dots[i].times), 3)
    print(f"{dots[i].val} : {dots[i].res}")


plt.figure(figsize=(10, 5))
plt.title('График времени работы')
plt.xlabel('n - количество процессов')
plt.ylabel('Время выполнения, микросекунды')
plt.grid()
y = [dots[i].res for i in range(4)]
x = [dots[i].val for i in range(4)]
plt.plot(x, y, marker='o')
# plt.show()
plt.savefig('time.jpg')



plt.figure(figsize=(10, 5))
plt.title('График времени работы')
plt.xlabel('n - количество процессов')
plt.ylabel('Время выполнения, микросекунды')
plt.grid()
y = [dots[i].res for i in range(3)]
x = [dots[i].val for i in range(3)]
plt.plot(x, y, marker='o')
# plt.show()
plt.savefig('time3.jpg')



plt.figure(figsize=(10, 5))
plt.title('График ускорения')
plt.xlabel('n - количество процессов')
plt.ylabel('Время выполнения, микросекунды')
plt.grid()
y = [dots[0].res / dots[i].res for i in range(4)]
x = [dots[i].val for i in range(4)]
plt.plot(x, y, marker='o')
# plt.show()
plt.savefig('dec.jpg')



plt.figure(figsize=(10, 5))
plt.title('График ускорения')
plt.xlabel('n - количество процессов')
plt.ylabel('Время выполнения, микросекунды')
plt.grid()
y = [dots[0].res / dots[i].res for i in range(3)]
x = [dots[i].val for i in range(3)]
plt.plot(x, y, marker='o')
# plt.show()
plt.savefig('dec3.jpg')


