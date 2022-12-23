from RedBlack import RBTree, insertRB, Node, dfs1


class Tree:
    def __init__(self, val, parent=None):
        self.val = val
        self.parent = parent
        self.left_tree = None
        self.right_tree = None


def dfs(tree: Tree, array):
    array.append(int(tree.val))
    if tree.left_tree is not None:
        dfs(tree.left_tree, array)
    if tree.right_tree is not None:
        dfs(tree.right_tree, array)


def nfactor(txt: str, i) -> str:  # collecting chars to integer
    number = ''
    while txt[i] not in ' ()':
        number += txt[i]
        i += 1
    return number


def root_create(text):
    with open(text, 'r') as name:  # (8 (9 () (3)) (1 (-2 (25) (10))))
        txt = name.readline()
        if txt.count('(') != txt.count(')'):
            raise Exception('parenthesis')

        ctree = Tree(txt[1])
        flag = False
        for i in range(2, len(txt) - 1):
            if txt[i] not in '1234567890()- ':
                raise Exception('Wrong Symbol')

            if txt[i] == '(':
                if txt[i + 1] == ')':
                    flag = True
                    continue
                if ctree.left_tree is None and not flag:
                    ctree.left_tree = Tree(int(nfactor(txt, i + 1)), ctree)
                    ctree = ctree.left_tree
                else:
                    if ctree.right_tree is None:
                        ctree.right_tree = Tree(int(nfactor(txt, i + 1)), ctree)
                        ctree = ctree.right_tree
                    else:
                        raise Exception('not a binary tree')
            elif txt[i] == ')' and txt[i - 1] != '(':
                ctree = ctree.parent
                flag = False
        return ctree


def RBlacking(t) -> RBTree:
    tree = RBTree()
    arr = []
    dfs(t, arr)
    for i in arr:
        insertRB(tree, Node(i))
    return tree


if __name__ == '__main__':
    t = root_create('tree.txt')
    array = []
    dfs(t, arr)
    print(arr)
    print(dfs1(RBlacking(t).root))
