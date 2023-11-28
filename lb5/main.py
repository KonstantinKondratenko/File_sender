import matplotlib.pyplot as plt


class FileReader_n:
    def __init__(self, input_filename):
        self.__input_filename = input_filename

    def read_data(self) -> list:
        data = []
        with open(self.__input_filename, "r") as file:
            for line in file:
                proc_info = {}
                proc_info['num_proc'], proc_info['time'] = int(line.split()[1]), float(line.split()[2])
                data.append(proc_info)
        return data

class FileReader:
    def __init__(self, input_filename):
        self.__input_filename = input_filename

    def read_data(self) -> list:
        data = []
        with open(self.__input_filename, "r") as file:
            for line in file:
                proc_info = {}
                proc_info['num_proc'], proc_info['time'] = int(line.split()[0]), float(line.split()[1])
                data.append(proc_info)
        return data


def plot_process_time(x, y):
    plt.figure(figsize=(10, 5))
    plt.title('График зависимости времени выполнения от кол-ва пар. запущенных процессов')
    plt.xlabel('n - количество процессов')
    plt.ylabel('Время выполнения, микросекунды')
    plt.grid()
    plt.plot(x, y, marker='o')
    # plt.show()
    plt.savefig('time.jpg')


def plot_process_deceleration(x, y):
    plt.figure(figsize=(10, 5))
    plt.title('График замедления (или ускорения) выполнения программы от кол-ва процессов')
    plt.xlabel('n - количество процессов')
    plt.ylabel('Замедление выполнения')
    plt.grid()
    plt.plot(x, y, marker='o')
    # plt.show()
    plt.savefig('deceleration.jpg')


if __name__ == "__main__":
    # dn = FileReader_n("result_50.txt")
    # dn = FileReader_n("result_100.txt")
    # dn = FileReader_n("result_1000.txt")
    # dn = FileReader_n("result_10000.txt")
    # dn = FileReader_n("result_100000.txt")
    # dn = FileReader_n("result_1000000.txt")

    d =  FileReader("result.txt")

    datan = d.read_data()
    print(f"{datan}")
    x = [proc_info['num_proc'] for proc_info in datan]
    y = [proc_info['time'] for proc_info in datan]
    print(f"x: {x}")
    print(f"y: {y}")
    plot_process_time(x, y)
    y = list(map(lambda time: y[0] / time, y))
    plot_process_deceleration(x, y)
