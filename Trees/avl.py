class NodoAVL:
    def __init__(self, valor):
        self.valor = valor
        self.izquierdo = None
        self.derecho = None
        self.altura = 1

class ArbolAVL:
    def __init__(self):
        self.root = None

    def insert(self, valor):
        self.root = self._insert(self.root, valor)

    def _insert(self, raiz, valor):
        if not raiz:
            return NodoAVL(valor)
        
        if valor < raiz.valor:
            raiz.izquierdo = self._insert(raiz.izquierdo, valor)
        else:
            raiz.derecho = self._insert(raiz.derecho, valor)

        raiz.altura = 1 + max(self._nodeHeight(raiz.izquierdo), self._nodeHeight(raiz.derecho))
        balance = self.getBalance(raiz)

        if balance > 1 and valor < raiz.izquierdo.valor:
            return self.rotacionDerecha(raiz)
        if balance < -1 and valor > raiz.derecho.valor:
            return self.rotacionIzquierda(raiz)
        if balance > 1 and valor > raiz.izquierdo.valor:
            raiz.izquierdo = self.rotacionIzquierda(raiz.izquierdo)
            return self.rotacionDerecha(raiz)
        if balance < -1 and valor < raiz.derecho.valor:
            raiz.derecho = self.rotacionDerecha(raiz.derecho)
            return self.rotacionIzquierda(raiz)

        return raiz

    def _nodeHeight(self, nodo):
        if not nodo:
            return 0
        return nodo.altura

    def height(self):
        return self._nodeHeight(self.root)

    def getBalance(self, nodo):
        if not nodo:
            return 0
        return self._nodeHeight(nodo.izquierdo) - self._nodeHeight(nodo.derecho)

    def rotacionDerecha(self, y):
        x = y.izquierdo
        T2 = x.derecho
        
        # Realizar rotación
        x.derecho = y
        y.izquierdo = T2
        
        # Actualizar alturas
        y.altura = 1 + max(self._nodeHeight(y.izquierdo), self._nodeHeight(y.derecho))
        x.altura = 1 + max(self._nodeHeight(x.izquierdo), self._nodeHeight(x.derecho))
        
        return x

    def rotacionIzquierda(self, x):
        y = x.derecho
        T2 = y.izquierdo
        
        # Realizar rotación
        y.izquierdo = x
        x.derecho = T2
        
        # Actualizar alturas
        x.altura = 1 + max(self._nodeHeight(x.izquierdo), self._nodeHeight(x.derecho))
        y.altura = 1 + max(self._nodeHeight(y.izquierdo), self._nodeHeight(y.derecho))
        
        return y

    # Recorridos (se puede usar un método wrapper para iniciar en self.root)
    def preOrden(self, raiz=None):
        if raiz is None:
            raiz = self.root
        if not raiz:
            return
        print(raiz.valor, end=" ")
        self.preOrden(raiz.izquierdo)
        self.preOrden(raiz.derecho)

    def inOrden(self, raiz=None):
        if raiz is None:
            raiz = self.root
        if not raiz:
            return
        self.inOrden(raiz.izquierdo)
        print(raiz.valor, end=" ")
        self.inOrden(raiz.derecho)

    def postOrden(self, raiz=None):
        if raiz is None:
            raiz = self.root
        if not raiz:
            return
        self.postOrden(raiz.izquierdo)
        self.postOrden(raiz.derecho)
        print(raiz.valor, end=" ")

    # Método para buscar (find) un nodo con un valor dado
    def find(self, valor, raiz=None):
        if raiz is None:
            raiz = self.root
        if not raiz:
            return None
        if raiz.valor == valor:
            return raiz
        elif valor < raiz.valor:
            return self.find(valor, raiz.izquierdo)
        else:
            return self.find(valor, raiz.derecho)

    def nodoMinimo(self, nodo):
        actual = nodo
        while actual.izquierdo is not None:
            actual = actual.izquierdo
        return actual

    # Método público para eliminar un nodo con un valor dado
    def delete(self, valor):
        self.root = self._delete(self.root, valor)

    # Método recursivo para eliminar un nodo
    def _delete(self, raiz, valor):
        if not raiz:
            return raiz

        if valor < raiz.valor:
            raiz.izquierdo = self._delete(raiz.izquierdo, valor)
        elif valor > raiz.valor:
            raiz.derecho = self._delete(raiz.derecho, valor)
        else:
            # Nodo encontrado
            if raiz.izquierdo is None:
                temp = raiz.derecho
                raiz = None
                return temp
            elif raiz.derecho is None:
                temp = raiz.izquierdo
                raiz = None
                return temp
            # Nodo con dos hijos: obtener el sucesor in-orden
            temp = self.nodoMinimo(raiz.derecho)
            raiz.valor = temp.valor
            raiz.derecho = self._delete(raiz.derecho, temp.valor)

        if raiz is None:
            return raiz

        raiz.altura = 1 + max(self.height(raiz.izquierdo), self.height(raiz.derecho))
        balance = self.getBalance(raiz)

        # Rebalancear si es necesario
        # Caso Left Left
        if balance > 1 and self.getBalance(raiz.izquierdo) >= 0:
            return self.rotacionDerecha(raiz)
        # Caso Left Right
        if balance > 1 and self.getBalance(raiz.izquierdo) < 0:
            raiz.izquierdo = self.rotacionIzquierda(raiz.izquierdo)
            return self.rotacionDerecha(raiz)
        # Caso Right Right
        if balance < -1 and self.getBalance(raiz.derecho) <= 0:
            return self.rotacionIzquierda(raiz)
        # Caso Right Left
        if balance < -1 and self.getBalance(raiz.derecho) > 0:
            raiz.derecho = self.rotacionDerecha(raiz.derecho)
            return self.rotacionIzquierda(raiz)

        return raiz
