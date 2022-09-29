class DynamicArray(): 
    def __init__(self) -> None:
        self._lenght = 0
        self._capacity = 10
        self._array = self._make__array(self._capacity)
    
    def __len__(self) -> int: 
        return self._lenght
    
    
    def __getitem__(self, index: int) -> any: 
        if index >= self._lenght: 
            return IndexError('Index is out of range!') 
        return self._array[index]  


    def append(self, element: any) -> any: 
        if self._lenght == self._capacity: 
            self._resize(int(1.6 * self._capacity)) 
        self._array[self._lenght] = element 
        self._lenght += 1
        return element
    
    
    def insert(self, index, element): 
 
        if index < 0 or index > self._lenght: 
            return IndexError('Index is out of range!') 
         
        if self._lenght == self._capacity: 
            self._resize((1.6*self._capacity)) 
         
        for i in range(self._lenght - 1, index - 1, -1): 
            self._array[i+1] = self._array[i] 
             
         
        self._array[index] = element 
        self._lenght += 1
        
        
    def removeAt(self, index: int) -> any: 
        if self._lenght == 0: 
            return IndexError('Index is out of range!')  
                 
        if index < 0 or index >= self._lenght: 
            return IndexError('Index is out of range!')         
        
        element = self._array[index] 
        if index == self._lenght - 1: 
            element = self._array[index]
            self._array[index] = None
            self._lenght -= 1
            return element     
         
        for i in range(index, self._lenght - 1): 
            self._array[i] = self._array[i+1]
        self._array[self._lenght-1] = None
        self._lenght -= 1
        return element
    
    def __str__(self) -> str:
        line = '['
        for i in range(0, self._lenght - 1):
            line += str(self[i]) + ', '
        line += str(self[self._lenght - 1]) + ']'
        return line
    
    
    def _resize(self, new_capacity: int) -> None: 
        new_array = self.make__array(new_capacity) 
         
        for k in range(self._lenght):  
            new_array[k] = self._array[k] 
             
        self._array = new_array 
        self._capacity = new_capacity 
         
         
    def _make__array(self, new_capacity:int) -> list[None]: 
        return ([None] * new_capacity)
