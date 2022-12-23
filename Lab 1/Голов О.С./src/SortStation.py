from Structures import Stack


def sort_station(equation):
    """put smth like sin ( 25 ) + 8 * ( 2 / 4 )
    and you will get smth like 25 sin 8 2 4 / * +"""
    priority_list = {'^': 2, '*': 1, '/': 1, '+': 0, '-': 0}
    stack = Stack()
    queue = Stack()
    eq = equation.split()
    l_bracket_counter = 0
    r_bracket_counter = 0
    for i in eq:
        if not i.isdigit() and i not in ['*', '/', '+', '-', '^', 'sin', 'cos', '(', ')']:
            raise Exception("Incorrect symbol")
        if i.isdigit():
            queue.push(i)
        elif i in ['sin', 'cos']:
            stack.push(i)
        elif i in ['*', '/', '+', '-', '^']:
            while stack.peak() not in ['sin', 'cos', '(', ')', None] and priority_list.get(i) <= priority_list.get(
                    stack.peak()) and not (stack.peak() == '^' and i == '^'):
                queue.push(stack.pop())
            stack.push(i)
        elif i in ['(', ')']:
            if i == '(':
                stack.push(i)
                l_bracket_counter += 1
            else:
                r_bracket_counter += 1
                while stack.peak() not in ['(', None]:
                    queue.push(stack.pop())
                stack.pop()
            if stack.peak() in ['sin', 'cos']:
                queue.push(stack.pop())
    if r_bracket_counter != l_bracket_counter:
        raise Exception('Too much parentesis')
    while stack.peak() is not None:
        if stack.peak() not in ['(', ')']:
            queue.push(stack.pop())
    final_str = [queue.pop() for _ in range(len(eq)) if queue.peak() is not None]
    return ' '.join(reversed(final_str))


if __name__ == "__main__":
    a = input('type expression ')
    print(sort_station(a))
    input()
