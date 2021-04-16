/* Welcome to Mamat, 044101
 *
 * Use this project as a template for other C/C++ projects.
 * To copy this project, right-click on the project name "hello-world"
 * in the "project explorer" tab (left), then "copy" and finally "paste".
 *
 * To compile the project use "gcc" within the terminal.
 * To debug the project use "gdb" within the terminal.
 *
 * The red vertical line (right) represents the code width limit (80 chars).
 * Make sure not to cross it. */

#include <stdio.h>
#include <stdlib.h>
#define N 100
/**
 * @brief Application's main entry point
 * @param argc Number of arguments
 * @param argv Pointer to arguments
 * @return Non-zero value in case of an error
 */
int main(int argc, char **argv) {
	printf("num of students = %d\n", argc-1);
	int sum = 0;
	int sum_1 = 0;
	int pass = 0;
	int* grades = malloc(sizeof(int)*argc);
	int hist[N] = {0};
	for (int i = 1; i < argc; i++){
		for (int j = 0; argv[i][j] != '\0'; j++){
		if (j == 0 && (argv[i][j+1]!= '\0')){ //sum all the digits in the string
			sum_1 += (argv[i][j] - '0')*10;
			}
		else {
			sum_1 += (argv[i][j] - '0');
			}
		}	
		sum += sum_1;
		if (sum_1 >= 55){
		pass += 1;
		}
		grades[i-1] = sum_1;
		sum_1 = 0;
	}
	for(int k = 0; k < argc-2; k++){  //sort the grades
		for(int p = k+1; p < argc-1; p++){
			if (grades[k] > grades[p]){
				int t = grades[k]; 
				grades[k] = grades[p]; 
				grades[p] = t; 
				}
			}
		} 
	float avg = (float)(sum)/(argc-1); 
	printf("avg = %.3f\n", avg);
	printf("the median is = %d\n", grades[(argc)/2]);
	printf("max grade = %d, min grade = %d\n", grades[argc-2], grades[0]);
	float pass_prec = (float)(pass)/(argc-1)*100;
	printf("pass rate = %.2f%\n", pass_prec);
	for (int i = 0; i < argc-1; i++){
		hist[grades[i]-1] += 1;
		}
	for (int i = 0; i < N; i++){
		if (((i+1)%10) == 0){
			printf ("%d\n",hist[i]);
			}
		else {
			printf ("%d ",hist[i]);
		}
	}
	free(grades);
	return 0;
}
