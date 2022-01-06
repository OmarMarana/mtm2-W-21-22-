#include "Manager.h"
#include "exceptions.h"
#include <iostream>

namespace mtm
{

    std::set<Employee*, mtm::CompareEmployee>& Manager::getEmployees()
    {
        return employees;
    }

    Manager::Manager(const Manager& other) : Citizen(other.getId(), other.getFirstName(), other.getLastName(), other.getBirthYear())
    {
        salary = other.salary;
        hired = other.hired;
        for(std::set<Employee*, mtm::CompareEmployee>::iterator i = other.employees.begin(); i !=
        other.employees.end(); ++i)
        {   
            // Employee* employee = dynamic_cast<Employee*>((*i)->clone()); 
            std::shared_ptr<Employee> employee(new Employee(*(*i)));
            empls.push_back(employee);
            employees.insert(employee.get());
        }
    }

    Manager& Manager::operator=(const Manager& other)
    {
        hired = other.hired;
        salary = other.salary;
        // for(std::set<Employee*, mtm::CompareEmployee>::iterator i = employees.begin(); i !=
        // employees.end(); ++i)
        // {   
        //     delete (*i);
        // }

        employees.clear();
        empls.clear();

        for(std::set<Employee*, mtm::CompareEmployee>::iterator i = other.employees.begin(); i !=
        other.employees.end(); ++i)
        {   
            // Employee* employee = dynamic_cast<Employee*>((*i)->clone()); 
            std::shared_ptr<Employee> employee(new Employee(*(*i)));
            empls.push_back(employee);
            employees.insert(employee.get());
        }
        
        return *this;
    }

    int Manager::getSalary()const
    {
        return salary;
    }
    void Manager::addEmployee(Employee* employee)
    {
        if(employees.find(employee) == employees.end())
        {
            employees.insert(employee);
            return;
        }
        
        throw EmployeeAlreadyHired();
    }

    void Manager::removeEmployee(int employee_id)
    {
        Employee tmp_employee(employee_id,"a","a",1);

        if(employees.find(&tmp_employee) == employees.end())
        {
            throw EmployeeIsNotHired();
        }
        employees.erase(&tmp_employee);
    }
    
    void Manager::setSalary(int delta)
    {   
        int new_salary = salary + delta;
        if(new_salary <= 0)
        {
            this->salary = 0;
            return;
        }
        this->salary =new_salary;
    }
    std::ostream& Manager::printShort(std::ostream& stream) const 
    {
        return stream << getFirstName() << " " << getLastName() << std::endl 
        << "Salary: " << salary <<  std::endl;
        
    }
    std::ostream& Manager::printLong(std::ostream& stream) const 
    {
        stream << getFirstName() << " " << getLastName() << std::endl <<
        "id - " << getId() << " birth_year - " << getBirthYear() << std::endl <<
        "Salary: " << salary <<  std::endl << "Employees:"<<std::endl;       // check if there should be a space after Employees:
        
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
            (*i)->printShort(stream) ;
        } 
        // stream << std::endl;
        return stream;
    }
    
    Citizen* Manager::clone() const 
    {
        Citizen* ptr(new Manager(*this));
        return ptr; 
    }

    bool Manager::getHired() const
    {
        return hired;
    }

    void Manager::setHired(bool hired)
    {
        this->hired = hired;
    }


    bool Manager::isEmployeeIn(int employee_id)
    {
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {
               return true;
           }
        } 
        return false;
    }

    Employee* Manager::getEmployee(int employee_id)
    {
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {
               return *i;
           }
        } 
        return nullptr;

    }

    void Manager::updateEmployeesSalaryAfterFire(int delta)
    {
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
            (*i)->setSalary(delta);
        } 
    }

    void Manager::findEmployeeAndDeduceSalary(int employee_id,int delta)
    {  
        Employee tmp_employee(employee_id,"a","a",1);
        Employee* employee = *(employees.find(&tmp_employee));
        employee->setSalary(delta);
    }
}