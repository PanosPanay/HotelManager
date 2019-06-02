#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_Manager.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QMessageBox>
#include <string>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QJsonParseError>
#include <QJsonObject>

#include "xlsx\xlsxdocument.h"				//用于对excel的操作

using namespace std;

class Manager : public QMainWindow
{
	Q_OBJECT

public:
	Manager(QWidget *parent = Q_NULLPTR);

private:
	Ui::ManagerClass ui;
	QListWidget *roomListWidget;			//房间ID列表控件
	QLineEdit *selectedRoomLineEdit;		//显示选中的房间
	QNetworkAccessManager *netAccManager;	//通信
	int ImportRoomIDList();					//导入房间ID列表
	QString ImportIP();							//导入IP和端口

private slots:
	int ClickedOnBtnLogIn();				//点击登录按钮
	int SelectOnComboBoxReportType();
	int SelectOnDate();
	int ChangeOnRoomIDCheckBox();
	int ClickedOnBtnReportQuery();
	int ClickedOnBtnPrint();
	int finishedReply(QNetworkReply *reply);
};
