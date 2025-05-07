# ---------------------------------------------------- Version 1
class Array:
    def __init__(self, size: int):
        self.size = size
        self.array = []
        self.array = [None] * size
        self.last = 0
    
    def printf(self): #1
        text = ""
        for index, n in enumerate(self.array):
            if (n != None):
                if(index == 0):
                    text = text + str(n)
                else:
                    text = text + " " + str(n)
        text = '[' + text + ']'
        print('Elementos en el arreglo: ' + text)

    def addEnd(self, insert): #2
        try:
            self.array[self.last] = insert
            self.last += 1
        except:
            print('Error: Lista llena. No se puede agregar el elemento.')


    def removeLast(self): #3s
        if (not(self.last <= 0)):
            self.array[self.last-1] = None
            self.last -= 1
        else:
            print('Error: Lista vacia. No se puede eliminar el elemento.')


    def addBeginning(self, insert): #4
        for index in range(self.size):
            n = len(self.array) - index - 1 
            if(self.array[n] != None):
                try: 
                    self.array[n+1] = self.array[n]
                except:
                    pass
        if(self.array[0] == None):
            self.array[0] = insert
        self.array[0] = insert
            

    def removeBeginning(self): #5
        for index in range(self.size):
            if(self.array[index] != None):
                try:
                    self.array[index] = self.array[index+1]
                except:
                    self.array[index] = None
        
    def selector(self, select: str):
        
        if select.startswith('1'):
            self.printf()
        elif select.startswith('2'):
            text = select.split()
            self.addEnd(text[1])
        elif select.startswith('3'):
            self.removeLast()
        elif select.startswith('4'):
            text = select.split()
            self.addBeginning(text[1])
        elif select.startswith('5'):
            self.removeBeginning()
            

size = input()
Array = Array(int(size))
while True:
    try:
        selections = input()
    except EOFError:
        break
    Array.selector(selections)

# ---------------------------------------------------- Version 2
class Array:
    def __init__(self, size: int):
        self.size = size
        self.array = []
        self.array = [None] * size
        self.last = 0
    
    def printf(self): #1
        text = ""
        for index, n in enumerate(self.array):
            if (n != None):
                if(index == 0):
                    text = text + str(n)
                else:
                    text = text + " " + str(n)
        text = '[' + text + ']'
        print('Elementos en el arreglo: ' + text)

    def addEnd(self, insert): #2
        try:
            self.array[self.last] = insert
            self.last += 1
        except:
            print('Error: Lista llena. No se puede agregar el elemento.')


    def removeLast(self): #3s
        if (not(self.last <= 0)):
            self.array[self.last-1] = None
            self.last -= 1
        else:
            print('Error: Lista vacia. No se puede eliminar el elemento.')


    def addBeginning(self, insert): #4
        for index in range(self.size):
            n = len(self.array) - index - 1 
            if(self.array[n] != None):
                try: 
                    self.array[n+1] = self.array[n]
                except:
                    pass
        if(self.array[0] == None):
            self.array[0] = insert
        self.array[0] = insert
            

    def removeBeginning(self): #5
        for index in range(self.size):
            if(self.array[index] != None):
                try:
                    self.array[index] = self.array[index+1]
                except:
                    self.array[index] = None
        
    def selector(self, select: str):
        
        if select.startswith('1'):
            self.printf()
        elif select.startswith('2'):
            text = select.split()
            self.addEnd(text[1])
        elif select.startswith('3'):
            self.removeLast()
        elif select.startswith('4'):
            text = select.split()
            self.addBeginning(text[1])
        elif select.startswith('5'):
            self.removeBeginning()
            

size = input()
Array = Array(int(size))
while True:
    try:
        selections = input()
    except EOFError:
        break
    Array.selector(selections)

# ---------------------------------------------------- Version 3
class Array:
    def __init__(self, size: int):
        self.size = size
        self.array = [None] * size
        self.last = 0
    
    def printf(self): #1
        text = ""
        for index in range(self.last):
            n = self.array[index]
            if(index == 0):
                text = text + str(n)
            else:
                text = text + " " + str(n)
        text = '[' + text + ']'
        print('Elementos en el arreglo: ' + text)

    def addEnd(self, insert): #2
        try:
            self.array[self.last] = insert
            self.last += 1
        except:
            print('Error: Lista llena. No se puede agregar el elemento.')


    def removeLast(self): #3
        if (not(self.last <= 0)):
            self.last -= 1
        else:
            print('Error: Lista vacia. No se puede eliminar el elemento.')


    def addBeginning(self, insert): #4
        for index in range(self.last):
            n = self.last - index 
            self.array[n] = self.array[n - 1 ]
        self.array[0] = insert
        self.last += 1
            

    def removeBeginning(self): #5
        for index in range(self.size-1):
            self.array[index] = self.array[index+1]
        self.last -= 1
        
    def selector(self, select: str):
        
        if select.startswith('1'):
            self.printf()
        elif select.startswith('2'):
            text = select.split()
            self.addEnd(text[1])
        elif select.startswith('3'):
            self.removeLast()
        elif select.startswith('4'):
            text = select.split()
            self.addBeginning(text[1])
        elif select.startswith('5'):
            self.removeBeginning()
            

size = input()
Array = Array(int(size))
while True:
    try:
        selections = input()
    except EOFError:
        break
    Array.selector(selections)