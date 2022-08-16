// course data.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>


#include "CSVparser.hpp"

using namespace std;

// define a structure to hold course information
struct Course {
    string courseNumber; // unique identifier
    string courseName;
    string prerequisites;

};

Course getCourse() {
    Course course;

    cout << "Enter courseNumber: ";
    cin.ignore();
    getline(cin, course.courseNumber);

    cout << "Enter courseName: ";
    getline(cin, course.courseName);

    cout << "Enter prerequisites: ";
    cin >> course.prerequisites;

    return course;
}

vector<Course> loadCourses(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of Courses.
    vector<Course> courses;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseNumber = file[i][0];
            course.courseName = file[i][1];
            course.prerequisites = file[i][2];

            // push this course to the end
            courses.push_back(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}

void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseName << endl;

    return;
}

void selectionSort(vector<Course>& courses) {
    //define min as int (index of the current minimum course)
    int min;


    // check size of courses vector
    // set size_t platform-neutral result equal to course.size()
    size_t size = courses.size();

    // pos is the position within courses that divides sorted/unsorted
    // for size_t pos = 0 and less than size -1 
    for (size_t pos = 0; pos < size - 1; ++pos) {

        // set min = pos
        min = pos;
        // loop over remaining elements to the right of position
        for (int i = pos + 1; i < size; ++i) {
            // if this element's courseNumber is less than minimum courseNumber
            if (courses[i].courseNumber < courses[min].courseNumber) {
                // this element becomes the minimum
                min = i;
            }
        }
        // swap the current minimum with smaller one found
        swap(courses[pos], courses[min]);

    }
}
void displayPrerequisites(Course course) {
    cout << "Prerequisites: " << course.prerequisites << endl;
    cout << endl; 
}

void printCourse(vector<Course>& courses) {
    string courseEnter;
    cin >> courseEnter;

    // remove case sensitivity
    for (int i = 0; i < courseEnter.size(); i++) {
        int c = courseEnter[i];
        if (islower(c))
            courseEnter[i] = toupper(c);
    }
    int m = 0;
    for (int i = 0; i < courses.size(); ++i) {
        // if course is found print course with Prerequisites
        if (courses[i].courseNumber == courseEnter) {
            m = 1;
            displayCourse(courses[i]);
            displayPrerequisites(courses[i]);
            break;
        }
    }  
    // if not found print error message
    if (m == 0) {
        cout << "Course not found" << endl;
    }
}




int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv";
    }

    // Define a vector to hold all the courses
    vector<Course> courses;

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl << "Menu:" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Complete the method call to load the courses
            courses = loadCourses(csvPath);

            cout << courses.size() << " courses read" << endl;
            break;

        case 2:
            cout << "Here is a sample schedule: " << endl;
            cout << endl;

            // Complete the method call to selectionSort the courses
            selectionSort(courses);

            // Loop and display the courses read
            for (int i = 0; i < courses.size(); ++i) {
                displayCourse(courses[i]);
            }

            cout << endl;

            break;

        case 3:
            cout << "What course do you want to know about? ";
            // Complete the method call to printCourse the courses
            printCourse(courses);

            break;

        default:

            cout << choice << " is not a valid option." << endl << endl;

        }
    }

    cout << "Thank you for using the course planner! Good bye." << endl;

    return 0; 
}

