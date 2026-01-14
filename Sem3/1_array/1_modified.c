// SANCHITA GUPTA-2024CSB047 , ASSIGNMENT-1

#define MAX_STUDENTS 10
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int roll;
    char telephone[11];
    char address [20];
}Student;

typedef struct{
int count;
Student studentArray[MAX_STUDENTS]; 
}SReg;


int add(SReg *sr,Student s){
    for(int i=0;i<sr->count;i++){
        if(sr->studentArray[i].roll== s.roll){
            return 0;
            }
        }
    sr->studentArray[sr->count++]=s;
            return 1; 
}

Student get(SReg *sr,int r){
    Student NotFound={"Error",00," X","X"};
    for(int i=0;i<sr->count;i++){
    if(sr->studentArray[i].roll==r){
        return sr->studentArray[i];
        }
    }
    return NotFound;
}

int delete(SReg *sr, int r){
    for(int i=0;i<sr->count;i++){
    if(sr->studentArray[i].roll==r){
        for(int j=i;j<=sr->count;j++){
            sr->studentArray[j]=sr->studentArray[j+1];
        }
        sr->count--;
        return 1;
        }
    }
    return 0;
}

int modify(SReg *sr, Student s){
    for(int i=0;i<sr->count;i++){
    if(sr->studentArray[i].roll==s.roll){
        sr->studentArray[i]=s;
        return 1;      
        }
    }
    return 0;
}

int getCount(SReg sr){
    return sr.count;
}

void sortStudents(SReg *sr){
    Student temp;
    for(int i=0;i<=sr->count;i++){
        for(int j=i+1;j<sr->count;j++){
            if(strcmp(sr->studentArray[i].name,sr->studentArray[j].name)>0){
                temp = sr->studentArray[i];
                sr->studentArray[i]=sr->studentArray[j];
                sr->studentArray[j]=temp;
            }
        }
    }
}

void export(SReg sr, char file[]) {
    FILE *fp = fopen(file, "w");
    if (fp==NULL) {
        printf("File cannot be opened for writing!\n");
        return;
    }
    for (int i = 0; i < sr.count; i++) {
        fprintf(fp, "Name: %s, Roll: %d, Telephone: %s, Address: %s\n", sr.studentArray[i].name, sr.studentArray[i].roll,sr.studentArray[i].telephone, sr.studentArray[i].address);
    }
    fclose(fp);
    printf("Exported to %s\n", file);
}

void load(SReg *sr, char file[]) {
    FILE *fp = fopen(file, "r");
    if (fp==NULL) {
        printf("File cannot be opened for reading!\n");
        return;
    }
    sr->count = 0;
    while (!feof(fp) && sr->count < MAX_STUDENTS) {
        Student s;
        if (fscanf(fp, "%19[^,],%d,%10[^,],%19[^\n]\n", s.name, &s.roll, s.telephone, s.address) == 4) {
            sr->studentArray[sr->count++] = s;
        }
    }
    fclose(fp);
    printf("Loaded from %s\n", file);
}

int main(){
    int roll=0;
    Student s;
    char file[20];
    SReg sr;
    sr.count=0;
    int running=1;
    int choice=0;
    while (running) {
        printf("\n=== MENU ===\n");
        printf("1. Add student manually\n");
        printf("2. Search a student by roll number\n");
        printf("3. Delete a student by roll number\n");
        printf("4. Modify a student details\n");
        printf("5. Number of students entered\n");
        printf("6. Sort students by name\n");
        printf("7. Export students details to file\n");
        printf("8. Load students details from file\n");
        printf("9. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); 
    switch (choice)
    {
    case 1:
        printf("Enter stduent details: \n");
        printf("Name:");
        scanf("%s",s.name);
        printf("Roll:");
        scanf("%d",&s.roll);
        printf("Telephone:");
        scanf("%s",s.telephone);
        printf("Address:");
        scanf("%s",s.address);
        if(add(&sr,s)) printf("Added!");
        else printf("Error");
        
        break;
    case 2: 
        printf("Enter the roll number:");
        scanf("%d",&roll);
        get(&sr,roll);
        printf("Name: %s\nRoll:%d\nTelephhone: %s\nAddress: %s\n",get(&sr,roll).name,get(&sr,roll).roll,get(&sr,roll).telephone,get(&sr,roll).address);
        break;
    case 3:
        printf("Enter the roll number:");
        scanf("%d",&roll);
        if(delete(&sr,roll)){
            printf("Deleted!");
        }
        else{
            printf("Not found");
        }
        break;
    case 4:
        printf("Enter the Roll of the student you want to modify: ");
        scanf("%d",&s.roll);
        printf("Enter new details:\n");
        printf("Name: "); scanf("%s",s.name);
        printf("Telephone: "); scanf("%s",s.telephone);
        printf("Address: "); scanf("%s",s.address);

    if(modify(&sr,s)) {
        printf("Modified successfully!\n");
    } else {
        printf("Roll number doesn't exist\n");
    }

        break;
    case 5:
        printf("Count = %d",getCount(sr));
        break;
    case 6: 
        sortStudents(&sr);
        for(int i=0;i<sr.count;i++){
        printf("%s | %d | %s | %s\n",sr.studentArray[i].name,sr.studentArray[i].roll,sr.studentArray[i].address,sr.studentArray[i].telephone);
        }
        break;
    case 7: 
        printf("Enter the file name:");
        scanf("%s",file);
        export(sr,file);
        break;
    case 8:
        printf("Enter the file name to read from:");
        scanf("%s",&file);
        load(&sr,file);
        break;
    case 9:
        running=0;
        break;
    default:
        printf("Invalid choice!");
        break;
    }
}
    
    
    return 0;
}
