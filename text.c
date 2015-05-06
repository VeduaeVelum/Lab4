#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#define M 2
#define K 10
#define N 25

struct queue
{
	int number_places[M];
	int district_number;
	int(*func_pointer)(int distans);
	struct queue *next;
}*q_first = { NULL }, *q_last = { NULL };

struct patients
{
	char *surname;
	int district_number;
	int nearest_hospital;
	int number_of_patients;
}*str = { NULL };

int input_patients_information(void);
int input_hospital_information(void);
int output_patient_information(void);
int output_hospital_information(void);
int print_patient_information(void);
int determine_optimal_hospitals(void);
int read_information(void);
int distans(int number);
int func_delete(void);
void delete_struct(void);
void delete_queue(void);
char* memory_allocation(char *string);
int input_data_of_patients(void);
int* input_places(int *massive);
void check_flag(void);
int check_letter(void);
int check_string(char *string);
void clean_stdin(void);
void push(int *number_places, int k);
void pop(struct queue **top);

int main(int argc, char** argv)
{
	int flag;
	printf("Do you want to input nesessary information or read it from file?(Y - console input/N - file input): ");
	flag = check_letter();
	if (flag == 0)
	{
		printf("\nChoose the operation please: \n");
		printf("\t\t\t1 - input surnames and districts of patients\n");
		printf("\t\t\t2 - input informarion about hospitals\n");
		printf("\t\t\t3 - output patients's surnames\n");
		printf("\t\t\t4 - output hospitals's information\n");
		printf("\t\t\t5 - print information about patients and hospitals\n");
		printf("\t\t\t6 - determine optimal hospital for patients\n");
		printf("\t\t\t7 - print results of determining\n");
		printf("\t\t\t0 - stop the program\n\n");
		check_flag();
	}
	else
	{
		flag = read_information();
		flag = output_patient_information();
		flag = output_hospital_information();
		flag = determine_optimal_hospitals();
		flag = print_patient_information();
		flag = print_patient_information();
		flag = func_delete();
	}
	printf("Thanks for work with us\n");
	return 0;
}

