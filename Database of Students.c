/****************************
 * Program 4: Database of Students
 *
 * Course: CS 211, Spring 2023
 * System: WindowsOS using Clion
 * Student Author: Zaid Khan Mohammed
 ****************************/


/*
* Instructions for Use:
* 
* 1. Start the program:
*    - Choose 'E' to start with an empty database.
*    - Choose 'F' to load a database from a file (provide the file name when prompted).
*
* 2. Once the database is set up, you will be presented with a menu:
*    - Enter 'C' to create a new student:
*        - Input the student's name, ID, GPA, and credit hours.
*    - Enter 'R' to read from the database:
*        - Choose an option to display:
*            1) Display the first 10 rows of the database
*            2) Display students on the honor roll (GPA >= 3.5)
*            3) Display students on academic probation (GPA < 2.0)
*            4-7) Display freshmen, sophomore, junior, or senior students by name
*            8) Display the information of a particular student by ID
*    - Enter 'D' to delete a student from the database by ID.
*    - Enter 'X' to exit the program.
*
* 3. Follow the prompts for input; ensure data is entered correctly.
*
* Note: The program manages memory dynamically, so ensure proper cleanup is handled
* when exiting.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char bufferDump[99];
typedef struct {
	char* name;
	char* id;
	double gpa;
	int creditHours;
} Student;

typedef struct StudentNode{
	Student* pStudent;
	struct StudentNode* pNext;
} StudentNode;

typedef struct {
	StudentNode* pIDList;
	StudentNode* pHonorRollList;
	StudentNode* pAcademicProbationList;
	StudentNode* pFreshmanList;
	StudentNode* pSophomoreList;
	StudentNode* pJuniorList;
	StudentNode* pSeniorList;
} Database;


void insert(char* name, char* id, double gpa, int creditHours, StudentNode* *pHead){
    //insertionType1=insert by ID
    //insertionType1=insert by GPA
    //insertionType1=insert by name
    StudentNode *pTemp;
    pTemp = malloc(sizeof(StudentNode));
    pTemp->pStudent = malloc(sizeof(Student));
    pTemp->pStudent->gpa = gpa;
    pTemp->pStudent->creditHours = creditHours;
    pTemp->pStudent->name = malloc(strlen(name) + 1);
    strcpy(pTemp->pStudent->name, name);
    pTemp->pStudent->id = malloc(strlen(id) + 1);
    strcpy(pTemp->pStudent->id, id);
    pTemp->pNext=NULL;

    if(*pHead==NULL){
        *pHead=pTemp;
        return;
    }

    StudentNode *pTemp2=*pHead;
    while ((pTemp2->pNext != NULL) && (strcmp(id, pTemp2->pNext->pStudent->id) > 0)) {
        pTemp2 = pTemp2->pNext;
    }
    if (strcmp(id, (*pHead)->pStudent->id) < 0) {
        pTemp->pNext = *pHead;
        *pHead = pTemp;
    } else {
        pTemp->pNext = pTemp2->pNext;
        pTemp2->pNext = pTemp;
    }
}


void updateListsGpa(char *id,Database *database){
    StudentNode *pStudentToAdd;
    pStudentToAdd = malloc(sizeof(StudentNode));
    pStudentToAdd->pNext=NULL;
    StudentNode *pTemp=database->pIDList; // pTemp traverses through id
    while (strcmp(id,pTemp->pStudent->id)!=0){
        pTemp=pTemp->pNext;
    }
    pStudentToAdd->pStudent=pTemp->pStudent;
    if (pStudentToAdd->pStudent->gpa>=3.5){ // by gpa
        StudentNode *pTemp2=database->pHonorRollList;
        if (database->pHonorRollList==NULL){
            database->pHonorRollList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && pStudentToAdd->pStudent->gpa>pTemp2->pNext->pStudent->gpa) {
            pTemp2 = pTemp2->pNext;
        }
        if (pStudentToAdd->pStudent->gpa<=(database->pHonorRollList)->pStudent->gpa) {
            pStudentToAdd->pNext=database->pHonorRollList;
            database->pHonorRollList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
    else if(pStudentToAdd->pStudent->gpa<2){
        StudentNode *pTemp2=database->pAcademicProbationList;
        if (database->pAcademicProbationList==NULL){
            database->pAcademicProbationList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && pStudentToAdd->pStudent->gpa>pTemp2->pNext->pStudent->gpa) {
            pTemp2 = pTemp2->pNext;
        }
        if (pStudentToAdd->pStudent->gpa<=(database->pAcademicProbationList)->pStudent->gpa) {
            pStudentToAdd->pNext=database->pAcademicProbationList;
            database->pAcademicProbationList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
    else { free(pStudentToAdd);}
}


void updateListsYear(char *id,Database *database){
    StudentNode *pStudentToAdd;
    pStudentToAdd = malloc(sizeof(StudentNode));
    pStudentToAdd->pNext=NULL;
    StudentNode *pTemp=database->pIDList; // pTemp traverses through id
    while (strcmp(id,pTemp->pStudent->id)!=0){
        pTemp=pTemp->pNext;
    }
    pStudentToAdd->pStudent=pTemp->pStudent;
    if (pStudentToAdd->pStudent->creditHours<=29){ // by name/credit hrs
        StudentNode *pTemp2=database->pFreshmanList;
        if (database->pFreshmanList==NULL){
            database->pFreshmanList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && strcmp(pStudentToAdd->pStudent->name,pTemp2->pNext->pStudent->name)>0) {
            pTemp2 = pTemp2->pNext;
        }
        if (strcmp(pStudentToAdd->pStudent->name,(database->pFreshmanList)->pStudent->name)<=0) {
            pStudentToAdd->pNext=database->pFreshmanList;
            database->pFreshmanList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
    else if (pStudentToAdd->pStudent->creditHours<=59){ // by name/credit hrs
        StudentNode *pTemp2=database->pSophomoreList;
        if (database->pSophomoreList==NULL){
            database->pSophomoreList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && strcmp(pStudentToAdd->pStudent->name,pTemp2->pNext->pStudent->name)>0) {
            pTemp2 = pTemp2->pNext;
        }
        if (strcmp(pStudentToAdd->pStudent->name,(database->pSophomoreList)->pStudent->name)<=0) {
            pStudentToAdd->pNext=database->pSophomoreList;
            database->pSophomoreList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
    else if (pStudentToAdd->pStudent->creditHours<=89){ // by name/credit hrs
        StudentNode *pTemp2=database->pJuniorList;
        if (database->pJuniorList==NULL){
            database->pJuniorList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && strcmp(pStudentToAdd->pStudent->name,pTemp2->pNext->pStudent->name)>0) {
            pTemp2 = pTemp2->pNext;
        }
        if (strcmp(pStudentToAdd->pStudent->name,(database->pJuniorList)->pStudent->name)<=0) {
            pStudentToAdd->pNext=database->pJuniorList;
            database->pJuniorList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
    else{ // by name/credit hrs
        StudentNode *pTemp2=database->pSeniorList;
        if (database->pSeniorList==NULL){
            database->pSeniorList=pStudentToAdd;
            return;
        }
        while ((pTemp2->pNext != NULL) && strcmp(pStudentToAdd->pStudent->name,pTemp2->pNext->pStudent->name)>0) {
            pTemp2 = pTemp2->pNext;
        }
        if (strcmp(pStudentToAdd->pStudent->name,(database->pSeniorList)->pStudent->name)<=0) {
            pStudentToAdd->pNext=database->pSeniorList;
            database->pSeniorList=pStudentToAdd;
        } else {
            pStudentToAdd->pNext = pTemp2->pNext;
            pTemp2->pNext = pStudentToAdd;
        }
    }
}


void delete(char* idToDelete, Database *database){
    StudentNode *prev =NULL;
    StudentNode *honorCheck=database->pHonorRollList;
    StudentNode *probationCheck=database->pAcademicProbationList;
    StudentNode *freshmanCheck=database->pFreshmanList;
    StudentNode *sophomoreCheck=database->pSophomoreList;
    StudentNode *juniorCheck=database->pJuniorList;
    StudentNode *seniorCheck=database->pSeniorList;
    while (honorCheck!=NULL && strcmp(honorCheck->pStudent->id,idToDelete)!=0){
        prev=honorCheck;
        honorCheck=honorCheck->pNext;
    }
    if (honorCheck!=NULL){
        if (honorCheck==database->pHonorRollList){
            prev=database->pHonorRollList;
            database->pHonorRollList=database->pHonorRollList->pNext;
            free(prev);
        } else{
            prev->pNext=honorCheck->pNext;
            free(honorCheck);
        }
    }
    while (probationCheck!=NULL && strcmp(probationCheck->pStudent->id,idToDelete)!=0){
        prev=probationCheck;
        probationCheck=probationCheck->pNext;
    }
    if (probationCheck!=NULL){
        if (probationCheck==database->pAcademicProbationList){
            prev=database->pAcademicProbationList;
            database->pAcademicProbationList=database->pAcademicProbationList->pNext;
            free(prev);
        } else{
            prev->pNext=probationCheck->pNext;
            free(probationCheck);
        }
    }
    while (freshmanCheck!=NULL && strcmp(freshmanCheck->pStudent->id,idToDelete)!=0){
        prev=freshmanCheck;
        freshmanCheck=freshmanCheck->pNext;
    }
    if (freshmanCheck!=NULL){
        if (freshmanCheck==database->pFreshmanList){
            prev=database->pFreshmanList;
            database->pFreshmanList=database->pFreshmanList->pNext;
            free(prev);
        } else{
            prev->pNext=freshmanCheck->pNext;
            free(freshmanCheck);
        }
    }
    while (sophomoreCheck!=NULL && strcmp(sophomoreCheck->pStudent->id,idToDelete)!=0){
        prev=sophomoreCheck;
        sophomoreCheck=sophomoreCheck->pNext;
    }
    if (sophomoreCheck!=NULL){
        if (sophomoreCheck==database->pSophomoreList){
            prev=database->pSophomoreList;
            database->pSophomoreList=database->pSophomoreList->pNext;
            free(prev);
        } else{
            prev->pNext=sophomoreCheck->pNext;
            free(sophomoreCheck);
        }
    }
    while (juniorCheck!=NULL && strcmp(juniorCheck->pStudent->id,idToDelete)!=0){
        prev=juniorCheck;
        juniorCheck=juniorCheck->pNext;
    }
    if (juniorCheck!=NULL){
        if (juniorCheck==database->pJuniorList){
            prev=database->pJuniorList;
            database->pJuniorList=database->pJuniorList->pNext;
            free(prev);
        } else{
            prev->pNext=juniorCheck->pNext;
            free(juniorCheck);
        }
    }
    while (seniorCheck!=NULL && strcmp(seniorCheck->pStudent->id,idToDelete)!=0){
        prev=seniorCheck;
        seniorCheck=seniorCheck->pNext;
    }
    if (seniorCheck!=NULL){
        if (seniorCheck==database->pSeniorList){
            prev=database->pSeniorList;
            database->pSeniorList=database->pSeniorList->pNext;
            free(prev);
        } else{
            prev->pNext=seniorCheck->pNext;
            free(seniorCheck);
        }
    }
    StudentNode *pTemp=database->pIDList;
    while (pTemp!=NULL && strcmp(pTemp->pStudent->id,idToDelete)!=0){
        prev=pTemp;
        pTemp=pTemp->pNext;
    }
    if (pTemp!=NULL){
        if (pTemp==database->pIDList){
            prev=database->pIDList;
            database->pIDList=database->pIDList->pNext;
            free(prev->pStudent->name);
            free(prev->pStudent->id);
            free(prev->pStudent);
            free(prev);
        } else{
            prev->pNext=pTemp->pNext;
            free(pTemp->pStudent->name);
            free(pTemp->pStudent->id);
            free(pTemp->pStudent);
            free(pTemp);
        }
    } else{
        printf("Sorry, there is no student in the database with the id %s.",idToDelete);
        return;
    }
}


void displayList(StudentNode *pHead){
    if (pHead==NULL){
        printf("There are no students matching that criteria.\n\n\n");
    }
    else{
        while (pHead!=NULL){
            printf("%s:\n", pHead->pStudent->name);
            printf("\tID - %s\n", pHead->pStudent->id);
            printf("\tGPA - %.2f\n", pHead->pStudent->gpa);
            printf("\tCredit Hours - %d\n", pHead->pStudent->creditHours);
            pHead = pHead->pNext;
        }
    }
}


void readDatabase(Database database){
    int databaseNumber;
    printf("Select one of the following: \n");
    printf("\t1) Display the head (first 10 rows) of the database\n");
    printf("\t2) Display students on the honor roll, in order of their GPA\n");
    printf("\t3) Display students on academic probation, in order of their GPA\n");
    printf("\t4) Display freshmen students, in order of their name\n");
    printf("\t5) Display sophomore students, in order of their name\n");
    printf("\t6) Display junior students, in order of their name\n");
    printf("\t7) Display senior students, in order of their name\n");
    printf("\t8) Display the information of a particular student\n");
    scanf("%d",&databaseNumber);
    fgets(bufferDump,99,stdin);
    printf("Your choice --> ");
    while (databaseNumber<1 || databaseNumber>8) {
        printf("Sorry, that input was invalid. Please try again.\n");
        scanf("%d",&databaseNumber);
        fgets(bufferDump,99,stdin);
        printf("Your choice --> ");
    }
    if (databaseNumber==1){
        StudentNode *pTemp=database.pIDList;
        for (int i=0;i<10;++i) {
            if (pTemp != NULL) {
                printf("%s:\n", pTemp->pStudent->name);
                printf("\tID - %s\n", pTemp->pStudent->id);
                printf("\tGPA - %.2f\n", pTemp->pStudent->gpa);
                printf("\tCredit Hours - %d\n", pTemp
                ->pStudent->creditHours);
                pTemp = pTemp->pNext;
            }
            else{ return;}
        }
        return;
    }
    else if (databaseNumber==2) {
        StudentNode *pTemp = database.pHonorRollList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==3) {
        StudentNode *pTemp = database.pAcademicProbationList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==4) {
        StudentNode *pTemp = database.pFreshmanList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==5) {
        StudentNode *pTemp = database.pSophomoreList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==6) {
        StudentNode *pTemp = database.pJuniorList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==7) {
        StudentNode *pTemp = database.pSeniorList;
        displayList(pTemp);
        return;
    }
    else if (databaseNumber==8){
        char studentID[99];
        printf("Enter the id of the student to find: ");
        fgets(studentID,99,stdin);
        studentID[strlen(studentID)-1]='\0';
        StudentNode *pTemp=database.pIDList;
        while (pTemp!=NULL){
            if (strcmp(pTemp->pStudent->id,studentID)==0){
                printf("%s:\n", pTemp->pStudent->name);
                printf("\tID - %s\n", pTemp->pStudent->id);
                printf("\tGPA - %.2f\n", pTemp->pStudent->gpa);
                printf("\tCredit Hours - %d\n", pTemp->pStudent->creditHours);
                return;
            }
            pTemp=pTemp->pNext;
        }
        printf("Sorry, there is no student in the database with the id %s.\n",studentID);
    }

}


void readFromFile(char fileName[],Database *database){
    FILE *filePtr = fopen(fileName, "r");
    // Check that the file was able to be opened
    if (filePtr == NULL) {
        printf("Error: could not open %s for reading\n", fileName);
        return;
    }
    char firstLine[99];
    fgets(firstLine,99,filePtr
    );
    char studentName[99];
    char studentId[99];
    double studentGpa;
    int studentCreditHours;
    while (fscanf(filePtr, "%[^,],%[^,],%lf,%d", studentName, studentId, &studentGpa, &studentCreditHours) == 4) {
        if (studentName[0]=='\n'){
            for (int i = 0; studentName[i] != '\0'; i++) {
                studentName[i] = studentName[i + 1];
            }
        }
        insert(studentName, studentId, studentGpa, studentCreditHours, &database->pIDList);
        updateListsGpa(studentId,database);
        updateListsYear(studentId,database);
    }

    fclose(filePtr);
}


int main() {
    char fileName[]="C:\\Users\\zaidk\\Downloads\\small-list.csv";

    setbuf( stdout, 0);
    char fileChoice[99];
    char databaseChoice[]="blank";

    double studentGpa;
    int studentCreditHours;
    Database database;
    database.pIDList=NULL;
    database.pHonorRollList=NULL;
    database.pAcademicProbationList=NULL;
    database.pFreshmanList=NULL;
    database.pSophomoreList=NULL;
    database.pJuniorList=NULL;
    database.pSeniorList=NULL;

	printf("Enter E to start with an empty database, \n");
	printf("or F to start with a database that has information on students from a file.\n");
    fgets(fileChoice,99,stdin);
	printf("Your choice --> ");
    while ((fileChoice[0]!='E' && fileChoice[0]!='F') || strlen(fileChoice)!=2) {
        printf("Sorry, that input was invalid. Please try again.\n");
        fgets(fileChoice,99,stdin);
        printf("Your choice --> ");
    }

        if(fileChoice[0]=='F') {
            printf("Enter the name of the file you would like to use: ");
            fgets(fileName,99,stdin);
            fileName[strlen(fileName)-1]='\0';
            readFromFile(fileName,&database);
        }
        while (databaseChoice[0]!='X') {
            char studentName[99];
            char studentId[99];
            printf("\nEnter: \tC to create a new student and add them to the database,\n");
            printf("\tR to read from the database,\n");
            printf("\tD to delete a student from the database, or\n");
            printf("\tX to exit the program.\n");
            fgets(databaseChoice, 99, stdin);
            printf("Your choice --> ");
            while ((databaseChoice[0] != 'C' && databaseChoice[0] != 'R' && databaseChoice[0] != 'D' &&
                databaseChoice[0] != 'X') || strlen(databaseChoice)!=2) {
                printf("Invalid option. Try again.\n");
                fgets(databaseChoice, 99, stdin);
                printf("Your choice --> ");
            }
            if (databaseChoice[0] == 'C') {
                printf("Enter the name of the new student: ");
                fgets(studentName, 99, stdin);
                studentName[strlen(studentName) - 1] = '\0';
                printf("Enter the ID of the new student: ");
                fgets(studentId, 99, stdin);
                studentId[strlen(studentId) - 1] = '\0';
                printf("Enter the GPA of the new student: ");
                scanf("%lf", &studentGpa);
                fgets(bufferDump,99,stdin);
                printf("Enter the credit hours of the new student: ");
                scanf("%d", &studentCreditHours);
                fgets(bufferDump,99,stdin);
                insert(studentName, studentId, studentGpa, studentCreditHours, &database.pIDList);
                updateListsGpa(studentId,&database);
                updateListsYear(studentId,&database);
                printf("Successfully added the following student to the database!\n");
                printf("%s:\n", studentName);
                printf("\tID - %s\n", studentId);
                printf("\tGPA - %.2f\n", studentGpa);
                printf("\tCredit Hours - %d\n", studentCreditHours);
            } else if (databaseChoice[0] == 'R') {
                readDatabase(database);
            }
            else if(databaseChoice[0]=='D'){
                printf("Enter the id of the student to be removed: ");
                char studentToRemove[99];
                fgets(studentToRemove,99,stdin);
                studentToRemove[strlen(studentToRemove)-1]='\0';
                delete(studentToRemove,&database);
            }
        }

    while (database.pIDList!=NULL){
        delete(database.pIDList->pStudent->id,&database);
    }

        printf("\n");
        printf("Thanks for playing!\n");
        printf("Exiting...\n");

	return 0;
}