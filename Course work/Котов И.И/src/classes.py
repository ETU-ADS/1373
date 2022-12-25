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
            self.resize(2 * (self.size + 1))

        self.array[self.countElements] = element
        self.countElements += 1


    def insertByIndex(self, element, index):
        assert 0 <= index < self.countElements, "Incorrect index"

        if self.countElements == self.size:
            self.resize(2 * self.size + 1)

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