import arrayMy as ar

class DinamycArrayList(ar.StaticArrayList ):
    def push_front(self, element):
        if self.size >= self.max_size:
            self.max_size = self.max_size * 2
            NewArray = ar.StaticArrayList(self.max_size)
            for index, value in  enumerate(self.data):
                NewArray.data[index] = value
            self.data = NewArray.data
            
        for i in range(self.size, 0, -1):
            self.data[i] = self.data[i - 1]
        self.data[0] = element
        self.size += 1

    def push_back(self, element):
        if self.size >= self.max_size:
            raise OverflowError("List is full")
        self.data[self.size] = element
        self.size += 1

        