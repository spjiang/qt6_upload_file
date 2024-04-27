#ifndef VIDEOUPLOADDIALOG_H
#define VIDEOUPLOADDIALOG_H
#include "createprojectdialog.h"
#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>



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

    // 初始化数据
    void setToken(QString token);
    void setDirectoryPath(QString directoryPath);
    void setOutputFilePath(QString outputFilePath);

    bool uploadFileRequest(QString path, QString filename,int projectId);

public slots:
    void uploadFileEvent();
    void createProject();
    void refreshProject();

signals:
    void uploadFileSuccess(const QString &data);
    void uploadFileError(const QString &data);

private:
    Ui::VideoUploadDialog *ui;
    CreateProjectDialog* m_CreateProjectDialog;
    QString m_token;
    QString m_directoryPath;
    QString m_outputFilePath;
};
#endif // VIDEOUPLOADDIALOG_H
