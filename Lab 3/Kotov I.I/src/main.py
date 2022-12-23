from binTree import BinTree, printTree
from parsing import parser
from AVL import AVLTree

def main():
    with open('tree.txt') as f:
        data = f.read()

    root = parser(data)
    bin = BinTree(root)
    printTree(bin.getValue())
    print("\nBFS")
    print(bin.bfs())


    tree = AVLTree()

    elements = [8, 10, 3, 2, 2, 6, 13, 15, 14, 4]
    for i in elements:
        tree.insert(i)
    print(tree.display())
    print('\n\n\nINORDER')
    print(tree.traverse_in_order())
    print('\n\nPREORDER')
    print(tree.traverse_pre_order())
    print('\n\nPOSTORDER')
    print(tree.traverse_post_order())
    print('\n\nBreadth-first search')
    print(tree.bfs())

    for i in range(16, 25):
        tree.insert(i)
    print(tree.display())
    print('\n\n\nINORDER')
    print(tree.traverse_in_order())
    print('\n\n\nPREORDER')
    print(tree.traverse_pre_order())
    print('\n\n\nPOSTORDER')
    print(tree.traverse_post_order())
    print('\n\n\nBreadth-first search')
    print(tree.bfs())

    tree.remove(8)
    tree.remove(15)
    tree.remove(2)
    tree.remove(3)


    print(tree.display())
    print('\n\n\nINORDER')
    print(tree.traverse_in_order())
    print('\n\n\nPREORDER')
    print(tree.traverse_pre_order())
    print('\n\n\nPOSTORDER')
    print(tree.traverse_post_order())
    print('\n\n\nBreadth-first search')
    print(tree.bfs())


main()