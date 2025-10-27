#include "utils.hh"

unsigned int utils::stoi_with_check(const std::string &str)
{
    bool is_numeric = true;
    if(str == "")
    {
        return 0;
    }
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

QImage utils::scaleImage(QImage image, const QSize size)
{
    QImage scaledImage = image.scaled(size, Qt::KeepAspectRatio);
    return scaledImage;
}
