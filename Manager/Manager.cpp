#include "Manager.h"

Manager::Manager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(1);	//���ε�¼ҳ�棬Ĭ��ֱ�ӽ���鿴����ҳ��
	ui.stackedWidgetTimeSelection->setCurrentIndex(0);	//Ĭ������ʾ����ѡ���ձ����ڡ�����ӦĬ�ϵ��ձ�
	ImportRoomIDList();//���뷿���б�
	//��ʾ����ͷ
	ui.tableReport->setColumnCount(8);
	QStringList headers;
	headers << "����ID" << "�յ����ش���" << "�յ�ʹ��ʱ��" << "�ܷ���" << "�����ȵĴ���" << "�굥��" << "���´���" << "�������";
	ui.tableReport->setHorizontalHeaderLabels(headers);
	ui.tableReport->setEditTriggers(QAbstractItemView::NoEditTriggers);	//��ֹ�û��༭��������

	//����ͨ��
	netAccManager = new QNetworkAccessManager(this);
	connect(netAccManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedReply(QNetworkReply*)));	//ͨ��

	connect(ui.BtnLogIn, SIGNAL(clicked()), this, SLOT(ClickedOnBtnLogIn()));	//�����¼��ť
	connect(ui.comboBoxReportType, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectOnComboBoxReportType()));	//ѡ�񱨱�����
	connect(ui.calendarWidget, SIGNAL(selectionChanged()), this, SLOT(SelectOnDate()));	//ѡ������
	connect(ui.BtnReportQuery, SIGNAL(clicked()), this, SLOT(ClickedOnBtnReportQuery()));	//������ı���
	connect(ui.BtnPrint, SIGNAL(clicked()), this, SLOT(ClickedOnBtnPrint()));	//�����������

	
}

int Manager::ImportRoomIDList()	//���뷿�����б�
{
	QFile file("roomlist.txt");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream RoomIDInput(&file);
		QString lineStr;	//һ�д���һ������ID
		roomListWidget = new QListWidget(this);
		selectedRoomLineEdit = new QLineEdit(this);
		while (!RoomIDInput.atEnd())
		{
			lineStr = RoomIDInput.readLine();	//��ȡһ������ID
			QListWidgetItem *listItem = new QListWidgetItem(roomListWidget);
			roomListWidget->addItem(listItem);
			QCheckBox *roomIDCheckBox = new QCheckBox(this);
			roomIDCheckBox->setText(lineStr);
			//roomListWidget->addItem(listItem);
			roomListWidget->setItemWidget(listItem, roomIDCheckBox);
			connect(roomIDCheckBox, SIGNAL(stateChanged(int)), this, SLOT(ChangeOnRoomIDCheckBox()));	//����ID��ѡ��״̬�ı�
		}
		ui.comboBoxRoomID->setModel(roomListWidget->model());
		ui.comboBoxRoomID->setView(roomListWidget);
		ui.comboBoxRoomID->setLineEdit(selectedRoomLineEdit);
		selectedRoomLineEdit->setReadOnly(true);//��Ϊֻ��
		file.close();
	}
	else
	{
		ui.statusBar->showMessage(tr("�������б���ʧ�ܣ�Ĭ�ϲ鿴���з�����Ϣ�����˳����������鿴..."));
	}
	return 0;
}

QString Manager::ImportIP()	//����IP�Ͷ˿�
{
	QString IP="";
	QFile file("IP.txt");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream RoomIDInput(&file);
		IP = RoomIDInput.readLine();
		file.close();
	}
	else
	{
		ui.statusBar->showMessage(tr("IP��ַ����ʧ�ܣ�"));
	}
	return IP;
}

int Manager::ClickedOnBtnLogIn()	//�����¼��ť
{
	QString username;	//�û���
	QString password;	//����
	username = ui.lineEditUserName->text();
	password = ui.lineEditPassWord->text();
	//ͨ���ж��Ƿ���ȷ
	if (1)//����û���������ȷ
	{
		ui.stackedWidget->setCurrentIndex(1);	//��¼�ɹ����л���page2
		ui.stackedWidgetTimeSelection->setCurrentIndex(0);	//Ĭ������ʾ����ѡ���ձ����ڡ�����ӦĬ�ϵ��ձ�
		ui.statusBar->showMessage(username + tr("��¼�ɹ���"), 3000);	 //״̬����ʾ��¼�ɹ�3��
	}
	return 0;
}

