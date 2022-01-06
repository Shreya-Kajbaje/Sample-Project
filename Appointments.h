#pragma once
#include<iostream>
#include<string>
#include<set>
#include"Doctor.h"
using namespace std;


class Appointments{

int appointment_id;
string appointment_date;
string appointment_time;


public:
Appointments();
Appointments(int,string,string);
void view_Appointments();

int getAppointmentId();
string getAppointmentDate();
string getAppointmentTime();

void setAppointment_date(string);
void setAppointment_time(string);

};