#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define cls system("cls");
#define pr printf
#define sc scanf
int m0id=1,e0id=0;
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

int fsize;

struct Student loggedInStudent;
struct Doctor loggedInDoctor;
struct Admin loggedInAdmin;

void enroll_course(int student_id, struct Course, int);

void create_course(int, char[]);

void display_courses();

bool isStudentCourseFinished(int, int);

 bool Finnish_course(int,int);

bool login(int);

bool checkPrerequistes(struct Course, int);

void enrollStudentById2(int);

void enroll_course2(int , struct Course , int );

void listStudents();

char *getCourseNameById(int);

struct Course findCourse(int);

void showsubjectGrades(int ,int);

bool issubjectenrolled2(struct Course ,int );

float calculategpa(struct StudentCourses );

void main()
{
    system("color a");
    //reg(2);
  a:  printf("1. Student Portal\n2. Doctor Portal\n3. Adminstrator Portal\n");
    int userType = 1;
    scanf("%d", &userType);
    cls
    if(userType>3 || userType<1)
    {
        cls
        pr("Wrong input pleas try again\n");
        goto a;
    }
    while(!login(userType-1)) {
        cls
        printf("invalid login credentials please try again\n");
    }
     switch(userType){
     case 1:
        Student();
        break;
     case 2:
        Doctor();
        break;

        case 3:
        Admin();
        break;
        default :
            printf("Wrong input\n");
     }
}

void Student()
{
    cls
    printf("Hi you're currently logged in as %s\n======================================================\n", loggedInStudent.name);

    int key;
    //scanf("%d", &key);
    showGrades(loggedInStudent.id);
    /*
        Check grades
        Check available courses
    */
}

void Doctor()
{
    cls
    printf("Hi you're currently logged in as %s\n======================================================\n", loggedInDoctor.name);
    int key;
    pr("SELECT \n[1]- to change student grade\n[2]-to see all students at this subject\n");
    scanf("%d", &key);
    FILE *pt=fopen("courses.bin","ab+");
    int i=0,id,ff;
    struct Course c[100];
    struct StudentCourses cs[100];
    while(fread(&c[i],sizeof(struct Course),1,pt))
    {
        if(c[i].doctor_id==loggedInDoctor.id)
        {
            break;
        }
    }
    ff=i;
    fclose(pt);
        if(key==1)
        {
            int flag=0;
            pr("Enter student ID\n");
            sc("%d",&id);
            pt = fopen("studentcourses.bin","ab+");
            int j=i;
            i=0;
            int found=-1;
                while(fread(&cs[i],sizeof(struct StudentCourses),1,pt))
                {
               //     pr("%d - %d\n",cs[i].course_id,c[j].id);
                if(cs[i].course_id==c[j].id && id == cs[i].student_id)
                {
                    found =i;
                }
                i++;
            }fclose(pt);
            if(found==-1)
            {
                    pr("User not found");
                    sleep(5);
            }else {
            a:pr("select \n[1]- 7th grade\n[2]- 12th grade\n[3]- Finals grade\n");
            sc("%d",&key);
            if(key>=1 && key<=3)
            {
                pr("Pleas enter the grade:\n");
                int grd;
                sc("%d",&grd);
                cs[found].grades[key-1]=grd;
                if(key==3){
                if(Finnish_course(cs[found].grades[0]+cs[found].grades[1],cs[found].grades[key-1]))
                    cs[found].is_finished=1;
                }else {
                cs[found].grades[0]=cs[found].grades[1]=cs[found].grades[2]=0;
                cs[found].is_finished=0;
                }
                sleep(1);
            }else {
               pr("Wrong input try again \n");
               goto a;
            }
            }
        }else if(key==2)
        {
            FILE *pt=fopen("studentcourses.bin","ab+");
            struct StudentCourses css;

            while(fread(&css,sizeof(struct StudentCourses ),1,pt))
            {
                if(css.course_id==c[ff].id)
                {

                    struct Student s;
                    FILE *ptt=fopen("students.bin","ab+");
                    while(fread(&s,sizeof(struct Student),1,ptt))
                    {
                        if(css.student_id==s.id)
                        {
                            pr("%s - %d\n",s.name,s.id);
                           showsubjectGrades(s.id,css.course_id);
                        }
                    }
                    fclose(ptt);
                }
            }fclose(pt);

            sleep(5);
        }

    remove("studentcourses.bin");
    pt=fopen("studentcourses.bin","ab+");
    for (int j=0;j<i;j++)
    {
        fwrite(&cs[j],sizeof(struct StudentCourses),1,pt);
    }fclose(pt);
    // update Student grades

}

