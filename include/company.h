#ifndef COMPANY_H
#define COMPANY_H

#include <vector>

#include <ppl7.h>


class Object
{
    // Base class for all objects
public:
    virtual ~Object() = default;
    float x, y; // Position coordinates



};

class Person : public Object
{
    // Represents a person in the company
public:
    Person(const char* name) : name(name) {}
    const char* name;
};

class Employee : public Person
{
    // Represents an employee in the company
public:
    Employee(const ppl7::String& name);
    ppl7::String position;
};



class Team
{
    // Represents a team in the company
private:
    ppl7::String teamName;
    std::list<Employee> members;
public:
    Team(const ppl7::String& teamName);
    ppl7::String getTeamName() const;
    void addMember(const Person& person);

};





#endif