#include "common.h"
#include <QtCore/qobject.h>
#include <QDebug>
#include <quazip/JlCompress.h>
#include<QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>

Common::Common() {}

bool Common::compressDirectory(const QString &directoryPath, const QString &outputFilePath) {
    return JlCompress::compressDir(outputFilePath, directoryPath);
}
void Common::errDialog(const QString text){
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox :: Critical);
    messageBox.setText(text);
    messageBox.setWindowTitle("警告");
    messageBox.setStyleSheet("QLabel{ color: red; }");
    messageBox.exec();
}

void Common::infoDialog(const QString text){
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox :: Information);
    messageBox.setText(text);
    messageBox.setWindowTitle("消息");
    messageBox.setStyleSheet("QLabel{ color: green; }");
    messageBox.exec();
}

/**
 * 模拟登录
 *
 * @brief VideoUploadDialog::login
 * @return
 */
QString Common::login(){
    return "111";
    QString username = "admin";
    QString password = "admin@2024";
    QNetworkRequest request;
    QString fullRequest = "http://123.249.67.68:8998/user/login";
    request.setUrl(QUrl(fullRequest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//因为QT和java的请求头不一致
    request.setRawHeader(QByteArray("Source"), "app");//这里是设置非标准的请求头
    // 查看请求头
    qDebug()<<request.rawHeaderList();
    //传入josn
    QJsonObject object;
    object.insert("username",username);
    object.insert("password",password);
    QJsonDocument document;
    document.setObject( object );
    QByteArray array = document.toJson( QJsonDocument::Compact );
    qDebug()<<object;
    //发送请求
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request,array);
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"请求连接超时";
        qDebug()<< reply->error();
        return NULL;
    }
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<"状态码："<<statusCode.toInt();
    if (statusCode.isValid()) {
        if (statusCode.toInt() >= 200 && statusCode.toInt() < 300) {
            // 请求成功
        } else {
            // 请求失败
            qDebug()<<"接口请求返回异常";
            return NULL;
        }
    }

    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug()<<json_error.error<<replyData;
        return NULL;
    }
    QJsonObject rootObj = jsonDoc.object();
    qDebug()<<rootObj;
    QJsonValue code = rootObj.value("code");//返回的代码,因为是double类型的所以不能转换成QString
    if (code == 200) {
        qDebug() << "登录成功";
        QJsonObject dataObject = rootObj.value("data").toObject();
        //TODO token保存
        QString token = dataObject.value("token").toString();
        return token;
    }
    return NULL;
}


