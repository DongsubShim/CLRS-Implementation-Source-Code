from universal_hashing import UniversalHashing
from circular_DLL import CircularDLL

class HashTableChain:
    """
    Hash table
    - use chaining (circular doubly linked list) to resolve collision
    - use universal hashing function
    """
    def __init__(self, max_key, m, n):
        self.hash_table = self.make_hash_table(m)
        self.__hash_function = UniversalHashing(max_key, m, n).function

    def make_hash_table(self, m):
        """
        Create a list of size m (i.e., m slots)
        Each element is a sentinel node
            for an empty circular doubly linked list
        """
        initial_hash_table = []
        for i in range(m):
            initial_hash_table.append(CircularDLL())
        return initial_hash_table

    def get_hash(self, key):
        """
        Return a hash value for a key using a universal hashing function
        """
        return self.__hash_function(key)

    def insert(self, key):
        """
        Insert a key using a universal hashing function
        """
        hash = self.get_hash(key)
        self.hash_table[hash].insert(key)
        return

    def search(self, key):
        """
        Search a key using a universal hashing function
        Return a pointer to the first object with the key
            in the slot specified by the hash value
        If the key is not found, return the slot's sentinel node
        """
        hash = self.get_hash(key)
        return self.hash_table[hash].search_by_key(key)

    def delete(self, key):
        """
        Delete a key using a universal hashing function
        """
        hash = self.get_hash(key)
        self.hash_table[hash].delete_by_key(key)

    def key_list(self):
        """
        Return a list in the following format:
            [[<KEYS IN FIRST SLOT>],
             [<KEYS IN SECOND SLOT>], ...]

            e.g.)
            [[1, 3, 5], [2, 9], [], [13, 21], []]
        """
        key_list = []
        for (i, s) in enumerate(self.hash_table):
            key_list.append(s.key_list())
        return key_list
