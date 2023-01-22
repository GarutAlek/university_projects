import json
import os

from class_Sample import Sample


def main():
    with open('input.json', 'r', encoding='utf-8') as f:
        input = json.loads(f.read())

    samples_list = []
    res = {}
    for i in range(len(input)):
        samples_list.append(Sample(input[i]))
        k = samples_list[i].class_number
        try:
            res[str(k)].append(samples_list[i])
        except:
            res[str(k)] = [samples_list[i]]

    dir = f"{os.getcwd()}\output"

    try:
        os.mkdir(dir)
    except:
        pass

    for i in res:
        new_dir = f"{dir}\class{i}"

        try:
            os.mkdir(new_dir)
        except:
            pass

        for j in range(len(res[i])):
            res[i][j].show_matrix(new_dir, j)


if __name__ == '__main__':
    main()