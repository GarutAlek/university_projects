# Лабораторная работа №4

## Алгоритмы машинного обучения

### Реализовать базовый алгоритм машинного обучения - эволюционный алгоритм.

### Объявите эталонную функцию в виде y(x) = k1*x^3 + k2*x^2 + k3*x + k4. 
### Задайте величины коэффициентов самостоятельно, прямо в программе.

### Далее реализуйте программу, находящую параметры целевой функции по косвенному и по прямому признаку.
### Для этого задавайте с клавиатуры начальные параметры k1, k2, k3, k4, максимальное случайное отклонение параметра d и количество потомков в одном поколении N.

### Далее по начальным параметрам сгенерируйте первое поколение потомков, где каждый параметр случайно отличается от родительского не более чем на d. Проведите оценку потомков по выбранному признаку, выберете потомка, наиболее близкого к эталонной функции, как родителя для следующего поколения.
### Повторяйте генерацию поколений пока позитивное изменение не сократиться до пренебрежимо малых значений.

### В качества косвенного признака сравнивайте определенный интеграл от -100 до 100 у эталонной и проверяемой функции.
### В качества прямого признака считайте расстояние между графиками функций на интервале от -100 до 100.

### В программе выбирайте, по какому из признаков будет проходить проверка.

### Программа должна выводить значение признаков родителя каждого поколения.