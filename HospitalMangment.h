#pragma once
#include"Patient.h"
#include"Doctor.h"
#include"Accountant.h"
#include"Payment.h"
#include <mutex>


class HospitalMangment{

public:
void DoctorFunction(Doctor*);
void PatientFunction(Patient*);
void PatientUserFunction();
Doctor* doctorLogin(string, string);
Patient* patientLogin();
void AccountantFunction(Accountant*);
Accountant* accountantLogin(string, string);
void registerPatient();
void menuScreen();
};