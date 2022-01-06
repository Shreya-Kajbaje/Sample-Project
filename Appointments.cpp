#include"Appointments.h"

Appointments::Appointments() { }

Appointments::Appointments(int id, string date, string time) : appointment_id(id),appointment_date(date),appointment_time(time) { }

void Appointments::view_Appointments(){
cout<<appointment_id<<"\t"<<appointment_date<<"\t"<<appointment_time<<endl;
}

int Appointments::getAppointmentId()
{
    return appointment_id;
}

string Appointments::getAppointmentDate()
{
    return appointment_date;
}

string Appointments::getAppointmentTime()
{
    return appointment_time;
}


void Appointments::setAppointment_date(string date)
{
    this->appointment_date=date;
}

void Appointments::setAppointment_time(string time)
{
    this->appointment_time = time;
}