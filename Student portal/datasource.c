#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define cls system("cls");
#define pr printf
#define sc scanf

struct Student {
    int id;
    char username[50];
    char password[20];
    char *subject[14];
}aast[1000];

struct Course {
    int id;
    char name[1000];
    int prerequisites[10]; // stores the courses required to be finished before enrolling in this course
};


struct StudentCourses {
    int student_id;
    int course_id;
    int grades[3];
    bool is_finished; // specifies whether the student has finished this course or not
};

// Course

void create_course(int id, char name[])
{
    struct Course course;
    strcpy(course.name, name);
    course.id = id;
    FILE *crs=fopen("courses.bin","ab+");
    fwrite(&course,sizeof(struct Course),1,crs);
    fclose(crs);
}
/*
Course get_course()
{
    struct Course courses[];
    FILE*pt;
    pt = fopen("courses.bin", "ab+");
    while(fread(&course, sizeof(struct Course), 1, pt)) {
        course.append(Course);
    }
}

void display_courses()
{
    struct Course course;
    FILE*pt;
    pt = fopen("courses.bin", "ab+");
    printf("    Name    |  ID  \n");
    while(fread(&course, sizeof(struct Course), 1, pt)) {
        printf("%-14s|%-6d%\n", course.name, course.id);
    }
} */
