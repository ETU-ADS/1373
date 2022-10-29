import random
from timsort import timsort, DynamicArray
from datetime import datetime


def run_test_time(n: int) -> None:
    input_array = DynamicArray()
    for i in range(n):
        input_array.append(random.randint(0, n))

    start_time = datetime.now()
    result = 'result = Ok'
    try:
        timsort(input_array)
    except Exception as e:
        result = f'result = {str(e)}'
    end_time = datetime.now()

    print(f'array_len = {n}, time = {end_time-start_time}, {result}')


def main():
    n = 100
    while n <= 10000:
        run_test_time(n)
        n += int(n * 0.5)


if __name__ == "__main__":
    main()
