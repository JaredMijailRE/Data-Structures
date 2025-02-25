class UnionFind:
    def __init__(self, n):
        # Inicializa n conjuntos; cada elemento es su propio representante
        self.parent = [i for i in range(n)]
        self.rank = [0] * n  # Rango para la unión por tamaño
        
    def find(self, x):
        # Retorna el representante del conjunto al que pertenece x
        if self.parent[x] != x:
            # Compresión de caminos: actualiza el padre de x para apuntar al representante
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        # Une los conjuntos que contienen x e y
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX == rootY:
            return  # Ya están unidos

        # Unión por rango: el árbol de menor rango se cuelga del de mayor rango
        if self.rank[rootX] < self.rank[rootY]:
            self.parent[rootX] = rootY
        elif self.rank[rootX] > self.rank[rootY]:
            self.parent[rootY] = rootX
        else:
            self.parent[rootY] = rootX
            self.rank[rootX] += 1
            
    def connected(self, x, y):
        # Retorna True si x e y están en el mismo conjunto
        return self.find(x) == self.find(y)