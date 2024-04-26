/********************************************************************************
** Form generated from reading UI file 'createprojectdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPROJECTDIALOG_H
#define UI_CREATEPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateProjectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *project_name;
    QHBoxLayout *horizontalLayout_7;
    QDialogButtonBox *okcancelButtonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CreateProjectDialog)
    {
        if (CreateProjectDialog->objectName().isEmpty())
            CreateProjectDialog->setObjectName("CreateProjectDialog");
        CreateProjectDialog->resize(322, 200);
        CreateProjectDialog->setStyleSheet(QString::fromUtf8("background-color: black"));
        verticalLayout = new QVBoxLayout(CreateProjectDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, -1, 0, 10);
        label = new QLabel(CreateProjectDialog);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:white"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(CreateProjectDialog);
        closeButton->setObjectName("closeButton");
        closeButton->setBaseSize(QSize(0, 0));
        closeButton->setFont(font);
        closeButton->setStyleSheet(QString::fromUtf8("color:white"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(20, -1, -1, -1);
        label_3 = new QLabel(CreateProjectDialog);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color:green"));

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(20, -1, -1, -1);
        project_name = new QLineEdit(CreateProjectDialog);
        project_name->setObjectName("project_name");
        project_name->setStyleSheet(QString::fromUtf8("color:white"));

        verticalLayout_3->addWidget(project_name);


        verticalLayout->addLayout(verticalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        okcancelButtonBox = new QDialogButtonBox(CreateProjectDialog);
        okcancelButtonBox->setObjectName("okcancelButtonBox");
        okcancelButtonBox->setStyleSheet(QString::fromUtf8("color:green"));
        okcancelButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        okcancelButtonBox->setCenterButtons(true);

        horizontalLayout_7->addWidget(okcancelButtonBox);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CreateProjectDialog);
        QObject::connect(okcancelButtonBox, &QDialogButtonBox::rejected, CreateProjectDialog, qOverload<>(&QDialog::close));
        QObject::connect(closeButton, &QPushButton::clicked, CreateProjectDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(CreateProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateProjectDialog)
    {
        CreateProjectDialog->setWindowTitle(QString());
        label->setText(QCoreApplication::translate("CreateProjectDialog", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        closeButton->setText(QCoreApplication::translate("CreateProjectDialog", "X", nullptr));
        label_3->setText(QCoreApplication::translate("CreateProjectDialog", "\351\241\271\347\233\256\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateProjectDialog: public Ui_CreateProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPROJECTDIALOG_H
