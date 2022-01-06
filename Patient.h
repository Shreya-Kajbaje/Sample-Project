#pragma once
#include<iostream>
#include<string>
#include<set>
using namespace std;


class Patient{
    int Patient_id;
    string Patient_password;
    string Patient_name;
    int Patient_age;
    string Patient_gender;
    long Patient_monileno;

public:
Patient();
Patient(int,string,string,int,string,long);
void create_appointment();
void view_appointmentsDate(); // for a particular date
void view_prescription();
void show_DepartmentWiseDoctor();

int getPatient_id();
string getPatient_name();
int getPatient_age();
string getPatient_gender();
long getPatient_mobileno();


};