/*
 * THIS FUCKING PROGRAM DOESN'T NEED TO COUNT THE WORDS BECAUSE THE FUCKING ASSIGNMENT
 * SAYS THAT IT ONLY NEEDS TO COUNT THE AMOUNT OF LINES IT'S ON: WHY???
 * I WASTED SO LONG ON THAT
 */

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main()
{
    string inputFile;
    cout << "Input file: ";
    getline(cin, inputFile);

    ifstream text(inputFile);
    if (not text)
    {
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        map<string, pair<int, set<int>>> wordData;

        string row;
        int rowNumber = 0;
        while (getline(text, row))
        {
            ++rowNumber;

            stringstream rowStream(row);
            string word;
            while (rowStream >> word)
            {
                if (wordData.find(word) != wordData.end())
                {
                    wordData.at(word).first += 1;
                    wordData.at(word).second.insert(rowNumber);
                }
                else
                {
                    wordData[word].first = 1;
                    wordData.at(word).second.insert(rowNumber);
                }
            }
        }


        for (const auto& values : wordData)
        {
            cout << values.first << " " << values.second.second.size() << ": ";
            bool firstElement = true;
            for (auto element : values.second.second)
            {
                if (not firstElement)
                {
                    cout << ", ";
                }
                cout << element;
                firstElement = false;
            }
            cout << endl;
        }
    }

    return 0;
}
