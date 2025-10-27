#include <iostream>
#include <string>

using namespace std;

/*
 * Encrypts the string
 * Params:
 *      key - Encryption key
 *      text - Text to be encrypted
 * Return:
 *      result, encrypted text
 */
string encrypt(string key, string text)
{
    string result = "";

    // Replace every character in the text with
    // character dicatated by key
    for ( char ch : text) {
        ch = key[ch - 'a'];
        result += ch;
    }

    return result;
}


/*
 * Checks for incorrect letters in encryption key
 * Params:
 *      key - Encryption key
 * Return:
 *      true if there are incorrect letters
 */
bool incorrectLetters(string key)
{
    // check if ASCII values of each character is a-z
    for ( char ch : key ) {
        if (ch < 'a' or ch > 'z') {
            return true;
        }
    }

    return false;
}


/*
 * Checks that all letters a-z are in key
 * Params:
 *      key - Encryption key
 * Return:
 *      true if it doesn't pass
 */
bool notAllLetters(string key)
{
    // compare every letter with each other
    for (size_t i = 0; i < key.size(); ++i) {
        for (size_t j = 0; j < key.size(); ++j) {
            if ( i != j and key[i] == key[j] ) {
                return true;
            }
        }
    }

    return false;
}


/*
 * Checks for errors in encryption key
 * Params:
 *      key - Encryption key
 * Return:
 *      False if check is OK.
 */
bool errorCheck(string key)
{

    if ( key.length() != 26 ) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return true;
    }
    else if ( incorrectLetters(key) ) {
        cout << "Error! The encryption key must contain only lower case characters." <<
                endl;
        return true;
    }
    else if ( notAllLetters(key) ) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return true;
    }
    else {
        return false;
    }
}


int main()
{
    cout << "Enter the encryption key: ";
    string key; cin >> key;

    if ( errorCheck(key) ) {
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
            string text; cin >> text;
    if (!( incorrectLetters(text) ) ) {
        string encryptedMessage = encrypt(key, text);
        cout << "Encrypted text: " << encryptedMessage << endl;
    }
    else {
        cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
