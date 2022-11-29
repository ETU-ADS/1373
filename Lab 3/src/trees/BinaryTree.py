class Node:
    def __init__(self, data: any, left=None, right=None):
        self.data = data

        self.left = left
        self.right = right

    def __str__(self) -> str:
        return str(self.data)


class BinaryTree:
    def __init__(self, root: Node = None):
        self.root = root  # корень дерева

    # BFS - обход в ширину
    def bfs(self):
        if not self.root:
            return []

        result = []

        def proccess(n: Node):
            result.append(n)

        queue = [self.root]
        while len(queue) > 0:
            node = queue.pop()
            proccess(node)

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        return result

    def preorder(self) -> list:
        result = []

        def proccess(n: Node):
            result.append(n)

        def _preorder(node: Node):
            if not node:
                return

            proccess(node)
            _preorder(node.left)
            _preorder(node.right)

        if not self.root:
            return []
        else:
            _preorder(self.root)

        return result

    def inorder(self) -> list:
        result = []

        def proccess(n: Node):
            result.append(n)

        def _inorder(node: Node):
            if not node:
                return

            _inorder(node.left)
            proccess(node)
            _inorder(node.right)

        if not self.root:
            return []
        else:
            _inorder(self.root)

        return result

    def postorder(self) -> list:
        result = []

        def proccess(n: Node):
            result.append(n)

        def _postorder(node: Node):
            if not node:
                return

            _postorder(node.left)
            _postorder(node.right)
            proccess(node)

        if not self.root:
            return []
        else:
            _postorder(self.root)

        return result
