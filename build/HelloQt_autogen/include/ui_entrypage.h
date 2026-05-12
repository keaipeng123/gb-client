/********************************************************************************
** Form generated from reading UI file 'entrypage.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTRYPAGE_H
#define UI_ENTRYPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntryPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *hintLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ipEdit;
    QLabel *label_2;
    QLineEdit *portEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *confirmButton;

    void setupUi(QWidget *EntryPage)
    {
        if (EntryPage->objectName().isEmpty())
            EntryPage->setObjectName("EntryPage");
        EntryPage->resize(520, 320);
        verticalLayout = new QVBoxLayout(EntryPage);
        verticalLayout->setSpacing(18);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(36, 32, 36, 32);
        titleLabel = new QLabel(EntryPage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);

        verticalLayout->addWidget(titleLabel);

        hintLabel = new QLabel(EntryPage);
        hintLabel->setObjectName("hintLabel");
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(16);
        formLayout->setVerticalSpacing(14);
        label = new QLabel(EntryPage);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        ipEdit = new QLineEdit(EntryPage);
        ipEdit->setObjectName("ipEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, ipEdit);

        label_2 = new QLabel(EntryPage);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        portEdit = new QLineEdit(EntryPage);
        portEdit->setObjectName("portEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, portEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(EntryPage);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setMinimumSize(QSize(100, 36));

        horizontalLayout->addWidget(cancelButton);

        confirmButton = new QPushButton(EntryPage);
        confirmButton->setObjectName("confirmButton");
        confirmButton->setMinimumSize(QSize(100, 36));

        horizontalLayout->addWidget(confirmButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(EntryPage);

        QMetaObject::connectSlotsByName(EntryPage);
    } // setupUi

    void retranslateUi(QWidget *EntryPage)
    {
        EntryPage->setWindowTitle(QCoreApplication::translate("EntryPage", "\345\205\245\345\217\243", nullptr));
        titleLabel->setText(QCoreApplication::translate("EntryPage", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        hintLabel->setText(QCoreApplication::translate("EntryPage", "\350\257\267\350\276\223\345\205\245\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\345\222\214\347\253\257\345\217\243\357\274\214\347\204\266\345\220\216\350\277\233\345\205\245\347\233\256\345\275\225\351\241\265\351\235\242\343\200\202", nullptr));
        label->setText(QCoreApplication::translate("EntryPage", "\346\234\215\345\212\241\345\231\250 IP", nullptr));
        ipEdit->setPlaceholderText(QCoreApplication::translate("EntryPage", "\344\276\213\345\246\202 192.168.1.10", nullptr));
        label_2->setText(QCoreApplication::translate("EntryPage", "\347\253\257\345\217\243", nullptr));
        portEdit->setPlaceholderText(QCoreApplication::translate("EntryPage", "\344\276\213\345\246\202 8554", nullptr));
        cancelButton->setText(QCoreApplication::translate("EntryPage", "\345\217\226\346\266\210", nullptr));
        confirmButton->setText(QCoreApplication::translate("EntryPage", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EntryPage: public Ui_EntryPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTRYPAGE_H
