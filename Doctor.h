#pragma once
#include <string>

using namespace std;


class Doctor{
    int doctor_id;
    string doctor_name;
    string password;
    string doctor_department;
    string doctor_specialzation;
    long doctor_mobileno;
    
public:
Doctor();
Doctor(int, string,string,string,string,long);
void show_Appointments(string doctor_name); //it will show patient name appointment time and appointment date.
void delete_appointment(); //docotr name, patient name, patien time and patient date
void show_previous_history_of_patient();
void create_prescription();

string getDoctor_name();
int getDoctor_id();
string getDoctor_department();
string getDoctor_specialzation();
long getDoctor_mobileno();
};