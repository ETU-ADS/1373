class DynamicArray:
    def __init__(self):
        self.size = 1
        self.countElements = 0
        self.array = self.createArray(self.size)


    def createArray(self, size):
        return size * [None]


    def resize(self, newSize):
        newArray = self.createArray(newSize)

        for i in range(self.size):  # перенос данных
            newArray[i] = self.array[i]

        self.array = newArray  # обновление массива
        self.size = newSize


    def len(self):
        return self.countElements


    def getItem(self, index):
        assert 0 <= index < self.countElements, "Incorrect index"
        return self.array[index]


    def append(self, element):
        if self.countElements == self.size:
            self.resize(2 * self.size)

        self.array[self.countElements] = element
        self.countElements += 1


    def insertByIndex(self, element, index):
        assert 0 <= index < self.countElements, "Incorrect index"

        if self.countElements == self.size:
            self.resize(2 * self.size)

        for i in range(self.countElements - 1, index - 1, -1):  # перезапись эл-тов для вставки
            self.array[i + 1] = self.array[i]

        self.array[index] = element
        self.countElements += 1

    def removeByIndex(self, index):
        assert self.countElements > 0, "Array is empty"
        assert 0 <= index < self.countElements, "Incorrect index"

        for i in range(index, self.countElements - 1):  # перезапись эл-тов
            self.array[i] = self.array[i + 1]

        self.countElements -= 1


class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next

    def getData(self):
        return self.data

    def getNext(self):
        return self.next

    def setData(self, data):
        self.data = data

    def setNext(self, next):
        self.next = next




class LinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        newNode = Node(data)
        curNode = self.head

        if curNode is None:
            self.head = newNode
            return

        while curNode.getNext() is not None:  # перемещение текущей ноды до момента создания новой ссылки
            curNode = curNode.getNext()
        curNode.setNext(newNode)

    def printAll(self):
        curNode = self.head
        result = ''

        while curNode is not None:
            result += f'{curNode.getData()}, '
            curNode = curNode.getNext()
        print(result)


    def length(self):
        curNode = self.head
        length = 0

        while curNode is not None:
            length += 1
            curNode = curNode.getNext()
        return length

    def getItem(self, index):
        assert 0 <= index < self.length(), "Incorrect index"
        curNode = self.head
        length = 0

        while curNode is not None:
            if index == length:
                return curNode.getData()

            length += 1
            curNode = curNode.getNext()


    def insertByIndex(self, data, index):
        assert 0 <= index < self.length(), "Incorrect index"
        newNode = Node(data)
        curNode = self.head
        length = 0

        while curNode.getNext() is not None:
            if index == 0:
                newNode.setNext(curNode)
                self.head = newNode
                return
            elif index == length + 1:
                nodeAfterCur = curNode.getNext()
                curNode.setNext(newNode)
                newNode.setNext(nodeAfterCur)
                return
            length += 1
            curNode = curNode.getNext()



    def removeByIndex(self, index):
        assert 0 <= index < self.length(), "Incorrect index"
        curNode = self.head
        length = 0

        if index == 0 and curNode.getNext() is None:  # если остался один эл-т в списке
            curNode = self.head
            self.head = curNode.getNext()
            return curNode.getData()

        while curNode.getNext() is not None:
            if index == 0:
                curNode = self.head
                self.head = curNode.getNext()
                return curNode.getData()

            elif index == length + 1:
                nodeAfterCur = curNode.getNext()
                nodeAfterAfterCur = nodeAfterCur.getNext()
                curNode.setNext(nodeAfterAfterCur)
                return nodeAfterCur.getData()
            length += 1
            curNode = curNode.getNext()



class Stack:
    def __init__(self):
        self.linkedList = LinkedList()

    def size(self):
        return self.linkedList.length()

    def push(self, data):
        return self.linkedList.append(data)

    def pop(self):
        return self.linkedList.removeByIndex(self.size() - 1)

    def top(self):
        return self.linkedList.getItem(self.size() - 1)

    def printAll(self):
        self.linkedList.printAll()

    def reverse(self):
        tmp1 = Stack()
        while self.size() > 0:
            tmp1.push(self.pop())

        tmp2 = Stack()
        while tmp1.size() > 0:
            tmp2.push(tmp1.pop())

        while tmp2.size() > 0:
            self.push(tmp2.pop())
