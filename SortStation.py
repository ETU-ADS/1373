from Stack import Stack

def sortStation(expression):
    stack, result = Stack(), Stack()
    priority_list = {'+': 0, '-': 0, '/': 1, '*': 1, '^': 2}
    book = expression.split()
    for i in book:
        if not i.isdigit() and i not in ['*', '/', '+', '-', '^', 'sin', 'cos', '(', ')']:
            raise Exception("Incorrect symbol")
        if i.isdigit():
            result.push(i)
        elif i in ['sin', 'cos']:
            stack.push(i)
        elif i in ['*', '/', '+', '-', '^']:
            while stack.peak() not in ['sin', 'cos', '(', ')', None] and priority_list.get(i) <= priority_list.get(stack.peak()) and not stack.peak() == '^' and not i == '^':
                result.push(stack.pop())
            stack.push(i)
        elif i in ['(', ')']:
            if i == '(':
                stack.push(i)
            else:
                while stack.peak() not in ['(', None]:
                    result.push(stack.pop())
                stack.pop()
            if stack.peak() in ['sin', 'cos']:
                result.push(stack.pop())
    while stack.peak() is not None:
        if stack.peak() not in ['(', ')']:
            result.push(stack.pop())
    final = [result.pop() for _ in range(len(book)) if result.peak() is not None]
    return ' '.join(reversed(final))

if __name__ == "__main__":
    a = input('type expression: ')
    print(sortStation(a))