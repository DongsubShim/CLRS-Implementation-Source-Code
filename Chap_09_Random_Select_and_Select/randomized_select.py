from random import randint
import numpy as np 

class RandomSelect:
	"""
	Randomized selection of i th smallest element of an input array
	"""
	def __init__(self, array, i_th):
		self.input_array = array.copy()
		self.array = array
		# i_th: order statistics for the whole array
		self.i_th = i_th
		# temp_i_th: order statistics for subarrays
		self.temp_i_th = i_th
		self.i_th_smallest = self.random_select(0, len(self.array) - 1)

	def exchange_elements(self, p, r):
		"""
		Exchange two elements of an input array based on their indices
		"""
		temp = self.array[p]
		self.array[p] = self.array[r]
		self.array[r] = temp
		return

	def random_pivot_index(self, p, r):
		"""
		Return random index for selecting a pivot
		"""
		return randint(p, r)

	def random_partition(self, p, r):
		"""
		Split input array into two: low side and high side of the partition

		Return pivot's index after partitioning is done
		"""
		i = p - 1
		j = p
		random_pivot_index = self.random_pivot_index(p, r)
		pivot_element = self.array[random_pivot_index]
		self.exchange_elements(random_pivot_index, r)

		for j in range(p, r):
			if(self.array[j] <= pivot_element):
				i += 1
				self.exchange_elements(i, j)

		final_pivot_index = i + 1
		self.exchange_elements(final_pivot_index, r)

		return final_pivot_index


	def random_select(self, p, r):
		"""
		Recursively partition one of the sides that contains i th smallest element

		Return i th smallest element 

		Only pivot element is guaranteed to be in correct ascending order in the input array after partitioning

		Determine the order statistics of i th smallest element in the subarray, and save that in temp_i_th
		Use temp_i_th and pivot element to see which side would have i th smallest element

		Return the pivot as i th smallest element if the number of elements in the low side equals temp_i_th,
		or the only element if there is one element left in the subarray
		"""
		if(p == r):
			return self.array[p]

		final_pivot_index = self.random_partition(p, r)
		k = final_pivot_index - p + 1

		if(self.temp_i_th == k):
			return self.array[final_pivot_index]

		elif(self.temp_i_th < k):
			return self.random_select(p, final_pivot_index - 1)

		else:
			# already know k number of elements are smaller than i th smallest element
			# determine order statistics in the high side by subtracting k from temp_i_th
			self.temp_i_th = self.temp_i_th - k
			return self.random_select(final_pivot_index + 1, r)
