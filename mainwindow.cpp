#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videouploaddialog.h"
#include "common.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 登录
    QString token = Common::login();
    if(token.isNull()){
        Common::errDialog("登录失败");
        return;
    }
    m_token = token;

    m_VideoUploadDialog = new VideoUploadDialog(this);
    // TODO 点击保存并上传
    // 目录压缩地址
    m_VideoUploadDialog->setDirectoryPath("D:/XNDD/workplace/video_upload_file/1");
    // 压缩后zip保存地址
    m_VideoUploadDialog->setOutputFilePath("D:/XNDD/compressDirectory/1");
    // 登录TOKEN
    m_VideoUploadDialog->setToken(token);

    ui->setupUi(this);

    connect(ui->filesavebutton,&QPushButton::clicked,this,&MainWindow::savefileWindow);

    connect(m_VideoUploadDialog,&VideoUploadDialog::uploadClick,this, &MainWindow::videoUploadFileClicek);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::savefileWindow(){
    m_VideoUploadDialog->show();
}

void MainWindow::showMessage(const QString &data){
    statusbarList.append(data);
    ui->statusbar->showMessage(statusbarList.join(";"), 3000); // 显示消息3秒
}

void MainWindow::videoUploadStatusbar(const QString filename,const QString message){
    for (const QString& tip : statusbarList) {
        // a.zip:50%
        QStringList tipList =  tip.split(":");
        if(tipList.size() == 2 && tipList[0] == filename){
            //刪除旧数据
            statusbarList.removeAll(tip);
        }
    }
    // 新增新数据
    QString newTip = filename+":"+message;
    statusbarList.append(newTip);
    ui->statusbar->showMessage(statusbarList.join(";"), 1000); // 显示消息3秒
}


void MainWindow::videoUploadFileClicek(const QString &directoryPath, const QString &outputFilePath, const QString &filename, const int &projectId){
    qDebug()<<"directoryPath:"<<directoryPath<<",outputFilePath:"<<outputFilePath<<",filename:"<<filename<<",projectId:"<<projectId;
    // zip压缩文件名
    QString filenameZip = filename+".zip";

    // 文件压缩
    qDebug()<< "视频文件压缩目录:" << directoryPath;
    qDebug()<< "视频文件压缩保存目录:" << outputFilePath;
    QString outputFilePathName = outputFilePath+"/"+filename+".zip";
    qDebug()<< "视频文件压缩后zip文件:" << outputFilePathName;
    bool compressDirectoryStatus = Common::compressDirectory(directoryPath, outputFilePathName);
    if(!compressDirectoryStatus){
        qDebug()<< "视频文件文件压缩结果失败："<<outputFilePathName;
        videoUploadStatusbar(filenameZip,"视频文件文件压缩结果失败");
        return;
    }
    qDebug()<< "视频文件文件压缩结果成功："<<outputFilePathName;

    // 创建一个multipart/form-data请求
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 添加文本参数 name
    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    namePart.setBody(filename.toUtf8());
    multiPart->append(namePart);

    // 添加整数参数 projectId
    QHttpPart projectIdPart;
    projectIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"projectId\""));
    projectIdPart.setBody(QString::number(projectId).toUtf8());
    multiPart->append(projectIdPart);


    // 添加文件
    QFile *file = new QFile(outputFilePathName);
    if (!file->exists()) {
        qDebug()<<"视频保存上传:"<<filenameZip<<"文件读取异常:"<<outputFilePathName;
        videoUploadStatusbar(filenameZip,"文件读取异常");
        file->close();
        return;
    }
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug()<<"视频保存上传:"<<filenameZip<< "Failed to open file";
        videoUploadStatusbar(filenameZip,"Failed to open file");
        file->close();
        return;
    }

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + QFileInfo(*file).fileName() + "\""));
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // 设置文件对象的父对象，以便其生命周期由multiPart管理
    multiPart->append(filePart);


    //发送请求
    QNetworkRequest request;
    QString fullRequest = "http://123.249.67.68:8998/file/upload/video";

    request.setUrl(QUrl(fullRequest));
    request.setRawHeader("Source", "app");
    request.setRawHeader("Authorization", m_token.toUtf8());
    qDebug()<<"视频保存上传:"<<filenameZip<< "uploadFile Authorization:"<<m_token.toUtf8();
    // 查看请求头
    qDebug()<<"视频保存上传:"<<filenameZip<<"查看请求头:"<<request.rawHeaderList();


    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, multiPart);

    multiPart->setParent(reply); // 设置multiPart的父对象为reply，以便其生命周期由reply管理

    // 监听上传进度
    QObject::connect(reply, &QNetworkReply::uploadProgress, [&](qint64 bytesSent, qint64 bytesTotal){
        qDebug()<<"视频保存上传:"<<filenameZip<<"Upload progress:" << bytesSent << "of" << bytesTotal;

        if (bytesTotal == 0) {
            return;
        }
        qint64 result = bytesSent/bytesTotal;
        qint64 roundedResult = qRound(static_cast<double>(result));
        qint64 percentage = roundedResult*100;
        QString percentageTip = QString::number(percentage);
        videoUploadStatusbar(filenameZip,percentageTip);
        return;
    });

    // 处理响应
    // 开启时间循环，直到请求完成
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"视频保存上传:"<<filenameZip<<"请求连接超时";
        qDebug()<< reply->error();
        // 清理资源
        file->close();
        reply->deleteLater();
        return;
    }

    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<"状态码："<<statusCode.toInt();
    if (statusCode.isValid()) {
        if (statusCode.toInt() != 200) {
            // 请求失败
            qDebug()<<"视频保存上传:"<<filenameZip<<"接口请求返回异常";
            // 清理资源
            file->close();
            reply->deleteLater();
            return;
        }
    }

    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug()<<"视频保存上传:"<<filenameZip<<"json_error.error:"<<json_error.error<<replyData;
        // 清理资源
        file->close();
        reply->deleteLater();
        return;
    }

    QJsonObject rootObj = jsonDoc.object();
    qDebug()<<rootObj;
    QJsonValue code = rootObj.value("code");
    if (code == 200) {
        qDebug()<<"视频保存上传:"<< filenameZip<< "成功";
        // 清理资源
        file->close();
        reply->deleteLater();
        return;
    }
    file->close();
    reply->deleteLater();
    return;
}


