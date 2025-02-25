class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        
class BST:
    def __init__(self, value=None):
        """Initialize the BST. Optionally start with a value."""
        self.root = None
        if value is not None:
            self.root = Node(value)
    
    def insert(self, value):
        """Insert a new node with the specified value."""
        if self.root is None:
            self.root = Node(value)
            return
        
        current = self.root
        while True:
            if value < current.value:
                if current.left is None:
                    current.left = Node(value)
                    return
                current = current.left
            elif value > current.value:
                if current.right is None:
                    current.right = Node(value)
                    return
                current = current.right
            else:
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
        def _inorder(node):
            if node:
                _inorder(node.left)
                result.append(node.value)
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
        
        
    def __str__(self):
        pass
