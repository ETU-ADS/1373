class DynamicArray():
    def __init__(self):
        self.array = []
        self.max = None

    def __getitem__(self, index):
        if index >= len(self):
            print ('Array do not have this index') 
        return self[index]

    def delete(self):
        self.pop(len(self)-1)

    def delete_content(self):
        for i in range(len(self)):
            self.pop(len(self)-1)

    def remove(self, index):
        for i in range(index, len(self) - 1):
            self[i] = self[i + 1]
        self.pop(len(self)-1)

    def find(self, value):
        for i in range(len(self)):
            if i == value:
                return i
        print ('Array do not have this value')

    def insert(self, value, index):
        if index > len(self) or index < 0:
            print ('Invalid index') 
            return
        if index == len(self):
            self.append(value)
        if index < len(self) or index > 0:
            for i in range(len(self) - 1, index - 1, -1): 
                self[i] = self[i-1] 
                self[index] = value
        

    


