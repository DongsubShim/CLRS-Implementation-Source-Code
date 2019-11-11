import numpy as np

class RadixSort:
	"""
	Radix Sort for array of integers expressed in decimal
	"""
	base = 10

	def __init__(self, array):
		self.array = array
		self.original_array = array.copy()
		self.sorted_array = self.radix_sort()

	def get_digit(self, integer, digit_pos):
		"""
		Return digit at specified digit position of number
		"""
		return integer // (self.base ** (digit_pos - 1)) % self.base

	def counting_sort(self, digit_pos):
		"""
		Run digit-based counting sort on input array of integers
		"""
		sorted_array = np.zeros(len(self.array), dtype=int)
		temp_array = np.zeros(self.base, dtype=int)

		for i in self.array:
			temp_array[self.get_digit(i, digit_pos)] += 1

		temp_array = np.cumsum(temp_array, dtype=int)

		for i in reversed(self.array):
			sorted_array[temp_array[self.get_digit(i, digit_pos)] - 1] = i
			temp_array[self.get_digit(i, digit_pos)] -= 1

		return sorted_array

	def radix_sort(self):
		"""
		Run radix sort
		"""
		digit_pos = 1
		while(digit_pos):
			counting_sorted_array = self.counting_sort(digit_pos)
			digit_pos += 1
			if(np.array_equal(self.array, counting_sorted_array)):
				return counting_sorted_array

			else:
				self.array = counting_sorted_array
