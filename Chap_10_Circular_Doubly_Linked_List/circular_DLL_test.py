from circular_DLL import CircularDLL

circular_DLL = CircularDLL()
circular_DLL.insert(5)
circular_DLL.insert(6)
circular_DLL.insert(3)
circular_DLL.insert(10)
circular_DLL.insert(21)
circular_DLL.delete_by_key(3)

circular_DLL_size = circular_DLL.size
keys = circular_DLL.key_list()
print("\nThe size of the circular DLL is {}\n".format(circular_DLL_size))
print("Key list is {}\n".format(keys))
print("Expected size is {}\n".format(4))
print("Expected key list is {}\n".format([21, 10, 6, 5]))

circular_DLL.delete_at_offset(2)
circular_DLL.insert_at_offset(123, 0)
circular_DLL.insert_at_offset(333, -1)
circular_DLL.insert_at_offset(77, -2)
circular_DLL.insert_at_offset(1211, 20)
circular_DLL.delete_at_offset(-4)

circular_DLL_size = circular_DLL.size
keys = circular_DLL.key_list()
print("\nThe size of the circular DLL is {}\n".format(circular_DLL_size))
print("Key list is {}\n".format(keys))
print("Expected size is {}\n".format(5))
print("Expected key list is {}\n".format([123, 21, 5, 77, 333]))
