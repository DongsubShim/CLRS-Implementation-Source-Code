from randomized_select import RandomSelect 
from select import Select
import numpy as np 

input_array = np.array([2, 38, 582, 5, 22, 73, 91, 62, 83, 99, 7])
order_smallest = (int)(input("Please enter which order statistics to find: "))
random_select_obj = RandomSelect(input_array, order_smallest)
i_th_smallest = random_select_obj.i_th_smallest
print()
print("Random Select: {}th smallest element in input array is {}\n".format(order_smallest, i_th_smallest))

select_obj = Select(input_array, order_smallest)
i_th_smallest = select_obj.i_th_smallest
print("Select: {}th smallest element in input array is {}\n".format(order_smallest, i_th_smallest))