bool Finnish_course(int g,int fg)
   {
         if(g+fg>=50 && fg>=12)
         {
             return true;
         }
         return false;
   }

void Admin()
{
    int key;
    while(key != 9) {
        cls
        printf("Hi you're currently logged in as %s\n======================================================\n", loggedInAdmin.name);
        printf("1. Create new Account\n2. Create Course\n3. Enroll Student to course\n4. Show student info\n");
        scanf("%d", &key);
        cls
        switch(key) {
        case(1): ;
            int userType;
            printf("1. Student account\n2. Doctor Account\n3. Admin Account\n");
            scanf("%d", &userType);
            reg(userType-1);
            break;
        case(2):
            createCourse();
            break;
        case(3):
            printf("Enter student id: ");
            int student_id;
            scanf("%d", &student_id);
            enrollStudentById(student_id);
            break;
        case(4):
            listStudents();
            break;
        }
    }
}

bool login(int userType)
{
    int id;

    char password[255];
    printf("Enter ID: ");
    scanf("%d", &id);
    fflush(stdin);
    printf("Enter Password: ");
    scanf("%s", password);
    fflush(stdin);
    FILE *f;
    switch(userType) {
        case(0): ;
            struct Student student;
            f = fopen("students.bin", "ab+");
            rewind(f);
            while(fread(&student, sizeof(struct Student), 1, f)) {
                if(student.id == id && strcmp(student.password, password)==0) {
                    loggedInStudent = student;
                    fclose(f);
                    return true;
                }
            }
            fclose(f);
        break;
    case(1): ;
        struct Doctor doctor;
        f = fopen("doctors.bin", "ab+");
        rewind(f);
        while(fread(&doctor, sizeof(struct Doctor), 1, f)) {
            if(doctor.id == id && strcmp(doctor.password, password)==0) {
                loggedInDoctor = doctor;
                fclose(f);
                return true;
            }
        }
        fclose(f);
        break;
    case(2): ;
        struct Admin admin;
        f = fopen("admins.bin", "ab+");
        rewind(f);
        while(fread(&admin, sizeof(struct Admin), 1, f)) {
            if(admin.id == id && strcmp(admin.password, password)==0) {
                loggedInAdmin = admin;
                fclose(f);
                return true;
            }
        }
        fclose(f);
        break;
    }
    return false;
}

void reg(int userType)
{
    int d=0,id;
    if(userType==0)
    {
        int grd;
        pr("Pleas enter the high school\n");
        sc("%d",&grd);
        if(grd<245)
        {
            cls
            pr("You are not able to enroll in the collague\n");
            sleep(1);
            return ;
        }
        /*a:if(d==1){pr("Pleas enter the ESP test\n");
        sc("%d",&grd);
        if(grd>=30)
           {
           Finnish_course(60,40);
           enrollStudentById2(id);
           }


           pr("Pleas enter the student div \n1- math\n2- sceince\n");
        sc("%d",&grd);
        if(grd==1)
           {
            Finnish_course(60,40);
           enrollStudentById3(id);
           }
           goto b;
           }*/
    }

    char name[255];
    char password[255];
    printf("Enter ID:");
    scanf("%d", &id);
    fflush(stdin);
    printf("Enter Name:");
    fseek(stdin,0,SEEK_END);
    fgets(name,255,stdin);
    name[strcspn(name,"\n")]='\0';
    fflush(stdin);
    printf("Enter Password:");
    scanf("%s", password);
    FILE *f;
    switch(userType) {
    case(0): ;
        struct Student student;
        student.id = id;
        strcpy(student.password, password);
        strcpy(student.name, name);
        f = fopen("students.bin", "ab+");
        fwrite(&student, sizeof(struct Student), 1, f);
        fclose(f);
        d=1;
        //goto a;
        b:break;
    case(1): ;

        struct Doctor doctor;
        doctor.id = id;
        strcpy(doctor.password, password);
        strcpy(doctor.name, name);
        f = fopen("doctors.bin", "ab+");
        fwrite(&doctor, sizeof(struct Doctor), 1, f);
        fclose(f);
        break;
    case(2): ;

        struct Admin admin;
        admin.id = id;
        strcpy(admin.password, password);
        strcpy(admin.name, name);
        printf(admin.name);
        f = fopen("admins.bin", "ab+");
        fwrite(&admin, sizeof(struct Admin), 1, f);
        fclose(f);
        break;
    }
}

