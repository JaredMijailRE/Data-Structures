class Stack:
    def __init__(self, max_size):
        self.max_size = max_size
        self.size = 0
        self.data = [None] * max_size

    def is_empty(self):
        return self.size == 0

    def is_full(self):
        return self.size == self.max_size

    def push(self, element):
        if self.is_full():
            raise OverflowError("Stack is full")
        self.data[self.size] = element
        self.size += 1

    def pop(self):
        if self.is_empty():
            raise IndexError("Stack is empty")
        self.size -= 1
        return self.data[self.size]

    def print(self):
        print("{ ", end="")
        for i in range(self.size):
            print(self.data[i], end=", " if i < self.size - 1 else "")
        print(" }")

def evaluar(expression):
    tokens = expression.split()
    stack = Stack(len(tokens))
    operan = {'+', '-', '*', '/'}
    for token in reversed(tokens):
        if token not in operan:
            stack.push(token)
        else:
            operand1 = stack.pop()
            operand2 = stack.pop()
            infix_expression = f"({operand1} {token} {operand2})"
            stack.push(infix_expression)
    final_expression = stack.pop()
    result = eval(final_expression)
    return f"{final_expression} = {result}"

