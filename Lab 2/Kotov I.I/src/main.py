def reverse(arr, left, right):  # в разбиении на runs
    for i in range((right - left) // 2 + 1):
        tmp = arr[left + i]
        arr[left + i] = arr[right - i]
        arr[right - i] = tmp


def tim_sort(arr):
    length = len(arr)
    min_run = get_minrun(length)

    start = 0
    runs = []

    # Разбиение на runs
    while start + 1 < length:  # Шаг 5. Если конец входного массива не достигнут — переход к шагу 1.
        size = 0
        if arr[start] <= arr[start + 1]:  # Шаг 1. по возрастанию - все норм, сортируем вставками
            # Шаг 2. Если размер текущего run меньше minrun, тогда выбираются следующие за найденным подмассивом run элементы в количестве  minrun−size(run).
            # На выходе - подмассив размером большим или равным minrun, часть которого (в лучшем случае — он весь) упорядочена.
            while start + size + 1 < length and (size <= min_run or arr[start + size] <= arr[start + size + 1]):  # нахожу границу будущего рана
                size += 1

        else:  #  Шаг 1. по убыванию => reverse
            while start + size + 1 < length and (size <= min_run or arr[start + size] >= arr[start + size + 1]):  # аналогично, но с реверсом
                size += 1

            reverse(arr, start, start + size)

        insertion_sort(arr, start, start + size) # Шаг 3. К данному подмассиву применяем сортировку вставками. Так как размер подмассива невелик и часть его уже упорядочена — сортировка работает эффективно.
        runs.append([start, size])  # теперь будем знать начало и конец каждого рана, чтобы эффективное слияние сделать
        start += size + 1  # Шаг 4. Указатель текущего элемента ставится на следующий за подмассивом элемент.

    # Слияние. Идея: объединять подмассивы примерно равного размера и cохранять стабильность алгоритма
    while len(runs) > 1:
        if len(runs) == 2:  # (если интервалов меньше трёх, проверяем лишь условия с оставшимися интервалами).
            merge_sort(arr, runs[0][0], runs[0][0] + runs[0][1], runs[1][0], runs[1][0] + runs[1][1])
            return arr
        offset = 0

        # Пусть X,Y,Z — длины верхних трех интервалов, которые лежат в стеке. Причем X — это последний элемент стека
        # X - runs[2 + offset][1], Y - runs[1 + offset][1], Z - runs[offset][1]
        while len(runs) > 2 + offset:
            # Шаг 4. Повторяем пока выражение (Z>X+Y∧Y>X) ЛОЖНО
            # 4.1 Если размер стека не меньше 2 и Y⩽X — сливаем X c Y
            if runs[1 + offset][1] <= runs[2 + offset][1]:
                merge_sort(arr, runs[1 + offset][0], sum(runs[1 + offset]), runs[2 + offset][0], sum(runs[2 + offset]))
                runs[1 + offset][1] += runs[2 + offset][1] + 1
                runs.pop(2 + offset)

            # 4.2 Если размер стека не меньше 3 и Z⩽X+Y — сливаем Y c min(X,Z).
            if len(runs) >= 3 + offset and runs[offset][1] <= runs[1 + offset][1] + runs[2 + offset][1]:
                if runs[2 + offset][1] > runs[offset][1]:  # X > Z
                    merge_sort(arr, runs[offset][0], runs[offset][0] + runs[offset][1], runs[1 + offset][0], runs[1 + offset][0] + runs[1 + offset][1])
                    runs[offset][1] += runs[1 + offset][1] + 1
                    runs.pop(1 + offset)
                else:  # X < Z
                    merge_sort(arr, runs[1 + offset][0], runs[1 + offset][0] + runs[1 + offset][1], runs[2 + offset][0], runs[2 + offset][0] + runs[2 + offset][1])
                    runs[1 + offset][1] += runs[2 + offset][1] + 1
                    runs.pop(2 + offset)
                offset += 1
            offset += 1

    return arr


def insertion_sort(arr, left, right):
    for i in range(left + 1, right + 1):
        j = i
        while j > left and arr[j] < arr[j - 1]:
            arr[j], arr[j - 1] = arr[j - 1], arr[j]
            j -= 1


def merge_sort(arr, start1, end1, start2, end2):
    left, right = [], []
    for i in range(start1, end1 + 1):
        left.append(arr[i])
    for i in range(start2, end2 + 1):
        right.append(arr[i])

    len1, len2 = len(left), len(right)

    max_count, left_count, right_count = 2, 0, 0
    i, j, k = 0, 0, min(start1, start2)

    while i < len1 and j < len2:  # пока один из массивов не закончится
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
            left_count += 1  # для того, чтобы понять, сколько раз подряд было взято с каждого под массива
            right_count = 0
        else:
            arr[k] = right[j]
            j += 1
            right_count += 1
            left_count = 0
        k += 1

        # Шаг 2. Если уже некоторое количество элементов было взято из одного и того же массива — предполагается редполагается, что и дальше придётся брать данные из него.
        if left_count >= max_count:  # про левый
            left_count = 0  # обнуление для начала галопа
            right_count = 0
            start = i  # запоминаем место, с которого стартуем галоп
            n = 1
            stop_gallop = False

            while i < len1 and not stop_gallop:  # бежим по левому подмассиву до конца
                old_i = i  # запоминаем место, с которого прыгаем
                i = i + (2 ** n)  # прыжок по формуле
                if i >= len1:  # если за пределы вышли, то на ласт эл-т массива, и конец галопа
                    i = len1 - 1
                    stop_gallop = True

                if i < len1 and left[i] <= right[j]:  # все норм - идем дальше, увеличивая прыжок
                    n += 1
                else:  # если не норм, то возврат назад на место, с которого прыгали
                    i = old_i
                    stop_gallop = True

            for m in range(start, i):  # копирование эл-тов галопа с момента старта галопа до место краша
                arr[k] = left[m]
                k += 1

        if right_count >= max_count:  # все то же самое для правого подмассива
            left_count = 0
            right_count = 0
            start = j
            n = 1
            stop_gallop = False

            while j < len2 and not stop_gallop:
                old_j = j
                j = j + (2 ** n)
                if j >= len2:
                    j = len2 - 1
                    stop_gallop = True

                if j < len2 and right[j] <= left[i]:
                    n += 1
                else:
                    j = old_j
                    stop_gallop = True

            for m in range(start, j):
                arr[k] = right[m]
                k += 1

    # копирование остатка
    while i < len1:
        arr[k] = left[i]
        k += 1
        i += 1

    while j < len2:
        arr[k] = right[j]
        k += 1
        j += 1


def get_minrun(n):
    flag = 0
    while n >= 64:
        flag |= n & 1
        n >>= 1

    return n + flag


import random
array_ = []
for nn in range(700):
    array_.append(random.randint(1, 777))

#print(f'input {array_}')
print(f'sorted {tim_sort(array_)}')