void enrollStudentById(int student_id)
{
    FILE *pt = fopen("courses.bin", "ab+");
    struct Course course[1000];
    struct Course courses[400];
    int i = 0;
    while(fread(&course[i], sizeof(struct Course), 1, pt)) {
        printf("[%d] %d\t%s\n", i+1, course[i].id, course[i].name);
        i++;
    }
    fclose(pt);
    printf("Enter course ID: ");
    int in;
    scanf("%d", &in);
    struct Course c;
    c = findCourse(course[in-1].id);
    enroll_course(student_id, c, course[in-1].id);
}

void enrollStudentById2(int student_id)
{
    FILE *pt = fopen("courses.bin", "ab+");
    struct Course course[1000];
    struct Course courses[400];
    int i = 0;
    while(fread(&course[i], sizeof(struct Course), 1, pt)) {

        i++;
    }
    fclose(pt);

    int id=0;
    struct Course c;
    c = findCourse(id);
    enroll_course2(student_id, c, id);
}

void enrollStudentById3(int student_id)
{
    FILE *pt = fopen("courses.bin", "ab+");
    struct Course course[1000];
    struct Course courses[400];
    int i = 0;
    while(fread(&course[i], sizeof(struct Course), 1, pt)) {

        i++;
    }
    fclose(pt);
    struct Course c;
int     id=1;
    c = findCourse(id);
    enroll_course2(student_id, c, id);
}

void enroll_course(int student_id, struct Course course, int course_id)
{
   // printf("%d",student_id);
    if(!checkPrerequistes(course, student_id)) {
        printf("Course prerequistes not fulfilled");
    } else {
        struct StudentCourses newRecord;
        newRecord.course_id = course_id;
        newRecord.student_id = student_id;
        for(int i =0; i<3;i++) {
            newRecord.grades[i] = 0;
        }

        newRecord.is_finished = false;
        FILE *pt = fopen("studentcourses.bin", "ab+");
        fwrite(&newRecord, sizeof(struct StudentCourses), 1, pt);
        printf("Student enrolled succesfully");
        fclose(pt);
        sleep(5);
    }
}






void enroll_course2(int student_id, struct Course course, int course_id)
{
   // printf("%d",student_id);
    if(!checkPrerequistes(course, student_id)) {
        printf("Course prerequistes not fulfilled");
    } else {
        struct StudentCourses newRecord;
        newRecord.course_id = course_id;
        newRecord.student_id = student_id;
        for(int i =0; i<3;i++) {
            newRecord.grades[i] = 0;
        }

        newRecord.is_finished = false;
        FILE *pt = fopen("studentcourses.bin", "ab+");
        fwrite(&newRecord, sizeof(struct StudentCourses), 1, pt);
        //printf("Student enrolled succesfully");
        fclose(pt);
        sleep(5);
    }
}


