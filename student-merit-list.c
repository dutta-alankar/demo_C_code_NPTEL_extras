#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct student {
    int id;
    char name[128];
    int score;
} Student;

int main() {
    int nstudents;
    printf("Enter the number of students: ");
    scanf("%d", &nstudents);
    Student *students = (Student *)malloc(nstudents * sizeof(Student));
    for (int i = 0; i < nstudents; i++) {
        printf("Enter the id of student %d: ", i + 1);
        scanf("%d", &students[i].id);
        printf("Enter the name of student %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter the score of student %d: ", i + 1);
        scanf("%d", &students[i].score);
    }
    int *ranks = malloc(nstudents * sizeof(int));
    for (int i = 0; i < nstudents; i++) {
        ranks[i] = 1;
        for (int j = 0; j < nstudents; j++) {
            if (students[j].score > students[i].score) {
                ranks[i]++;
            }
        }
    }
    for (int i = 0; i < nstudents; i++) {
        printf("%d %s %d\n", students[ranks[i]-1].id, students[ranks[i]-1].name, students[ranks[i]-1].score);
    }
    free(students);
    free(ranks);
    return 0;
}
