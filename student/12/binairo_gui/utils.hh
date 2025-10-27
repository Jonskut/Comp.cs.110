/* Module: Utils
 * Module for different utilities needed in the program.
 *Written by:
 *  Name: Jonatan Tevaniemi
 *  Student number: 150176680
 *  Username: cnjote
 *  E-mail: jonatantevaniemi@tuni.fi
 * */

#ifndef UTILS_HH
#define UTILS_HH
#include <string>
#include <QImage>

namespace utils
{
    /*
     * Converts the given numeric string to the corresponding integer
     * (by calling stoi) and returns the integer.
     * If the given string is not numeric, returns zero.
     */
    unsigned int stoi_with_check(const std::string& str);

    /*
     * Scales image to input size.
     * Returns a QImage.
     */
    QImage scaleImage(QImage image, const QSize size);
}
#endif // UTILS_HH
