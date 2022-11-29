from trees.BinaryTree import Node


def parse_string(string: str) -> Node | None:

    if string.count('(') == 1 and string.count(')') == 1:
        head = string.replace('(', '').replace(')', '')
        if head == '':
            return None
        return Node(data=int(head))

    formatted_string = string[1:-1]
    head = string[1:-1].split(' ')[0]

    left = None
    right = None
    open_barckets = 0
    close_brackets = 0
    start = 0
    for i in range(len(formatted_string)):
        s = formatted_string[i]
        if s == '(':
            if open_barckets == 0:
                start = i
            open_barckets += 1
        if s == ')':
            close_brackets += 1

        if open_barckets == close_brackets and open_barckets > 0:
            if not left:
                left = formatted_string[start:i+1]
                open_barckets = 0
                close_brackets = 0
            else:
                right = formatted_string[start:i+1]

    return Node(data=int(head), left=parse_string(left), right=parse_string(right))
