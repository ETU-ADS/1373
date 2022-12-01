class Node:
    def __init__(self, value=0):
        self.data = value
        self.next = None

class Stack:

    def __init__(self):
        self.head = None

    def pop(self):
        if self.head != None:
            current = self.head.data
            self.head = self.head.next
            return current
        else:
            return None

    def push(self, value):
        current = Node(value)
        if self.head == None:
            self.head = current
        else:
            current.next = self.head
            self.head = current

    def peak(self):
        if self.head != None:
            return self.head.data
        else:
            return None

