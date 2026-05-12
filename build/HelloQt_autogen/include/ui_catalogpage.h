/********************************************************************************
** Form generated from reading UI file 'catalogpage.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATALOGPAGE_H
#define UI_CATALOGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CatalogPage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *pageTitleLabel;
    QSpacerItem *headerSpacer;
    QHBoxLayout *contentLayout;
    QFrame *treePanel;
    QVBoxLayout *treePanelLayout;
    QLabel *treeTitleLabel;
    QTreeWidget *treeWidget;
    QFrame *videoPanel;
    QVBoxLayout *videoPanelLayout;
    QLabel *videoTitleLabel;
    QLabel *videoLabel;

    void setupUi(QWidget *CatalogPage)
    {
        if (CatalogPage->objectName().isEmpty())
            CatalogPage->setObjectName("CatalogPage");
        CatalogPage->resize(980, 620);
        verticalLayout = new QVBoxLayout(CatalogPage);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        pageTitleLabel = new QLabel(CatalogPage);
        pageTitleLabel->setObjectName("pageTitleLabel");
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        pageTitleLabel->setFont(font);

        headerLayout->addWidget(pageTitleLabel);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);


        verticalLayout->addLayout(headerLayout);

        contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(16);
        contentLayout->setObjectName("contentLayout");
        treePanel = new QFrame(CatalogPage);
        treePanel->setObjectName("treePanel");
        treePanel->setMinimumSize(QSize(260, 0));
        treePanel->setFrameShape(QFrame::Shape::StyledPanel);
        treePanel->setFrameShadow(QFrame::Shadow::Raised);
        treePanelLayout = new QVBoxLayout(treePanel);
        treePanelLayout->setObjectName("treePanelLayout");
        treePanelLayout->setContentsMargins(12, 12, 12, 12);
        treeTitleLabel = new QLabel(treePanel);
        treeTitleLabel->setObjectName("treeTitleLabel");

        treePanelLayout->addWidget(treeTitleLabel);

        treeWidget = new QTreeWidget(treePanel);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setAlternatingRowColors(true);

        treePanelLayout->addWidget(treeWidget);


        contentLayout->addWidget(treePanel);

        videoPanel = new QFrame(CatalogPage);
        videoPanel->setObjectName("videoPanel");
        videoPanel->setFrameShape(QFrame::Shape::StyledPanel);
        videoPanel->setFrameShadow(QFrame::Shadow::Raised);
        videoPanelLayout = new QVBoxLayout(videoPanel);
        videoPanelLayout->setObjectName("videoPanelLayout");
        videoPanelLayout->setContentsMargins(12, 12, 12, 12);
        videoTitleLabel = new QLabel(videoPanel);
        videoTitleLabel->setObjectName("videoTitleLabel");

        videoPanelLayout->addWidget(videoTitleLabel);

        videoLabel = new QLabel(videoPanel);
        videoLabel->setObjectName("videoLabel");
        videoLabel->setMinimumSize(QSize(640, 360));
        videoLabel->setFrameShape(QFrame::Shape::Box);
        videoLabel->setAlignment(Qt::AlignCenter);
        videoLabel->setWordWrap(true);

        videoPanelLayout->addWidget(videoLabel);


        contentLayout->addWidget(videoPanel);


        verticalLayout->addLayout(contentLayout);


        retranslateUi(CatalogPage);

        QMetaObject::connectSlotsByName(CatalogPage);
    } // setupUi

    void retranslateUi(QWidget *CatalogPage)
    {
        CatalogPage->setWindowTitle(QCoreApplication::translate("CatalogPage", "\347\233\256\345\275\225\351\241\265", nullptr));
        pageTitleLabel->setText(QCoreApplication::translate("CatalogPage", "\347\233\256\345\275\225\344\270\216\346\222\255\346\224\276\345\214\272\345\237\237", nullptr));
        treeTitleLabel->setText(QCoreApplication::translate("CatalogPage", "\345\252\222\344\275\223\347\233\256\345\275\225", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("CatalogPage", "\347\233\256\345\275\225", nullptr));
        videoTitleLabel->setText(QCoreApplication::translate("CatalogPage", "\346\222\255\346\224\276\345\214\272\345\237\237", nullptr));
        videoLabel->setText(QCoreApplication::translate("CatalogPage", "\347\255\211\345\276\205\346\222\255\346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CatalogPage: public Ui_CatalogPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATALOGPAGE_H
