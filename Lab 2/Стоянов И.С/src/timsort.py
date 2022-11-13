from structures import DynamicArray
from dataclasses import dataclass


# Использую просто чтобы можно было удобно и красиво хранить инфу о ранах
@dataclass
class Run:
    start: int
    end: int
    size: int


def timsort(arr: DynamicArray):
    n = len(arr)


    # Шаг 0. Вычисление minrun
    minrun = get_minrun(n)

    # Шаг 1. Разбиение на подмассивы и их сортировка
    i = 0
    start = 0
    size = 0
    runs = []
    is_desc = False

    while i < n:
        if size == 0:
            if i == n - 1:
                start = i
                size += 1
                runs.append(Run(start=start, end=i, size=size))
                break
            else:
                if arr[i] > arr[i+1]:
                    is_desc = True
                start = i
                size += 2
                i += 2

        if not is_desc:
            if arr[i] > arr[i-1]:
                size += 1
                i += 1
                continue
            else:
                if size < minrun:
                    delta = minrun - size
                    if i + delta >= n:
                        delta = n - i - 1

                    size += delta
                    i += delta

                insertion_sort(arr, start, start + size)

                runs.append(Run(start=start, end=i, size=size + 1))
                i += 1
                start = 0
                size = 0
                is_desc = False
                continue
        else:
            if arr[i] < arr[i-1]:
                size += 1
                i += 1
                continue
            else:
                reverse(arr, start, start + size)
                if size < minrun:
                    delta = minrun - size
                    if i + delta >= n:
                        delta = n - i - 1

                    size += delta
                    i += delta
                insertion_sort(arr, start, start + size)

                runs.append(Run(start=start, end=i, size=size + 1))
                i += 1
                start = 0
                size = 0
                is_desc = False
                continue

    # Шаг 2. Слияние

    if len(runs) > 2:
        x, y, z = runs[0], runs[1], runs[2]
        while not ((z.size > x.size + y.size) and (y.size > x.size)):
            if len(runs) >= 2 and y.size <= x.size:
                merge(arr, x.start, x.end, y.start, y.end)
                x.size += y.size
                x.end = y.end
                y = z
                del runs[1]
                try:
                    z = runs[2]
                except IndexError:
                    break

            if len(runs) >= 3 and z.size <= x.size + y.size:
                if x.size <= z.size:
                    merge(arr, x.start, x.end, y.start, y.end)
                    x.size += y.size
                    x.end = y.end
                    y = z
                    del runs[1]
                    try:
                        z = runs[2]
                    except IndexError:
                        break
                else:
                    merge(arr, y.start, y.end, z.start, z.end)
                    y.size += z.size
                    y.end = z.end
                    del runs[2]

                    try:
                        z = runs[2]
                    except IndexError:
                        break

    if len(runs) == 2:
        x, y = runs[0], runs[1]
        merge(arr, x.start, x.end, y.start, y.end)


def reverse(arr: DynamicArray, left: int, right: int):
    size = right - left
    for i in range(0, size // 2 + 1):
        arr.swap(left + i, right - i)


def insertion_sort(arr: DynamicArray, left: int, right: int):
    for i in range(left + 1, right + 1):
        j = i
        while j > left and arr[j] < arr[j - 1]:
            arr.swap(j, j - 1)
            j -= 1


def get_minrun(n: int) -> int:
    r = 0
    while n >= 64:
        r |= n & 1
        n >>= 1
    return n + r


def merge(arr: DynamicArray, start1: int, end1: int, start2: int, end2: int):
    left, right = [], []
    for i in range(start1, end1 + 1):
        left.append(arr[i])
    for i in range(start2, end2 + 1):
        right.append(arr[i])

    len1, len2 = len(left), len(right)

    max_count = 2
    left_count = 0
    right_count = 0
    i, j, k = 0, 0, min(start1, start2)
    while i < len1 and j < len2:
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
            left_count += 1
            right_count = 0
        else:
            arr[k] = right[j]
            j += 1
            right_count += 1
            left_count = 0
        k += 1

        if left_count >= max_count:
            left_count = 0
            right_count = 0
            start = i
            n = 1
            stop_gallop = False

            while i < len1 and not stop_gallop:
                old_i = i
                i = i + (2 ** n)
                if i >= len1:
                    i = len1 - 1
                    stop_gallop = True

                if i < len1 and left[i] <= right[j]:
                    n += 1
                else:
                    i = old_i
                    stop_gallop = True

            for m in range(start, i):
                arr[k] = left[m]
                k += 1

        if right_count >= max_count:
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

    while i < len1:
        arr[k] = left[i]
        k += 1
        i += 1

    while j < len2:
        arr[k] = right[j]
        k += 1
        j += 1