int Manager::SelectOnComboBoxReportType()	//ѡ�񱨱�����
{
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//�ձ�
		ui.stackedWidgetTimeSelection->setCurrentIndex(0);
		ui.statusBar->showMessage(tr("����ѡ��鿴�ձ�����ѡ����Ҫ�鿴�����ڣ�"), 3000);
		break;
	case 1:	//�ܱ�
		ui.stackedWidgetTimeSelection->setCurrentIndex(1);
		ui.statusBar->showMessage(tr("����ѡ��鿴�ܱ�����ѡ����Ҫ�鿴���ܣ�"), 3000);
		break;
	case 2:	//�±�
		ui.stackedWidgetTimeSelection->setCurrentIndex(2);
		ui.statusBar->showMessage(tr("����ѡ��鿴�±�����ѡ����Ҫ�鿴���£�"), 3000);
		break;
	case 3:	//�걨	
		ui.stackedWidgetTimeSelection->setCurrentIndex(3);
		ui.statusBar->showMessage(tr("����ѡ��鿴�걨����ѡ����Ҫ�鿴���꣡"), 3000);
		break;
	}
	return 0;
}

int Manager::SelectOnDate()	//ѡ�񱨱�����
{
	QDate selectedDate = ui.calendarWidget->selectedDate();	//��õ�ǰѡ�е�����
	QString currentDate = selectedDate.toString("yyyy-MM-dd");
	ui.statusBar->showMessage(tr("��ѡ����") + currentDate, 3000);
	return 0;
}

int Manager::ChangeOnRoomIDCheckBox()	//ѡ�񷿼�ID
{
	QString RoomIDListText = " ";
	QList<QCheckBox *> checkBoxList = ui.comboBoxRoomID->findChildren<QCheckBox *>();
	for (int i = 0; i < checkBoxList.count(); ++i)	//��������RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//�÷���ID��ѡ��
		{
			RoomIDListText += checkBoxList.at(i)->text();
			RoomIDListText += ", ";
		}
	}
	//��ʾѡ�еķ���ID
	selectedRoomLineEdit->setText(tr("����ѡ�з��� ") + RoomIDListText);
	ui.statusBar->showMessage(tr("����ѡ�з���") + RoomIDListText, 3000);
	return 0;
}

int Manager::ClickedOnBtnReportQuery()	//������ı���ť
{
	QString  queryUrl;
	QString IP = ImportIP();
	//QString queryUrl = "http://10.128.200.116:8080/api/report/";
	QDate selectedDate = ui.calendarWidget->selectedDate();	//��õ�ǰѡ�е�����
	int reportType = 1; //Ĭ�ϲ�ѯ�ձ�
	QString strReportType = "�ձ�";
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//�ձ�
		reportType = 1;
		strReportType = "�ձ�";
		break;
	case 1:	//�ܱ�
		reportType = 2;
		strReportType = "�ܱ�";
		selectedDate = selectedDate.addDays(1 - (selectedDate.dayOfWeek()));//ת��Ϊ������һ
		break;
	case 2:	//�±�
		reportType = 3;
		strReportType = "�±�";
		selectedDate = selectedDate.addDays(1 - (selectedDate.day()));//ת��Ϊ����1��
		break;
	case 3:	//�걨	
		reportType = 4;
		strReportType = "�걨";
		selectedDate = selectedDate.addDays(1 - (selectedDate.dayOfYear()));//ת��Ϊ�����һ��
		break;
	}
	QString dateTime = selectedDate.toString("yyyy-MM-dd") + " 00:00:01";
	QDateTime selectedDateTime = QDateTime::fromString(dateTime, "yyyy-MM-dd hh:mm:ss");
	int queryDate = selectedDateTime.toTime_t();	//��ʱ��ת��Ϊunixʱ���

	ui.labelShowReport->setText(tr("������� ") + dateTime + tr(" ���") + strReportType + tr(":"));
	ui.statusBar->showMessage(tr("������� ") + dateTime + tr(" ���") + strReportType + tr(":"));	//״̬����ʾ��ǰ�����ı������ͺ�����

	//����ÿ������ѯ�ķ���
	QList<QCheckBox *> checkBoxList = ui.comboBoxRoomID->findChildren<QCheckBox *>();
	//ȷ��ѡ�еķ�����
	int selectedRoomCnt = 0;
	for (int i = 0; i < checkBoxList.count(); ++i)	//��������RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//�÷���ID��ѡ��
		{
			++selectedRoomCnt;
		}
	}
	ui.tableReport->setRowCount(selectedRoomCnt);	//���ñ���tableWidget�ĵ�����

	int row = 0;//��ʾ�Ǳ�ѡ�еĵ�row�����䣬������ĵ�row��
	for (int i = 0; i < checkBoxList.count(); ++i)	//��������RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//�÷���ID��ѡ��
		{
			ui.tableReport->setItem(row, 0, new QTableWidgetItem(checkBoxList.at(i)->text()));	//�ڱ��������뱻ѡ�еķ���ID

			queryUrl = IP+"/api/report/";
			queryUrl += checkBoxList.at(i)->text();	//��ѯurl���Ϸ����
			queryUrl += "/";
			queryUrl += QString::number(reportType);
			queryUrl += "/";
			queryUrl += QString::number(queryDate);
			//queryUrl += "345";

			ui.statusBar->showMessage(queryUrl, 3000);	//״̬����ʾ��ǰ���͵�url

			//ͨ��
			const QUrl aUrl(queryUrl);
			QNetworkRequest netRequest(aUrl);
			netRequest.setRawHeader("Content-Type", "application/json");
			netAccManager->get(netRequest);	

			++row;
		}
	}
	return 0;
}

