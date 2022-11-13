# Алгоритм сортировки Timsort

Стоянов Иван, гр. 1373

## Getting Started

Для запуска потребуется `python=3.10.2`

### Installing

1. Склонируйте репозиторий и запустите:

```bash
python main.py
```

## Usage

```python
import random
from timsort import timsort, DynamicArray


n = 1000
input_array = DynamicArray()
for i in range(n):
input_array.append(random.randint(0, n)) # Заполнем массив случайными числами

timsort(input_array) # Сортируем массив

print(input_array) # Выводим отсортированный массив

```