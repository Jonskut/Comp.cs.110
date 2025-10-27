#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_network(
    const std::map< std::string, std::vector<std::string> >& network,
    const std::string& id,
    int depth
)
{
    // Check if the node exists in the network
    if (network.find(id) == network.end())
    {
        std::cout << std::string(depth * 2, '.') << id << std::endl;
        return;
    }

    // Print the current node
    std::cout << std::string(depth * 2, '.') << id << std::endl;

    // Iterate over the children of the current node and recursively print them
    for (const auto& child : network.at(id))
    {
        print_network(network, child, depth + 1);
    }
}

int calculate_depth(
    const std::map<std::string, std::vector<std::string>>& network,
    const std::string& id
)
{
    if (network.find(id) == network.end())
    {
        return 0;
    }

    int max_depth = 0;
    const std::vector<std::string>& connections = network.find(id)->second;
    for (const auto& connection : connections)
    {
        int depth = calculate_depth(network, connection) + 1;
        if (depth > max_depth)
        {
            max_depth = depth;
        }
    }
    return max_depth;
}


int calculate_size(
    const std::map<std::string, std::vector<std::string>>& network,
    const std::string& id
)
{
    if (network.find(id) == network.end())
    {
        return 1;
    }

    int size = 1;
    const std::vector<std::string>& connections = network.find(id)->second;
    for (const auto& connection : connections)
    {
        // Add the size of each connected person recursively
        size += calculate_size(network, connection);
    }
    return size;
}

int main()
{
    // Datastructure for network
    std::map< std::string, std::vector<std::string> > network;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            network[id1].push_back(id2);


        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print_network(network, id, 0);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int size;
            size = calculate_size(network, id);
            // remove 1, because function calculates also person theirselves.
            std::cout << size - 1 << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int depth;
            depth = calculate_depth(network, id);
            // add 1, because function calculates dist to other nodes
            std::cout << depth + 1 << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
