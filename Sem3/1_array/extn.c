#include <stdio.h>

#include <stdlib.h>

#include <string.h>



typedef struct {

    char* name;

    int roll;

    char telephone[11];

    char* address;

} Student;



typedef struct {

    int maxStudents;

    int currentCount;

    Student** studentList;

} StudentRegister;



void trimNewline(char* str) {

    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')

        str[len - 1] = '\0';

}



Student* createStudentRecord() {

    Student* s = malloc(sizeof(Student));

    if (!s) return NULL;
	
    char buffer[200];



    printf("Enter name: ");

    fgets(buffer, sizeof(buffer), stdin);

    trimNewline(buffer);

    s->name = malloc(strlen(buffer) + 1);

    strcpy(s->name, buffer);



    printf("Enter roll number: ");

    scanf("%d", &s->roll);

    getchar(); // clear newline from buffer



    printf("Enter telephone number: ");

    fgets(s->telephone, sizeof(s->telephone), stdin);

    trimNewline(s->telephone);

    


    printf("Enter address: ");

    fgets(buffer, sizeof(buffer), stdin);

    trimNewline(buffer);

    s->address = malloc(strlen(buffer) + 1);

    strcpy(s->address, buffer);



    return s;

}



Student* readStudentFromFile(FILE* fp) {

    int roll;

    char name[100], tel[11], address[200];



    if (fscanf(fp, "%d\n", &roll) != 1) return NULL;
	
    fgets(fp);

    if (!fgets(name, sizeof(name), fp)) return NULL;

    if (!fgets(tel, sizeof(tel), fp)) return NULL;

    trimNewline(tel);

    if (!fgets(address, sizeof(address), fp)) return NULL;
	


    trimNewline(name);

    trimNewline(tel);

    trimNewline(address);



    Student* s = malloc(sizeof(Student));

    if (!s) return NULL;



    s->roll = roll;

    s->name = malloc(strlen(name) + 1);

    strcpy(s->name, name);

    strcpy(s->telephone, tel);

    s->address = malloc(strlen(address) + 1);

    strcpy(s->address, address);



    return s;

}



void freeStudent(Student* sp) {

    if (!sp) return;

    free(sp->name);

    free(sp->address);

    free(sp);

}



int addStudent(StudentRegister* reg, Student* student) {

    if (reg->currentCount >= reg->maxStudents) return 0;

    reg->studentList[reg->currentCount++] = student;

    return 1;

}



void displayStudents(const StudentRegister* reg) {

    printf("\n=== Student List ===\n");

    for (int i = 0; i < reg->currentCount; i++) {

        Student* s = reg->studentList[i];

        printf("Student %d:\n", i + 1);

        printf("  Name     : %s\n", s->name);

        printf("  Roll No. : %d\n", s->roll);

        printf("  Phone    : %s\n", s->telephone);

        printf("  Address  : %s\n\n", s->address);

    }

}



int main() {

    StudentRegister reg;

    int choice;



    printf("Enter maximum number of students to register: ");

    scanf("%d", &reg.maxStudents);

    getchar();



    reg.currentCount = 0;

    reg.studentList = malloc(sizeof(Student*) * reg.maxStudents);



    while (1) {

        printf("\n=== MENU ===\n");

        printf("1. Add student manually\n");

        printf("2. Add students from file\n");

        printf("3. Show all students\n");

        printf("4. Exit\n");

        printf("Choose an option: ");

        scanf("%d", &choice);

        getchar(); 



        if (choice == 1) {

            Student* student = createStudentRecord();

            if (!student || !addStudent(&reg, student)) {

                printf("Failed to add student.\n");

                if (student) freeStudent(student);

            }

        }

        else if (choice == 2) {

            char filename[100];

            printf("Enter filename: ");

            fgets(filename, sizeof(filename), stdin);

            trimNewline(filename);



            FILE* file = fopen(filename, "r");

            if (!file) {

                printf("Could not open file: %s\n", filename);

                continue;

            }



            while (!feof(file) && reg.currentCount < reg.maxStudents) {

                Student* student = readStudentFromFile(file);

                if (student) {

                    if (!addStudent(&reg, student)) {

                        freeStudent(student);

                        break;

                    }

                }

            }

            fclose(file);

        }

        else if (choice == 3) {

            displayStudents(&reg);

        }

        else if (choice == 4) {

            for (int i = 0; i < reg.currentCount; i++) {

                freeStudent(reg.studentList[i]);

            }

            free(reg.studentList);

            printf("Exiting...\n");

            break;

        }

        else {

            printf("Invalid choice. Please try again.\n");

        }

    }



    return 0;

}
