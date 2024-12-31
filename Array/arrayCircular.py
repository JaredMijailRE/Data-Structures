class SCA:
    def __init__(self, max_size):
        self.size = 0
        self.data = [None] * max_size
        self.start = 0

    def is_empty(self):
        if ((abs(self.start) + self.size) == 0):
            print('Error: Lista vacia. No se puede eliminar el elemento.')
        else: return False
    
    def is_full(self):
        if ((abs(self.start) + self.size) == len(self.data)):
            print('Error: Lista llena. No se puede agregar el elemento.')
        else: return False

    def push_front(self, element):
        if not(self.is_full()): 
            self.start -= 1
            self.data[self.start % len(self.data)] = element

    def push_back(self, element):
        if not(self.is_full()): 
            self.data[self.size % len(self.data)] = element
            self.size += 1

    def pop_front(self):
        if not(self.is_empty()): 
            self.start += 1

    def pop_back(self):
        if not(self.is_empty()):
            self.size -= 1

    def printf(self): #1
        text = ""
        for index in range(self.start, self.size):
            n = self.data[index]
            if(index == self.start):
                text = text + str(n)
            else:
                text = text + " " + str(n)
        text = '[' + text + ']'
        print('Elementos en el arreglo: ' + text)

    def selector(self, select: str):
        
        if select.startswith('1'):
            self.printf()
        elif select.startswith('2'):
            text = select.split()
            self.push_back(text[1])
        elif select.startswith('3'):
            self.pop_back()
        elif select.startswith('4'):
            text = select.split()
            self.push_front(text[1])
        elif select.startswith('5'):
            self.pop_front()
            

size = input()
Array = SCA(int(size))
while True:
    try:
        selections = input()
    except EOFError:
        break
    Array.selector(selections)