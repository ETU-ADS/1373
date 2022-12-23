from .LinkedList import LinkedList

class Stack():
    def __init__(self) -> None:
        self.linked_list: LinkedList =  LinkedList()
    
        
    def __len__(self) -> int:
        return self.size()
    
    
    def size(self) -> int:
        return len(self.linked_list)
    
    
    def is_empty(self) -> bool:
        return True if len(self.linked_list) == 0 else False
    
    
    def top(self) -> any:
        return self.linked_list.head.element
    
    
    def push(self, element: any) -> any:
        return self.linked_list.insert(0, element)
    
    
    def pop(self) -> any:
        return self.linked_list.delete(0)  

    def __str__(self) -> str:
        return str(self.linked_list)
