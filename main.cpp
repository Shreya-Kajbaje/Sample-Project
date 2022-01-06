//main driver file
#include <iostream>
#include "sqlite3.h"
#include "HospitalMangment.h"
#include<thread>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

sqlite3* db;
int rc = sqlite3_open("hospital1.db", &db);

int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main()
{
    HospitalMangment obj;
    
    thread t(&HospitalMangment::menuScreen, &obj);
    
    t.join();

    cout << "Thank You for using Hospital Management System!" << endl;
    
    return 0;
}

