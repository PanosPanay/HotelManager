/********************************************************************************
** Form generated from reading UI file 'Manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManagerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QLineEdit *lineEditUserName;
    QLineEdit *lineEditPassWord;
    QPushButton *BtnLogIn;
    QWidget *page2;
    QComboBox *comboBoxReportType;
    QLabel *labelReportType;
    QStackedWidget *stackedWidgetTimeSelection;
    QWidget *pageDay;
    QLabel *labelDay;
    QWidget *pageWeek;
    QLabel *labelWeek;
    QWidget *pageMonth;
    QLabel *labelMonth;
    QWidget *pageYear;
    QLabel *labelYear;
    QCalendarWidget *calendarWidget;
    QPushButton *BtnReportQuery;
    QTableWidget *tableReport;
    QLabel *labelShowReport;
    QPushButton *BtnPrint;
    QComboBox *comboBoxRoomID;
    QLabel *labelRoomID;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ManagerClass)
    {
        if (ManagerClass->objectName().isEmpty())
            ManagerClass->setObjectName(QString::fromUtf8("ManagerClass"));
        ManagerClass->resize(1250, 703);
        ManagerClass->setMinimumSize(QSize(1250, 703));
        ManagerClass->setMaximumSize(QSize(1250, 703));
        ManagerClass->setSizeIncrement(QSize(0, 0));
        ManagerClass->setBaseSize(QSize(1250, 703));
        centralWidget = new QWidget(ManagerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setAutoFillBackground(true);
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        page1->setStyleSheet(QString::fromUtf8("#page1{border-image: url(:/Manager/Resources/login.jpg);}\n"
""));
        lineEditUserName = new QLineEdit(page1);
        lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));
        lineEditUserName->setGeometry(QRect(510, 280, 231, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\200\235\346\272\220\351\273\221\344\275\223 Bold"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lineEditUserName->setFont(font);
        lineEditPassWord = new QLineEdit(page1);
        lineEditPassWord->setObjectName(QString::fromUtf8("lineEditPassWord"));
        lineEditPassWord->setGeometry(QRect(510, 350, 231, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\200\235\346\272\220\351\273\221\351\253\224 Bold"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lineEditPassWord->setFont(font1);
        lineEditPassWord->setEchoMode(QLineEdit::Password);
        BtnLogIn = new QPushButton(page1);
        BtnLogIn->setObjectName(QString::fromUtf8("BtnLogIn"));
        BtnLogIn->setGeometry(QRect(540, 430, 121, 41));
        BtnLogIn->setFont(font);
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        page2->setAutoFillBackground(false);
        page2->setStyleSheet(QString::fromUtf8("#page2{border-image: url(:/Manager/Resources/workbg.jpg);}"));
        comboBoxReportType = new QComboBox(page2);
        comboBoxReportType->addItem(QString());
        comboBoxReportType->addItem(QString());
        comboBoxReportType->addItem(QString());
        comboBoxReportType->addItem(QString());
        comboBoxReportType->setObjectName(QString::fromUtf8("comboBoxReportType"));
        comboBoxReportType->setGeometry(QRect(20, 110, 241, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\200\235\346\272\220\351\273\221\344\275\223 Bold"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        comboBoxReportType->setFont(font2);
        labelReportType = new QLabel(page2);
        labelReportType->setObjectName(QString::fromUtf8("labelReportType"));
        labelReportType->setGeometry(QRect(20, 70, 241, 41));
        labelReportType->setFont(font2);
        labelReportType->setAutoFillBackground(false);
        labelReportType->setStyleSheet(QString::fromUtf8("#labelReportType{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidgetTimeSelection = new QStackedWidget(page2);
        stackedWidgetTimeSelection->setObjectName(QString::fromUtf8("stackedWidgetTimeSelection"));
        stackedWidgetTimeSelection->setGeometry(QRect(20, 160, 241, 41));
        stackedWidgetTimeSelection->setAutoFillBackground(false);
        stackedWidgetTimeSelection->setStyleSheet(QString::fromUtf8(""));
        pageDay = new QWidget();
        pageDay->setObjectName(QString::fromUtf8("pageDay"));
        labelDay = new QLabel(pageDay);
        labelDay->setObjectName(QString::fromUtf8("labelDay"));
        labelDay->setGeometry(QRect(0, 0, 241, 41));
        labelDay->setFont(font2);
        labelDay->setStyleSheet(QString::fromUtf8("#labelDay{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidgetTimeSelection->addWidget(pageDay);
        pageWeek = new QWidget();
        pageWeek->setObjectName(QString::fromUtf8("pageWeek"));
        labelWeek = new QLabel(pageWeek);
        labelWeek->setObjectName(QString::fromUtf8("labelWeek"));
        labelWeek->setGeometry(QRect(0, 0, 241, 41));
        labelWeek->setFont(font2);
        labelWeek->setStyleSheet(QString::fromUtf8("#labelWeek{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidgetTimeSelection->addWidget(pageWeek);
        pageMonth = new QWidget();
        pageMonth->setObjectName(QString::fromUtf8("pageMonth"));
        labelMonth = new QLabel(pageMonth);
        labelMonth->setObjectName(QString::fromUtf8("labelMonth"));
        labelMonth->setGeometry(QRect(0, 0, 241, 41));
        labelMonth->setFont(font2);
        labelMonth->setStyleSheet(QString::fromUtf8("#labelMonth{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidgetTimeSelection->addWidget(pageMonth);
        pageYear = new QWidget();
        pageYear->setObjectName(QString::fromUtf8("pageYear"));
        labelYear = new QLabel(pageYear);
        labelYear->setObjectName(QString::fromUtf8("labelYear"));
        labelYear->setGeometry(QRect(0, 0, 241, 41));
        labelYear->setFont(font2);
        labelYear->setStyleSheet(QString::fromUtf8("#labelYear{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidgetTimeSelection->addWidget(pageYear);
        calendarWidget = new QCalendarWidget(page2);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(20, 200, 241, 211));
        BtnReportQuery = new QPushButton(page2);
        BtnReportQuery->setObjectName(QString::fromUtf8("BtnReportQuery"));
        BtnReportQuery->setGeometry(QRect(20, 530, 241, 41));
        BtnReportQuery->setFont(font2);
        BtnReportQuery->setAutoFillBackground(true);
        BtnReportQuery->setStyleSheet(QString::fromUtf8(""));
        tableReport = new QTableWidget(page2);
        tableReport->setObjectName(QString::fromUtf8("tableReport"));
        tableReport->setGeometry(QRect(290, 50, 941, 621));
        tableReport->setStyleSheet(QString::fromUtf8("#tableReport{background-color:rgba(255, 255, 255, 60%);}"));
        labelShowReport = new QLabel(page2);
        labelShowReport->setObjectName(QString::fromUtf8("labelShowReport"));
        labelShowReport->setGeometry(QRect(290, 10, 941, 41));
        labelShowReport->setFont(font2);
        labelShowReport->setAutoFillBackground(false);
        labelShowReport->setStyleSheet(QString::fromUtf8("#labelShowReport{background-color:rgba(255, 255, 255, 60%);}"));
        BtnPrint = new QPushButton(page2);
        BtnPrint->setObjectName(QString::fromUtf8("BtnPrint"));
        BtnPrint->setGeometry(QRect(20, 590, 241, 41));
        BtnPrint->setFont(font2);
        BtnPrint->setAutoFillBackground(true);
        comboBoxRoomID = new QComboBox(page2);
        comboBoxRoomID->setObjectName(QString::fromUtf8("comboBoxRoomID"));
        comboBoxRoomID->setGeometry(QRect(20, 470, 241, 41));
        comboBoxRoomID->setFont(font2);
        labelRoomID = new QLabel(page2);
        labelRoomID->setObjectName(QString::fromUtf8("labelRoomID"));
        labelRoomID->setGeometry(QRect(20, 430, 241, 41));
        labelRoomID->setFont(font2);
        labelRoomID->setStyleSheet(QString::fromUtf8("#labelRoomID{background-color:rgba(255, 255, 255, 60%);}"));
        stackedWidget->addWidget(page2);

        verticalLayout->addWidget(stackedWidget);

        ManagerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ManagerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ManagerClass->setStatusBar(statusBar);

        retranslateUi(ManagerClass);

        stackedWidget->setCurrentIndex(1);
        stackedWidgetTimeSelection->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ManagerClass)
    {
        ManagerClass->setWindowTitle(QApplication::translate("ManagerClass", "Manager", nullptr));
        lineEditUserName->setPlaceholderText(QApplication::translate("ManagerClass", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        lineEditPassWord->setPlaceholderText(QApplication::translate("ManagerClass", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        BtnLogIn->setText(QApplication::translate("ManagerClass", "\347\231\273\345\275\225", nullptr));
        comboBoxReportType->setItemText(0, QApplication::translate("ManagerClass", "\346\227\245\346\212\245", nullptr));
        comboBoxReportType->setItemText(1, QApplication::translate("ManagerClass", "\345\221\250\346\212\245", nullptr));
        comboBoxReportType->setItemText(2, QApplication::translate("ManagerClass", "\346\234\210\346\212\245", nullptr));
        comboBoxReportType->setItemText(3, QApplication::translate("ManagerClass", "\345\271\264\346\212\245", nullptr));

        labelReportType->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\347\273\237\350\256\241\346\212\245\350\241\250\347\261\273\345\236\213", nullptr));
        labelDay->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\346\227\245\346\212\245\346\227\245\346\234\237", nullptr));
        labelWeek->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\345\221\250\346\212\245\346\211\200\345\234\250\345\221\250\344\273\273\346\204\217\346\227\245\346\234\237", nullptr));
        labelMonth->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\346\234\210\346\212\245\346\211\200\345\234\250\346\234\210\344\273\273\346\204\217\346\227\245\346\234\237", nullptr));
        labelYear->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\345\271\264\346\212\245\346\211\200\345\234\250\345\271\264\344\273\273\346\204\217\346\227\245\346\234\237", nullptr));
        BtnReportQuery->setText(QApplication::translate("ManagerClass", "\346\237\245\351\230\205\346\212\245\350\241\250", nullptr));
        labelShowReport->setText(QApplication::translate("ManagerClass", "\350\257\267\346\237\245\351\230\205\346\212\245\350\241\250\357\274\232", nullptr));
        BtnPrint->setText(QApplication::translate("ManagerClass", "\345\257\274\345\207\272\346\212\245\350\241\250", nullptr));
        labelRoomID->setText(QApplication::translate("ManagerClass", "\350\257\267\351\200\211\346\213\251\346\202\250\350\246\201\346\237\245\347\234\213\347\232\204\346\210\277\351\227\264ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManagerClass: public Ui_ManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
