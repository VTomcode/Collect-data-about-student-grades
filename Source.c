#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
int amount_of_students;
typedef struct student_init_data
{
	int ID_number;
	int number_of_tests;
	int* Student_tests_grades;
}student_init_data;
typedef struct student_processed_data
{
	int ID_number;
	double Average_grades_on_the_test;  

}student_processed_data;
typedef struct statistics
{
	 student_processed_data* Below_average;
	 student_processed_data* Above_average;
	int size_of_below_average;
	int size_of_above_average;
	double average_of_the_group;

}statistics;
int* Input_Data(int numtest);

double Student_Average(int* Grades,int amount);

double Total_Average(student_processed_data *ptr_list, int amount);

void Classfication(student_init_data* Students, double total_average, int amount, statistics *ptr_stats);

void Print_Tab(int amount, statistics *ptr_stats);

void Free_function(student_init_data *stud,student_processed_data *student ,statistics *students,int amount);
int main()
{
	
	double total_average;

	printf("Insert the amount of students");

	scanf_s("%d", &amount_of_students);

	student_processed_data *Student_list=NULL;

	Student_list = (student_processed_data*)malloc(amount_of_students * sizeof(student_processed_data));  //average = (double*)calloc(amount_of_students, sizeof(double));
	
	  student_init_data* Students=NULL;

	  statistics stat;

	  statistics *statsic=&stat;

	  Students = (student_init_data*)malloc(amount_of_students*sizeof(student_init_data));

		 for (int i = 0; i < amount_of_students;i++)
		 {
			 printf("Enter the ID:");

			scanf_s("%d", &Students[i].ID_number);

			printf(" \n Hello this program is for saving grades and making averages \n please insert the amount of grades you are willing to save their data here :");

			scanf_s("%d",&Students[i].number_of_tests);

			Students[i].Student_tests_grades = Input_Data(Students[i].number_of_tests);

		 }
		 for (int i = 0; i < amount_of_students; i++)
		 {
			 Student_list[i].Average_grades_on_the_test= Student_Average(Students[i].Student_tests_grades, Students[i].number_of_tests);

			 Student_list[i].ID_number = Students[i].ID_number;
		 }
	  total_average = Total_Average(Student_list, amount_of_students);

	  printf(" \n the average total is : %lf \n", total_average);

	  Classfication(Students, total_average, amount_of_students, statsic);

	  Print_Tab(amount_of_students, statsic);

	  Free_function(Students, Student_list, &stat, amount_of_students);

	  return 0;
}
int* Input_Data(int numtest)
{
		int* Grades=NULL;

		Grades = (int*)malloc(numtest * (sizeof(int)));

			for (int i = 0; i < numtest; i++)
			{
				printf(" \n insert the grade :");
				scanf_s("%d",&Grades[i]);
			}

	return Grades;
	
}
double Student_Average(int* Grade,int amount)
{
	int sum = 0;

	double average;

		for (int i = 0; i < amount; i++)
		{
			sum = Grade[i] + sum;
		}
	average = sum / amount;

	return average;
}
double Total_Average(student_processed_data *ptr_list, int amount)
{
	double sum = 0;

	double total_average;

		for (int i = 0; i < amount; i++)
		{
			sum = ptr_list[i].Average_grades_on_the_test + sum;
		}
	total_average = sum / amount;

	return total_average;

}
void Classfication(student_init_data* Students, double total_average, int amount, statistics *ptr_stats)
{

	ptr_stats->size_of_below_average = 0;

	ptr_stats->size_of_above_average = 0;

	ptr_stats->average_of_the_group = total_average;

	double average;

	for (int i = 0; i < amount; i++)
	{
		average = Student_Average(Students[i].Student_tests_grades, Students[i].number_of_tests);
		if (average < total_average)
		{

			ptr_stats->size_of_below_average++;
		}
		else
		{

			ptr_stats->size_of_above_average++;
		}

	}
	ptr_stats->Below_average = (student_processed_data*)malloc((ptr_stats->size_of_below_average * sizeof(student_processed_data)));

	ptr_stats->Above_average = (student_processed_data*)malloc((ptr_stats->size_of_above_average * sizeof(student_processed_data)));

	ptr_stats->size_of_below_average = 0;

	ptr_stats->size_of_above_average = 0;

	for (int i = 0; i < amount; i++)
	{
		average = Student_Average(Students[i].Student_tests_grades, Students[i].number_of_tests);
		if (average < total_average)
		{

			ptr_stats->Below_average[ptr_stats->size_of_below_average].ID_number = Students[i].ID_number;

			ptr_stats->Below_average[ptr_stats->size_of_below_average].Average_grades_on_the_test = average;

			ptr_stats->size_of_below_average++;
		}
		else
		{

			ptr_stats->Above_average[ptr_stats->size_of_above_average].ID_number = Students[i].ID_number;

			ptr_stats->Above_average[ptr_stats->size_of_above_average].Average_grades_on_the_test = average;

			ptr_stats->size_of_above_average++;
		}

	}
}
		void Print_Tab(int amount, statistics *ptr_stats)
		{
			printf("\n this is the students who are below the average \n");

			for (int i = 0; i < ptr_stats->size_of_below_average; i++)
			{
				printf("%d ", ptr_stats->Below_average[i].ID_number);

				printf(" and this is his average : = %lf \n", ptr_stats->Below_average[i].Average_grades_on_the_test);
			}
			printf("\n this is the students who are above the average \n");

			for (int i = 0; i < ptr_stats->size_of_above_average; i++)
			{
				printf("%d", ptr_stats->Above_average[i].ID_number);

				printf(" and this is his average : = %lf \n", ptr_stats->Above_average[i].Average_grades_on_the_test);
			}
		}
		void Free_function(student_init_data* stud, student_processed_data **student, statistics* students, int amount)
		{
			for (int i = 0; i < amount; i++)
			{
					free(stud[i].Student_tests_grades);

					stud[i].Student_tests_grades = NULL;

					free(&student[i]);
			
				
			}

				free(students->Above_average);

				free(students->Below_average);

				students->Above_average=NULL;

				students->Below_average=NULL;


		}
