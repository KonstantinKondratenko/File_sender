import numpy as np
import matplotlib.pyplot as plt


# def f(x):
#     # желаемые а = 0, b = 5
#     return x**2 - 6*x + 4
# def f(x):
#     # желаемые а = 0.5, b = 2
#     return x**3 - 4*x**2+2*x+3

def ab_validation(a, b):
    if f(a) * f(b) > 0:
        print(f'В точках a и b функция должна иметь разные знаки')
        print(f'Значение точки a : {a} ')
        print(f'Значение f(a) : {f(a)} ')
        print(f'Значение точки b : {b} ')
        print(f'Значение f(b) : {f(b)} ')
        exit(0)


def epsilon_validation(epsilon):
    if epsilon < 0:
        print("Эпсилон должна быть больше 0")
        exit(0)



def f(x):
    global K1, K2, K3, K4, K5, K0
    return K5 * x ** (5) + K4 * x ** (4) + K3 * x ** (3) + K2 * x ** (2) + K1 * x ** (1) + K0


K0 = 0
K1 = 0
K2 = 0
K3 = 0
K4 = 0
K5 = 0


def dichotomy_method(a, b, epsilon):
    input_a = a
    input_b = b
    iterations = 0
    points = []
    while abs(b - a) > epsilon:
        iterations += 1
        c = (a + b) / 2
        if f(c) == 0:
            break
        elif f(a) * f(c) < 0:
            b = c
        else:
            a = c
        points.append((c, f(c)))
        x = np.linspace(input_a, input_b, 100)
        y = f(x)

        plt.plot(x, y)
        plt.axhline(0, color='black', linewidth=0.5)

        plt.plot(a, f(a), color='green', marker='v')
        plt.text(a, f(a), 'a')
        plt.plot(b, f(b), color='brown', marker='v')
        plt.text(b, f(b), 'b')
        print(f'\nИтерация {iterations}\n\tЗначения а = {a}\n\tЗначение f(a) = {f(a)}')
        print(f'\n\tЗначения b = {b}\n\tЗначение f(b) = {f(b)}')
        print(f'\n\tВыбираем с = {c}\n')

        if iterations > 1:
            i = iterations - 1
            plt.annotate(f'шаг {iterations}', xy=(points[i][0], points[i][1]), xycoords='data',
                         xytext=(points[i - 1][0], points[i - 1][1]), textcoords='data',
                         arrowprops=dict(facecolor='g'))
            # plt.annotate(f'шаг {iterations}', xy=(points[i][1], points[i][1]))
            # plt.plot([points[i-1][0], points[i][0]], [points[i-1][1], points[i][1]], 'r-')

        for p in points:
            plt.plot(p[0], p[1], )

        plt.xlabel('x')
        plt.ylabel('f(x)')
        plt.title('Function and its root found by Dichotomy Method')
        plt.grid(True)
        plt.show()

        # cont = input("Do you want to continue? (anything/n): ")
        # if cont.lower() == 'n':
        #     break

    return c, iterations, points


if __name__ == "__main__":
    deg = int(input("Какой степени будет ваша функция [введите число от 2 до 5]? : "))
    if deg == 2:
        K2 = float(input("\n Введите значение коэффициента при x^2 : "))
        K1 = float(input("\n Введите значение коэффициента при x : "))
        K0 = float(input("\n Введите значение свободного члена : "))
        print(f'Введенная функция: {K2}x^2 + {K1}x + {K0} ')
    elif deg == 3:
        K3 = float(input("\n Введите значение коэффициента при x^3 : "))
        K2 = float(input("\n Введите значение коэффициента при x^2 : "))
        K1 = float(input("\n Введите значение коэффициента при x : "))
        K0 = float(input("\n Введите значение свободного члена : "))
    elif deg == 4:
        K4 = float(input("\n Введите значение коэффициента при x^4 : "))
        K3 = float(input("\n Введите значение коэффициента при x^3 : "))
        K2 = float(input("\n Введите значение коэффициента при x^2 : "))
        K1 = float(input("\n Введите значение коэффициента при x : "))
        K0 = float(input("\n Введите значение свободного члена : "))
    elif deg == 5:
        K5 = float(input("\n Введите значение коэффициента при x^5 : "))
        K4 = float(input("\n Введите значение коэффициента при x^4 : "))
        K3 = float(input("\n Введите значение коэффициента при x^3 : "))
        K2 = float(input("\n Введите значение коэффициента при x^2 : "))
        K1 = float(input("\n Введите значение коэффициента при x : "))
        K0 = float(input("\n Введите значение свободного члена : "))
    else:
        print("Вы ввели неправильно значение степени функции")
        exit(0)

    a = float(input("\n Введите значение а : "))
    b = float(input("\n Введите значение b : "))
    ab_validation(a, b)
    epsilon = float(input("\n Введите значение epsilon : "))
    epsilon_validation(epsilon)

    root, iterations, points = dichotomy_method(a, b, epsilon)
    print("Root found at:", root)
    print("Number of iterations:", iterations)
