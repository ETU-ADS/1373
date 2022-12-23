from binTree import Node

def parser(string_):
    if string_ is None:
        return

    if string_.count('(') != string_.count(')'):
        print("Не совпадает кол-во '(' и ')'")
        return

    if string_.count('(') == 1 and string_.count(')') == 1:
        head = string_.replace('(', '').replace(')', '')
        if head == '':
            return None
        return Node(int(head))

    string = string_[1:-1]
    head = string.split(' ')[0]
    left, right = None, None
    open, close, start, i = 0, 0, 0, 0

    for i in range(len(string)):
        symbol = string[i]
        if symbol == '(':
            if open == 0:
                start = i
            open += 1
        if symbol == ')':
            close += 1

        if open == close and open > 0:
            if not left:
                left = string[start:i+1]
                open, close = 0, 0
            else:
                right = string[start:i+1]
                break

    if i + 1 != len(string):
        print('Это не двоичное дерево')
        exit()

    result = Node(int(head))
    result.left = parser(left)
    result.right = parser(right)

    return result
