// hashtableDemo_A.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Hash Table Implementation
//Example usecase: University Student Record


#include <iostream>
//#include <stdlib.h>
#include <chrono>

#define TABLELENGTH 5000
#define STUDENTNAMELEN 32

/*
unsigned int concantenate(unsigned a, unsigned b ) {
    unsigned pow = 10;
    while (b >= pow)
        pow *= 10;
    return a * pow + b;
}
*/

struct studentEntry {
    int ID;
    char studentName[STUDENTNAMELEN];
    float GPA;
};

//modified djb2 hashing algorithm from Dan Bernstein
long hashDJB2(char* str)
{
    long hash = 5381;
    //unsigned long finalHash;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    //original algorithm requires unsigned key-- this allows it to use regular chars without returning negative values
    if (hash < 0) {
        hash = (hash * -1) + 1;
    }

    return hash;
}

 
void addStudent(studentEntry targetTable[], int ID, char name[], float GPA) {
    //generate index from key using hash func
    unsigned int index = (hashDJB2(name) % TABLELENGTH);
    

    printf("Adding student at index %u, ", index);
    printf("given key = \"%s\"\n", name);
    //printf("index unsigned: %u\n", index);
    //printf("index signed: %d\n", index);

    //check if position is already populated, skip if true-- I don't think this works but ¯\_(._.)_/¯ )
    if (targetTable[index].studentName == NULL || targetTable[index].ID == NULL || targetTable[index].GPA == NULL) {
        printf("%s", "Table position already taken: Check for hash collision!\n");
    }

    //insert data into index position in table
    else {
        printf("%s", "Position seems unoccupied...\n");

        targetTable[index].ID = ID;
        strcpy_s(targetTable[index].studentName, name);
        targetTable[index].GPA = GPA;
    }
}

void editStudent(studentEntry targetTable[], char name[], int ID, float GPA) {
    //generate index from key using hash func
    unsigned int index = (hashDJB2(name) % TABLELENGTH);


    printf("Changing student data at index %u, ", index);
    printf("given key \"%s\"\n", name);
    //printf("index unsigned: %u\n", index);
    //printf("index signed: %d\n", index);

    targetTable[index].ID = ID;
    targetTable[index].GPA = GPA;

}

void printTable(studentEntry targetTable[], int tableLen) {
    tableLen = TABLELENGTH;

    for (int i = 0; i < tableLen; i++) {
        printf("For index i = %d\n", i);
        //if (targetTable[i].studentName != NULL || targetTable[i].ID != NULL || targetTable[i].GPA != NULL) {
        if (targetTable[i].GPA > 0) {
            //LOL ^
            printf("Student ID: %d, ", targetTable[i].ID);
            printf("Name: %s, ", targetTable[i].studentName);
            printf("GPA: %f \n", targetTable[i].GPA);
        }
        else {
            printf("No entry found...\n");
        }
    }
}


void findStudent(studentEntry targetTable[], char name[]) {
    //generate index from key func
    unsigned int index = (hashDJB2(name) % TABLELENGTH);

    //return/print data at index
    printf("For key \"%s\", ", name); 
    printf("index = %d:\n", index);
    if (targetTable[index].GPA > 0) {
        //see printTable()
        printf("Student ID: %d, ", targetTable[index].ID);
        printf("Name: %s, ", targetTable[index].studentName);
        printf("GPA: %f \n", targetTable[index].GPA);
    }
    else {
        printf("No entry found...\n");
    }
}

float getStudentGPA(studentEntry targetTable[], char name[]) {
    float GPA = -1;
    //generate index from key func
    unsigned int index = (hashDJB2(name) % TABLELENGTH);

    printf("For key \"%s\", ", name);
    printf("index = %d:\n", index);
    if (targetTable[index].GPA > 0) {
        //see printTable()
        GPA = targetTable[index].GPA;
        return GPA;
    }
    else {
        printf("getStudentGPA(): No entry found...\n");
        return -1;
    }

    //return/print data at index

}

int main() {
    
    studentEntry mainStudentTable[TABLELENGTH];
    char testNameA[32] = "John Smith";
    char testNameB[32] = "Jane Smith";
    char testNameC[32] = "John Doe";
    float testGPA_A = 4.22;
    float testGPA_B = 4.44;
    float testGPA_C = 3.32;

    //insertion time test

    auto startTimeA1 = std::chrono::high_resolution_clock::now();
    addStudent(mainStudentTable, 2400220, testNameA, testGPA_A);
    auto endTimeA1 = std::chrono::high_resolution_clock::now();

    auto startTimeB1 = std::chrono::high_resolution_clock::now();
    addStudent(mainStudentTable, 2400221, testNameB, testGPA_B);
    auto endTimeB1 = std::chrono::high_resolution_clock::now();

    auto startTimeC1 = std::chrono::high_resolution_clock::now();
    addStudent(mainStudentTable, 2400223, testNameC, testGPA_C);
    auto endTimeC1 = std::chrono::high_resolution_clock::now();

    auto elapsedTimeA1 = std::chrono::duration_cast<std::chrono::microseconds>(endTimeA1 - startTimeA1);
    auto elapsedTimeB1 = std::chrono::duration_cast<std::chrono::microseconds>(endTimeB1 - startTimeB1);
    auto elapsedTimeC1 = std::chrono::duration_cast<std::chrono::microseconds>(endTimeC1 - startTimeC1);

    printf("Elapsed time for insert A: %d us\n", elapsedTimeA1.count());
    printf("Elapsed time for insert B: %d us\n", elapsedTimeB1.count());
    printf("Elapsed time for insert C: %d us\n\n", elapsedTimeC1.count());


    //lookup time test

    char toSearchStrA[32] = "John Smith";
    char toSearchStrB[32] = "Tom Smith"; //does not exist in the table
    char toSearchStrC[32] = "Jane Smith";


    auto startTimeA = std::chrono::high_resolution_clock::now();
    findStudent(mainStudentTable, toSearchStrA);
    auto endTimeA = std::chrono::high_resolution_clock::now();

    auto startTimeB = std::chrono::high_resolution_clock::now();
    findStudent(mainStudentTable, toSearchStrB);
    auto endTimeB = std::chrono::high_resolution_clock::now();
    
    auto startTimeC = std::chrono::high_resolution_clock::now();
    printf("%f\n", getStudentGPA(mainStudentTable, toSearchStrC));
    auto endTimeC = std::chrono::high_resolution_clock::now();


    auto elapsedTimeA = std::chrono::duration_cast<std::chrono::microseconds>(endTimeA - startTimeA);
    auto elapsedTimeB = std::chrono::duration_cast<std::chrono::microseconds>(endTimeB - startTimeB);
    auto elapsedTimeC = std::chrono::duration_cast<std::chrono::microseconds>(endTimeC - startTimeC);

    printf("Elapsed time for lookup A: %d us\n", elapsedTimeA.count());
    printf("Elapsed time for lookup B: %d us\n", elapsedTimeB.count());
    printf("Elapsed time for lookup C: %d us\n", elapsedTimeC.count());


    //printTable(mainStudentTable, TABLELENGTH);

    /*
    char testName[32] = "John F Smith";
    int hashReturned = hashDJB2(testName) ;
    printf("%u\n", hashReturned);
    printf("%d\n", hashReturned % TABLELENGTH);
    */

    return 0;
}
