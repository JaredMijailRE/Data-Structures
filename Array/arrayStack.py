class Stack:
    def __init__(self, max_size):
        self.max_size = max_size
        self.size = 0
        self.data = [None] * max_size

    def is_empty(self):
        return self.size == 0
    
    def is_full(self):
        return self.max_size == self.max_size

    def push(self, element):
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        self.data[self.size] = element
        self.size += 1

    def pop(self):
        if self.is_empty():
            raise IndexError("List is empty")
        self.size -= 1
        return self.data[self.size]

    def print(self):
        print("{ ", end="")
        for i in range(self.size):
            print(self.data[i], end=", " if i < self.size - 1 else "")
        print(" }")

class Solution:
    def __init__(self, len):
        self.stack = Stack(len)
    
    def isValid(self, s: str) -> bool:
        par_map = {')': '(', ']': '[', '}': '{'}
        for char in s:
            if char in par_map:  
                top_element = self.stack.pop() if self.stack.is_empty() else '#'
                if par_map[char] != top_element:
                    return False
            else:
                self.stack.push(char)
        return self.stack.is_empty()
    
while(True):
    s = input()
    solve = Solution(100)
    answer = solve.isValid(s)
    solve.stack.print()
    if(answer):
        print('YES')
    else:
        print('NO')
        
def isBalanced(s):
    try:
        if(int(s) == int):
                pass
    except:
        pass
    solve = Solution(100000)
    answer = solve.isValid(s)
    if(answer):
        return('YES')
    else:
        return('NO')