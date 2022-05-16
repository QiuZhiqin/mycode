#pragma once
#include <iostream>
using namespace std;
class student
{
private:
    string name;
    int score;

public:
    void showinfo();
    student();
    student(string n, int s);
};
void student::showinfo()
{
    cout << this->score << endl;
    cout << this->name << endl;
}
student::student()
{
    cout << "no var dectected" << endl;
}
student::student(string n, int s)
{
    name = n;
    score = s;
}