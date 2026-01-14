// SANCHITA GUPTA-2024CSB047 , ASSIGNMENT-1

#define MAX_STUDENTS 10
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

struct Student {
    char name[20];
    int roll;
    char telephone[11];
    char address [20];
};

struct SReg{
int count;
struct Student studentArray[MAX_STUDENTS]; 
};


int add(struct SReg *sr, struct Student s){
    for(int i=0;i<=sr->count;i++){
        if(sr->studentArray[i].roll== s.roll){
            return 0;
            }
        }
    sr->studentArray[sr->count++]=s;
            return 1; 
}

struct Student get(struct SReg *sr, int r){
    struct Student NotFound={"Error",00," X","X"};
    for(int i=0;i<=sr->count;i++){
    if(sr->studentArray[i].roll==r){
        return sr->studentArray[i];
    }
    return NotFound;
    }
}

int delete(struct SReg *sr, int r){
    for(int i=0;i<=sr->count;i++){
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

int modify(struct SReg *sr, struct Student s){
    for(int i=0;i<=sr->count;i++){
    if(sr->studentArray[i].roll==s.roll){
        sr->studentArray[i]=s;
        return 1;      
        }
    }
    return 0;
}

int getCount(struct SReg sr){
    return sr.count;
}

void sortStudents(struct SReg *sr){
    for(int i=0;i<=sr->count;i++){
        struct Student temp;
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
}

void export(struct SReg sr, char file[]) {
    FILE *fp = fopen(file, "w");
    if (fp==NULL) {
        printf("File cannot be opened for writing!\n");
        return;
    }
    for (int i = 0; i < sr.count; i++) {
        fprintf(fp, "%s,%d,%s,%s\n", sr.studentArray[i].name, sr.studentArray[i].roll,sr.studentArray[i].telephone, sr.studentArray[i].address);
    }
    fclose(fp);
    printf("Exported to %s\n", file);
}

void load(struct SReg *sr, char file[]) {
    FILE *fp = fopen(file, "r");
    if (fp==NULL) {
        printf("File cannot be opened for reading!\n");
        return;
    }
    sr->count = 0;
    while (!feof(fp) && sr->count < MAX_STUDENTS) {
        struct Student s;
        if (fscanf(fp, "%19[^,],%d,%10[^,],%19[^\n]\n", s.name, &s.roll, s.telephone, s.address) == 4) {
            sr->studentArray[sr->count++] = s;
        }
    }
    fclose(fp);
    printf("Loaded from %s\n", file);
}

int main(){
    struct SReg sr;
    sr.count=0;
    struct Student s1={"Sanchita",101,"9999999","address1"};
    struct Student s2={"Aaa",102,"8888888","address2"};
    struct Student s3={"Bbb",103,"7777777","address3"};
    printf("Added:%d\n",add(&sr,s1));
    add(&sr,s2);
    add(&sr,s3);
    struct Student found= get(&sr,106);
    printf("Your Search: Name- %s, Roll- %d\n",found.name,found.roll);
    printf("Delete:%d\n",delete(&sr,108));
    struct Student s={"Stud",109,"3333333","address10"};
    printf("Modify: %d\n",modify(&sr,s));
    sortStudents(&sr);
    for(int i=0;i<sr.count;i++){
        printf("%s | %d | %s | %s\n",sr.studentArray[i].name,sr.studentArray[i].roll,sr.studentArray[i].address,sr.studentArray[i].telephone);
    }
    printf("The number of students registered is %d\n",getCount(sr));
    export(sr,"student.txt");
    load(&sr,"student.txt");
    for(int i=0;i<sr.count;i++){
        printf("%s | %d | %s | %s\n",sr.studentArray[i].name,sr.studentArray[i].roll,sr.studentArray[i].address,sr.studentArray[i].telephone);
    }
    return 0;
}
