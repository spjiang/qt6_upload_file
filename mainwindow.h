#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videouploaddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showMessage(const QString &data);
    void videoUploadStatusbar(const QString filename,const QString message);

public slots:
    void savefileWindow();
    void videoUploadFileClicek(const QString &directoryPath,const QString &outputFilePath, const QString &filename, const int &projectId);

private:
    Ui::MainWindow *ui;
    QStringList statusbarList;
    VideoUploadDialog* m_VideoUploadDialog;
    QString m_token;
};

#endif // MAINWINDOW_H
