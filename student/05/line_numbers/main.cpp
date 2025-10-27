#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string inputFile;
    string outputFile;
    cout << "Input file: ";
    cin >> inputFile;
    cout << "Output file: ";
    cin >> outputFile;

    ifstream inputObject(inputFile);
    if (not inputObject)
    {
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        ofstream outputObject(outputFile);
        int lineNumber = 0;
        string row;
        while (getline(inputObject, row))
        {
            ++lineNumber;
            outputObject << lineNumber << " " << row << endl;
        }
        outputObject.close();
    }
    inputObject.close();

    return 0;
}
