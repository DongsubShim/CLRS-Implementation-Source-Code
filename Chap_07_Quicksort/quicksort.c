#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int input_array[], int last_index) {
	for (int i = 0; i <= last_index; i++) {
		printf("%d th element is %d\n", i, input_array[i]);
	}
	return;
}

void exchange(int input_array[], int first_index, int second_index) {
	// exchange two elements in the input array
	int temp = input_array[first_index];
	input_array[first_index] = input_array[second_index];
	input_array[second_index] = temp;
	return;
}

int random_index_pivot(int length) {
	// randomly pick an index of the input array, and use that as pivot index
	int index_pivot = rand() % length;
	return index_pivot;
}

int random_partition(int input_array[], int first_index, int last_index) {
	// partition input array using random pivot

	// randomly choose pivot index
	int array_length = last_index - first_index + 1;
	int index_pivot = random_index_pivot(array_length) + first_index;

	// exchange pivot and last element in input array
	int x = input_array[index_pivot];
	exchange(input_array, index_pivot, last_index);

	// start partitioning
	int i = first_index - 1;
	for (int j = first_index; j < last_index; j++) {
		if (input_array[j] < x) {
			// increment i, and exchange ith and jth elements
			exchange(input_array, ++i, j);
		}
	}
	// q: index for pivot after partitioning is done
	int q = i + 1;
	// exchange q th element and the last element
	// then pivot element is at pivot index
	exchange(input_array, q, last_index);
	return q;
}

void random_quicksort(int input_array[], int first_index, int last_index) {
	// randomized quicksort algorithm

	if (first_index >= last_index) {
		return;
	}

	// randomized partitioning
	int index_pivot_partitioned = random_partition(input_array, first_index, last_index);
	// recursive calls for randomized quicksort
	random_quicksort(input_array, first_index, index_pivot_partitioned - 1);
	random_quicksort(input_array, index_pivot_partitioned + 1, last_index);
}

int main() {
	// generate current time based random seed
	srand((unsigned)time(NULL));
	int input_array[] = { 23, 39, 1, 44, 482, 4, 9, 13, 223, 5, 73};
	int input_array_length = sizeof(input_array) / sizeof(input_array[0]);
	int last_index = input_array_length - 1;

	// run randomized quicksort on input array
	random_quicksort(input_array, 0, last_index);

	// print sorted array
	print_array(input_array, last_index);
	
	return 0;
}