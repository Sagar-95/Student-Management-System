#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// for tracking no of students and users in database
int no_of_students, no_of_users;
// structure data type for storing student details
struct student
{
    char name[50];
    char parents[50];
    char branch[50];
    char semester[50];
    char roll_no[50];
    char ph_no[13];
    char email[50];
};

struct sign_up
{
    char name[50], pass[50];
    char security_pin[50];
};

void login();
void sign_in();
void sign_up();
void forgot_password();
void menu();
void add_student();
void add_student_message();
void search();
void search_name();
void search_roll();
void student_list();
void update();
void delete ();

int main()
{
    FILE *fp;

    fp = fopen("no_of_students.txt", "r"); //no of students initially is 0.

    if (fp == NULL)
    {
        printf("Number of students not found in database.\n");
        exit(1);
    }
    fscanf(fp, "%d", &no_of_students);
    fclose(fp);

    fp = fopen("no_of_users.txt", "r"); //no of users initially is 0.
    if (fp == NULL)
    {
        printf("Number of users not found in database.\n");
        exit(1);
    }
    fscanf(fp, "%d", &no_of_users);
    fclose(fp);

    login();

    return 0;
}

void login()
{
    system("cls");
    int value;
    printf("1: Sign In    2: Sign Up    3: Forgot Password    ||   Input: ");
    scanf("%d", &value);
    if (value == 1)
        sign_in();
    else if (value == 2)
        sign_up();
    else if (value == 3)
        forgot_password();
    else
    {
        printf("Invalid Input.");
        exit(0);
    }
}

// function for Sign In page
void sign_in()
{
    char name1[50], pass1[50];
    struct sign_up a[no_of_users];
    int y, i, c = 0;
    system("cls");
    //input section
    printf("____Welcome To Sign In page____\n");
    printf("Enter UserName: ");
    scanf("%s", &name1);
    printf("Enter Password: ");
    scanf("%s", &pass1);
    //using file to retrive stored data
    FILE *fp = NULL;
    fp = fopen("user_pass.bin", "rb");
    if (fp == NULL)
    {
        printf("No users records found");
        exit(0);
    }

    fread(a, sizeof(struct sign_up), no_of_users, fp);
    for (i = 0; i < no_of_users; i++)
    {
        if (!strcmp(a[i].name, name1))
        {
            if (!strcmp(a[i].pass, pass1))
            {
                c = 1;
                menu();
            }
        }
    }

    if (c != 1) //if sign in fails
    {
        printf("\nSign In Failed\n");
        printf("1: Try again    2: Forgot Password    3: Sign Up   4: Exit  ||  Input: ");
        scanf("%d", &y);
        if (y == 1)
            sign_in();
        else if (y == 2)
            forgot_password();
        else if (y == 3)
            sign_up();
        else
            exit(1);
    }
    fclose(fp);
}

//function for sign up page
void sign_up()
{
    system("cls");
    struct sign_up a[no_of_users];
    char name1[50], pass1[50], pin1[50];
    int x, i;
    FILE *fp;
    fp = fopen("user_pass.bin", "rb");
    fread(a, sizeof(struct sign_up), no_of_users, fp);

    //input section
    printf("____Welcome to Sign Up page____\n");
    printf("Enter UserName: ");
    scanf("%s", name1);
    for (i = 0; i < no_of_users; i++)
    {
        if (!strcmp(a[i].name, name1))
        {
            printf("Username already taken.\n");
            printf("1: Try again   2: Exit  ||  Input: ");
            scanf("%d", &x);
            if (x == 1)
                sign_up();
            else
                exit(1);
        }
    }
    fclose(fp);

    printf("Enter Password: ");
    scanf("%s", &pass1);
    printf("Enter Security Pin: ");
    scanf("%s", &pin1);

    struct sign_up b[no_of_users + 1];
    for (i = 0; i < no_of_users; i++)
    {
        strcpy(b[i].name, a[i].name);
        strcpy(b[i].pass, a[i].pass);
        strcpy(b[i].security_pin, a[i].security_pin);
    }
    strcpy(b[no_of_users].name, name1);
    strcpy(b[no_of_users].pass, pass1);
    strcpy(b[no_of_users].security_pin, pin1);
    no_of_users += 1;

    //file handling to store data in file
    fp = fopen("user_pass.bin", "wb");
    if (fp == NULL)
    {
        printf("Cannot open file\n");
    }
    fwrite(b, sizeof(struct sign_up), no_of_users, fp);
    fclose(fp);

    fp = fopen("no_of_users.txt", "w");
    fprintf(fp, "%d", no_of_users);
    fclose(fp);

    printf("\n____Sign Up Successful____\n\n");
    printf("1: GoTo -> Sign In page    2: Exit   3. Sign Up Again  ||  Input: ");
    scanf("%d", &x);
    if (x == 1)
        sign_in();
    else if (x == 3)
        sign_up();
    else
        exit(1);
}

