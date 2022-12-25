from binTree import Node

class AVLTree:
    def __init__(self, root=None):
        self.__root = root

    def insert(self, data):
        if not self.__root:
            self.__root = Node(data)
        else:
            self.__insert_data(data, self.__root)

    def remove(self, data):
        try:
            if self.__root:
                self.__remove_data(data, self.__root)
        except TypeError:
            print("Неверный тип данных")

    def __insert_data(self, data, node):
        if data <= node.data:
            if node.left:
                self.__insert_data(data, node.left)
            else:
                node.left = Node(data, node)
                self.__violation_handler(node.left)
        if data > node.data:
            if node.right:
                self.__insert_data(data, node.right)
            else:
                node.right = Node(data, node)
                self.__violation_handler(node.right)

    def __remove_data(self, data, node):
        # поиск значения
        if data < node.data:
            if node.left:
                self.__remove_data(data, node.left)
        elif data > node.data:
            if node.right:
                self.__remove_data(data, node.right)
        elif data == node.data:

            # 1) когда удаляемая нода без детей - лист
            if not node.left and not node.right:
                parent_node = node.parent
                if parent_node:
                    if parent_node.left == node:
                        parent_node.left = None
                    elif parent_node.right == node:
                        parent_node.right = None
                # если коренная нода
                else:
                    self.__root = None
                del node
                self.__violation_handler(parent_node)

            # 2) когда только левый сын
            elif node.left and not node.right:
                parent_node = node.parent
                # отец-сын отношения
                if parent_node:
                    if parent_node.left == node:  # та, которую хотим удалить
                        parent_node.left = node.left
                    elif parent_node.right == node:
                        parent_node.right = node.left
                else:
                    self.__root = node.left
                # сын-отец отношения
                node.left.parent = parent_node
                del node
                self.__violation_handler(parent_node)

            # 3) когда только правый сын
            elif node.right and not node.left:
                parent_node = node.parent
                # отец-сын отношения
                if parent_node:
                    if parent_node.left == node:  # удаляемая нода
                        parent_node.left = node.right
                    elif parent_node.right == node:
                        parent_node.right = node.right
                else:
                    self.__root = node.right
                # сын-отец отношения
                node.right.parent = parent_node
                del node
                self.__violation_handler(parent_node)

            # 4) когда два сына
            # 4.1 мы должны найти либо узел-предшественник, либо узел-преемник (successor)
            # 4.2 поменять местами значения узла и любого из этих узлов
            # 4.3 удалить один этих узлов
            elif node.left and node.right:
                # successor: наименьший узел в правом поддереве node
                successor_node = self.__find_successor(node.right)
                successor_node.data, node.data = node.data, successor_node.data
                self.__remove_data(successor_node.data, node.right)

    def __find_successor(self, node):
        if node.left:
            return self.__find_successor(node.left)
        return node

    def __violation_handler(self, node):
        while node:
            node.height = max(self.__calculate_height(node.left), self.__calculate_height(node.right)) + 1
            self.__violation_fix(node)
            node = node.parent   # пробег до корня

    def __calculate_height(self, node):
        if not node:
            return -1
        return node.height

    def __violation_fix(self, node):
        # левый левый
        if self.__balance_factor(node) > 1:
            # левый правый
            if self.__balance_factor(node.left) < 0:
                self.__rotate_left(node.left)
            self.__rotate_right(node)
        # правый правый
        if self.__balance_factor(node) < -1:
            # правый левый
            if self.__balance_factor(node.right) > 0:
                self.__rotate_right(node.right)
            self.__rotate_left(node)

    def __balance_factor(self, node):  # разница в высотах
        if not node:
            return 0
        return self.__calculate_height(node.left) - self.__calculate_height(node.right)

    def __rotate_left(self, node):
        temp_right_node = node.right
        t = node.right.left

        # обновление ссылок
        temp_right_node.left = node
        node.right = t

        # обновление отношений сын-отец
        temp_parent = node.parent
        temp_right_node.parent = temp_parent
        node.parent = temp_right_node
        if t:
            t.parent = node

        # обновление отношений отец-сын
        if temp_right_node.parent:   # не коренная нода
            if temp_right_node.parent.left == node:
                temp_right_node.parent.left = temp_right_node
            elif temp_right_node.parent.right == node:
                temp_right_node.parent.right = temp_right_node
        else:  # коренная нода
            self.__root = temp_right_node

        # обновление высот нод
        node.height = max(self.__calculate_height(node.left), self.__calculate_height(node.right)) + 1
        temp_right_node.height = max(self.__calculate_height(temp_right_node.left),
                                     self.__calculate_height(temp_right_node.right)) + 1


    def __rotate_right(self, node):
        temp_left_node = node.left
        t = node.left.right

        # обновление отношений
        temp_left_node.right = node
        node.left = t

        # сын-отец
        temp_parent = node.parent
        temp_left_node.parent = temp_parent
        node.parent = temp_left_node
        if t:
            t.parent = node

        # отец-сын
        if temp_left_node.parent:
            if temp_left_node.parent.left == node:
                temp_left_node.parent.left = temp_left_node
            elif temp_left_node.parent.right == node:
                temp_left_node.parent.right = temp_left_node
        else:
            self.__root = temp_left_node

        # обновление высот
        node.height = max(self.__calculate_height(node.left), self.__calculate_height(node.right)) + 1
        temp_left_node.height = max(self.__calculate_height(temp_left_node.left),
                                    self.__calculate_height(temp_left_node.right)) + 1


    # обходы
    def traverse_in_order(self):
        if self.__root:
            tmp = []
            self.__in_order(self.__root, tmp)
            print(tmp)

    def traverse_pre_order(self):
        if self.__root:
            tmp = []
            self.__pre_order(self.__root, tmp)
            print(tmp)

    def traverse_post_order(self):
        if self.__root:
            tmp = []
            self.__post_order(self.__root, tmp)
            print(tmp)

    def __in_order(self, node, tmp, level=0):
        if node.left:
            self.__in_order(node.left, tmp, level + 1)
        tmp.append(node.data)
        #print(' ' * 4 * level + str(node.data))
        if node.right:
            self.__in_order(node.right, tmp, level + 1)

    def display(self):
        if self.__root:
            tmp = []
            self.__display(self.__root, tmp)
            print(tmp)

    def __display(self, node, tmp, level=0):
        if node.right:
            self.__display(node.right, tmp, level + 1)
        tmp.append(node.data)
        print(' ' * 4 * level + str(node.data))
        if node.left:
            self.__display(node.left, tmp, level + 1)

    def __pre_order(self, node, tmp):
        tmp.append(node.data)
        if node.left:
            self.__pre_order(node.left, tmp)
        if node.right:
            self.__pre_order(node.right, tmp)

    def __post_order(self, node, tmp):
        if node.left:
            self.__pre_order(node.left, tmp)
        if node.right:
            self.__pre_order(node.right, tmp)
        tmp.append(node.data)

    def bfs(self):
        currLevel = [self.__root]
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


    def find(self, data):
        if self.__root:
            return self.__find_data(data, self.__root)

    def __find_data(self, data, node):
        try:
            if data < node.data:
                if node.left:
                    return self.__find_data(data, node.left)
            elif data > node.data:
                if node.right:
                    return self.__find_data(data, node.right)
            elif data == node.data:
                return True
            return False
        except TypeError:
            return "Неверный тип"