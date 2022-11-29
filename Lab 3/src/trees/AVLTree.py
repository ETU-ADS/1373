from trees.BinaryTree import BinaryTree


class BoolObject(object):
    def __init__(self, status=False):
        self.status = status

    def set_status(self, status):
        self.status = status

    def get_status(self):
        return self.status


class AVLNode(object):
    LEFT_HIGHER = -1
    EQUAL_HEIGHT = 0
    RIGHT_HIGHER = 1

    def __init__(self, data, left=None, right=None, parent=None, bf=0):
        self.data = data
        self.left, self.right = left, right
        self.parent = parent
        self.bf = bf

    def __str__(self):
        return f'{self.data}'

    def __repr__(self):
        return self.__str__()


class AVLTree(BinaryTree):

    # ---------- Поиск эл-та ----------
    def find(self, key) -> AVLNode | None:
        if not self.root:
            return None
        else:
            return self._find(key, self.root)

    def _find(self, key, node: AVLNode) -> AVLNode | None:
        if not node:
            return None
        elif key < node.data:
            return self._find(key, node.left)
        elif key > node.data:
            return self._find(key, node.right)
        else:
            return node

    # --------------------------------

    # ----------- Повороты -----------
    def right_rotate(self, node: AVLNode):
        if not node or not node.left:
            raise AssertionError(" right rotate to illegal node " + str(node))
        parent_node = node.parent
        node_left = node.left
        node.left = node_left.right
        if node.left:
            node.left.parent = node
        node_left.right = node
        node.parent = node_left
        if parent_node:
            if node == parent_node.left:
                parent_node.left = node_left
            else:
                parent_node.right = node_left
            node_left.parent = parent_node
        else:
            self.root = node_left
            node_left.parent = None

    def left_rotate(self, node: AVLNode):
        if not node or not node.right:
            raise AssertionError(" right rotate to illegal node " + str(node))
        parent_node = node.parent
        node_right = node.right
        node.right = node_right.left
        if node.right:
            node.right.parent = node
        node_right.left = node
        node.parent = node_right
        if parent_node:
            if node == parent_node.right:
                parent_node.right = node_right
            else:
                parent_node.left = node_right
            node_right.parent = parent_node
        else:
            self.root = node_right
            node_right.parent = None

    def left_right_rotate(self, node: AVLNode):
        self.left_rotate(node.left)
        self.right_rotate(node)

    # --------------------------------

    # ------- Добавление эл-та -------

    def add(self, key):
        if not self.root:
            self.root = AVLNode(data=key)
            return
        else:
            self._add(self.root, key, BoolObject())

    def _add(self, node: AVLNode, value, taller):
        result = True
        if not node:
            result = False
        elif node.data == value:
            result = False
        elif value < node.data:
            if node.left:
                result = self._add(node.left, value, taller)
            else:
                node.left = AVLNode(value, parent=node)
                taller.set_status(True)
            if result and taller.get_status():
                if node.bf == AVLNode.LEFT_HIGHER:
                    self.left_balance(node)
                    taller.set_status(False)
                elif node.bf == AVLNode.EQUAL_HEIGHT:
                    node.bf = AVLNode.LEFT_HIGHER
                else:
                    node.bf = AVLNode.EQUAL_HEIGHT
                    taller.set_status(False)
        else:
            if node.right:
                result = self._add(node.right, value, taller)
            else:
                node.right = AVLNode(value, parent=node)
                taller.set_status(True)
            if result and taller.get_status():
                if node.bf == AVLNode.LEFT_HIGHER:
                    node.bf = AVLNode.EQUAL_HEIGHT
                    taller.set_status(False)
                elif node.bf == AVLNode.EQUAL_HEIGHT:
                    node.bf = AVLNode.RIGHT_HIGHER
                else:
                    self.right_balance(node)
                    taller.set_status(False)
        return result

    def left_balance(self, node):
        if not node or not node.left:
            raise AssertionError(" left balance to illegal node " + str(node))
        left_node = node.left
        if left_node.bf == AVLNode.LEFT_HIGHER:
            node.bf = AVLNode.EQUAL_HEIGHT
            left_node.bf = AVLNode.EQUAL_HEIGHT
            self.right_rotate(node)
        elif left_node.bf == AVLNode.RIGHT_HIGHER:
            left_node_right = left_node.right
            if left_node_right.bf == AVLNode.LEFT_HIGHER:
                node.bf = AVLNode.RIGHT_HIGHER
                left_node.bf = AVLNode.EQUAL_HEIGHT
            elif left_node_right.bf == AVLNode.RIGHT_HIGHER:
                node.bf = AVLNode.EQUAL_HEIGHT
                left_node.bf = AVLNode.LEFT_HIGHER
            else:
                node.bf = AVLNode.EQUAL_HEIGHT
                left_node.bf = AVLNode.EQUAL_HEIGHT
            left_node_right.bf = AVLNode.EQUAL_HEIGHT
            self.left_rotate(left_node)
            self.right_rotate(node)
        else:
            raise AssertionError("logic error , should not left balance node " + str(node))

    def right_balance(self, node):
        if not node or not node.right:
            raise AssertionError("right balance to illegal node " + str(node))
        right_node = node.right
        if right_node.bf == AVLNode.RIGHT_HIGHER:
            node.bf = AVLNode.EQUAL_HEIGHT
            right_node.bf = AVLNode.EQUAL_HEIGHT
            self.left_rotate(node)
        elif right_node.bf == AVLNode.LEFT_HIGHER:
            right_node_left = right_node.left
            if right_node_left.bf == AVLNode.RIGHT_HIGHER:
                node.bf = AVLNode.LEFT_HIGHER
                right_node.bf = AVLNode.EQUAL_HEIGHT
            elif right_node_left.bf == AVLNode.LEFT_HIGHER:
                node.bf = AVLNode.EQUAL_HEIGHT
                right_node.bf = AVLNode.RIGHT_HIGHER
            else:
                node.bf = AVLNode.EQUAL_HEIGHT
                right_node.bf = AVLNode.EQUAL_HEIGHT
            right_node_left.bf = AVLNode.EQUAL_HEIGHT
            self.right_rotate(right_node)
            self.left_rotate(node)
        else:
            raise AssertionError(" logic error , should not left balance node " + str(node))

    # --------------------------------

    # -------- Удаление эл-та --------

    def remove(self, value):
        return self.__remove__(self.root, value, BoolObject(False))

    def __remove__(self, node: AVLNode, value: any, shorter: BoolObject):
        result = False
        if not node:
            return False
        is_remove_at_right = False
        if value == node.data:
            if node.left and node.right:  # case Существуют левый и правый дочерние элементы удаленного узла
                min_node = node.right
                while min_node.left:
                    min_node = min_node.left
                node.data = min_node.data
                is_remove_at_right = True
                result = self.__remove__(node.right, node.data, shorter)
            else:  # case Существует не более одного дочернего элемента
                if node.parent:
                    if node == node.parent.left:
                        node.parent.left = node.left or node.right
                        if node.parent.left:
                            node.parent.left.parent = node.parent
                    else:
                        node.parent.right = node.left or node.right
                        if node.parent.right:
                            node.parent.right.parent = node.parent
                    shorter.set_status(True)
                else:
                    self.root = node.left or node.right
                    if self.root:
                        self.root.parent = None
                    shorter.set_status(False)
                return True
        elif value < node.data and node.left:
            result = self.__remove__(node.left, value, shorter)
        elif value > node.data and node.right:
            is_remove_at_right = True
            result = self.__remove__(node.right, value, shorter)
        if result and shorter.get_status():
            self.remove_balance(node, is_remove_at_right, shorter)
        return result

    def remove_balance(self, node, is_remove_at_right, shorter):
        if not node:
            raise AssertionError('remove_balance to empty node.')
        if node.bf == AVLNode.EQUAL_HEIGHT:
            node.bf = (is_remove_at_right and AVLNode.LEFT_HIGHER) or AVLNode.RIGHT_HIGHER
            shorter.set_status(False)
        elif (node.bf == AVLNode.LEFT_HIGHER and not is_remove_at_right) \
            or (node.bf == AVLNode.RIGHT_HIGHER and is_remove_at_right):
            node.bf = AVLNode.EQUAL_HEIGHT
            shorter.set_status(True)
        else:
            if node.bf == AVLNode.LEFT_HIGHER:
                left_node = node.left
                if left_node.bf == AVLNode.EQUAL_HEIGHT:
                    self.right_rotate(node)
                    left_node.bf = AVLNode.RIGHT_HIGHER
                    shorter.set_status(False)
                elif left_node.bf == AVLNode.LEFT_HIGHER:
                    self.right_rotate(node)
                    node.bf = AVLNode.EQUAL_HEIGHT
                    left_node.bf = AVLNode.EQUAL_HEIGHT
                    shorter.set_status(True)
                else:
                    self.left_balance(node)
                    shorter.set_status(True)
            elif node.bf == AVLNode.RIGHT_HIGHER:
                right_child = node.right
                if right_child.bf == AVLNode.EQUAL_HEIGHT:
                    self.left_rotate(node)
                    right_child.bf = AVLNode.LEFT_HIGHER
                    shorter.set_status(False)
                elif right_child.bf == AVLNode.RIGHT_HIGHER:
                    self.left_rotate(node)
                    node.bf = AVLNode.EQUAL_HEIGHT
                    right_child.bf = AVLNode.EQUAL_HEIGHT
                else:
                    self.right_balance(node)
                    shorter.set_status(True)

    # --------------------------------