int Manager::ClickedOnBtnPrint()	//�����������ť
{
	QXlsx::Document reportXlsx;	//�����ļ�
	QString defaultXlsxName;	//Ĭ���ļ���
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//�ձ�
		defaultXlsxName = "�ձ�.xlsx";
		break;
	case 1:	//�ܱ�
		defaultXlsxName = "�ܱ�.xlsx";
		break;
	case 2:	//�±�
		defaultXlsxName = "�±�.xlsx";
		break;
	case 3:	//�걨	
		defaultXlsxName = "�걨.xlsx";
		break;
	}

	//����Ĭ���ļ���Ϊ ��������_��ǰʱ��.xlsx	//��Ϊxls�򿪻���ʾ�ļ���ʽ����չ����ƥ��
	QFileInfo fileInfo(defaultXlsxName);
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentTimeStr = currentDateTime.toString("yyyyMMddhhmmss");
	defaultXlsxName = fileInfo.baseName() + "_" + currentTimeStr + ".xlsx";

	//��ȡ�ļ�����·��
	QFileDialog *fileDlg = new QFileDialog(this);
	fileDlg->setWindowTitle("��������");
	fileDlg->setAcceptMode(QFileDialog::AcceptSave);
	fileDlg->selectFile(defaultXlsxName);
	fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
	fileDlg->setDefaultSuffix("xlsx");

	QString filePathName;	//�ļ�·����

	if (fileDlg->exec() == QDialog::Accepted)
	{
		filePathName = fileDlg->selectedFiles().at(0);
	}

	//�����ļ���Ӻ�׺��
	fileInfo = QFileInfo(filePathName);
	if (fileInfo.suffix() != "xls" && fileInfo.suffix() != "xlsx")
	{
		filePathName += ".xlsx";
	}

	int row = ui.tableReport->rowCount();	//����
	int col = ui.tableReport->columnCount();	//����
	
	//д�����
	for (int i = 0; i < col; ++i)			
	{
		reportXlsx.write(1, i + 1, ui.tableReport->horizontalHeaderItem(i)->text()); //excel���ж���1��ʼ����
	}
	//�����п�
	reportXlsx.setColumnWidth(1, 10);
	reportXlsx.setColumnWidth(2, 18);
	reportXlsx.setColumnWidth(3, 18);
	reportXlsx.setColumnWidth(4, 10);
	reportXlsx.setColumnWidth(5, 18);
	reportXlsx.setColumnWidth(6, 10);
	reportXlsx.setColumnWidth(7, 13);
	reportXlsx.setColumnWidth(8, 13);
	//д������䱨������
	QString value;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			QTableWidgetItem *item = ui.tableReport->item(i, j);
			if (item == NULL)
				value = "";
			else
				value = item->text();
			reportXlsx.write(i + 2, j + 1, value);	//excel���ж���1��ʼ���������Ǵ�0��ʼ������һ�б�����������i+2,j+1
		}
	}
	if (reportXlsx.saveAs(filePathName))//����ɹ�
	{
		ui.statusBar->showMessage(tr("�����ѳɹ�������") + filePathName, 3000);
		QMessageBox::information(this, tr("��������"), tr("�ɹ�������") + filePathName + " !", QMessageBox::Ok);
	}
	
	return 0;
}