//function for forget password
void forgot_password()
{
    system("cls");
    struct sign_up a[no_of_users];
    int x, c = 0, i;
    char name1[50], pin[50];

    printf("____Welcome to Forgot Password page____\n");
    printf("Enter UserName: ");
    scanf("%s", name1);
    printf("Enter Security Pin: ");
    scanf("%s", pin);

    FILE *fp = NULL;
    fp = fopen("user_pass.bin", "rb");
    if (fp == NULL)
    {
        printf("File opening error.\n");
        exit(0);
    }
    fread(a, sizeof(struct sign_up), no_of_users, fp);

    for (i = 0; i < no_of_users; i++)
    {
        if (!strcmp(a[i].name, name1))
        {
            if (!strcmp(a[i].security_pin, pin))
            {
                c = 1;
                fflush(stdin);
                printf("Security Pin Matched Successful.\n");
                printf("Enter New Password: ");
                gets(a[i].pass);
                printf("Password change succesful.\n");
            }
        }
    }
    fclose(fp);
    if (c != 1)
    {
        printf("____Security pin not matched____\n\n");
        printf("1: Try Again    2: Exit ||  Input: ");
        scanf("%d", &x);
        if (x == 1)
            forgot_password();
        else
            exit(1);
    }
    else
    {
        fp = fopen("user_pass.bin", "wb");
        fwrite(a, sizeof(struct sign_up), no_of_users, fp);
        fclose(fp);
    }

    printf("\n1: Sign In    2:Sign Up    3: Exit  ||  Input: ");
    scanf("%d", &x);
    if (x == 1)
        sign_in();
    else if (x == 2)
        sign_up();
    else
        exit(1);
}

void menu()
{
    system("cls");
    printf("Sign In Successful.\n");
    int x;
    printf("\t1: Add Student\n\t2: Search Student\n\t3: Student List\n\t4: Update Details\n\t5: Delete Details\n\t6: Exit");
    printf("\n\n\t  Input: ");
    fflush(stdin);
    scanf("%d", &x);
    switch (x)
    {
    case 1:
        add_student();
        break;

    case 2:
        search();
        break;

    case 3:
        student_list();
        break;

    case 4:
        update();
        break;

    case 5:
        delete ();
        break;

    case 6:
        exit(1);
        break;

    default:
        printf("Invalid Choice.");
        exit(0);
    }
    exit(0);
}

void add_student()
{
    struct student info;
    int y, c;
    // taking input for storing to database
    fflush(stdin);
    printf("Enter Student Name: ");
    gets(info.name);
    fflush(stdin);
    printf("Enter Parent's Name: ");
    gets(info.parents);
    fflush(stdin);
    printf("Enter Branch: ");
    gets(info.branch);
    fflush(stdin);
    printf("Enter Semester: ");
    gets(info.semester);
    fflush(stdin);
    printf("Enter Roll No: ");
    gets(info.roll_no);
    fflush(stdin);
    printf("Enter Phone Number: ");
    gets(info.ph_no);
    fflush(stdin);
    printf("Enter Email: ");
    gets(info.email);

    //file handling
    FILE *fp = NULL;
    fp = fopen("student_info.bin", "ab+");
    if (fp == NULL)
        printf("Cannot open file at add_student function");
    printf("1: Confirm    2: Cancel  ||  Input: ");
    fflush(stdin);
    scanf("%d", &y);
    if (y == 1)
    {
        no_of_students = no_of_students + 1;
        fwrite(&info, 1, sizeof(struct student), fp);
        fclose(fp);
        // printing inceremented value to no_of_student file
        fp = fopen("no_of_students.txt", "w");
        fprintf(fp, "%d", no_of_students);
        fclose(fp);
        add_student_message();
    }
    else if (y == 2)
        add_student_message();
}

