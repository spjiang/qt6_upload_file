/********************************************************************************
** Form generated from reading UI file 'videouploaddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOUPLOADDIALOG_H
#define UI_VIDEOUPLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VideoUploadDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *project_list;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *createProjectPushButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *video_rename;
    QHBoxLayout *horizontalLayout_7;
    QDialogButtonBox *okcancelButtonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *VideoUploadDialog)
    {
        if (VideoUploadDialog->objectName().isEmpty())
            VideoUploadDialog->setObjectName("VideoUploadDialog");
        VideoUploadDialog->resize(433, 319);
        VideoUploadDialog->setStyleSheet(QString::fromUtf8("background-color: black"));
        verticalLayout = new QVBoxLayout(VideoUploadDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, -1, 0, 10);
        label = new QLabel(VideoUploadDialog);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:white"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        closeButton = new QPushButton(VideoUploadDialog);
        closeButton->setObjectName("closeButton");
        closeButton->setBaseSize(QSize(0, 0));
        closeButton->setFont(font);
        closeButton->setStyleSheet(QString::fromUtf8("color:white"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(20, -1, -1, -1);
        label_2 = new QLabel(VideoUploadDialog);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color:green"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(20, -1, -1, 10);
        project_list = new QComboBox(VideoUploadDialog);
        project_list->setObjectName("project_list");
        project_list->setMinimumSize(QSize(0, 21));
        project_list->setStyleSheet(QString::fromUtf8("color:green"));
        project_list->setIconSize(QSize(160, 160));
        project_list->setFrame(true);

        horizontalLayout_3->addWidget(project_list);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(20, -1, -1, 10);
        createProjectPushButton = new QPushButton(VideoUploadDialog);
        createProjectPushButton->setObjectName("createProjectPushButton");
        createProjectPushButton->setStyleSheet(QString::fromUtf8("color:green"));

        horizontalLayout_5->addWidget(createProjectPushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(20, -1, -1, -1);
        label_3 = new QLabel(VideoUploadDialog);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color:green"));

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(20, -1, -1, -1);
        video_rename = new QLineEdit(VideoUploadDialog);
        video_rename->setObjectName("video_rename");

        verticalLayout_3->addWidget(video_rename);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        okcancelButtonBox = new QDialogButtonBox(VideoUploadDialog);
        okcancelButtonBox->setObjectName("okcancelButtonBox");
        okcancelButtonBox->setStyleSheet(QString::fromUtf8("color:green"));
        okcancelButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        okcancelButtonBox->setCenterButtons(true);

        horizontalLayout_7->addWidget(okcancelButtonBox);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(VideoUploadDialog);
        QObject::connect(closeButton, &QPushButton::clicked, VideoUploadDialog, qOverload<>(&QDialog::close));
        QObject::connect(okcancelButtonBox, &QDialogButtonBox::rejected, VideoUploadDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(VideoUploadDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoUploadDialog)
    {
        VideoUploadDialog->setWindowTitle(QString());
        label->setText(QCoreApplication::translate("VideoUploadDialog", "\344\277\235\345\255\230\345\271\266\344\270\212\344\274\240\345\275\261\347\211\207", nullptr));
        closeButton->setText(QCoreApplication::translate("VideoUploadDialog", "X", nullptr));
        label_2->setText(QCoreApplication::translate("VideoUploadDialog", "\351\200\211\346\213\251\346\211\200\345\261\236\351\241\271\347\233\256", nullptr));
        createProjectPushButton->setText(QCoreApplication::translate("VideoUploadDialog", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        label_3->setText(QCoreApplication::translate("VideoUploadDialog", "\345\217\214\347\233\256\345\275\261\347\211\207\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoUploadDialog: public Ui_VideoUploadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOUPLOADDIALOG_H
