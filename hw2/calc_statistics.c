#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int num_lines_in_file(FILE *fd, char l) {  //count how many grades
	int j = 0;
  	for(; (!feof(fd));){
  		l = fgetc(fd);
  		if(l == '\n')
  		{
   			 j++;
  		}
	}
	return j;
}

int checking_grades(FILE *fd, int *pass, 
									int *grades, char c) {  //cheking and sum the grades
	int sum = 0, pass_1 = 0;
  	for (int sum_1 = 0, i = 0;c != EOF;) {
  	    c = fgetc(fd);        
        if (c == '\n') {
        	if (sum_1 > 54){
        			pass_1 += 1;
        	}
        	if (!sum_1) { //check if grade = 0
        		return 0;
        		}
        	sum += sum_1;
       		grades[i] = sum_1;
        	i += 1;
        	sum_1 = 0;
        	}
         else {
        	sum_1 = ((sum_1*10) + (int)(c - '0'));
        	}
        }
        *pass = pass_1;
        return sum;
}

void sort(int *grades, int count) //function header
{
   	for(int k = 0; k < count-1; k++){  //sort the grades
		for(int p = k+1; p < count; p++){
			if (grades[k] > grades[p]){
				int t = grades[k]; 
				grades[k] = grades[p]; 
				grades[p] = t; 
				}
			}
		}
   return;
}
int main(int argc, char **argv) {
    char address_1[50];
    char address_2[50];
    strcpy( address_1, argv[1] );
    strcpy( address_2, argv[1] );
    char path[] = "/grades.txt"; // Added some space for array[0]
    char new_file[] = "/course_statistics.txt"; // Added some space for array[0]
    strcat(address_1,path);
    strcat(address_2,new_file);
// Open the file
    FILE *fd, *fd_out;
    char buf_1[0x100];
    char buf_2[0x100];
	snprintf(buf_1, sizeof(buf_1), "%s", address_1);
	fd = fopen(buf_1, "r");
	if (!fd){
		fprintf(stderr, "file not good");
		return 0;
		}
	snprintf(buf_2, sizeof(buf_2), "%s", address_2);
	fd_out = fopen(buf_2, "w+");
    char c, l;
    int sum = 0, count = 0, pass = 0;
    int hist[N] = {0};
	count = num_lines_in_file(fd, l);	
	int* grades = malloc(sizeof(int)*count);
	rewind(fd);
	if (count){ //check grades only if file not empty
		sum = checking_grades(fd, &pass, grades,c);
		if (!sum){ //if there is grade 0
			fprintf(stderr, "grade 0! kick out of Technion!");
			return 0;
			}
		}
	sort(grades, count); 
	float avg = (float)(sum)/(count); 
	fprintf(fd_out,"avg = %.3f\n", avg);
	fprintf(fd_out,"the median is = %d\n", grades[(count+1)/2]);
	fprintf(fd_out,"max grade = %d, min grade = %d\n", grades[count-1], grades[0]);
	float pass_prec = (float)(pass)/(count)*100;
	fprintf(fd_out,"pass rate = %.2f%\n", pass_prec);
	for (int i = 0; i < count-1; i++){
		hist[grades[i]-1] += 1;
		}
	for (int i = 0; i < N; i++){
		if (((i+1)%10) == 0){
			fprintf (fd_out,"%d\n",hist[i]);
			}
		else {
			fprintf (fd_out,"%d ",hist[i]);
		}
	}
	free(grades);
	fclose(fd);
	fclose(fd_out);
	return 0;
}