int Manager::finishedReply(QNetworkReply *reply)	//����ͨ�ŷ��صı�����Ϣ
{
	int roomRow = -1;//�����ڱ����е��к�
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray replyBytes = reply->readAll();
		QString replyStr(replyBytes);
		ui.statusBar->showMessage(replyStr, 5000);//���ظ������ʾ��״̬��
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(replyBytes, &jsonError);
		if (jsonError.error == QJsonParseError::NoError)	//δ����
		{
			if (json.isObject())
			{
				QJsonObject rootObj = json.object();
				if (rootObj.contains("RoomId"))
				{
					//ȡ��keyΪRoomId��ֵ
					QJsonValue value = rootObj.value("RoomId");	
					int tableRowCnt = ui.tableReport->rowCount();
					for (int i = 0; i < tableRowCnt && roomRow == -1; ++i)
					{
						int roomId = value.toInt();
						//QString strRoomId = QString::number(roomId);
						int tableRowID = ui.tableReport->item(i, 0)->text().toInt();
						if (tableRowID == roomId)	//�ҵ������и÷���id������
						{
							roomRow = i;
						}
					}
				}
				if (rootObj.contains("TimesOfOnOff"))
				{
					//ȡ��keyΪTimesOfOnOff��ֵ
					QJsonValue value = rootObj.value("TimesOfOnOff");
					int timesOfOnOff = value.toInt();
					QString strTimesOfOnOff = QString::number(timesOfOnOff);
					ui.tableReport->setItem(roomRow, 1, new QTableWidgetItem(strTimesOfOnOff));
				}
				if (rootObj.contains("Duration"))
				{
					//ȡ��keyΪDuration��ֵ
					QJsonValue value = rootObj.value("Duration");
					int duration = value.toInt();
					QString strDuration = QString::number(duration);
					ui.tableReport->setItem(roomRow, 2, new QTableWidgetItem(strDuration));
				}
				if (rootObj.contains("TotalFee"))
				{
					//ȡ��keyΪTotalFee��ֵ
					QJsonValue value = rootObj.value("TotalFee");
					double totalFee = value.toDouble();
					QString strTotalFee = QString::number(totalFee);
					ui.tableReport->setItem(roomRow, 3, new QTableWidgetItem(strTotalFee));
				}
				if (rootObj.contains("TimesOfDispatch"))
				{
					//ȡ��keyΪTimesOfDispatch��ֵ
					QJsonValue value = rootObj.value("TimesOfDispatch");
					int timesOfDispatch = value.toInt();
					QString strTimesOfDispatch = QString::number(timesOfDispatch);
					ui.tableReport->setItem(roomRow, 4, new QTableWidgetItem(strTimesOfDispatch));
				}
				if (rootObj.contains("NumberOfRDR"))
				{
					//ȡ��keyΪNumberOfRDR��ֵ
					QJsonValue value = rootObj.value("NumberOfRDR");
					int numberOfRDR = value.toInt();
					QString strNumberOFRDR = QString::number(numberOfRDR);
					ui.tableReport->setItem(roomRow, 5, new QTableWidgetItem(strNumberOFRDR));
				}
				if (rootObj.contains("TimesOfChangeTemp"))
				{
					//ȡ��keyΪTimesOfChangeTemp��ֵ
					QJsonValue value = rootObj.value("TimesOfChangeTemp");
					int timesOfChangeTemp = value.toInt();
					QString strTimesOfChangeTemp = QString::number(timesOfChangeTemp);
					ui.tableReport->setItem(roomRow, 6, new QTableWidgetItem(strTimesOfChangeTemp));
				}
				if (rootObj.contains("TimesOfChangeFanSpeed"))
				{
					//ȡ��keyΪTimesOfChangeFanSpeed��ֵ
					QJsonValue value = rootObj.value("TimesOfChangeFanSpeed");
					int timesOfChangeFanSpeed = value.toInt();
					QString strTimesOfChangFanSpeed = QString::number(timesOfChangeFanSpeed);
					ui.tableReport->setItem(roomRow, 7, new QTableWidgetItem(strTimesOfChangFanSpeed));
				}
			}
		}
		else
		{
			ui.statusBar->showMessage(tr("��������"), 3000);
		}
	}
	else
	{
		ui.statusBar->showMessage(tr("������룺") + reply->errorString(), 3000);
	}
	reply->deleteLater();
	reply = 0;
	return 0;
}