void check_flag(void)
{
	int element = 0, element1, flag;
	do
	{
		do
		{
			printf("\t\t\tYour choice: ");
			element1 = scanf("%d", &element);
			clean_stdin();
			if (element < 0 || element > 7 || element1 != 1) printf("\n\tInvalid input, try again, look to the hint\n");
		} while (element < 0 || element > 7 || element1 != 1);
		switch (element)
		{
		case 1:
			flag = input_patients_information();
			break;
		case 2:
			flag = input_hospital_information();
			break;
		case 3:
			flag = output_patient_information();
			break;
		case 4:
			flag = output_hospital_information();
			break;
		case 5:
			flag = print_patient_information();
			printf("\tFile was successfully created\n");
			break;
		case 6:
			flag = determine_optimal_hospitals();
			break;
		case 7:
			flag = print_patient_information();
			break;
		case 0:
			flag = func_delete();
			break;
		}
		if (flag == 1) printf("\nSomething happened wrong, maybe you choose operations in incorrect order\nTry to choose another operation\n");
	} while (flag != 2);
}
char* memory_allocation(char *string)
{
	string = (char*)calloc((N + 1), sizeof(char));
	if (!string)
	{
		printf("Memory is not allocated\n");
		func_delete();
		exit(-1);
	}
	return string;
}
int input_data_of_patients(void)
{
	int element1 = 0, element;
	do
	{
		element1 = scanf("%d", &element);
		clean_stdin();
		if (element1 != 1 || element < 1 || element > K)   printf("\tIncorrect input! Use one number from 1 to 10: ");
	} while (element1 != 1 || element < 1 || element > K);
	return element;
}
int* input_places(int *massive)
{
	int element1 = 0;
	do
	{
		element1 = scanf("%d%d", &massive[0], &massive[1]);
		clean_stdin();
		if (element1 != 2 || massive[0] < 1 || massive[0] > K || massive[1] < 0 || massive[0] < massive[1])   printf("\tIncorrect input! Use two numbers from 1 to 10(examle: 4 3): ");
	} while (element1 != 2 || massive[0] < 1 || massive[0] > K || massive[1] < 0 || massive[0] < massive[1]);
	return massive;
}
int distans(int number)
{
	struct queue *q_current;
	int min_distans = (K + 1), hosp_number, min_hosp_number;
	q_current = q_first;
	do
	{
		hosp_number = q_current->district_number;
		if (abs(number - hosp_number) < min_distans)
		{
			if (q_current->number_places[1] != 0)
			{
				min_distans = abs(number - hosp_number);
				min_hosp_number = q_current->district_number;
			}
		}
		q_current = q_current->next;
	} while (q_current != NULL);
	if (min_distans == K + 1) return (K + 1);
	q_current = q_first;
	do
	{
		if (q_current->district_number != min_hosp_number)
		{
			q_current = q_current->next;
			continue;
		}
		else
		{
			q_current->number_places[1]--;
			break;
		}
	} while (1);
	return min_hosp_number;
}
int input_patients_information(void)
{
	printf("\tInput number of patients please: ");
	int i, flag;
	int n = input_data_of_patients();
	if (str != NULL)
	{
		printf("You inputed information about patients earlier, do you want to reinput it?-(Y/N): ");
		flag = check_letter();
		if (flag == 0) delete_struct();
		else return 1;
	}
	str = (struct patients*)calloc(n, sizeof(struct patients));
	str[0].number_of_patients = n;
	for (i = 0; i < n; i++)
	{
		printf("\tInput surname of the %d patient in english: ", i + 1);
		str[i].surname = memory_allocation(str[i].surname);
		do
		{
			scanf("%s", str[i].surname);
			flag = check_string(str[i].surname);
		} while (flag == 1);
		printf("\tInput number of his district: ");
		str[i].district_number = input_data_of_patients();
		putchar('\n');
	}
	return 0;
}
int input_hospital_information(void)
{
	printf("\tInput number of hospitals please: ");
	int i, flag, k, *massive;
	int n = input_data_of_patients();
	if (q_first != NULL)
	{
		printf("\tYou inputed information about hospitals earlier, do you want to reinput it?-(Y/N): ");
		flag = check_letter();
		if (flag == 0) delete_queue();
		else return 1;
	}
	massive = (int*)calloc(M, sizeof(int));
	if (!massive)
	{
		printf("Memory is not allocated\n");
		free(massive);
		flag = func_delete();
		exit(-1);
	}
	for (i = 0; i < n; i++)
	{
		printf("\tInput number of places and free places in the %d hospital: ", i + 1);
		massive = input_places(massive);
		printf("\tInput number of district of the %d hospital: ", i + 1);
		k = input_data_of_patients();
		push(massive, k);
	}
	free(massive);
	return 0;
}
int output_patient_information(void)
{
	int i;
	if (str == NULL) return 1;
	printf("\t\tList of patients:\n");
	for (i = 0; i < str[0].number_of_patients; i++) printf("\t%s, district%2d\n", str[i].surname, str[i].district_number);
	return 0;
}
int output_hospital_information(void)
{
	struct queue *q_current;
	int i = 1;
	if (q_first == NULL) return 1;
	q_current = q_first;
	printf("\t\tList of hospitals:\n");
	do
	{
		printf("\tHospital number %2d in %2d district has %2d free places\n", i++, q_current->district_number, q_current->number_places[1]);
		q_current = q_current->next;
	} while (q_current != NULL);
	return 0;
}
int print_patient_information(void)
{
	int i;
	static int flag;
	struct queue *q_current;
	FILE *f;
	if (str == NULL || q_first == NULL) return 1;
	if (flag != 1 && flag != 2)
	{
		if (!(f = fopen("patients_output.txt", "w+t")))
		{
			printf("\tFile couldn't be open\n");
			return 1;
		}
		fprintf(f, "\t\tList of patients:\n");
		for (i = 0; i < str[0].number_of_patients; i++)	fprintf(f, "%s, district%3d\n", str[i].surname, str[i].district_number);
		q_current = q_first;
		fprintf(f, "\t\tList of hospitals:\n");
		do
		{
			fprintf(f, "Hospital number %2d in %2d district has %2d free places\n", i++, q_current->district_number, q_current->number_places[1]);
			q_current = q_current->next;
		} while (q_current != NULL);
		flag = 1;
		fclose(f);
		return 0;
	}
	else if (flag == 1)
	{
		if (!(f = fopen("patients_output.txt", "a+t")))
		{
			printf("File couldn't be open\n");
			return 1;
		}
		fprintf(f, "\t\tList of the nearest hospitals:\n");
		for (i = 0; i < str[0].number_of_patients; i++) 	str[i].nearest_hospital == (K + 1) ? fprintf(f, "%s, no free places\n", str[i].surname) : fprintf(f, "%s, hospital%3d\n", str[i].surname, str[i].nearest_hospital);
		printf("\tFile was successfully created\n");
		flag = 2;
		fclose(f);
		return 0;
	}
	else if (flag == 2)
	{
		printf("\tYou input all information into the file\n\tRestart program if you want to create new file\n");
		return 1;
	}
	return 0;
}
int determine_optimal_hospitals(void)
{
	int i;
	if (str == NULL || q_first == NULL) return 1;
	for (i = 0; i < str[0].number_of_patients; i++) str[i].nearest_hospital = distans(str[i].district_number);
	printf("\tOptimal distans was determined\n");
	for (i = 0; i < str[0].number_of_patients; i++)
	{
		str[i].nearest_hospital == K + 1 ? printf("\t\tThere are not free places for %d patient\n", i + 1) : printf("\t\tNearest free hospital for %d patient is %d\n", i + 1, str[i].nearest_hospital);
	}
	return 0;
}
int read_information(void)
{
	FILE *f;
	int i, n = (M + 1), *massive, k;
	str = (struct patients*)calloc(n, sizeof(struct patients));
	massive = (int*)calloc(M, sizeof(int));
	str[0].number_of_patients = n;
	if (!(f = fopen("patients_input.txt", "r+t")) || !str || !massive)
	{
		printf("File couldn't be opened or memory isn't allocated\n");
		return 1;
	}
	for (i = 0; i < n; i++)
	{
		str[i].surname = memory_allocation(str[i].surname);
		fscanf(f, "%s", str[i].surname);
		fscanf(f, "%d", &str[i].district_number);
	}
	for (i = 0; i < (M*M); i++)
	{
		fscanf(f, "%d %d %d", &massive[0], &massive[1], &k);
		push(massive, k);
	}
	fclose(f); free(massive);
	return 0;
}
int func_delete(void)
{
	struct queue *q_current;
	int i = 0;
	if (q_first == NULL && str == NULL) return 2;
	while (i < str[0].number_of_patients)
	{
		if (str == NULL) break;
		free(str[i++].surname);
	}
	if (str != NULL) free(str);
	if (q_first == NULL) return 2;
	q_current = q_first;
	do
	{
		pop(&q_current);
	} while (q_current != NULL);
	return 2;
}
void delete_struct(void)
{
	int i = 0;
	while (i < str[0].number_of_patients) free(str[i++].surname);
	free(str);
}
void delete_queue(void)
{
	struct queue *q_current;
	q_current = q_first;
	while (q_current != NULL)  pop(&q_current);
}
void push(int *number_places, int k)
{
	struct queue *q;
	int i;
	if (!(q = (struct queue*)calloc(1, sizeof(struct queue))))
	{
		printf("Memory is not allocated\n");
		exit(-1);
	}
	for (i = 0; i < M; i++)
	{
		q->number_places[i] = number_places[i];
	}
	q->district_number = k;
	if (q_first == NULL) q_first = q_last = q;
	else
	{
		q_last->next = q;
		q_last = q;
	}
}
void pop(struct queue **current)
{
	struct queue *q;
	q = *current;
	*current = q->next;
	free(q);
}
int check_string(char *string)
{
	int i = 0, j, n = strlen(string);
	const char *massive = { "(){}[]%^+*/#:;&!.,~`'0123456789йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ" };
	while (massive[i++] != '\0')
	{
		for (j = 0; j < (n - 1); j++)
		{
			if (massive[i] == string[j] || n > N)
			{
				printf("\tSymbols you use in string are forbidden or it's longer 25 symbols, input in again: ");
				return 1;
			}
		}
	}
	return 0;
}
int check_letter(void)
{
	char c = 0;
	do
	{
		scanf("%c", &c);
		clean_stdin();
		if (c == 'Y' || c == 'y') return 0;
		else if (c == 'N' || c == 'n') return 1;
		else printf("\tIncorrect input, try again: ");
	} while (1);
}
void clean_stdin(void)
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

