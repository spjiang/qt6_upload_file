#ifndef VIDEOUPLOADDIALOG_H
#define VIDEOUPLOADDIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include "createprojectdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VideoUploadDialog;
}
QT_END_NAMESPACE

class VideoUploadDialog : public QDialog
{
    Q_OBJECT

public:
    VideoUploadDialog(QWidget *parent = nullptr);
    ~VideoUploadDialog();
    QJsonArray getProjectList();
    QString login(QString username,QString password);
    void setDirectoryPath(QString directoryPath);
    void setOutputFilePath(QString outputFilePath);
    void setToken(QString token);
    QString getToken();


public slots:
    void upload();
    void createProject();
    void refreshProject();

private:
    Ui::VideoUploadDialog *ui;
    QString m_directoryPath;
    QString m_outputFilePath;
    QString m_token;
    CreateProjectDialog* m_CreateProjectDialog;
};
#endif // VIDEOUPLOADDIALOG_H
