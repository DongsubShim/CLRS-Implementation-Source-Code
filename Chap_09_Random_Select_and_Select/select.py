import numpy as np 

class Select:
	"""
	Select i th smallest element of a data array using deterministic partitioning

	Divide the data array into multiple groups of 5 elements and a group of the remainder
	Find the medians of each group, and the median of those medians
	Use that median as a deterministic pivot for partitioning
	Index arrays help find the median's index in the data array

	Repeat the process above on the side in which i th smallest element is
	Use temporary i variable (temp_i_th) to keep track of the position of 
	i th smallest element in the applicable side of each partition
	"""

	def __init__(self, data_array, i):
		self.original_data_array = data_array.copy()
		self.data_array = data_array
		self.i_th = i
		self.temp_i_th = i
		self.i_th_smallest = self.select(0, len(self.data_array) - 1)

	def exchange_elements(self, input_array, idx_1, idx_2):
		"""
		Exchange two elements of an input array
		"""
		temp = input_array[idx_1]
		input_array[idx_1] = input_array[idx_2]
		input_array[idx_2] = input_array[idx_1]

		return input_array

	def insertion_sort(self, index_array, start_idx, end_idx):
		"""
		Run insertion sort on a portion of the data array specified by the two indices
		Reflect the sorted order in the index array only
		Using index array makes it easier to find the index of the median
		Sort at most 5 elements at a time
		"""
		for i in range(start_idx, end_idx):
			j = i - 1
			while(j >= start_idx and self.data_array[index_array[i]] < self.data_array[index_array[j]]):
				index_array = self.exchange_elements(index_array, i, j)
				j -= 1

		return index_array

	def sort_groups(self, index_array, number_groups_of_five):
		"""
		Sort each group using insertion sort
		"""
		# initialize end index to zero in case there is no groups of five
		end_idx = 0
		# use insertion sort for the groups of five elements
		for i in range(0, number_groups_of_five):
			start_idx = i * 5
			end_idx = start_idx + 4
			self.insertion_sort(index_array, start_idx, end_idx)

		# use insertion sort for the remainder
		self.insertion_sort(index_array, end_idx, len(index_array) - 1)

		return index_array

	def medians_idx_array(self, input_array, number_groups_of_five):
		"""
		Return an array of indices of medians of each group in an input array
		"""
		medians_idx_array = np.zeros((number_groups_of_five + 1), dtype=int)

		# medians of the groups of five elements - occurs at a constant interval
		for i in range(0, number_groups_of_five):
			median_idx = 5 * i + 2
			np.append(medians_idx_array, input_array[median_idx])

		# find the first and the last indices of the remainder group
		first_idx_remainder = number_groups_of_five * 5
		last_idx = (len(input_array) - 1)

		# median of the remainder group
		median_idx_remainder = (last_idx - first_idx_remainder) // 2 + first_idx_remainder
		np.append(medians_idx_array, input_array[median_idx_remainder])

		return medians_idx_array

	def get_median_of_medians(self, index_array):
		"""
		Return the index of the median of the medians of the data array

		Run on the groups of five elements and the group with the remaining elements
		"""
		# the median is found when there is only one index left in the index array
		if(len(index_array) == 1):
			return index_array[0]

		# find the number of groups of five in the index array
		number_groups_of_five =len(index_array) // 5
		# insertion sort each group
		index_array = self.sort_groups(index_array, number_groups_of_five)
		# get an index array for the medians of the groups
		medians_idx_array = self.medians_idx_array(index_array, number_groups_of_five)
		# resursively find the median of the medians
		median_of_medians_idx = self.get_median_of_medians(medians_idx_array)

		return median_of_medians_idx

	def partition(self, p, r, pivot_idx):
		"""
		Partition a portion of the data array using its median of medians as a pivot
		Return the final position of the pivot
		"""
		i = p - 1
		j = p
		pivot = self.data_array[pivot_idx]
		self.exchange_elements(self.data_array, pivot_idx, r)

		for j in range(p, r):
			if(self.data_array[j] <= pivot):
				i += 1
				self.exchange_elements(self.data_array, i, j)
		final_pivot_idx = i + 1
		self.exchange_elements(self.data_array, final_pivot_idx, r)

		return final_pivot_idx

	def select(self, p, r):
		"""
		Return i th smallest element in the data array through partitioning
		Use index arrays to keep track of the median's index in the data array
		The median is the deterministic pivot used for partitioning
		"""
		if(p == r):
			return self.data_array[p]

		index_array = np.array(list(range(p, r)))
		median_of_medians_idx = self.get_median_of_medians(index_array)
		final_pivot_idx = self.partition(p, r, median_of_medians_idx)

		k = final_pivot_idx - p + 1

		if(self.temp_i_th == k):
			return self.data_array[final_pivot_idx]

		elif(self.temp_i_th < k):
			return self.select(p, final_pivot_idx - 1)

		else:
			self.temp_i_th -= k
			return self.select(final_pivot_idx + 1, r)
