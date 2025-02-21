#include "student.h"
#include <vector>
#include <algorithm>

int main() {
    int selection =0;
    vector<Student> studentList;

    do
    {
        cout << " " << endl;
        cout << "------------------------------------" << endl;
        cout << "Select" << endl;
        cout << "0: Add student" << endl;
        cout << "1: Print all students" << endl;
        cout << "2: Sort and print students by Name" << endl;
        cout << "3: Sort and print students by Age" << endl;
        cout << "4: Find and print student" << endl;
        cout << "5: Remove student" << endl;
        cout << "6: Exit" << endl;
        cout << "------------------------------------" << endl;
        cin >> selection;

        switch (selection)
        {
        case 0:
        {
            string name;
            int age;
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter student age: ";
            cin >> age;
            studentList.emplace_back(name, age);
            break;
        }

        case 1:
            for (const Student& student : studentList)
            {
                student.printStudentInfo();
            }
            break;

        case 2:
            sort(studentList.begin(), studentList.end(), [](const Student& a, const Student& b)
                 {
                     return a.getName() < b.getName();
                 });

            for (const Student& student : studentList)
            {
                student.printStudentInfo();
            }
            break;

        case 3:
            sort(studentList.begin(), studentList.end(), [](const Student& a, const Student& b)
                 {
                     return a.getAge() > b.getAge();
                 });

            for (const Student& student : studentList)
            {
                student.printStudentInfo();
            }
            break;

        case 4:
        {
            string searchName;
            cout << "Enter student name to find: ";
            cin >> searchName;
            //could be written ´auto it = ...´
            vector<Student>::iterator it = find_if(studentList.begin(), studentList.end(), [&](const Student& student)
            {
            return student.getName() == searchName;
            });

            if (it != studentList.end())
            {
                it->printStudentInfo();
            }
            else
            {
                cout << "Student not found!" << endl;
            }
            break;
        }

        case 5:
        {
            string removeName;
            cout << "Enter student name to remove: ";
            cin >> removeName;

            //could be written ´auto it = ...´
            vector<Student>::iterator it = remove_if(studentList.begin(), studentList.end(),
            [&](const Student& student)
            {
            return student.getName() == removeName;
            });

            if (it != studentList.end())
            {
                studentList.erase(it, studentList.end());  // Erase the removed students
                cout << "Student removed successfully!" << endl;
            }
            else
            {
                cout << "Student not found!" << endl;
            }
            break;
        }

        case 6:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Wrong selection, try again!" << endl;
            break;
        }
    } while (true);

    return 0;
}