void showsubjectGrades(int student_id,int id)
{
    float gpa=0;
    struct StudentCourses course;
    FILE *studentCourseFile = fopen("studentcourses.bin", "ab+");
    printf("ID\tName\t\t7th\t12th\tFinal\n");
    while(fread(&course, sizeof(struct StudentCourses), 1, studentCourseFile)) {
        if(course.student_id == student_id && course.course_id==id) {
            //printf("%d\t%s\t%d\t%d\t%d\n", course.course_id, getCourseNameById(course.course_id), course.grades[0], course.grades[1], course.grades[2]);
        if(course.course_id==e0id || course.course_id==m0id)
        {
            printf("%d\t",course.course_id);
        getCourseNameById(course.course_id);
         if(course.is_finished)
            pr("PASSED\n");
            else
            pr("NOT PASSED\n");
        }else {
        printf("%d\t",course.course_id);
        getCourseNameById(course.course_id);
       gpa+=calculategpa(course);
        printf("%d\t%d\t%d\n", course.grades[0], course.grades[1], course.grades[2]);
        }

        }
    }

    fclose(studentCourseFile);


}


void showGrades(int student_id)
{
    float gpa=0;
    struct StudentCourses course;
    FILE *studentCourseFile = fopen("studentcourses.bin", "ab+");
    printf("ID\tName\t\t7th\t12th\tFinal\n");
    while(fread(&course, sizeof(struct StudentCourses), 1, studentCourseFile)) {
        if(course.student_id == student_id) {
            //printf("%d\t%s\t%d\t%d\t%d\n", course.course_id, getCourseNameById(course.course_id), course.grades[0], course.grades[1], course.grades[2]);
        if(course.course_id==e0id || course.course_id==m0id)
        {
            printf("%d\t",course.course_id);
        getCourseNameById(course.course_id);
         if(course.is_finished)
            pr("PASSED\n");
            else
            pr("NOT PASSED\n");
        }else {
        printf("%d\t",course.course_id);
        getCourseNameById(course.course_id);
       gpa+=calculategpa(course);
        printf("%d\t%d\t%d\n", course.grades[0], course.grades[1], course.grades[2]);
        }

        }
    }

    fclose(studentCourseFile);
    pr("GPA : %0.2f\n",gpa);
    int in;
    fflush(stdin);
    pr("SELECT \n[1]- To see the available courses to enroll \n[any other key]- to exit\n");
    scanf("%d", &in);
    if(in==1)
    {
        int f=0,ft=0;
        FILE *pt=fopen("courses.bin","ab+");

        struct Course c;
        while(fread(&c,sizeof(struct Course),1,pt))
        {
            //FILE *ptt=fopen("courses.bin","ab+");
            ft=issubjectenrolled2(c,student_id);
            if(!ft){
            f=checkPrerequistes( c, student_id);
            if(f)
            {
            pr("Your are allowed to enroll in : %s\n",c.name);
            f=0;
            }else {
            pr("Your are not allowed to enroll in : %s\n",c.name);
            }
            }
        }
        pr("No other courses are available to enroll\n");
        sleep(5);
    }else {
    return ;
    }
}

char *getCourseNameById(int courseId)
{
    struct Course course;
    FILE *courseFile = fopen("courses.bin", "ab+");
    while(fread(&course, sizeof(struct Course), 1, courseFile)) {
        if(course.id == courseId) {
           // fclose(courseFile);
            printf("%-12s    ",course.name);
            break;
        }
    }
    fclose(courseFile);
}

bool checkPrerequistes(struct Course course, int student_id)
{
    if(course.prerequisites[0] == 0) {
         //   pr("X");
        return true;
    }
    for(int i = 0; i < sizeof(course.prerequisites); i++) {

        if(!isStudentCourseFinished(student_id, course.prerequisites[i])) {
            return false;
        }
    }
    return true;
}

bool isStudentCourseFinished(int student_id, int course_id)
{
    if(course_id == 0) {
        return true;
    }
    FILE *pt = fopen("studentcourses.bin", "ab+");
    struct StudentCourses studentCourse;
    while(fread(&studentCourse, sizeof(struct StudentCourses), 1, pt)) {
        if(studentCourse.student_id == student_id && studentCourse.course_id == course_id && studentCourse.is_finished) {
            fclose(pt);
            return true;
        }
    }
    fclose(pt);
    return false;
}

