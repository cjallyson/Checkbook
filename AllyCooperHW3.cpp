/* **************************************************************************
** Author : Ally Cooper
** Question : HW 3
** Date Created : 3/21/25
************************************************************************** */

/* Person.h */
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    string birthdate;
public:
    Person(string n = "", string b = "") : name(n), birthdate(b) {}
    string getName() const { return name; }
    string getBirthdate() const { return birthdate; }
    void setName(string n) { name = n; }
    void setBirthdate(string b) { birthdate = b; }
};

#endif

/* Student.h */
#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"

class Student : public Person {
protected:
    int num_credits;
public:
    Student(string n = "", string b = "", int c = 0) : Person(n, b), num_credits(c) {}
    void setCredits(int c) { num_credits = c; }
    int getCredits() const { return num_credits; }
};

#endif

/* GradStudent.h */
#ifndef GRADSTUDENT_H
#define GRADSTUDENT_H
#include "Student.h"

class GradStudent : public Student {
public:
    GradStudent(string n = "", string b = "", int c = 0) : Student(n, b, c) {}
    bool canGraduate() const { return num_credits >= 30; }
};

#endif

/* UndergradStudent.h */
#ifndef UNDERGRADSTUDENT_H
#define UNDERGRADSTUDENT_H
#include "Student.h"

class UndergradStudent : public Student {
public:
    UndergradStudent(string n = "", string b = "", int c = 0) : Student(n, b, c) {}
    bool canGraduate() const { return num_credits >= 120; }
};

#endif

/* Polygon.h */
#ifndef POLYGON_H
#define POLYGON_H

class Polygon {
protected:
    int width, height;
public:
    Polygon(int w = 0, int h = 0) : width(w), height(h) {}
    virtual int getArea() const = 0;
    virtual void draw() const = 0;
};

#endif

/* Rectangle.h */
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Polygon.h"
#include <iostream>

class Rectangle : public Polygon {
public:
    Rectangle(int w = 0, int h = 0) : Polygon(w, h) {}
    int getArea() const override { return width * height; }
    void draw() const override {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

#endif

/* Triangle.h */
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Polygon.h"
#include <iostream>

class Triangle : public Polygon {
public:
    Triangle(int w = 0, int h = 0) : Polygon(w, h) {}
    int getArea() const override { return (width * height) / 2; }
    void draw() const override {
        int numStars = 1;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < numStars; j++) {
                cout << "*";
            }
            numStars += 2;
            cout << endl;
        }
    }
};

#endif

/* main.cpp */
#include <iostream>
#include "GradStudent.h"
#include "UndergradStudent.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace std;

int main() {
    // Test inheritance
    GradStudent grad("Alice", "01-01-1998", 30);
    UndergradStudent undergrad("Bob", "02-02-2000", 110);

    cout << grad.getName() << " can graduate: " << (grad.canGraduate() ? "Yes" : "No") << endl;
    cout << undergrad.getName() << " can graduate: " << (undergrad.canGraduate() ? "Yes" : "No") << endl;

    // Test virtual functions
    Rectangle rect(5, 3);
    Triangle tri(10, 5);

    cout << "Rectangle area: " << rect.getArea() << endl;
    rect.draw();

    cout << "Triangle area: " << tri.getArea() << endl;
    tri.draw();

    return 0;
}
