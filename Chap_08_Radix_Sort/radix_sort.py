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

	def max_number(self):
		"""
		Return largest integer in array
		"""
		largest = self.array[0]
		for i in self.array:
			if(i > largest):
				largest = i
		return largest

	def max_number_digits(self):
		"""
		Return number of digits of largest integer in array
		"""
		largest = self.max_number()
		max_number_digits = len(str(largest))
		return max_number_digits

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
		max_number_digits = self.max_number_digits()

		for digit_pos in range(1, max_number_digits + 1):
			counting_sorted_array = self.counting_sort(digit_pos)
			self.array = counting_sorted_array

		return counting_sorted_array
