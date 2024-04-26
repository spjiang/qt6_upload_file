#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

public slots:
    void createProjectRequest();
    void messageClose();

signals:
    void closeCreateProjectWindow();

private:
    QMessageBox* m_succQMessageBox;
    Ui::CreateProjectDialog *ui;
};

#endif // CREATEPROJECTDIALOG_H
