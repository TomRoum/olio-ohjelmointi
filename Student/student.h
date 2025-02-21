#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Student {
public:
    Student(string name, int age);
    void setAge(int age);
    void setName(string name);
    string getName() const;
    int getAge() const;
    void printStudentInfo() const;

private:
    string name;
    int age;
};

#endif // STUDENT_H
