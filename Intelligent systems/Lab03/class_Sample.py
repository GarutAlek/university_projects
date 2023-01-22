import numpy as np
import matplotlib.pyplot as plt
import os


class Sample:
    max_distance = 4
    classes = {}
    count_of_classes = 0

    def __init__(self, matrix):
        self.matrix = np.array(matrix)
        self.vector = [i for j in matrix for i in j]
        self.vector = np.array(self.vector, dtype=float)
        if Sample.count_of_classes == 0:
            Sample.classes[f'class{0}'] = {'core': self.vector, 'elements': [self.vector]}
            self.class_number = Sample.count_of_classes
            Sample.count_of_classes += 1
        else:
            distances = self.mahal_eucluid()
            if min(distances) > Sample.max_distance:
                Sample.classes[f'class{Sample.count_of_classes}'] = {'core': self.vector, 'elements': [self.vector]}
                self.class_number = Sample.count_of_classes
                Sample.count_of_classes += 1
            else:
                self.update_class(distances.index(min(distances)))

    def update_class(self, chosen_class):
        '''
        Заносим вектор в выбранный класс;

        перерассчитываем ядро
        '''

        Sample.classes[f'class{chosen_class}']['elements'].append(self.vector)

        core_vector = (Sample.classes[f'class{chosen_class}']['core'] * (len(Sample.classes[f'class{chosen_class}']['elements']) - 1) + self.vector) / len(Sample.classes[f'class{chosen_class}']['elements'])

        Sample.classes[f'class{chosen_class}']['core'] = core_vector
        self.class_number = chosen_class

    def show_matrix(self, dir, number_of_picture):
        '''
        Отрисовывает матрицу и помещает изображение в dir с именем number_of_picture.png
        '''
        os.chdir(dir)
        plt.imshow(self.matrix)
        plt.title(f"class #{self.class_number}")
        plt.savefig(f"{number_of_picture}.png")

    def mahal_eucluid(self):
        '''
        Считает расстояния от вектора до всех классов
        '''
        results = []

        for number in range(Sample.count_of_classes):
            vector_dif = self.vector - Sample.classes[f'class{number}']['core']
            if len(Sample.classes[f'class{number}']['elements']) == 1:
                cov_mat = np.eye(len(self.vector))
            else:
                cov_mat = [[0] * len(self.vector) for i in range(len(self.vector))]
                for i in range(len(self.vector)):
                    for j in range(len(self.vector)):
                        cov = 0
                        if i > j:
                            cov_mat[i][j] = cov_mat[j][i]
                        else:
                            for k in range(len(self.vector)):
                                cov += (self.vector[k] - Sample.classes[f'class{number}']['core'][i]) * (self.vector[k] - Sample.classes[f'class{number}']['core'][j])
                            cov_mat[i][j] = cov / (len(Sample.classes[f'class{number}']['elements']) - 1)
                cov_mat = np.array(cov_mat, dtype=float)
                cov_mat += np.eye(len(cov_mat))  # Добавляем единичную матрицу
                cov_mat = np.linalg.inv(cov_mat)  # Считаем обратную матрицу
            res = np.sqrt(np.dot(np.dot(np.transpose(vector_dif), cov_mat), vector_dif))
            results.append(res)
        return results