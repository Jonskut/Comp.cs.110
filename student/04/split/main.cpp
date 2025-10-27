#include <iostream>
#include <string>
#include <vector>


std::vector< std::string > split(std::string line, char separator, bool ignore_empty = false)
{

    // initialize vector
    std::vector< std::string > vector;

    // initialize part that will be element of vector
    std::string part;

    // find separator
    std::size_t line_size = line.size();

    for ( std::size_t i = 0; i < line_size; ++i )
    {
        if (separator == line[i])
        {
            // separator is whitespace, treat consecutive whitespaces as one separator
            if (!part.empty() or !ignore_empty)
            {
            vector.push_back(part);
            part = "";
            }
        }
        else if ( line[i] == separator )
        {
            vector.push_back(part);
            part = "";
        }
        else if ( ignore_empty )
        {
            if ( line[i] != separator )
            {
                part += line[i];
            }
        }
        else if ( !ignore_empty )
        {
            part += line[i];
        }
    }
    vector.push_back(part);

    return vector;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
