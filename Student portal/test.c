#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define cls system("cls");
#define pr printf
#define sc scanf

struct Student {
    int id;
    char name[255];
    char password[255];
};

struct Doctor {
    int id;
    char name[255];
    char password[255];
};

struct Admin {
    int id;
    char name[255];
    char password[255];
};

struct Course {
    int id;
    char name[255];
    int prerequisites[10]; // stores the courses required to be finished before enrolling in this course
    int doctor_id;
};

struct StudentCourses {
    int student_id;
    int course_id;
    int grades[3];
    bool is_finished; // specifies whether the student has finished this course or not
};

void listCourses();

void listStudentCourses();

void maisn() {
    listCourses();
    int s;
    scanf("%d", &s);
}

void listCourses() {
    struct StudentCourses scourse;
    FILE *pt = fopen("studentcourses.bin", "ab+");
    while(fread(&scourse, sizeof(struct StudentCourses), 1, pt)) {
        printf("\n%d\t%d", scourse.course_id, scourse.student_id);
    }
}

