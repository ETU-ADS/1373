"""Командная сортировка"""
__author__ = "Golov Oleg"


def minrun_calc(n) -> int:
    minrun = 0
    while n >= 64:
        minrun |= n & 1
        n >>= 1
    return minrun + n


def bin_search(array, n) -> int:
    if array[0] <= array[-1]:
        low = 0
        high = len(array) - 1
        mid = high // 2
        while low != high:
            if array[mid] <= n <= array[mid + 1]:
                return mid + 1
            elif n > array[mid]:
                low = mid
                mid = (low + high) // 2

            elif n < array[mid]:
                high = mid
                mid = (low + high) // 2

            elif n == array[mid]:
                return mid
    else:
        high = 0
        low = len(array) - 1
        mid = low // 2
        while low != high:
            if array[mid] >= n >= array[mid + 1]:
                return mid + 1
            elif n > array[mid]:
                low = mid
                mid = (low + high) // 2

            elif n < array[mid]:
                high = mid
                mid = (low + high) // 2

            elif n == array[mid]:
                return mid

    return mid


def ins_sort(array, start, end):
    exp = array[end]
    point = bin_search(array[start:end], array[end])
    if array[start] <= array[end - 1]:
        for i in range(end, start + point, -1):
            array[i] = array[i - 1]
    else:
        for i in range(end, start + point, -1):
            array[i] = array[i - 1]
    array[start + point] = exp


def reversing(array, start, end):
    for i in range((end - start) // 2 + 1):
        array[start + i], array[end - i] = array[end - i], array[start + i]


def merging(array, left, mid, right):
    lp, rp = left, mid
    tmparr = [0] * (right - left + 1)
    lgallop_flag = 0
    rgallop_flag = 0
    k = 0
    while k < right - left + 1:
        if lp < mid and rp == right + 1:
            while lp < mid:
                tmparr[k] = array[lp]
                lp += 1
                k += 1
            break
        elif rp < right + 1 and lp == mid:
            while rp < right + 1:
                tmparr[k] = array[rp]
                rp += 1
                k += 1
            break
        elif array[lp] < array[rp]:
            rgallop_flag = 0
            tmparr[k] = array[lp]
            lgallop_flag += 1
            if lgallop_flag == 7:  # gallop
                gal = 1
                while lp + gal * 2 < mid - left and array[lp + gal * 2] < array[rp]:
                    gal *= 2
                for i in range(1, gal + 1):
                    tmparr[k + i] = array[lp + i]
                k += gal - 1
                lp += gal - 1
            lp += 1
        else:
            lgallop_flag = 0
            tmparr[k] = array[rp]
            rgallop_flag += 1
            if rgallop_flag == 7:  # gallop too
                gal = 1
                while rp + gal * 2 < right - mid + 1 and array[rp + gal * 2] <= array[lp]:
                    gal *= 2
                for i in range(1, gal + 1):
                    tmparr[k + i] = array[rp + i]
                k += gal - 1
                rp += gal - 1
            rp += 1
        k += 1
    for k in range(left, right + 1):
        array[k] = tmparr[k - left]


def timsort(array) -> list:
    n = len(array)
    minrun = minrun_calc(n)
    runs = list()
    rstart = 0
    while rstart + 1 < n:  # run maker
        rpos = 0
        if array[rstart] <= array[rstart + 1]:  # 1 2 3 4
            while (rpos <= minrun or array[rpos + rstart] <= array[rstart + 1]) and rpos + rstart + 1 < n:
                rpos += 1
                if array[rpos + rstart - 1] >= array[rpos + rstart]:
                    ins_sort(array, rstart, rpos + rstart)
        else:  # 4 3 2 1
            while (rpos <= minrun or array[rpos + rstart] >= array[rstart + 1]) and rpos + rstart + 1 < n:
                rpos += 1
                if array[rpos + rstart - 1] <= array[rpos + rstart]:
                    ins_sort(array, rstart, rpos + rstart)
            reversing(array, rstart, rpos + rstart)
        if len(runs) == 2:  # stack imitator pt. 1
            if runs[-2][1] <= runs[-1][1]:
                merging(array, runs[-2][0], runs[-1][0], sum(runs[-1]))
                runs[-2][1] += runs[-1][1] + 1  #
                runs.pop(-1)  #
        runs.append([rstart, rpos])
        if len(runs) > 2:  # stack imitator pt. 2
            if runs[-3][1] <= runs[-2][1] + runs[-1][1]:
                if runs[-3][1] > runs[-1][1]:
                    merging(array, runs[-2][0], runs[-1][0], sum(runs[-1]))
                    runs[-2][1] += runs[-1][1] + 1  #
                    runs.pop(-1)  #
                else:
                    merging(array, runs[-3][0], runs[-2][0], sum(runs[-2]))
                    runs[-3][1] += runs[-2][1] + 1  #
                    runs.pop(-2)  #
            else:
                merging(array, runs[-2][0], runs[-1][0], sum(runs[-1]))
                runs[-2][1] += runs[-1][1] + 1  #
                runs.pop(-1)  #
        rstart += rpos + 1
    if len(runs) > 1:
        merging(array, runs[-2][0], runs[-1][0], sum(runs[-1]))
    return array


if __name__ == "__main__":
    print("you should import to use this func")
