class Node:
    def __init__(self, value=0):
        self.data = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def len(self):
        current = self.head
        count = 0
        while current:
            count += 1
            current = current.next
        return count

    def __getitem__(self, index):
        current = self.head
        transition = 0
        while transition <= index:
            if transition == index:
                return current
            transition = transition + 1
            current = current.next

    def add(self, new):
        if self.head is None:
            self.head = new
            return
        while (self.head.next):
            self.head = self.head.next
        self.head.next = new

    def find(self, value):
        current = self.head
        for i in range(self.len):
            if current.data == value:
                return i
            else:
                current = current.next
        print ("List do not have this value")

    def delete(self, index):
        if index == 0 and self.len == 0:
            print ("Nothing to delete")
        if index >= self.len:
            raise Exception("List do not nave this index")
        if index == 0:
            self.head = self.head.next
            self.len -= 1
        if index < self.len:
            self.__getitem__(index - 1).next = self.__getitem__(index - 1).next.next
            self.len -= 1