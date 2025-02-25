class HashTable:
    def __init__(self, size: int, hash_function: object = None):
        """
        Constructor de la clase HashTable usando encadenamiento.
        
        :param size: Tamaño de la tabla hash.
        :param hash_function: Función hash personalizada; si no se proporciona, se usa hash(key) % size.
        """
        self.size = size
        self.table = [[] for _ in range(size)]  # Cada casilla es una lista vacía.
        self.hash_function = hash_function if hash_function is not None else (lambda key: hash(key) % size)

    def insert(self, key, value):
        """
        Inserta el par (clave, valor) en la tabla.
        Si la clave ya existe, se actualiza el valor.
        """
        index = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                self.table[index][i] = (key, value)
                return
        self.table[index].append((key, value))

    def search(self, key):
        """
        Busca la clave y retorna su valor asociado; si no existe, retorna None.
        """
        index = self.hash_function(key)
        for k, v in self.table[index]:
            if k == key:
                return v
        return None

    def remove(self, key):
        """
        Elimina el par (clave, valor) de la tabla.
        Retorna el valor eliminado o None si la clave no existe.
        """
        index = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                del self.table[index][i]
                return v
        return None

    def update(self, key, value):
        """
        Actualiza el valor asociado a la clave.
        Lanza KeyError si la clave no se encuentra.
        """
        index = self.hash_function(key)
        for i, (k, _) in enumerate(self.table[index]):
            if k == key:
                self.table[index][i] = (key, value)
                return
        raise KeyError("Clave no encontrada")

    def __str__(self):
        """
        Retorna una representación en cadena de la tabla hash.
        """
        result = []
        for i, bucket in enumerate(self.table):
            result.append(f"{i}: {bucket}")
        return "\n".join(result)