void add_student_message()
{
    // system("cls");
    int x;
    printf("1: Add Another Student 2: Exit  || Input: ");
    fflush(stdin);
    scanf("%d", &x);
    if (x == 1)
        add_student();
    else
        exit(1);
}

//search function
void search()
{
    int c;
    printf("1: Search using Name    2: Search using RollNo    3: Cancel Search    ||   Input: ");
    scanf("%d", &c);
    system("cls");
    if (c == 1)
        search_name();
    else if (c == 2)
        search_roll();
    else if (c == 3)
    {
        printf("Search was cancelled");
        exit(0);
    }
    else
    {
        printf("Invalid Input");
        exit(0);
    }
}

//searching using name
void search_name()
{
    struct student a[no_of_students];
    int i, n = 0;
    char name1[100];
    FILE *fp = NULL;
    fp = fopen("student_info.bin", "rb");
    if (fp == NULL)
    {
        printf("Error: No Records Found");
        exit(0);
    }
    fread(a, sizeof(struct student), no_of_students, fp);
    fflush(stdin);
    printf("Enter Name: ");
    gets(name1);
    for (i = 0; i < no_of_students; i++)
    {
        if (strcmp(a[i].name, name1) == 0)
        {
            system("cls");
            n = 1;
            printf("Match Found");
            printf("\nName - %s", a[i].name);
            printf("\nParents Name - %s", a[i].parents);
            printf("\nBranch - %s", a[i].branch);
            printf("\nSemester - %s", a[i].semester);
            printf("\nRoll Number - %s", a[i].roll_no);
            printf("\nPhone Number - %s", a[i].ph_no);
            printf("\nEmail - %s", a[i].email);
            break;
        }
    }
    if (n != 1)
        printf("No records found");
    fclose(fp);
}

//searching using roll number
void search_roll()
{
    struct student a[no_of_students];
    int n = 0, i;
    char roll1[100];
    FILE *fp = NULL;
    fp = fopen("student_info.bin", "rb");
    if (fp == NULL)
    {
        printf("Error: No Records Found");
        exit(0);
    }
    fread(a, sizeof(struct student), no_of_students, fp);
    fflush(stdin);
    printf("Enter Roll Number: ");
    gets(roll1);
    for (i = 0; i < no_of_students; i++)
    {
        if (strcmp(a[i].roll_no, roll1) == 0)
        {
            system("cls");
            n = 1;
            printf("Match Found");
            printf("\nName - %s", a[i].name);
            printf("\nParents Name - %s", a[i].parents);
            printf("\nBranch - %s", a[i].branch);
            printf("\nSemester - %s", a[i].semester);
            printf("\nRoll Number - %s", a[i].roll_no);
            printf("\nPhone Number - %s", a[i].ph_no);
            printf("\nEmail - %s", a[i].email);
            break;
        }
    }
    if (n != 1)
        printf("No records found");
    fclose(fp);
}

void student_list()
{
    struct student a[no_of_students];
    int i;
    FILE *fp;
    fp = fopen("student_info.bin", "rb");
    fread(a, no_of_students, sizeof(struct student), fp);
    fclose(fp);
    printf("LIST:- \n\n");
    for (int i = 0; i < no_of_students; i++)
    {
        printf("%d. %s\n", i + 1, a[i].name);
    }
}

