#include <stdio.h>
#include <stdlib.h>

void print_array(int input_array[], int end_index) {
	for (int i = 0; i <= end_index; i++) {
		printf("%d th element is %d\n", i, input_array[i]);
	}
	return;
}

int* merge(int ptr_subarray_left[], int ptr_subarray_right[], int left_length, int right_length, int total_length, int merged_array[]) {
	// merge two subarrays until one of them is fully merged
	int i = 0, j = 0;
	while (i < left_length && j < right_length) {
		if (ptr_subarray_left[i] < ptr_subarray_right[j]) {
			merged_array[i+j] = ptr_subarray_left[i];
			i++;
		}
		else {
			merged_array[i+j] = ptr_subarray_right[j];
			j++;
		}
	}
	
	// if one of the subarrays is not fully merged,
	// merge the rest of it to the end of the merged array
	// none or only one of the two for loops below would execute to complete the merge process

	// left subarray
	for (i; i < left_length; i++) {
		merged_array[i+j] = ptr_subarray_left[i];
	}
	
	// right subarray
	for (j; j < right_length; j++) {
		merged_array[i+j] = ptr_subarray_right[j];
	}

	return merged_array;
}

int* mergesort(int input_array[], int start_index, int end_index) {
	// base case when there is only one element in the array
	if (start_index >= end_index) {
		int* ptr_single = (int*)malloc(sizeof(int) * 1);
		*ptr_single = input_array[start_index];
		return ptr_single;
	}

	int middle_index = (start_index + end_index) / 2;
	int left_length = middle_index - start_index + 1;
	int right_length = end_index - middle_index;
	int total_length = left_length + right_length;

	// DIVIDE
	int* ptr_subarray_left = mergesort(input_array, start_index, middle_index);
	int* ptr_subarray_right = mergesort(input_array, middle_index + 1, end_index); 

	// CONQUER
	int* merged_array = (int*)malloc(sizeof(int) * total_length);
	merged_array = merge(ptr_subarray_left, ptr_subarray_right, left_length, right_length, total_length, merged_array);

	// free dynamic arrays
	free(ptr_subarray_left);
	free(ptr_subarray_right);
	return merged_array;
}

int main() {
	int input_array[] = { 2, 3, 84, 85, 41, 13, 32, 123, 9 };
	int array_length = sizeof(input_array) / sizeof(input_array[0]);
	int* merged_array = mergesort(input_array, 0, array_length - 1);

	print_array(merged_array, array_length - 1);
	free(merged_array);

	return 0;
}