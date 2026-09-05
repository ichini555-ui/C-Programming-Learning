#include <stdio.h>

int find_min_positive(int numbers[], int size) {
	int min = numbers[0];
	int found = 0;

	for (int i = 0; i < size; i++) {
		if (numbers[i] > 0 && found == 0) {
			min = numbers[i];
			found = 1;

		}
		else if (numbers[i] > 0 && numbers[i] < min && found !=0) {
			min = numbers[i];
		}

	}
	return min;
}


int main(void){
	int numbers[8] = { -10, 7, 3, -2, 15, 5, -8, 12 };
	int result = find_min_positive(numbers, 8);
	printf("%d\n", result);
	
return 0;


}
