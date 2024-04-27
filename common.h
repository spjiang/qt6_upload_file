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
    QString static login();
    bool static uploadFile(QString path, QString filename,QString projectId);
};

#endif // COMMON_H
