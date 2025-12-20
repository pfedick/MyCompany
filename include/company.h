#ifndef COMPANY_H
#define COMPANY_H

#include <vector>

#include <ppl7.h>

class CodeSkillTypes
{
public:
    enum SkillType {
        SkillSystem,
        Skill2D,
        Skill3D,
        SkillNetwork,
        SkillAudio,
        SkillHardware,
        SkillVideo,
        SkillMax
    };
};

class ArtSkillTypes
{
public:
    enum SkillType {
        Skill2D,
        Skill3D,
        SkillAudio,
        SkillVideo,
        SkillMax
    };
};

class DevSkills
{
public:
    float Design[CodeSkillTypes::SkillMax] = { 0.0f };
    float Code[CodeSkillTypes::SkillMax] = { 0.0f };
    float Art[ArtSkillTypes::SkillMax] = { 0.0f };
};

class SoftSkills
{
public:
    float Communication = 0.0f;
    float Teamwork = 0.0f;
    float ProblemSolving = 0.0f;
    float TimeManagement = 0.0f;
    float Adaptability = 0.0f;
    float Creativity = 0.0f;
    float Leadership = 0.0f;
    float Multitasking = 0.0f;
};

class SpecialSkills
{
public:
    float Support = 0.0f;
    float HR = 0.0f;
    float Marketing = 0.0f;
    float Accounting = 0.0f;
    float Law = 0.0f;
};


class Skills : public DevSkills
{
public:
    DevSkills dev;
    SoftSkills soft;
    SpecialSkills special;
};


class Object
{
    // Base class for all objects
public:
    Object();
    virtual ~Object();
    float x, y; // Position coordinates
};

class Person : public Object
{
    // Represents a person in the company
public:
    Person(const ppl7::String& name);
    ppl7::String name;
};

class Employee : public Person
{
    // Represents an employee in the company
public:
    Employee(const ppl7::String& name);
    Skills skills;

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
    void addMember(const Employee& person);

};



class Product
{
    // Represents a product developed by the company
private:
    ppl7::String name;

public:
    Product(const ppl7::String& name);
    ppl7::String getName() const;



};










#endif