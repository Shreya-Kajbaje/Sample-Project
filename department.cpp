#include "Department.h"


Department::Department() {}

Department::Department(int id ,string nm) : dept_id(id) , dept_name(nm) {}

void Department::showDepartment()
{
    cout<<this->dept_id<<" "<<this->dept_name<<endl;
}

int Department::getDepartment_id()
{
    return this->dept_id;
}

string Department::getDepartment_name()
{
    return this->dept_name;
}
