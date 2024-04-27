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


public slots:
    void savefile();
    void uploadFileSuccess(const QString &data);
    void uploadFileError(const QString &data);

private:
    Ui::MainWindow *ui;
    QStringList statusbarList;
    VideoUploadDialog* m_VideoUploadDialog;
};

#endif // MAINWINDOW_H
