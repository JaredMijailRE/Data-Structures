class NodoAVL:
    def __init__(self, fecha, titulo):
        self.fecha = fecha
        self.titulo = titulo
        self.izquierdo = None
        self.derecho = None
        self.altura = 1

class ArbolAVL:
    def __init__(self):
        self.root = None

    def _nodeHeight(self, nodo):
        if not nodo:
            return 0
        return nodo.altura

    def getBalance(self, nodo):
        if not nodo:
            return 0
        return self._nodeHeight(nodo.izquierdo) - self._nodeHeight(nodo.derecho)

    def rotacionDerecha(self, y):
        x = y.izquierdo
        T2 = x.derecho
        x.derecho = y
        y.izquierdo = T2
        y.altura = 1 + max(self._nodeHeight(y.izquierdo), self._nodeHeight(y.derecho))
        x.altura = 1 + max(self._nodeHeight(x.izquierdo), self._nodeHeight(x.derecho))
        return x

    def rotacionIzquierda(self, x):
        y = x.derecho
        T2 = y.izquierdo
        y.izquierdo = x
        x.derecho = T2
        x.altura = 1 + max(self._nodeHeight(x.izquierdo), self._nodeHeight(x.derecho))
        y.altura = 1 + max(self._nodeHeight(y.izquierdo), self._nodeHeight(y.derecho))
        return y

    def _insert(self, raiz, fecha, titulo):
        if not raiz:
            return NodoAVL(fecha, titulo)
        if fecha < raiz.fecha:
            raiz.izquierdo = self._insert(raiz.izquierdo, fecha, titulo)
        elif fecha > raiz.fecha:
            raiz.derecho = self._insert(raiz.derecho, fecha, titulo)
        else:
            return raiz
        raiz.altura = 1 + max(self._nodeHeight(raiz.izquierdo), self._nodeHeight(raiz.derecho))
        balance = self.getBalance(raiz)
        if balance > 1 and fecha < raiz.izquierdo.fecha:
            return self.rotacionDerecha(raiz)
        if balance < -1 and fecha > raiz.derecho.fecha:
            return self.rotacionIzquierda(raiz)
        if balance > 1 and fecha > raiz.izquierdo.fecha:
            raiz.izquierdo = self.rotacionIzquierda(raiz.izquierdo)
            return self.rotacionDerecha(raiz)
        if balance < -1 and fecha < raiz.derecho.fecha:
            raiz.derecho = self.rotacionDerecha(raiz.derecho)
            return self.rotacionIzquierda(raiz)
        return raiz

    def insert(self, fecha, titulo):
        self.root = self._insert(self.root, fecha, titulo)

    def _find(self, raiz, fecha):
        if raiz is None:
            return None
        if raiz.fecha == fecha:
            return raiz
        elif fecha < raiz.fecha:
            return self._find(raiz.izquierdo, fecha)
        else:
            return self._find(raiz.derecho, fecha)

    def find(self, fecha):
        return self._find(self.root, fecha)

    def nodoMinimo(self, nodo):
        actual = nodo
        while actual.izquierdo is not None:
            actual = actual.izquierdo
        return actual

    def _delete(self, raiz, fecha):
        if not raiz:
            return raiz
        if fecha < raiz.fecha:
            raiz.izquierdo = self._delete(raiz.izquierdo, fecha)
        elif fecha > raiz.fecha:
            raiz.derecho = self._delete(raiz.derecho, fecha)
        else:
            if raiz.izquierdo is None:
                temp = raiz.derecho
                raiz = None
                return temp
            elif raiz.derecho is None:
                temp = raiz.izquierdo
                raiz = None
                return temp
            temp = self.nodoMinimo(raiz.derecho)
            raiz.fecha = temp.fecha
            raiz.titulo = temp.titulo
            raiz.derecho = self._delete(raiz.derecho, temp.fecha)
        if not raiz:
            return raiz
        raiz.altura = 1 + max(self._nodeHeight(raiz.izquierdo), self._nodeHeight(raiz.derecho))
        balance = self.getBalance(raiz)
        if balance > 1 and self.getBalance(raiz.izquierdo) >= 0:
            return self.rotacionDerecha(raiz)
        if balance > 1 and self.getBalance(raiz.izquierdo) < 0:
            raiz.izquierdo = self.rotacionIzquierda(raiz.izquierdo)
            return self.rotacionDerecha(raiz)
        if balance < -1 and self.getBalance(raiz.derecho) <= 0:
            return self.rotacionIzquierda(raiz)
        if balance < -1 and self.getBalance(raiz.derecho) > 0:
            raiz.derecho = self.rotacionDerecha(raiz.derecho)
            return self.rotacionIzquierda(raiz)
        return raiz

    def delete(self, fecha):
        self.root = self._delete(self.root, fecha)

    def inOrden(self, raiz, result):
        if raiz:
            self.inOrden(raiz.izquierdo, result)
            result.append(f"{raiz.fecha}: {raiz.titulo}")
            self.inOrden(raiz.derecho, result)

    def imprimirAgenda(self):
        result = []
        self.inOrden(self.root, result)
        print(" | ".join(result))

if __name__ == "__main__":
    import sys
    sys.setrecursionlimit(100000)
    tree = ArbolAVL()
    n = int(input())
    for _ in range(n):
        line = input().split()
        op = line[0]
        if op == "1":
            fecha = int(line[1])
            titulo = line[2]
            if tree.find(fecha) is not None:
                print("-1")
            else:
                tree.insert(fecha, titulo)
                print("1")
        elif op == "2":
            fecha = int(line[1])
            nodo = tree.find(fecha)
            if nodo is not None:
                print(nodo.titulo)
            else:
                print(0)
        elif op == "3":
            fecha = int(line[1])
            tree.delete(fecha)
        elif op == "4":
            tree.imprimirAgenda()
