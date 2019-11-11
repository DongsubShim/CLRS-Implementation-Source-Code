from radix_sort import RadixSort
import numpy as np

array = np.array([32, 2, 5, 12, 5, 1, 9, 7, 11], dtype=int)
radix_obj = RadixSort(array)
sorted_array = radix_obj.sorted_array
print("\nsorted array is {}\n".format(sorted_array))
