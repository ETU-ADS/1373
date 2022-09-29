from structures import Stack


available_operators = {'+': 0, '-': 0, '*': 1, '/': 1, '^': 1} # оператор: прироритет
available_functions = ['sin', 'cos',]
available_separators = ['(', ')']
available_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
available_tokens = list(available_operators.keys()) + available_functions + available_separators + available_digits


def to_postfix(input_string: str) -> str:
    input_tokens = input_string.strip().split(' ')
   
    stack = Stack()
    output = '' 
    for token in input_tokens:
        if token not in available_tokens:
            print(f"Token '{token}' not in available tokens")
            return
        
        # Если токен — число, то добавить его в очередь вывода.
        if token in available_digits:
            output += token
            
        # Если токен — функция, то поместить его в стек.
        if token in available_functions:
            stack.push(token)
            
        # Если токен — оператор op1, то:
        if token in available_operators:
            # Пока присутствует на вершине стека токен оператор op2, чей приоритет выше или равен приоритету op1.
            while len(stack) > 0 and stack.top() in available_operators.keys() and available_operators[stack.top()] >= available_operators[token]:
                output += stack.pop() # Переложить op2 из стека в выходную очередь
            stack.push(token) # Положить op1 в стек.

        # Если токен — открывающая скобка, то положить его в стек.
        if token == '(':
            stack.push(token)
        
        # Если токен — закрывающая скобка:
        if token == ')':
            # Пока токен на вершине стека не открывающая скобка
            while stack.top() != '(':
                output += stack.pop() # Переложить оператор из стека в выходную очередь. 
            stack.pop() # Выкинуть открывающую скобку из стека, но не добавлять в очередь вывода.
            
            # Если токен на вершине стека — функция, переложить её в выходную очередь.
            if token in available_functions:
                output += stack.pop()
    
    # Если больше не осталось токенов на входе:
    while len(stack) > 0 and stack.top() in available_operators:
        output += stack.pop()
        
    return output


def main():
    # input_string = input()
    input_string = '3 + 4 * ( 2 - 1 )'
    print(to_postfix(input_string)) # 3421-*+


if __name__ == "__main__":
    main()
