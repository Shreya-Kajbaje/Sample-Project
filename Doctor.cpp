#include "Doctor.h"
#include<sqlite3.h>

#include <sstream>
#include <iostream>
using namespace std;
extern sqlite3 *db;

Doctor::Doctor() {}

Doctor::Doctor(int id, string dnm,string pass,string doc_dept,string spc,long mb) : doctor_id(id),doctor_name(dnm),password(pass),doctor_department(doc_dept),doctor_specialzation(spc),doctor_mobileno(mb) {}

void Doctor::show_Appointments(string docName) // patientName , appointment_date, appointment_time
{
    cout<<"Patient Name\tAppointment Date\tAppoinment Time"<<endl;

    char *zErrMsg = 0;
    const char *sql;
    int rc;
    const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt *stmt;

    std::stringstream sql2;
    sql2 << "select * from APPOINTMENT where Doctor_name ='" + docName + "';";
    query=sql2.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        
		string patientName = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
	
		string appointmentDate = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));

        string appointmentTime = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));

	    cout<<patientName<<"\t\t"<<appointmentDate<<"\t\t"<<appointmentTime;
        cout<<"\n";
    }

    sqlite3_finalize(stmt);
    std::cout << "After while" << std::endl;
}

void Doctor::delete_appointment()
{
    cout<<"Enter the patient name & appointment date and appointment respectively time to delete the appointment\n";
    string patientName,appointmentDate,appointmentTime;
    cin>>patientName>>appointmentDate;
    getline(cin,appointmentTime);
    getline(cin,appointmentTime);


    char *zErrMsg = 0;
	int rc;
	const char *sql;
	const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

	stringstream ss, ss2;
	string query, query2;

	ss << "DELETE FROM APPOINTMENT where Patient_name= '"<<patientName<<"' and appointment_date = '"<<appointmentDate<<"' and Appointment_time= '"<<appointmentTime<<"';";
	query = ss.str();
	sql = query.c_str();

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Appointment Details Deleted Successfully\n");
	}

}

void Doctor::show_previous_history_of_patient()
{
    cout<<"Enter the name of patient which you want to show previous history\n";
    string patientName;
    cin>>patientName;
    cout<<"Patient name \t Presription Date \t Prescription Details"<<endl;
    char *zErrMsg = 0;
    const char *sql;
    int rc;
    const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt *stmt;

    std::stringstream sql2;
    sql2 << "select * from PRESCRIPTION where Patient_name ='" + patientName + "';";
    query=sql2.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        
	
		string prescriptionDate = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));

        string prescriptionDetails = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));

	    cout<<patientName<<"\t\t"<<prescriptionDate<<"\t\t"<<prescriptionDetails;
        cout<<"\n";
    }

    sqlite3_finalize(stmt);
    std::cout << "After while" << std::endl;


}

void Doctor::create_prescription()
{

    cout<<"Doctor name is: "<<doctor_name;
    cout<<"Enter the name of patient for which you want to create a prescription\n";
    string patientName,Date,Details;
    cin>>patientName;
    cout<<"Enter the date of prescription in(dd-MM-YYYY) format\n";
    cin>>Date;
    cout<<"Enter the prescription Details\n";
    getline(cin,Details);
    getline(cin,Details);



    char *zErrMsg = 0;
	int rc;
	const char *sql;
	const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

	stringstream ss, ss2;
	string query, query2;
    


	ss << "INSERT INTO PRESCRIPTION (Patient_name,Doctor_name,Prescription_date,Prescription_detail) VALUES ('"<<patientName<<"','"<< doctor_name << "','" << Date << "','" << Details << "');";
	query = ss.str();
	sql = query.c_str();

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Prescription Record inserted successfully\n");
	}


}
string Doctor::getDoctor_name()
{
    return doctor_name;
}

string Doctor::getDoctor_department()
{
    return doctor_department;
}

string Doctor::getDoctor_specialzation()
{
    return  doctor_specialzation;
}

long Doctor::getDoctor_mobileno()
{
    return doctor_mobileno;
}
int Doctor::getDoctor_id()
{
    return doctor_id;
}