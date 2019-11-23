class _DLLNode:
    """
    Node inside a circular doubly linked list
        - attributes: key, next, prev
    """
    def __init__(self, key, next, prev):
        self.key = key
        self.next = next
        self.prev = prev

class CircularDLL:
    """
    Circular Doubly Linked List
        - use sentinel node
    """
    def __init__(self):
        self.sentinel = _DLLNode(None, None, None)
        self.sentinel.next = self.sentinel
        self.sentinel.prev = self.sentinel
        self.size = 0

    def search_by_key(self, key):
        """
        Search for a node with the specified key
        Return that node
        If the key is not found, return the sentinel
        """
        # Search from the first node until the key is found from any node
        current_node = self.sentinel.next
        while(current_node.key != key):
            # If the sentinel appears during the search, return None
            if(current_node == self.sentinel):
                return None
            current_node = current_node.next
        return current_node

    def search_by_offset(self, offset):
        """
        Search for a node at the specified offset
        Return that node
        If the offset is out-of-range, return the sentinel

        offset is similar to array index
        e.g.) offset of 1: next node of the sentinel
        e.g.) offset of -1: previous node of the sentinel
        """
        if(isinstance(offset, int)):
            # if offset is non-negative, use next pointers iteratively
            # to search from the sentinel
            if(offset >= 1):
                current_node = self.sentinel.next
                for i in range(1, offset):
                    if(current_node == self.sentinel):
                        return None
                    current_node = current_node.next
                return current_node
            # if offset is negative, use prev pointers iteratively
            # to search from the prev of the sentinel
            current_node = self.sentinel.prev
            for i in range(1, -1 * offset):
                if(current_node == self.sentinel):
                    return None
                current_node = current_node.prev
            return current_node
        return None

    def insert_next_to_node(self, key, node):
        """
        Insert a node next to the specified node
        """
        if(key != None and node != None):
            # Create a node with the specified 'key' value
            # - this node's 'prev' pointer points to the specified node
            # - this node's 'next' pointer points to that node
            #       pointed to by the specified node's 'next' pointer
            insert_node = _DLLNode(key, node.next, node)

            # That node's 'prev' pointer points to this node
            node.next.prev = insert_node
            # The specified node's 'next' pointer points to this node
            node.next = insert_node
            # Increment the size of the circularDLL
            self.size += 1

    def insert_at_offset(self, key, offset):
        """
        Insert a node next to the node at the offset
        """
        if(offset == 0):
            self.insert(key)
            return
        node_at_offset = self.search_by_offset(offset)
        self.insert_next_to_node(key, node_at_offset)

    def insert(self, key):
        """
        Insert a node next to the sentinel node
        """
        self.insert_next_to_node(key, self.sentinel)

    def delete(self, delete_node):
        """
        Delete a specified node
        Update the attributes of its neighboring nodes
        """
        if(delete_node != self.sentinel and delete_node != None):
            prev_node = delete_node.prev
            next_node = delete_node.next

            # Let the neighboring nodes point to each other
            prev_node.next = next_node
            next_node.prev = prev_node

            # Decrement the size of the CircularDLL
            self.size -= 1

    def delete_at_offset(self, offset):
        """
        Delete a node at the offset
        """
        delete_node = self.search_by_offset(offset)
        self.delete(delete_node)

    def delete_by_key(self, key):
        """
        Delete a node which has the key
        """
        # Find which node has that key
        delete_node = self.search_by_key(key)
        # If there is any node with that key,
        #   delete that node by calling delete function
        self.delete(delete_node)

    def key_list_helper(self, node, keys):
        """
        Helper function for key_list
        Recursively append the node's key value to the list
        Return the list when the sentinel node is encountered
        """
        if(node == self.sentinel):
            return keys
        else:
            keys.append(node.key)
            return self.key_list_helper(node.next, keys)

    def key_list(self):
        """
        Return a list of all keys
        Recursively append the key values using its helper function
        """
        return self.key_list_helper(self.sentinel.next, [])
