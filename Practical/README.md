# Лабораторная работа
## Задание 1. Изучение инструментальной среды имитационного моделирования для исследования характеристик беспроводных сетей стандарта 5G
### Часть 1
Построить матрицу c количеством строк 10 и столбцов 2, переменные заполняются случайными числами с равномерным распределением. Полученные сгенерированные случайные числа представить на графике в виде точек.
### Часть 2
Сгенерировать 1000 случайных чисел с любым известным распределением и построить их гистограмму, математическое ожидание, дисперсию.
### Часть 3
Сгенерировать случайную точку, равномерно распределенную в квадрате со стороной а.
## Задание 2. Методы оценки статических характеристик, связанных с распределением пользователей на плоскости
### Часть 1
Сгенерировать выборку случайных чисел размером 100 и 1000 для двух распределений – экспоненциального и нормального. Для созданных выборок сделать следующее:
1. Посчитать выборочное среднее и дисперсию, сравнить с математическим ожиданием соответствующих распределений;
2. Посчитать 0.5 и 0.99 квантили, сравнить с соответствующими теоретическими значениями;
3. Построить гистограмму распределения;
4. Построить функцию распределения случайной величины на основе выборки (на одном графике показать функции распределения, полученные из выборок разного размера и теоретическую);
5. Построить плотность распределения случайной величины на основе выборки (на одном графике показать плотности распределения, полученные из выборок разного размера и теоретическую).
В итоге проанализировать зависимость точности аппроксимации от количества экспериментов
### Часть 2
Сгенерировать три выборки размера 100, 1000 и 10000 для случайных расстояний между двумя точками, равномерно распределенные в прямоугольнике со сторонами 10 и 30. Получить среднее значение расстояния между точками, построить функцию распределения вероятностей и плотности вероятностей случайных расстояний. Показать разницу между соответствующими функциями на одном графике
## Задание 3. Исследование распределений и моментов связанных с преобразованием случайных величин
### Часть 1
Сгенерировать выборку точек, равномерно распределенных внутри круга двумя способами:
1. Равномерно распределить точки внутри квадрата, внутрь которого вписана окружность, и отфильтровать точки, лежащие за пределами окружности.
2. Генерировать точки путем задания случайного угла и расстояния от центра окружности.
### Часть 2
Радиус окружности R=10, размер выборки 1000 точек.
Для созданных выборок сделать следующее:
1. Создать рисунок, иллюстрирующий расположение точек сгенерированной выборки внутри окружности;
2. Найти выборочные средние координат точек и их дисперсию;
3. Построить график плотности распределения расстояния от случайной равномерно распределенной точки в круге до фиксированной точки, лежащей вне окружности (к примеру, с координатами X=20, Y=0).
4. Построить график плотности распределения расстояния между двумя случайными точками, равномерно расположенными внутри круга.
## Задание 4. Исследование моделей размещения пользователей и распространения сигнала
### Часть 1
Построить согласно описанному ниже алгоритму имитационную модель, позволяющую рассчитать вероятность блокировки линии прямой видимости, и сравнить полученную характеристику с результатами математической модели.
1. В квадратной области со стороной А согласно точечному Пуассоновскому процессу с плотностью q разместить объекты (окружности с фиксированным радиусом r), которые могут заблокировать линию прямой видимости между двумя точками, размещенными на расстоянии x друг от друга внутри обозначенной области. Проверить блокирует ли хотя бы один объект линию прямой видимости.
2. Количество блокирующих объектов определяется согласно распределению Пуассона с параметром qA2, а объекты вбрасываются независимо друг от друга. При этом центры блокирующих объектов должны быть распределены равномерно внутри рассматриваемой области.
3. На основе описанного выше алгоритма получить 1000 реализаций факта блокировки линии прямой видимости и рассчитать вероятность блокировки линии прямой видимости в поле
блокирующих объектов. Полученный результат сравнить с результатами математической модели
## Задание 5. Исследование вероятности экспозиции совместно с вероятностью блокировки на основе модели антенн
### Часть 1
В условиях предыдущего задания №4, на двух точках, между которыми производится проверка прямой видимости, формируется диаграмма направленности, задающаяся вектором направления и углом. Предполагается, что если для обеих из рассматриваемых точек вторая точка лежит внутри сектора, описанного вектором и углом и линия прямой видимости между ними не заблокирована, то точки находятся в области видимости друг друга.
При условии, что направление вектора диаграммы задается случайно равномерно распределенной величиной от 0 до 2Pi, а угол является константой, определить находятся ли рассматриваемые точки в области видимости друг друга.
На основе 1000 реализаций определить вероятность нахождения точек в области видимости друг друга. Полученный результат сравнить с результатами математической модели.
## Задание 6. Построение общей модели на основе случайных полей и статической модели блокировки
### Часть 1
В круге радиуса R, центром которого является целевой приемник, распределены согласно Пуассоновскому равномерному точечному процессу с интенсивностью B интерферирующие устройства. На целевом приемнике расположена всенаправленная антенна, а интерферирующие устройства оборудованы направленными антеннами с углом диаграммы направленности γ. Предполагается, что все антенны сориентированы случайным образом и постоянно излучают сигнал с мощностью P. При этом применяется модель распространения сигнала Cone (аналог модели Free Space Path Loss с поправкой на коэффициент диаграммы направленности). В этом же круге согласно Пуассоновскому равномерному точечному процессу с интенсивностью A распределены блокирующие объекты радиуса D. Для упрощения интерферирующие устройства не считать блокирующими объектами.
В случае если сигнал от интерферирующего передатчика до целевого приемника проходит через блокирующий объект, то он не создает помех на целевом приемнике. Аналогично, если целевой приемник не попадает в сектор диаграммы направленности интерферирующего передатчика, то соответствующий интерферирующий сигнал тоже не создает помех.
На основе полученной модели построить графики среднего значения интерференции как функции от направленности антенн γ, интенсивности Пуассоновского поля источников интерферирующих устройств B, интенсивности Пуассоновского поля блокирующих объектов A. При построении графиков использовать как минимум 1000 реализаций.