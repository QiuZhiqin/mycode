#pragma once
#include <cstring>
#include <iostream>
using namespace std;
class student
{
    friend ostream &operator<<(ostream &os, const student &s);

private:
    char *m_name;
    int m_score;

public:
    void showinfo();
    student();
    student(const char *n, int s, int size);
    ~student();
};
student::student()
{
    cout << "no var dectected" << endl;
}
student::student(const char *n, int s, int size)
{
    m_name = new char[size + 1];
    strcpy(m_name, n);
    m_score = s;
}
student::~student()
{
    delete[] m_name;
}
ostream &operator<<(ostream &os, const student &s)
{
    os << "name: " << s.m_name << " ";
    os << "score: " << s.m_score;
    return os;
}