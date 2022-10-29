from structures import DynamicArray


def timsort(arr: DynamicArray):
    n = len(arr)
    # Шаг 0. Вычисление minrun
    minrun = get_minrun(n)

    # Шаг 1. Разбиение на подмассивы и их сортировка
    for start in range(0, n, minrun):
        end = min(start + minrun - 1, n - 1)
        insertion_sort(arr, start, end)

    # Шаг 2. Слияние
    size = minrun
    while size < n:
        for left in range(0, n, 2 * size):
            mid = min(n - 1, left + size - 1)
            right = min((left + 2 * size - 1), (n - 1))
            if mid < right:
                merge(arr, left, mid, right)
        size = 2 * size


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


def merge(arr: DynamicArray, l: int, m: int, r: int):
    len1, len2 = m - l + 1, r - m
    left, right = [], []
    for i in range(0, len1):
        left.append(arr[l + i])
    for i in range(0, len2):
        right.append(arr[m + 1 + i])

    max_count = 2
    left_count = 0
    right_count = 0
    i, j, k = 0, 0, l
    while i < len1 - 1 and j < len2 - 1:
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

            while i < len1:
                i = i + (2 ** n)
                if i < len1 and left[i] <= right[j]:
                    n += 1
                else:
                    i = i - (2 ** n)
                    break

            for m in range(start, i):
                arr[k] = left[m]
                k += 1

        if right_count >= max_count:
            left_count = 0
            right_count = 0
            start = j
            n = 1

            while j < len2:
                j = j + (2 ** n)
                if j < len2 and right[j] <= left[i]:
                    n += 1
                else:
                    j = j - (2 ** n)
                    break

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