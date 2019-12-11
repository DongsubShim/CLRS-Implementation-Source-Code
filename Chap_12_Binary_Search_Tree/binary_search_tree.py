class Node:
    """
    Create a node which would be a part of a binary search tree
        - attributes: key, parent node, left child node, right child node
    """
    def __init__(self, key: int, parent=None, left=None, right=None):
        self.key = key
        self.parent = parent
        self.left = left
        self.right = right

class BinarySearchTree:
    """
    Build a binary search tree which accepts integer keys:

    The following dynamic set operations are supported:
        print, search, minimum, maximum,
        insert, delete, successsor, predecessor

    'list_inorder' function listifies all keys of
        a binary search tree or its subtree
    """

    def __init__(self, key: int):
        self.root = Node(key)

    def inorder_tree_walk(self, node, func):
        """
        Run input function on keys while performing an inorder tree walk
        """
        if(node):
            self.inorder_tree_walk(node.left, func)
            func(node.key)
            self.inorder_tree_walk(node.right, func)

    def list_inorder(self, subtree_root_node=None) -> list:
        """
        Return a list of all keys in a subtree of a binary search tree
            using an inorder tree walk
        """
        if(subtree_root_node == None):
            subtree_root_node = self.root
        key_list = []
        self.inorder_tree_walk(subtree_root_node, key_list.append)
        return key_list

    def print_inorder(self, subtree_root_node=None):
        """
        Print out all keys in a subtree of a binary search tree
            using an inorder tree walk
        """
        if(subtree_root_node == None):
            subtree_root_node = self.root
        self.inorder_tree_walk(subtree_root_node, print)

    def __repr__(self):
        return str(self.list_inorder())

    def search_key(self, key: int) -> Node:
        """
        Return a node containing an input key in a binary search tree
        """
        x = self.root
        while(x and x.key != key):
            if(x.key < key):
                x = x.right
            else:
                x = x.left
        return x

    def extremum(self, subtree_root_node, direction) -> Node:
        """
        Return a leaf node of a binary search tree by successively traveling
             in an input direction (i.e., left or right)
        """
        x = subtree_root_node
        while(x and getattr(x, direction)):
            x = getattr(x, direction)
        return x

    def minimum(self, subtree_root_node=None) -> Node:
        """
        Return a node with the smallest key value in a binary search tree
        """
        if(subtree_root_node == None):
            subtree_root_node = self.root
        return self.extremum(subtree_root_node, 'left')

    def maximum(self, subtree_root_node=None) -> Node:
        """
        Return a node with the largest key value in a binary search tree
        """
        if(subtree_root_node == None):
            subtree_root_node = self.root
        return self.extremum(subtree_root_node, 'right')

    def cessor_subroutine(self, node, direction, extremum_type) -> Node:
        """
        A subroutine for successor and predecessor
        """
        if(node == None):
            return None

        if(getattr(node, direction)):
            return extremum_type(getattr(node, direction))

        while(node.parent and getattr(node.parent, direction) == node):
            node = node.parent
        return node.parent

    def successor(self, node) -> Node:
        """
        Return a successor of an input node
        A successor's key should be the smallest among the keys
            that are larger than an input node's key
        """
        suc = self.cessor_subroutine(node, 'right', self.minimum)
        if(suc == None):
            print("No successor is found. Returned input node\n")
            return node
        return suc

    def predecessor(self, node) -> Node:
        """
        Return a predecessor of an input node
        A predecessor's key should be the largest among the keys
            that are smaller than an input node's key
        """
        prede = self.cessor_subroutine(node, 'left', self.maximum)
        if(prede == None):
            print("No predecessor is found. Returned input node\n")
            return node
        return prede

    def insert_node(self, node):
        """
        Insert a leaf node into a binary search tree
        """
        x = self.root
        y = None
        while(x):
            y = x
            if(x.key == node.key):
                return
            elif(x.key < node.key):
                x = x.right
            else:
                x = x.left

        node.parent = y
        if(y == None):
            self.root = node
        elif(node.key < y.key):
            y.left = node
        else:
            y.right = node

    def insert_key(self, key):
        """
        Create and insert a leaf node with an input key
            into a binary search tree
        """
        new_node = Node(key)
        self.insert_node(new_node)

    def insert_key_list(self, key_list):
        """
        Iteratively insert a leaf node for each input key
            into a binary search tree
        """
        for key in key_list:
            self.insert_key(key)

    def transplant(self, node_a, node_b):
        """
        Replace a node by another node

        If node_a's parent is called node_p,
        node_p replaces as a child node a with node b
        node b's parent is replaced by node_p
        """
        if(node_a.parent == None):
            self.root = node_b
        elif(node_a.parent.left == node_a):
            node_a.parent.left = node_b
        else:
            node_a.parent.right = node_b
        if(node_b):
            node_b.parent = node_a.parent

    def delete_node(self, node):
        """
        Detele a node from a binary search tree
        """
        if(node.left == None):
            self.transplant(node, node.right)
            return
        elif(node.right == None):
            self.transplant(node, node.left)
            return
        else:
            y = self.successor(node)
            if(y.parent != node):
                self.transplant(y, y.right)
                y.right = node.right
                node.right.parent = y
            self.transplant(node, y)
            y.left = node.left
            node.left.parent = y

    def delete_key(self, key):
        """
        Detele a node with an input key from a binary search tree
        """
        del_node = self.search_key(key)
        self.delete_node(del_node)
