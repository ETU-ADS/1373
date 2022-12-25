# Бинарное дерево и АВЛ Дерево

Стоянов Иван, гр. 1373

## Getting Started

Для запуска потребуется `python=3.10.2`

### Installing

1. Склонируйте репозиторий и запустите:
2. Установите необходимые зависимости с помощью `pip install -r requirements.txt`
3. Запустите `python main.py`

Все сгенерированные изображения хранятся в дериктории `output/`

## Usage

```python
from trees.parseString import parse_string
from trees.AVLTree import AVLTree
from trees.BinaryTree import BinaryTree
from trees.printTree import tree_to_image


def main():
    # Демонстрация работы алгоритма для парсинга скобочной записи дерева.
    with open('data.txt') as f:
        data = f.read()
    root = parse_string(data)
    binary_tree = BinaryTree(root=root)
    # Сохраняем изображение дерева > output/parse_string/{data}.png
    tree_to_image(binary_tree, f'parse_string/{data}.png')

    # АВЛ дерево
    avl_tree = AVLTree()
    # Добавление эл-ов
    data = [50, 25, 10, 5, 7, 3, 30, 20, 8, 15]
    n = 1
    for d in data:
        avl_tree.add(d)
        # Сохраняем изображения дерева после каждого добавления > output/avl_insert/insert_{1...n}.png
        tree_to_image(avl_tree, f'avl_insert/insert_{n}.png')
        n += 1

    # Демонстрация обхода дерева
    print(f'Обход в ширину: {avl_tree.bfs()}')
    print(f'Обход в глубину (preorder): {avl_tree.preorder()}')
    print(f'Обход в глубину (inorder): {avl_tree.inorder()}')
    print(f'Обход в глубину (postorder): {avl_tree.postorder()}')

    # Удаление эл-ов
    data = [8, 25, 30]
    for d in data:
        avl_tree.remove(d)

if __name__ == "__main__":
    main()
```