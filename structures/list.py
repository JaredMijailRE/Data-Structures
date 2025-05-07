class StaticArrayList:
    def __init__(self, max_size):
        self.max_size = max_size
        self.size = 0
        self.data = [None] * max_size

    def empty(self):
        return self.size == 0

    def pushFront(self, element):
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        for i in range(self.size, 0, -1):
            self.data[i] = self.data[i - 1]
        self.data[0] = element
        self.size += 1

    def pushBack(self, element):
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        self.data[self.size] = element
        self.size += 1

    def popFront(self):
        if self.empty():
            raise IndexError("List is empty")
        for i in range(self.size - 1):
            self.data[i] = self.data[i + 1]
        self.size -= 1

    def popBack(self):
        if self.empty():
            raise IndexError("List is empty")
        self.size -= 1

    def find(self, element):
        for i in range(self.size):
            if self.data[i] == element:
                return True
        return False

    def erase(self, element):
        index = -1
        for i in range(self.size):
            if self.data[i] == element:
                index = i
                break
        if index == -1:
            raise ValueError("Element not found")
        for i in range(index, self.size - 1):
            self.data[i] = self.data[i + 1]
        self.size -= 1

    def addBefore(self, target, element):
        index = -1
        for i in range(self.size):
            if self.data[i] == target:
                index = i
                break
        if index == -1:
            raise ValueError("Target not found")
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        for i in range(self.size, index, -1):
            self.data[i] = self.data[i - 1]
        self.data[index] = element
        self.size += 1

    def addAfter(self, target, element):
        index = -1
        for i in range(self.size):
            if self.data[i] == target:
                index = i
                break
        if index == -1:
            raise ValueError("Target not found")
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        for i in range(self.size, index + 1, -1):
            self.data[i] = self.data[i - 1]
        self.data[index + 1] = element
        self.size += 1

    def print_list(self):
        print("{ ", end="")
        for i in range(self.size):
            print(self.data[i], end=", " if i < self.size - 1 else "")
        print(" }")
