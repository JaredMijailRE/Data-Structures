class StaticArrayList:
    def __init__(self, max_size):
        self.max_size = max_size
        self.size = 0
        self.data = [None] * max_size

    def is_empty(self):
        return self.size == 0

    def push_back(self, element):
        self.data[self.size] = element
        self.size += 1
    
    def findIsBigger(self, n: int):
        if(self.data[self.size-1] <= n):
            self.push_back(n)
        else:        
            for index in range(self.size):
                if(self.data[index] > n):
                    self.add_before(index, n)
                    break

    def add_before(self, index, element):
        for i in range(self.size, index, -1):
            self.data[i] = self.data[i - 1]
        self.data[index] = element
        self.size += 1
        
    def insert(self, n: int):
        if self.is_empty():
            self.push_back(n)
        elif(self.max_size == self.size):
            print('Lista llena')
        else:
            self.findIsBigger(n)
            
    def print_list(self):
        print("{ ", end="")
        for i in range(self.size):
            print(self.data[i], end=", " if i < self.size - 1 else "")
        print(" }")

list = StaticArrayList(100)
while(True):
    n = int(input('values: '))
    list.insert(n)
    list.print_list()