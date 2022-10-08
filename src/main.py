from src.classes import Stack

def sortStation(inputLine):
    availableInput = ['*', '/', '+', '-', '^', 'sin', 'cos', '(', ')']
    operatorsPriority = {'+': 0, '-': 0, '*': 1, '/': 1, '^': 2}
    functions = ['sin', 'cos']
    stack, result = Stack(), Stack()
    inputLine = inputLine.split()
    assert inputLine.count('(') >= inputLine.count(')'), 'Separator "(" is missed in the input string'
    assert inputLine.count('(') <= inputLine.count(')'), 'Separator ")" is missed in the input string'

    for token in inputLine:
        assert token in availableInput or token.isdigit(), 'Incorrect symbol in the input string'

        if token.isdigit():
            result.push(token)

        elif token in functions:
            stack.push(token)

        elif token in operatorsPriority:
            while stack.size() > 0 and stack.top() in operatorsPriority and operatorsPriority.get(stack.top()) >= operatorsPriority.get(token):
                result.push(stack.pop())
            stack.push(token)

        elif token == '(':
            stack.push(token)

        elif token == ')':
            while stack.top() != '(':
                result.push(stack.pop())
            stack.pop()
            if stack.top() in functions:
                result.push(stack.pop())

    while stack.size() > 0 and stack.top() in operatorsPriority:
        result.push(stack.pop())

    output = ''
    result.reverse()
    while result.size() > 0:
        output += f'{result.pop()} '
    return output


if __name__ == "__main__":
    inputLine = '3 * ( sin ( 4 ) - 1 ) + 4 *  cos ( 2 )  * 7 )'
    print(sortStation(inputLine))
