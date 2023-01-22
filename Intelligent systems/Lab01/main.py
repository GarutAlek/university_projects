import random
# random.seed(0)


# Генерация связей
def create_matrix(n, k):
    if k >= n or k <= 1:
        print('uncorrected k')
        exit()
    res = []
    for i in range(n):
        temp_list = [j for j in range(n)]
        list_1 = [0 for j in range(n)]
        temp_list.remove(i)
        count = 0
        while count < k:
            place = random.randint(0, len(temp_list) - 1)
            list_1[temp_list[place]] = 1
            count += 1
            temp_list.pop(place)
        res.append(list_1)
    return res


# Логические функции
# Конъюнкция
def kon(a, b):
    return a*b


# Дизъюнкция
def dis(a, b):
    return (not (a == 0 and b == 0))*1


# Исключающее или
def iskl(a, b):
    return (a + b) % 2


# Эквивалентность
def ekv(a, b):
    return (a == b)*1


# Импликация
def impl(a, b):
    return (not (a == 1 and b == 0))*1


all_functions = [kon, dis, iskl, ekv, impl]


# Генерация функции
def function(k):
    res = []
    for i in range(k - 1):
        res.append(random.choice(all_functions))
    return res


# Найти значение функции
def value(func_list, value_list):
    res = value_list[0]
    for i in range(len(func_list)):
        res = func_list[i](res, value_list[i+1])
    return res


# Проверка наличия этого же аттрактора
def check_uniq(attr, uniq_attr):
    for i in uniq_attr:
        if i in attr:
            return False
    return True


def main():
    n = int(input('input n: '))
    k = int(input('input k: '))
    vect_str = '{{0:0{}b}}'.format(n)
    vect = (vect_str.format(i) for i in range(2 ** n))
    print('Матрица связей:')
    a = create_matrix(n, k)
    for i in range(n):
        print(a[i])
    matrix = []
    for i in range(n):
        tmp = []
        for j in range(n):
            if a[i][j] == 1:
                tmp.append(j)
        matrix.append(tmp)
    print('Матрица функций:')
    func_list = []
    for i in range(n):
        func_list.append(function(k))
        fff = [str(f.__name__) for f in func_list[i]]
        print(f'{i + 1}) {fff}')

    attract_list = []
    len_list = []
    for i in vect:
        print(i)
        prev_vect = i
        vect_list = [prev_vect]
        new_vect = ''
        idx1, idx2 = 0, 0
        while True:
            new_vect = ''
            for j in range(n):
                value_list = []
                for l in range(k):
                    value_list.append(int(prev_vect[matrix[j][l]]))
                new_vect += str(value(func_list[j], value_list))
            print(new_vect)
            if new_vect in vect_list:
                idx1 = vect_list.index(new_vect)
                vect_list.append(new_vect)
                idx2 = vect_list.index(new_vect, idx1 + 1)
                print('Len: ', idx2 - idx1)
                if check_uniq(vect_list[vect_list.index(new_vect):len(vect_list) - 1], attract_list):
                    attract_list.append(new_vect)
                    len_list.append(idx2 - idx1)
                if new_vect not in attract_list:
                    attract_list.append(new_vect)
                break
            prev_vect = new_vect
            vect_list.append(new_vect)
        print('-------------------------------------')
    print('Mean length: ', sum(len_list)/len(len_list))
    print('Different attractors: ', len(attract_list))


if __name__ == '__main__':
    main()
