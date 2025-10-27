/* Education Center
 *
 * Description:
 *
 * This program reads a (semicolon delimited) .csv file containing
 * information about an education center's course data. The program first
 * asks for a file name and checks if it can be opened.
 *
 * The .csv file has to have four fields in a line separated by a semicolon:
 * <location>;<theme>;<course name>;<enrollments>.
 * Course theme and name can have whitespaces, location can't.
 * Enrollments has to be either an integer or the word "full" (no parentheses).
 *
 * The data is stored to a map containing the location of the course
 * and a custom Course struct that has information about the courses name,
 * theme and enrollments.
 *
 * After the data is stored in the map, the program starts an input loop
 * where the user can input commands.
 *
 * Available commands:
 *  - quit, quits program.
 *  - locations, prints all known locations in alphabetical order.
 *  - themes_in_location <location>, prints all themes in a location in.
 *    alphabetical order.
 *  - courses <location> <theme>, prints all courses in a location in a theme
 *    in alphabetical order.
 *  - available, prints all available (non-full) courses, including theme and
 *    location, in alphabetical order.
 *  - courses_in_theme <theme>, prints all known courses in a theme in
 *    alphabetical order
 *  - favorite_theme, prints out the theme with most total enrolled students.
 *
 * In this program, a course is assumed to have 50 people if it is full.
 *
 * This program checks for errors in user input. The command and possible
 * theme and location have to exist in the program or the .csv file.
 *
 * Written by
 * Name: Jonatan Tevaniemi
 * Student number: 150176680
 * Username: cnjote
 * E-Mail: jonatan.tevaniemi@tuni.fi
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Global constant, full course enrollments
const int MAX_ENROLLMENTS = 50;

struct Course
{
    string name;
    string theme;
    int enrollments;
};


// From exercise 6.1.2: splits a string into substrings with user defined
// delimiter
// Params:        s : string, to be split
//        delimiter : char, delimiter
// Return: split (sub)string
vector<string> split(const string& s, const char delimiter)
{
    vector<string> result;
    string token;
    istringstream iss(s);

    while (getline(iss, token, delimiter))
    {
        // Check if the token starts with a quote
        if (token.front() == '"')
        {
            // Append tokens until we find the closing quote
            string quoted_token = token;
            while (getline(iss, token, delimiter))
            {
                quoted_token += delimiter + token;
                if (token.back() == '"')
                {
                    break;
                }
            }
            // Remove quotes from the quoted substring
            quoted_token.erase(0, 1);
            quoted_token.pop_back();

            result.push_back(quoted_token);
        }
        else
        {
            result.push_back(token);
        }
    }
    return result;
}

// Checks if an element is in a vector
// Params: elementToCheck : string, to be checked
//                 vector : vector, to be checked against
// Return: bool, true if element is in vector
bool isElementInVector(const string& elementToCheck,
                       const vector<string>& vector)
{
    for(const auto& element : vector)
    {
        if(element == elementToCheck)
        {
            return true;
        }
    }
    return false;
}

// Checks if a theme exists in a map
// Params: courses : map, data structure for all courses
//           theme : theme to check
// Return: bool, true if the theme exists
bool checkIfThemeExists(const map<string, vector<Course>>& courses,
                        const string& theme)
{
    for (const auto& pair : courses) {
        const vector<Course>& coursesInLocation = pair.second;
        for (const auto& course : coursesInLocation) {
            if (course.theme == theme) {
                return true;
            }
        }
    }
    return false;
}

// Custom comparison function to sort courses by theme and then by name
// Params: a : Course, first of two to be compared
//         b : Course, second of two to be copmared
// Return: bool, true if a is smaller than b
bool compareCourses(const Course& a, const Course& b)
{
    if (a.theme == b.theme) {
        return a.name < b.name;
    }
    return a.theme < b.theme;
}


// Opens file and saves its contents to a map
// Params: courses : map, data structure for all courses
// Return: bool, true if successfully opened file
bool loadFile(map<string, vector<Course>>& courses)
{
    string fileName = "";

    cout << "Input file: ";
    getline(cin, fileName);

    ifstream csvFile(fileName);
    if(not csvFile)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    string line;
    while(getline(csvFile, line))
    {
        vector<string> fields = split(line, ';');
        if(fields.size() == 4)
        {
            string location = fields[0];
            string theme = fields[1];
            string name = fields[2];
            string enrollmentsAsString = fields[3];
            int enrollments;

            if(enrollmentsAsString == "full")
            {
                enrollments = MAX_ENROLLMENTS;
            }
            else
            {
                enrollments = stoi(enrollmentsAsString);
            }

            // Check if a course with the same location, theme, and name exists
            bool found = false;
            for (auto& course : courses[location])
            {
                if (course.name == name && course.theme == theme)
                {
                    // Update enrollments for the existing course
                    course.enrollments = enrollments;
                    found = true;
                    break;
                }
            }
            if (not found)
            {
                courses[location].push_back({name, theme, enrollments});
            }
        }
        else
        {
            cout << "Error: empty field" << endl;
            return false;
        }
    }
    csvFile.close();
    return true;
}

// Prints all known locations
// Params: courses : map, data structure for all courses
void printLocations(const map<string, vector<Course>>& courses)
{
    // Sort the locations alphabetically
    vector<string> locations;
    for (const auto& pair : courses)
    {
        locations.push_back(pair.first);
    }
    sort(locations.begin(), locations.end());

    // Print the sorted locations
    for (const auto& location : locations)
    {
        cout << location << endl;
    }
}

// Prints all themes of courses available in a location
// Params: courses  : map, data structure for all courses
//         location : location of courses
void printThemesInLocation(const map<string, vector<Course>>& courses,
                           const string& location)
{
    vector<string> themes;

    auto it = courses.find(location);
    if (it != courses.end())
    {
        // Key exists in the map
        const std::vector<Course>& coursesInLocation = it->second;

        for (const auto& course : coursesInLocation)
        {
            if (not isElementInVector(course.theme, themes))
            {
                themes.push_back(course.theme);
            }
        }
        // Sort alphabetically
        sort(themes.begin(), themes.end());
        for (auto& theme : themes)
        {
            cout << theme << endl;
        }
    }
    else
    {
        cout << "Error: unknown location" << std::endl;
    }
}

// Prints all courses and their enrollments
// of a given theme in a given location
// Params: courses  : map, data structure for all courses
//         location : location of courses
//         theme    : theme of courses.
void printCoursesInLocationTheme(const map<string, vector<Course>>& courses,
                                 const string& location,
                                 const string& theme)
{
    vector<pair<string, int>> coursesAndEnrollments;

    auto it = courses.find(location);

    if (courses.find(location) == courses.end())
    {
        cout << "Error: unknown location name" << endl;
    }
    else if (not checkIfThemeExists(courses, theme))
    {
        cout << "Error: unknown theme" << endl;
    }
    else if (it != courses.end())
    {
        // Key exists in the map
        const std::vector<Course>& coursesInLocation = it->second;

        for(const auto& course : coursesInLocation)
        {
            if (course.theme == theme)
            {
                coursesAndEnrollments.push_back(make_pair(course.name,
                                                          course.enrollments));
            }
        }
    }

    // Sort by course name
    sort(coursesAndEnrollments.begin(), coursesAndEnrollments.end());

    // Print courses and enrollments
    for (const auto& pair : coursesAndEnrollments)
    {
        if (pair.second < MAX_ENROLLMENTS)
        {
            cout << pair.first << " --- " << pair.second
                 << " enrollments" << endl;
        }
        else
        {
            cout << pair.first << " --- full" << endl;
        }
    }
}

// Prints all available (non-full) courses.
// Params: courses: map, data structure for all courses
void printAvailable(const map<string, vector<Course>>& courses)
{
    // Create a vector of all locations
    vector<string> locations;
    for (const auto& location : courses)
    {
        locations.push_back(location.first);
    }
    // Sort list of locations
    sort(locations.begin(), locations.end());

    // Print all available courses
    for (const auto& location : locations)
    {
        vector<Course> sortedCourses = courses.at(location);

        sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);
        for (const auto& course : sortedCourses)
        {
            if (course.enrollments < MAX_ENROLLMENTS)
            {
                cout << location << " : " << course.theme
                     << " : " << course.name << endl;
            }

        }
    }
}

// Prints all courses in a theme
// Params: courses: map, data structure for all courses
//          themes: string, theme whose courses are to be printed
void printCoursesInTheme(const map<string, vector<Course>>& courses,
                         const string& theme)
{
    vector<string> coursesInTheme;

    if (not checkIfThemeExists(courses, theme))
    {
        cout << "Error: unknown theme" << endl;
    }
    else
    {
        for (const auto& location : courses)
        {
            for (const auto& course : location.second)
            {
                if (course.theme == theme and not
                    isElementInVector(course.name, coursesInTheme))
                {
                    coursesInTheme.push_back(course.name);
                }
            }
        }
    }

    // Sort vector of courses in theme
    sort(coursesInTheme.begin(), coursesInTheme.end());

    // Print courses in theme
    for (const auto& courseName : coursesInTheme)
    {
        cout << courseName << endl;
    }
}

// Prints themes with the most enrolled students
// Params: courses: map, data structure for all courses
void printFavoriteThemes(const map<string, vector<Course>>& courses)
{
    // Initialize map for total enrollments for a theme
    map<string, int> totalEnrollments;
    vector<string> biggestCourses;

    for (const auto& location : courses)
    {
        for (const auto& course : location.second)
        {
            totalEnrollments[course.theme] += course.enrollments;
        }
    }

    // Iterate through all and print the biggest one(s)
    int maxValue = 0;
    for (const auto& pair : totalEnrollments)
    {
        if (pair.second > maxValue)
        {
            maxValue = pair.second;
            biggestCourses.clear();
            biggestCourses.push_back(pair.first);
        }
        else if (pair.second == maxValue)
        {
            biggestCourses.push_back(pair.first);
        }
    }

    // Print the biggest courses
    if (totalEnrollments.size() != 0)
    {
        cout << maxValue << " enrollments in themes" << endl;
        for (string& course : biggestCourses)
        {
            cout << "--- " << course << endl;
        }
    }
    else
    {
        cout << "No enrollments" << endl;
    }

}

// This function has the input loop and some error handling for the inputs
// Params: courses: map, data structure for all courses
void askInput(const map<string, vector<Course>>& courses)
{
    string input = "";
    vector<string> command;

    while (input != "quit")
    {
        cout << "> ";
        getline(cin, input);
        command = split(input, ' ');

        if (command.empty())
        {
            continue;
        }

        if (command[0] == "locations")
        {
            if (command.size() == 1)
            {
                printLocations(courses);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] == "themes_in_location")
        {
            if (command.size() == 2)
            {
                printThemesInLocation(courses, command[1]);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] == "courses")
        {
            if (command.size() == 3)
            {
                printCoursesInLocationTheme(courses, command[1], command[2]);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] == "available")
        {
            if (command.size() == 1)
            {
                printAvailable(courses);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] == "courses_in_theme")
        {
            if (command.size() == 2)
            {
                printCoursesInTheme(courses, command[1]);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] == "favorite_theme")
        {
            if (command.size() == 1)
            {
                printFavoriteThemes(courses);
            }
            else
            {
                cout << "Error: error in command " << command[0] << endl;
            }
        }
        else if (command[0] != "quit")
        {
            cout << "Error: Unknown command: " << command[0] << endl;
        }
    }
}


int main()
{
    // Data structure to be used to store course data
    map<string, vector<Course>> courses;

    // Try to load file to data structure
    if (not loadFile(courses))
    {
        return EXIT_FAILURE;
    }

    // Go to input loop
    askInput(courses);

    return EXIT_SUCCESS;
}
