#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int roll;
    char telephone[11];   //(10 digits + null terminator)
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
    s->name = malloc(strlen(buffer));
    strcpy(s->name, buffer);

    printf("Enter roll number: ");
    scanf("%d", &s->roll);
    getchar(); // clear newline from buffer

    printf("Enter telephone number: ");
    fgets(buffer, sizeof(buffer), stdin);
    trimNewline(buffer);
    strncpy(s->telephone, buffer, sizeof(s->telephone) - 1);
    s->telephone[10] = '\0'; // safety

    printf("Enter address: ");
    fgets(buffer, sizeof(buffer), stdin);
    trimNewline(buffer);
    s->address = malloc(strlen(buffer) + 1);
    strcpy(s->address, buffer);

    return s;
}

// Comma Separated Values(csv) style file reader
Student* readStudentFromFile(FILE* fp) {
    int roll;
    char name[100], tel[100], address[200];

    if (fscanf(fp, "%99[^,],%d,%99[^,],%199[^\n]\n",name,&roll, tel, address) != 4)
        return NULL;

    Student* s = malloc(sizeof(Student));
    if (!s) return NULL;

    s->roll = roll;

    s->name = malloc(strlen(name) + 1);
    strcpy(s->name, name);

    strncpy(s->telephone, tel, sizeof(s->telephone) - 1);
    s->telephone[10] = '\0';

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

    for (int i = 0; i < reg->currentCount; i++) {
        if (reg->studentList[i]->roll == student->roll) {
            printf("Duplicate roll number not allowed!\n");
            return 0;
        }
    }

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
    if (!reg.studentList) {
        printf("Memory allocation failed!\n");
        return 1;
    }

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

            while (reg.currentCount < reg.maxStudents) {
                Student* student = readStudentFromFile(file);
                if (!student) break;
                if (!addStudent(&reg, student)) {
                    freeStudent(student);
                    break;
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
