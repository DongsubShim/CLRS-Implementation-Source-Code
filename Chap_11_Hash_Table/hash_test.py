from universal_hashing import UniversalHashing
from hash_table_chain import HashTableChain

# Check universal hashing function
n = 30
m = 20
max_key = 60
uh = UniversalHashing(max_key, m, n)
uhf = uh.function
uhf_set = set()
for k in range(0, 60, 2):
    uhf_set.add(uhf(k))
print("Number of slots with at least one key: {}".format(len(uhf_set)))
print("Slots containing at least one key: {}".format(uhf_set))

# Check hash table which uses chaining
n = 30
m = 20
max_key = 60
query_key = 30

hash_table_object = HashTableChain(max_key, m, n)
for k in range(0, 60, 2):
    hash_table_object.insert(k)
hash_table_object.delete(50)
search_node_key = hash_table_object.search(query_key).key
print("Query key: {}".format(query_key))
print("key of the node found: {}".format(search_node_key))
key_list = hash_table_object.key_list()
print("List of keys currently in hash table: {}".format(key_list))
