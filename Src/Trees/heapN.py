class DaryHeap:
    def __init__(self, d=2):
        """
        Inicializa el heap con un parámetro d que indica el número de hijos por nodo.
        Por defecto es 2 (heap binario), pero puede ser 3 (heap ternario), etc.
        """
        self.heap = []
        self.d = d

    def insert(self, value):
        """Inserta un elemento en el heap."""
        self.heap.append(value)
        self._sift_up(len(self.heap) - 1)

    def find(self, value):
        """
        Busca un elemento en el heap.
        Devuelve el índice del elemento si se encuentra, o -1 en caso contrario.
        """
        for i, val in enumerate(self.heap):
            if val == value:
                return i
        return -1

    def delete(self, value):
        """
        Elimina un elemento del heap.
        Devuelve True si se eliminó el elemento, o False si no se encontró.
        """
        index = self.find(value)
        if index == -1:
            return False  # Elemento no encontrado

        last_index = len(self.heap) - 1
        # Reemplaza el elemento a eliminar con el último elemento
        self.heap[index] = self.heap[last_index]
        self.heap.pop()

        # Si no era el último elemento, reajustar el heap
        if index < len(self.heap):
            self._sift_down(index)
            self._sift_up(index)
        return True

    def _sift_up(self, index):
        """
        Mueve el elemento en el índice hacia arriba hasta restaurar la propiedad del heap.
        En un heap d-ario, el padre de un nodo en el índice i se encuentra en (i-1) // d.
        """
        parent = (index - 1) // self.d
        while index > 0 and self.heap[index] < self.heap[parent]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            index = parent
            parent = (index - 1) // self.d

    def _sift_down(self, index):
        """
        Mueve el elemento en el índice hacia abajo hasta restaurar la propiedad del heap.
        En un heap d-ario, los hijos de un nodo en el índice i se encuentran en:
            d * i + 1, d * i + 2, ..., d * i + d
        """
        n = len(self.heap)
        while True:
            smallest = index
            # Revisa cada hijo del nodo actual
            for i in range(1, self.d + 1):
                child = self.d * index + i
                if child < n and self.heap[child] < self.heap[smallest]:
                    smallest = child
            if smallest == index:
                break
            self.heap[index], self.heap[smallest] = self.heap[smallest], self.heap[index]
            index = smallest

    def peek(self):
        """Devuelve el elemento mínimo sin eliminarlo (o None si el heap está vacío)."""
        return self.heap[0] if self.heap else None

    def extract_min(self):
        """
        Elimina y devuelve el elemento mínimo del heap.
        Devuelve None si el heap está vacío.
        """
        if not self.heap:
            return None
        min_val = self.heap[0]
        self.delete(min_val)
        return min_val

    def height(self):
        """
        Calcula la altura del heap como un árbol d-ario completo.
        La fórmula utilizada es:
            altura = ceil(log_d((n-1)*(d-1)+1)) - 1
        donde n es el número de elementos.
        """
        import math
        n = len(self.heap)
        if n == 0:
            return 0
        return math.ceil(math.log((n - 1) * (self.d - 1) + 1, self.d)) - 1

    def __str__(self):
        """Representación en cadena del heap."""
        return str(self.heap)
