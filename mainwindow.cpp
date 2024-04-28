#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videouploaddialog.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    // ui->statusbar->showMessage("Completed!", 3000); // 显示消息3秒
    // 登录
    QString token = Common::login();
    if(token.isNull()){
        Common::errDialog("登录失败");
        return;
    }

    m_VideoUploadDialog = new VideoUploadDialog(this);
    // TODO 点击保存并上传
    // 目录压缩地址
    m_VideoUploadDialog->setDirectoryPath("D:/XNDD/workplace/video_upload_file/1");
    // 压缩后zip保存地址
    m_VideoUploadDialog->setOutputFilePath("D:/XNDD/compressDirectory/1");
    // 登录TOKEN
    m_VideoUploadDialog->setToken(token);

    ui->setupUi(this);

    connect(ui->filesavebutton,&QPushButton::clicked,this,&MainWindow::savefile);

    connect(ui->filesavebutton,&QPushButton::clicked,this,&MainWindow::savefile);

    connect(m_VideoUploadDialog,&VideoUploadDialog::uploadFileSuccess,this, &MainWindow::uploadFileSuccess);

    connect(m_VideoUploadDialog,&VideoUploadDialog::uploadFileError,this, &MainWindow::uploadFileError);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::savefile(){
    m_VideoUploadDialog->show();
}

void MainWindow:: uploadFileSuccess(const QString &data){
    statusbarList.append(data);
    ui->statusbar->showMessage(statusbarList.join(";"), 3000); // 显示消息3秒
}

void MainWindow:: uploadFileError(const QString &data){
    statusbarList.append(data);
    ui->statusbar->showMessage(statusbarList.join(";"), 3000); // 显示消息3秒
}
