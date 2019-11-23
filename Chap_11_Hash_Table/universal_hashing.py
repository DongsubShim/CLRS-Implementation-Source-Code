import random

class UniversalHashing:
    """
    Universal Hashing

    for a hash table with m number of slots,
    if two distinct keys in a set were inserted
    using universal hashing function,
    the expected value of the probability of collision
    would be at most 1 / m.

    e.g.) h(k, m) = ((a*k + b) mod p) mod m
            where k is a key in an input set,
            m is the number of slots of a target hash table,
            p is a prime number larger than the maximum
                key value in the set,
            and a and b are integers randomly chosen
                from two uniformly distributed ranges,
                [1, p-1] and [0, p-1], respectively.
    """
    def __init__(self, max_key, m, n):
        self.__n = n # total number of keys in the set
        self.__m = m
        self.__max_key = max_key
        self.__p = self.prime_number()
        self.__a, self.__b = self.choose_coefficients()
        self.function = self.universal_hashing_function

    def is_prime(self, value):
        """
        Return true if value is a prime number, false otherwise
        """
        if(value < 2):
            return False
        for i in range(2, value):
            if(value % i == 0):
                return False
        return True

    def prime_number(self):
        """
        Return p at least larger than max_key
        """
        value = self.__max_key + 1
        while(not self.is_prime(value)):
            value += 1
        return value

    def choose_coefficients(self):
        """
        Choose a and b, and return them
        """
        if(self.__n < 2):
            return 0, 0
        a = random.randint(1, self.__p - 1)
        b = random.randint(0, self.__p - 1)
        return a, b

    def universal_hashing_function(self, key):
        """
        Return a universal hashing function
            of the form: h(k, m) = ((a*k + b) mod p) mod m
        """
        return ((self.__a * key + self.__b) % self.__p) % self.__m
