#include "student.h"

Student::Student(string name, int age) : name(name), age(age) {}

void Student::setAge(int age)
{
    this->age = age;
}

void Student::setName(string name)
{
    this->name = name;
}

string Student::getName() const
{
    return name;
}

int Student::getAge() const
{
    return age;
}

void Student::printStudentInfo() const
{
    cout << "Name: " << name << ", Age: " << age << endl;
}