void update()
{
    struct student a[no_of_students];
    int i, n, c = 0;
    char roll1[100];
    FILE *fp = NULL;
    fp = fopen("student_info.bin", "rb");
    if (fp == NULL)
    {
        printf("Error: No Student Records Found");
        exit(0);
    }
    fread(a, sizeof(struct student), no_of_students, fp);

    fflush(stdin);
    printf("Enter Roll Number of concerned student: ");
    gets(roll1);

    for (i = 0; i < no_of_students; i++)
    {
        if (strcmp(a[i].roll_no, roll1) == 0)
        {
            system("cls");
            c = 1;
            printf("Match Found");
            printf("\nName - %s", a[i].name);
            printf("\nParents Name - %s", a[i].parents);
            printf("\nBranch - %s", a[i].branch);
            printf("\nSemester - %s", a[i].semester);
            printf("\nRoll Number - %s", a[i].roll_no);
            printf("\nPhone Number - %s", a[i].ph_no);
            printf("\nEmail - %s", a[i].email);
            break;
        }
    }
    if (c != 1)
    {
        printf("No records found");
        exit(0);
    }

    printf("\nChoose appropriate option:-");
    printf("\n 1: Edit Name   2: Edit parent's name   3: Edit branch   4: Edit semester   5: Edit Roll Number   6: Edit Phone Number   7: Edit email");
    printf("\n Input: ");
    scanf("%d", &n);
    fflush(stdin);
    switch (n)
    {
    case 1:
        printf("Enter New Name: ");
        gets(a[i].name);
        printf("Information Updated Succesfully");
        break;
    case 2:
        printf("Enter New Parent's Name: ");
        gets(a[i].parents);
        printf("Information Updated Succesfully");
        break;
    case 3:
        printf("Enter New Branch: ");
        gets(a[i].branch);
        printf("Information Updated Succesfully");
        break;
    case 4:
        printf("Enter New Semester: ");
        gets(a[i].semester);
        printf("Information Updated Succesfully");
        break;
    case 5:
        printf("Enter New Roll Number: ");
        gets(a[i].roll_no);
        printf("Information Updated Succesfully");
        break;
    case 6:
        printf("Enter New Phone Number: ");
        gets(a[i].ph_no);
        printf("Information Updated Succesfully");
        break;
    case 7:
        printf("Enter New Email: ");
        gets(a[i].email);
        printf("Information Updated Succesfully");
        break;
    default:
        printf("Invalid Input");
        break;
    }
    fclose(fp);

    fp = fopen("student_info.bin", "wb");
    fwrite(a, sizeof(struct student), no_of_students, fp);
    fclose(fp);
}

void delete ()
{
    struct student a[no_of_students];
    int i, c = 0;
    char roll1[100];
    FILE *fp = NULL;
    fp = fopen("student_info.bin", "rb");
    if (fp == NULL)
    {
        printf("Error: No Student Records Found");
        exit(0);
    }
    fread(a, sizeof(struct student), no_of_students, fp);

    fflush(stdin);
    printf("Enter Roll Number of concerned student: ");
    gets(roll1);

    for (i = 0; i < no_of_students; i++)
    {
        if (strcmp(a[i].roll_no, roll1) == 0)
        {
            system("cls");
            c = 1;
            printf("Match Found");
            printf("\nName - %s", a[i].name);
            printf("\nParents Name - %s", a[i].parents);
            printf("\nBranch - %s", a[i].branch);
            printf("\nSemester - %s", a[i].semester);
            printf("\nRoll Number - %s", a[i].roll_no);
            printf("\nPhone Number - %s", a[i].ph_no);
            printf("\nEmail - %s", a[i].email);
            break;
        }
    }
    if (c != 1)
    {
        printf("No records found");
        exit(0);
    }

    printf("\n\nChoose appropriate option:-");
    printf("\n1: Delete Info   2: Cancel ");
    printf("\nInput: ");
    scanf("%d", &c);
    if (c == 1)
    {
        for (; i < no_of_students - 1; i++)
        {
            strcpy(a[i].name, a[i + 1].name);
            strcpy(a[i].parents, a[i + 1].parents);
            strcpy(a[i].branch, a[i + 1].branch);
            strcpy(a[i].roll_no, a[i + 1].roll_no);
            strcpy(a[i].semester, a[i + 1].semester);
            strcpy(a[i].ph_no, a[i + 1].ph_no);
            strcpy(a[i].email, a[i + 1].email);
        }
        no_of_students--;
        printf("\nThe information was deleted successfully.");
    }
    else if (c == 2)
    {
        printf("The deletion was terminated.");
        exit(0);
    }
    else
    {
        printf("Invalid Input");
        exit(0);
    }
    fclose(fp);

    fp = fopen("student_info.bin", "wb");
    fwrite(a, sizeof(struct student), no_of_students, fp);
    fclose(fp);

    fp = fopen("no_of_students.txt", "w");
    fprintf(fp, "%d", no_of_students);
    fclose(fp);
}   