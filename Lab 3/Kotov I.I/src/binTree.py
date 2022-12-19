class Node:
    def __init__(self, data, parent=None):
        self.data = data
        self.parent = parent
        self.height = 0
        self.left = None
        self.right = None

class BinTree:
    def __init__(self, value):
        self.data = value

    def getLeft(self):
        return self.left

    def getRight(self):
        return self.right

    def setdata(self, value):
        self.data = value

    def getValue(self):
        return self.data


    def insertRight(self, value):
        if self.right is None:
            self.right = BinTree(value)
        else:
            data = BinTree(value)
            data.right = self.right
            self.right = data

    def insertLeft(self, value):
        if self.left is None:
            self.left = BinTree(value)
        else:
            data = BinTree(value)
            data.left = self.left
            self.left = data

    def bfs(self):
        currLevel = [self.data]
        result = []
        while currLevel:
            nextLevel = []
            for n in currLevel:
                result.append(n.data)
                if n.left:
                    nextLevel.append(n.left)
                if n.right:
                    nextLevel.append(n.right)
            currLevel = nextLevel
        return result


def printTree(tree, level=0):
    if tree is not None:
        printTree(tree.left, level + 1)
        print(' ' * 4 * level + str(tree.data))
        printTree(tree.right, level + 1)


def testTree():
    myTree = BinTree(300)
    myTree.left = BinTree(1)
    myTree.right = BinTree(11)
    myTree.left.left = BinTree(2)
    myTree.left.right = BinTree(3)
    myTree.right.left = BinTree(12)
    myTree.right.right = BinTree(13)

    printTree(myTree)
