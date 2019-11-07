#include <stdio.h>

void print_array(int input_array[], int last_index) {
	for (int i = 0; i <= last_index; i++) {
		printf("%d th element is %d\n", i, input_array[i]);
	}
	return;
}

void insertion_sort_exchange(int input_array[], int index) {
	while (input_array[index] < input_array[index - 1] && index >= 1) {
		int temp = input_array[index - 1];
		input_array[index - 1] = input_array[index];
		input_array[index] = temp;
		index--;
	}
	return;
}

void insertion_sort(int input_array[], int last_index) {
	for (int idx = 0; idx <= last_index; idx++) {
		insertion_sort_exchange(input_array, idx);
	}
	return;
}

int main() {
	int input_array[] = { 3, 82, 22, 39, 192, 48, 77, 43, 8 };
	int array_length = sizeof(input_array) / sizeof(input_array[0]);
	insertion_sort(input_array, array_length - 1);
	print_array(input_array, array_length - 1);

	return 0;
}