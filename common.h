#ifndef COMMON_H
#define COMMON_H
#include <QString>

class Common
{
public:
    Common();
    bool static compressDirectory(const QString &directoryPath, const QString &outputFilePath);
    void static errDialog(const QString text);
    void static infoDialog(const QString text);
};

#endif // COMMON_H
