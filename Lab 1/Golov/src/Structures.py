class Node:
    def __init__(self, value=0):
        self.data = value
        self.next = None


class ForwardList:
    def __init__(self):
        self.head = None
        self.len = 0

    def add(self, index, value):
        nodename = Node(value)
        if index > self.len:
            raise Exception("out of bounds")

        elif index == 0 and self.len == 0:
            self.head = nodename
            self.len += 1
        elif index == 0:
            current = Node()
            current.next = self.head
            self.head = current
            self.len += 1

        elif index == self.len:
            self.__getitem__(index - 1).next = nodename
            self.len += 1
        else:
            current = self.__getitem__(index - 1).next
            self.__getitem__(index - 1).next = nodename
            self.__getitem__(index - 1).next = current
            self.len += 1

    def __getitem__(self, index):  # x[index]
        if index >= self.len:
            raise Exception("out of bounds")
        current = self.head
        for i in range(index):
            current = current.next
        return current

    def find(self, value):
        current = self.head
        for i in range(self.len):
            if current.data == value:
                return i
            else:
                current = current.next
        print("Not found")

    def delete(self, index):

        if index == 0 and self.len == 0:
            print("There is nothing to delete")

        elif index >= self.len:
            raise Exception("out of bounds")

        elif index == 0:
            self.head = self.head.next
            self.len -= 1

        else:
            self.__getitem__(index - 1).next = self.__getitem__(index - 1).next.next
            self.len -= 1


class Stack:

    def __init__(self):
        self.head = None

    def pop(self):
        if self.head is not None:
            current = self.head.data
            self.head = self.head.next
            return current
        else:
            return None

    def push(self, value):
        curr = Node(value)
        if self.head is None:
            self.head = curr
        else:
            curr.next = self.head
            self.head = curr

    def peak(self):
        if self.head is not None:
            return self.head.data
        else:
            return None


class Vector:
    def __init__(self):
        self.vector = list()
        self.maxsize = 0

    def __getitem__(self, index):
        if index < self.maxsize:
            return self.vector[index]
        else:
            raise Exception("Out Of Bounds")

    def find(self, val):
        for i in range(self.maxsize):
            if self.vector[i] == val:
                return i
        print("Not Found")

    def add(self, index, val=0):
        if index < self.maxsize:
            self.vector[index] = val

        else:
            tmp = self.vector
            self.maxsize = int((self.maxsize + 1) * 1.5)
            self.vector = [0 for _ in range(self.maxsize)]
            for i in range(len(tmp)):
                self.vector[i] = tmp[i]

            self.add(index, val)

    def delete(self, index):

        for i in range(index, self.maxsize - 1, 1):
            self.vector[i] = self.vector[i + 1]

    def __len__(self):
        return self.maxsize
