class LinkedList:
    def __init__(self) -> None:
        self.head = None
        self.lenght = 0
        
    class Node:
        element = None
        next_node = None
        
        def __init__(self, element: any, next_node=None) -> None:
            self.element = element
            self.next_node = next_node
            
            
    def append(self, element: any) -> any:
        if not self.head:
            self.head = self.Node(element)
            self.lenght += 1
            return element
    
        node = self.head
        while node.next_node:
            node = node.next_node
            
        node.next_node = self.Node(element)
        self.lenght += 1
        return element
    
    
    def __getitem__(self, index: int):
        i = 0    
        node = self.head
        
        while i < index:
            node = node.next_node
            i += 1
        
        return node.element
    
    
    def find(self, element: any) -> None:
        i = 0
        node = self.head
        prev_node = self.head
        
        if self.head.element == element:
            return element 
        
        while i < self.lenght:
            node = node.next_node
            if node.element == element:
                return element
            i += 1
        
        return None
    
    
    def insert(self, index: int, element: any) -> any:
        i = 0
        node = self.head
        prev_node = self.head
        
        if index == 0:
            old_head = self.head
            self.head = self.Node(element, next_node=old_head)
            self.lenght += 1
            return element    
        
        while i < index:
            prev_node = node
            node = node.next_node
            i += 1
        
        prev_node.next_node = self.Node(element, next_node=node)  
        self.lenght += 1
        return element
    
    
    def __delitem__(self, index: int) -> any:
        i = 0
        node = self.head
        prev_node = self.head
        
        if index == 0:
            old_head = self.head
            element = self.head.element
            self.head = self.head.next_node
            self.lenght -= 1
            del old_head
            return element
        
        while i < index:
            prev_node = node
            node = node.next_node
            i += 1
        
        prev_node.next_node = node.next_node  
        self.lenght -= 1
        
        element = node.element
        del node
        return element
    
    
    def delete(self, index: int) -> any:
        return self.__delitem__(index)
    
    
    def __len__(self) -> int:
        return self.lenght
    
    
    def __str__(self) -> str:
        node = self.head
        if len(self) == 0:
            return '[]'
        line = '['
        while node.next_node:
            line += str(node.element) + ', '
            node = node.next_node
        line += str(node.element) + ']'
        return line
