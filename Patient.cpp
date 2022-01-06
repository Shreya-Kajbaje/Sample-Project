#include "Patient.h"
#include<sqlite3.h>

#include <sstream>
#include <iostream>
using namespace std;

extern sqlite3 *db;

Patient::Patient() {}

Patient::Patient(int Pid,string pass,string name,int age,string gender,long mobileno) : Patient_id(Pid), Patient_password(pass),Patient_name(name),Patient_age(age),Patient_gender(gender),Patient_monileno(mobileno) {}

void Patient::create_appointment()
{

    string DoctorName,Date,Time;
    cout<<"Enter The Doctor name for which you want to create appointment\n";
    cin>>DoctorName;
    cout<<"Enter the date for appointment in(dd-MM-YYYY) format\n";
    cin>>Date;
    cout<<"Enter the Time(00:00 AM/PM ) format\n";
    getline(cin,Time);
    getline(cin,Time);



    char *zErrMsg = 0;
	int rc;
	const char *sql;
	const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

	stringstream ss, ss2;
	string query, query2;
    


	ss << "INSERT INTO APPOINTMENT (Patient_name,Doctor_name,Appointment_date,Appointment_time) VALUES ('"<<Patient_name<<"','"<< DoctorName << "','" << Date << "','" << Time << "');";
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
		fprintf(stdout, "Appointment Record inserted successfully\n");
	}


}

void Patient::view_appointmentsDate()
{
    string Date;
    cout<<"Enter the date(DD-MM-YYYY) for which you want to see the appointments\n";
    cin>>Date;
    cout<<"Appointments are: \n";
    cout<<"Doctor Name\t Timing\n";
    char *zErrMsg = 0;
    const char *sql;
    int rc;
    const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt *stmt;

    std::stringstream sql2;
    sql2 << "select * from APPOINTMENT where Patient_name ='" + Patient_name + "' and Appointment_date= '"+Date+"';";
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
        
        string dname = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
		string Time = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));

        

	    cout<<dname<<"\t\t"<<Time;
        cout<<"\n";
    }

    sqlite3_finalize(stmt);
    std::cout << "After while" << std::endl;

}

void Patient::view_prescription()
{
    cout<<"Prescription Date\tPrescription Details\n";

    char *zErrMsg = 0;
    const char *sql;
    int rc;
    const char *data = "Callback function called";
    int callback(void *data, int argc, char **argv, char **azColName);

    stringstream ss, ss2;
    string query, query2;

    sqlite3_stmt *stmt;

    std::stringstream sql2;
    sql2 << "select * from PRESCRIPTION where Patient_name ='" + Patient_name + "';";
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

	    cout<<prescriptionDate<<"\t\t"<<prescriptionDetails;
        cout<<"\n";
    }

    sqlite3_finalize(stmt);
    std::cout << "After while" << std::endl;

}

void Patient::show_DepartmentWiseDoctor()
{
    cout<<"The List of all Departments are: \n";
    char *zErrMsg = 0;
	int rc;
	const char *sql;
	const char *data = "Callback function called";
	int callback(void *data, int argc, char **argv, char **azColName);
    
	stringstream ss, ss2;
	string query, query2;

	sqlite3_stmt *stmt;


    ss << "select DISTINCT(Department_name) from DEPARTMENT ";
    query=ss.str();
    sql = query.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
		string dept_name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        cout<<dept_name<<endl;
    }

    sqlite3_finalize(stmt);


    string deptName;
    cout<<"choose from above department to view its doctor list\n";
    cin>>deptName;

    cout<<"Doctor List of "<<deptName<<" are: \n"; 
    string deptsss = "select * from DEPARTMENT where  Department_name = '"+deptName+"'";
    sql = deptsss.c_str();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        // fprintf("error: ", sqlite3_errmsg(sqlite3->db));
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
		string doctor_name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        cout<<doctor_name<<"\t";

    }

    sqlite3_finalize(stmt);
    cout<<"\n";

}

int Patient::getPatient_id()
{
    return Patient_id;
}

string Patient::getPatient_name()
{
    return Patient_name;
}

int Patient::getPatient_age()
{
    return Patient_age;
}

string Patient::getPatient_gender()
{
    return Patient_gender;
}

long Patient::getPatient_mobileno()
{
    return Patient_monileno;
}