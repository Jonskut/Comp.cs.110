#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    string inputFile;
    cout << "Input file: ";
    getline(cin, inputFile);

    ifstream Scores(inputFile);
    if (not Scores)
    {
        cout << "Error! The file " << inputFile << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        map<string, int> finalScores;
        string row;
        while (getline(Scores, row))
        {
            string name = "";
            int score = 0;
            size_t pos = row.find(':');
            if (pos != string::npos)
            {
                name = row.substr(0, pos);
                score = stoi(row.substr(pos + 1));
            }
            if (finalScores.find(name) != finalScores.end())
            {
                finalScores.at(name) += score;
            }
            else
            {
                finalScores[name] = score;
            }

        }
        cout << "Final scores:" << endl;
        for (const auto& values : finalScores)
        {
            cout << values.first << ": ";
            cout << values.second << endl;
        }
    }

    return 0;
}
