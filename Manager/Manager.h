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

#include "xlsx\xlsxdocument.h"				//���ڶ�excel�Ĳ���

using namespace std;

class Manager : public QMainWindow
{
	Q_OBJECT

public:
	Manager(QWidget *parent = Q_NULLPTR);

private:
	Ui::ManagerClass ui;
	QListWidget *roomListWidget;			//����ID�б�ؼ�
	QLineEdit *selectedRoomLineEdit;		//��ʾѡ�еķ���
	QNetworkAccessManager *netAccManager;	//ͨ��
	int ImportRoomIDList();					//���뷿��ID�б�
	QString ImportIP();							//����IP�Ͷ˿�

private slots:
	int ClickedOnBtnLogIn();				//�����¼��ť
	int SelectOnComboBoxReportType();
	int SelectOnDate();
	int ChangeOnRoomIDCheckBox();
	int ClickedOnBtnReportQuery();
	int ClickedOnBtnPrint();
	int finishedReply(QNetworkReply *reply);
};
