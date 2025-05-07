class Heap:
    def __init__(self):
        """Inicializa el heap como una lista vacía."""
        self.heap = []

    def insert(self, value):
        """Inserta un elemento en el heap."""
        self.heap.append(value)
        self._sift_up(len(self.heap) - 1)

    def find(self, value):
        """
        Busca un elemento en el heap.
        Devuelve el índice del elemento si se encuentra, o -1 en caso contrario.
        """
        for i in range(len(self.heap)):
            if self.heap[i] == value:
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
        """
        parent = (index - 1) // 2
        while index > 0 and self.heap[index] < self.heap[parent]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            index = parent
            parent = (index - 1) // 2

    def _sift_down(self, index):
        """
        Mueve el elemento en el índice hacia abajo hasta restaurar la propiedad del heap.
        """
        n = len(self.heap)
        while 2 * index + 1 < n:
            smallest = index
            left = 2 * index + 1
            right = 2 * index + 2

            if left < n and self.heap[left] < self.heap[smallest]:
                smallest = left
            if right < n and self.heap[right] < self.heap[smallest]:
                smallest = right

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
        """Calcula la altura del heap como un árbol binario completo."""
        import math
        return math.ceil(math.log2(len(self.heap) + 1)) - 1 if self.heap else 0

    def __str__(self):
        """Representación en cadena del heap."""
        return str(self.heap)