void listStudents()
{
    struct Student student;
    struct Student students[300];
    int i = 1;
    FILE *pt;
    pt = fopen("students.bin", "ab+");
    while(fread(&student, sizeof(student), 1, pt)) {
        students[i] = student;
        printf("%d- %d\t%s\t%s\n", i, student.id, student.name, student.password);
        i++;
    }
    fclose(pt);
    int key;
    scanf("%d", &key);
}

struct Course findCourse(int id)
{
    struct Course course;
    FILE *pt = fopen("courses.bin", "ab+");
    while(fread(&course, sizeof(struct Course), 1, pt)) {
        if(course.id == id) {
            return course;
        }
    }
};

void createCourse()
{
    cls
    int hour;
    struct Course course;
    for(int i =0; i < 10; i++){
        course.prerequisites[i] = 0;
    }
    printf("Enter Course Id: ");
    scanf("%d", &course.id);
    fflush(stdin);
    printf("Enter Course Name: ");
    scanf("%s", course.name);
    fflush(stdin);
    printf("Enter Doctor Id: ");
    scanf("%d", &course.doctor_id);
    printf("Enter Course Hours: ");
    scanf("%d", &hour);
    if(hour==3)
    {
        FILE*pt=fopen("3 hours.bin","ab+");
        fwrite(&course.id,sizeof(struct Course),1,pt);
        fclose(pt);
    }else {

        FILE*pt=fopen("2 hours","ab+");
        fwrite(&course.id,sizeof(struct Course),1,pt);
        fclose(pt);
    }
    fflush(stdin);
    int in = -1;
    printf("Enter prerequisites courses Id's Or type 0 to confirm: ");
    int i = 0;
    scanf("%d", &in);
    while(in != 0 && i != 10) {
        course.prerequisites[i] = in;
        fflush(stdin);
        scanf("%d", &in);
        i++;
    }
    FILE *pt;
    pt = fopen("courses.bin", "ab+");
    fwrite(&course, sizeof(struct Course), 1, pt);
    cls
    printf("Course created successfully!\nRedirecting in 5 seconds");
    fclose(pt);
    sleep(5);
}

void printArr(int arr[]) {
    for(int i =0;i < sizeof(arr); i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");

}
bool issubjectenrolled2(struct Course c,int student_id)
{
    FILE *ptt=fopen("studentcourses.bin","ab+");
    struct StudentCourses s;
    while(fread(&s,sizeof(struct StudentCourses),1,ptt))
    {
        if(s.student_id==student_id && s.course_id==c.id)
        {
            fclose(ptt);
            return true;
        }
    }
    fclose(ptt);
            return false;
}

float calculategpa(struct StudentCourses grade)
{
    float gpa=0;
    int n2=0,n3=0;
    struct StudentCourses s;

        int h;

           int  f=0;
            FILE *ptt=fopen("3 hours.bin","ab+");
            while(fread(&h,sizeof(struct StudentCourses),1,ptt))
            {
                if(s.course_id==h)
                {
                    h==3;
                    f=1;
                    break;
                }
            }
            fclose(ptt);
            if(!f)
            {
                 int h;
                 FILE *ptt=fopen("2 hours.bin","ab+");
                 while(fread(&h,sizeof(struct StudentCourses),1,ptt))
                 {
                     if(s.course_id==h)
                {
                    h==2;
                    break;
                }
                 }
                             fclose(ptt);
            }


        if(h==3)
        {
        gpa+=(grade.grades[0]+grade.grades[1]+grade.grades[2])*3.0;
        n3++;
        }else {

        gpa+=(grade.grades[0]+grade.grades[1]+grade.grades[2])*2.0;
        n2++;
        }


    int n=n3+n2;
  //  pr("%f",gpa);
    return gpa/(n*100);
}
