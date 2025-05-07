class Node:
    def __init__(self, value, quantity):
        self.value = value
        self.quantity = quantity
        self.left = None
        self.right = None
        
class BST:
    def __init__(self, value=None):
        """Initialize the BST. Optionally start with a value."""
        self.root = None
        if value is not None:
            self.root = Node(value, None)
    
    def insert(self, value, quantity):
        """Insert a new node with the specified value."""
        if self.root is None:
            self.root = Node(value, quantity)
            return
        
        current = self.root
        while True:
            if value < current.value:
                if current.left is None:
                    current.left = Node(value, quantity)
                    return
                current = current.left
            elif value > current.value:
                if current.right is None:
                    current.right = Node(value, quantity)
                    return
                current = current.right
            else:
                # Si el nodo ya existe, no se inserta uno nuevo.
                return

    def find(self, value):
        """Search for a node with the given value.
        
        Returns:
            The node if found; otherwise, None.
        """
        current = self.root
        while current:
            if value < current.value:
                current = current.left
            elif value > current.value:
                current = current.right
            else:
                return current  
        return None

    def delete(self, value):
        """Delete the node with the given value from the tree."""
        def _delete(node, value):
            if node is None:
                return None
            if value < node.value:
                node.left = _delete(node.left, value)
            elif value > node.value:
                node.right = _delete(node.right, value)
            else:
                if node.left is None:
                    return node.right
                if node.right is None:
                    return node.left
                successor = node.right
                while successor.left:
                    successor = successor.left
                node.value = successor.value
                node.quantity = successor.quantity
                node.right = _delete(node.right, successor.value)
            return node
        
        self.root = _delete(self.root, value)
    
    def height(self):
        """Return the height of the tree (number of levels)."""
        def _height(node):
            if node is None:
                return 0
            return 1 + max(_height(node.left), _height(node.right))
        return _height(self.root)
    
    def traverse(self):
        """Return an in-order traversal (sorted order) of the tree's values."""
        result = []
        def _inorder(node: Node):
            if node:
                _inorder(node.left)
                result.append(node.value)
                result.append(node.quantity)
                _inorder(node.right)
        _inorder(self.root)
        return result
    
    def __print__(self):
        """Print the tree with indentation representing the depth (like a file system)."""
        def _print(node, indent=""):
            if node is not None:
                print(indent + str(node.value))
                if node.left or node.right:
                    if node.left:
                        _print(node.left, indent + "    ")
                    else:
                        print(indent + "    " + "None")
                    if node.right:
                        _print(node.right, indent + "    ")
                    else:
                        print(indent + "    " + "None")
        _print(self.root)
        
def format(result: list) -> str:
    n = ""
    for index in range(len(result)//2):
        n = n  + str(result[index*2]) + ": " + str(result[index*2+1])
        if index != len(result)//2 - 1:
            n = n + " | "
    return n
        
if '__main__' == __name__:
    tr = BST()
    n = int(input())
    for _ in range(n):
        command = input().split()

        if command[0] == '1':  # find e insertar o actualizar
            result = tr.find(int(command[1]))
            if result is not None:
                result.quantity = result.quantity + int(command[2])
            else:   
                tr.insert(int(command[1]), int(command[2]))
        elif command[0] == '2':
            result = tr.find(int(command[1]))
            if result is not None:
                print(result.quantity)
            else:
                print(0)
        elif command[0] == '3':
            tr.delete(int(command[1]))
        elif command[0] == '4':
            print(format(tr.traverse()))