import random
from timsort import timsort, DynamicArray


def main():
    n = 1000
    input_array = DynamicArray()
    for i in range(n):
        input_array.append(random.randint(0, n))

    timsort(input_array)

    print(input_array)
    

if __name__ == "__main__":
    main()
