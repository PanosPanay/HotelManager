#include "Manager.h"

Manager::Manager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(1);	//屏蔽登录页面，默认直接进入查看报表页面
	ui.stackedWidgetTimeSelection->setCurrentIndex(0);	//默认是显示“请选择日报日期”，对应默认的日报
	ImportRoomIDList();//导入房间列表
	//显示报表头
	ui.tableReport->setColumnCount(8);
	QStringList headers;
	headers << "房间ID" << "空调开关次数" << "空调使用时长" << "总费用" << "被调度的次数" << "详单数" << "调温次数" << "调风次数";
	ui.tableReport->setHorizontalHeaderLabels(headers);
	ui.tableReport->setEditTriggers(QAbstractItemView::NoEditTriggers);	//禁止用户编辑表项数据

	//网络通信
	netAccManager = new QNetworkAccessManager(this);
	connect(netAccManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedReply(QNetworkReply*)));	//通信

	connect(ui.BtnLogIn, SIGNAL(clicked()), this, SLOT(ClickedOnBtnLogIn()));	//点击登录按钮
	connect(ui.comboBoxReportType, SIGNAL(currentIndexChanged(int)), this, SLOT(SelectOnComboBoxReportType()));	//选择报表类型
	connect(ui.calendarWidget, SIGNAL(selectionChanged()), this, SLOT(SelectOnDate()));	//选择日期
	connect(ui.BtnReportQuery, SIGNAL(clicked()), this, SLOT(ClickedOnBtnReportQuery()));	//点击查阅报表
	connect(ui.BtnPrint, SIGNAL(clicked()), this, SLOT(ClickedOnBtnPrint()));	//点击导出报表

	
}

int Manager::ImportRoomIDList()	//导入房间编号列表
{
	QFile file("roomlist.txt");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream RoomIDInput(&file);
		QString lineStr;	//一行代表一个房间ID
		roomListWidget = new QListWidget(this);
		selectedRoomLineEdit = new QLineEdit(this);
		while (!RoomIDInput.atEnd())
		{
			lineStr = RoomIDInput.readLine();	//获取一个房间ID
			QListWidgetItem *listItem = new QListWidgetItem(roomListWidget);
			roomListWidget->addItem(listItem);
			QCheckBox *roomIDCheckBox = new QCheckBox(this);
			roomIDCheckBox->setText(lineStr);
			//roomListWidget->addItem(listItem);
			roomListWidget->setItemWidget(listItem, roomIDCheckBox);
			connect(roomIDCheckBox, SIGNAL(stateChanged(int)), this, SLOT(ChangeOnRoomIDCheckBox()));	//房间ID复选框状态改变
		}
		ui.comboBoxRoomID->setModel(roomListWidget->model());
		ui.comboBoxRoomID->setView(roomListWidget);
		ui.comboBoxRoomID->setLineEdit(selectedRoomLineEdit);
		selectedRoomLineEdit->setReadOnly(true);//设为只读
		file.close();
	}
	else
	{
		ui.statusBar->showMessage(tr("房间编号列表导入失败！默认查看所有房间信息，或退出程序重启查看..."));
	}
	return 0;
}

QString Manager::ImportIP()	//导入IP和端口
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
		ui.statusBar->showMessage(tr("IP地址导入失败！"));
	}
	return IP;
}

int Manager::ClickedOnBtnLogIn()	//点击登录按钮
{
	QString username;	//用户名
	QString password;	//密码
	username = ui.lineEditUserName->text();
	password = ui.lineEditPassWord->text();
	//通信判断是否正确
	if (1)//如果用户名密码正确
	{
		ui.stackedWidget->setCurrentIndex(1);	//登录成功，切换到page2
		ui.stackedWidgetTimeSelection->setCurrentIndex(0);	//默认是显示“请选择日报日期”，对应默认的日报
		ui.statusBar->showMessage(username + tr("登录成功！"), 3000);	 //状态栏提示登录成功3秒
	}
	return 0;
}

int Manager::SelectOnComboBoxReportType()	//选择报表类型
{
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//日报
		ui.stackedWidgetTimeSelection->setCurrentIndex(0);
		ui.statusBar->showMessage(tr("您已选择查看日报，请选择你要查看的日期！"), 3000);
		break;
	case 1:	//周报
		ui.stackedWidgetTimeSelection->setCurrentIndex(1);
		ui.statusBar->showMessage(tr("您已选择查看周报，请选择您要查看的周！"), 3000);
		break;
	case 2:	//月报
		ui.stackedWidgetTimeSelection->setCurrentIndex(2);
		ui.statusBar->showMessage(tr("您已选择查看月报，请选择您要查看的月！"), 3000);
		break;
	case 3:	//年报	
		ui.stackedWidgetTimeSelection->setCurrentIndex(3);
		ui.statusBar->showMessage(tr("您已选择查看年报，请选择您要查看的年！"), 3000);
		break;
	}
	return 0;
}

int Manager::SelectOnDate()	//选择报表日期
{
	QDate selectedDate = ui.calendarWidget->selectedDate();	//获得当前选中的日期
	QString currentDate = selectedDate.toString("yyyy-MM-dd");
	ui.statusBar->showMessage(tr("您选中了") + currentDate, 3000);
	return 0;
}

int Manager::ChangeOnRoomIDCheckBox()	//选择房间ID
{
	QString RoomIDListText = " ";
	QList<QCheckBox *> checkBoxList = ui.comboBoxRoomID->findChildren<QCheckBox *>();
	for (int i = 0; i < checkBoxList.count(); ++i)	//遍历所有RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//该房间ID被选中
		{
			RoomIDListText += checkBoxList.at(i)->text();
			RoomIDListText += ", ";
		}
	}
	//显示选中的房间ID
	selectedRoomLineEdit->setText(tr("您已选中房间 ") + RoomIDListText);
	ui.statusBar->showMessage(tr("您已选中房间") + RoomIDListText, 3000);
	return 0;
}

int Manager::ClickedOnBtnReportQuery()	//点击查阅报表按钮
{
	QString  queryUrl;
	QString IP = ImportIP();
	//QString queryUrl = "http://10.128.200.116:8080/api/report/";
	QDate selectedDate = ui.calendarWidget->selectedDate();	//获得当前选中的日期
	int reportType = 1; //默认查询日报
	QString strReportType = "日报";
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//日报
		reportType = 1;
		strReportType = "日报";
		break;
	case 1:	//周报
		reportType = 2;
		strReportType = "周报";
		selectedDate = selectedDate.addDays(1 - (selectedDate.dayOfWeek()));//转化为该周周一
		break;
	case 2:	//月报
		reportType = 3;
		strReportType = "月报";
		selectedDate = selectedDate.addDays(1 - (selectedDate.day()));//转化为该月1号
		break;
	case 3:	//年报	
		reportType = 4;
		strReportType = "年报";
		selectedDate = selectedDate.addDays(1 - (selectedDate.dayOfYear()));//转化为该年第一天
		break;
	}
	QString dateTime = selectedDate.toString("yyyy-MM-dd") + " 00:00:01";
	QDateTime selectedDateTime = QDateTime::fromString(dateTime, "yyyy-MM-dd hh:mm:ss");
	int queryDate = selectedDateTime.toTime_t();	//将时间转化为unix时间戳

	ui.labelShowReport->setText(tr("请查阅自 ") + dateTime + tr(" 起的") + strReportType + tr(":"));
	ui.statusBar->showMessage(tr("请查阅自 ") + dateTime + tr(" 起的") + strReportType + tr(":"));	//状态栏显示当前产看的报表类型和日期

	//遍历每个待查询的房间
	QList<QCheckBox *> checkBoxList = ui.comboBoxRoomID->findChildren<QCheckBox *>();
	//确定选中的房间数
	int selectedRoomCnt = 0;
	for (int i = 0; i < checkBoxList.count(); ++i)	//遍历所有RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//该房间ID被选中
		{
			++selectedRoomCnt;
		}
	}
	ui.tableReport->setRowCount(selectedRoomCnt);	//设置报表tableWidget的的行数

	int row = 0;//表示是被选中的第row个房间，即报表的第row行
	for (int i = 0; i < checkBoxList.count(); ++i)	//遍历所有RoomID
	{
		if (checkBoxList.at(i)->isChecked() == true)	//该房间ID被选中
		{
			ui.tableReport->setItem(row, 0, new QTableWidgetItem(checkBoxList.at(i)->text()));	//在报表上填入被选中的房间ID

			queryUrl = IP+"/api/report/";
			queryUrl += checkBoxList.at(i)->text();	//查询url加上房间号
			queryUrl += "/";
			queryUrl += QString::number(reportType);
			queryUrl += "/";
			queryUrl += QString::number(queryDate);
			//queryUrl += "345";

			ui.statusBar->showMessage(queryUrl, 3000);	//状态栏显示当前发送的url

			//通信
			const QUrl aUrl(queryUrl);
			QNetworkRequest netRequest(aUrl);
			netRequest.setRawHeader("Content-Type", "application/json");
			netAccManager->get(netRequest);	

			++row;
		}
	}
	return 0;
}

int Manager::ClickedOnBtnPrint()	//点击导出报表按钮
{
	QXlsx::Document reportXlsx;	//报表文件
	QString defaultXlsxName;	//默认文件名
	switch (ui.comboBoxReportType->currentIndex())
	{
	case 0:	//日报
		defaultXlsxName = "日报.xlsx";
		break;
	case 1:	//周报
		defaultXlsxName = "周报.xlsx";
		break;
	case 2:	//月报
		defaultXlsxName = "月报.xlsx";
		break;
	case 3:	//年报	
		defaultXlsxName = "年报.xlsx";
		break;
	}

	//设置默认文件名为 报表类型_当前时间.xlsx	//若为xls打开会提示文件格式和扩展名不匹配
	QFileInfo fileInfo(defaultXlsxName);
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentTimeStr = currentDateTime.toString("yyyyMMddhhmmss");
	defaultXlsxName = fileInfo.baseName() + "_" + currentTimeStr + ".xlsx";

	//获取文件保存路径
	QFileDialog *fileDlg = new QFileDialog(this);
	fileDlg->setWindowTitle("导出报表");
	fileDlg->setAcceptMode(QFileDialog::AcceptSave);
	fileDlg->selectFile(defaultXlsxName);
	fileDlg->setNameFilter("Excel Files(*.xls *.xlsx)");
	fileDlg->setDefaultSuffix("xlsx");

	QString filePathName;	//文件路径名

	if (fileDlg->exec() == QDialog::Accepted)
	{
		filePathName = fileDlg->selectedFiles().at(0);
	}

	//保存文件添加后缀名
	fileInfo = QFileInfo(filePathName);
	if (fileInfo.suffix() != "xls" && fileInfo.suffix() != "xlsx")
	{
		filePathName += ".xlsx";
	}

	int row = ui.tableReport->rowCount();	//行数
	int col = ui.tableReport->columnCount();	//列数
	
	//写入标题
	for (int i = 0; i < col; ++i)			
	{
		reportXlsx.write(1, i + 1, ui.tableReport->horizontalHeaderItem(i)->text()); //excel行列都从1开始计数
	}
	//设置列宽
	reportXlsx.setColumnWidth(1, 10);
	reportXlsx.setColumnWidth(2, 18);
	reportXlsx.setColumnWidth(3, 18);
	reportXlsx.setColumnWidth(4, 10);
	reportXlsx.setColumnWidth(5, 18);
	reportXlsx.setColumnWidth(6, 10);
	reportXlsx.setColumnWidth(7, 13);
	reportXlsx.setColumnWidth(8, 13);
	//写入各房间报表内容
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
			reportXlsx.write(i + 2, j + 1, value);	//excel行列都从1开始计数，而非从0开始，且有一行标题栏，所以i+2,j+1
		}
	}
	if (reportXlsx.saveAs(filePathName))//保存成功
	{
		ui.statusBar->showMessage(tr("报表已成功导出到") + filePathName, 3000);
		QMessageBox::information(this, tr("导出报表"), tr("成功导出到") + filePathName + " !", QMessageBox::Ok);
	}
	
	return 0;
}

int Manager::finishedReply(QNetworkReply *reply)	//处理通信返回的报表信息
{
	int roomRow = -1;//房间在报表中的行号
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray replyBytes = reply->readAll();
		QString replyStr(replyBytes);
		ui.statusBar->showMessage(replyStr, 5000);//将回复语句显示在状态栏
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(replyBytes, &jsonError);
		if (jsonError.error == QJsonParseError::NoError)	//未出错
		{
			if (json.isObject())
			{
				QJsonObject rootObj = json.object();
				if (rootObj.contains("RoomId"))
				{
					//取出key为RoomId的值
					QJsonValue value = rootObj.value("RoomId");	
					int tableRowCnt = ui.tableReport->rowCount();
					for (int i = 0; i < tableRowCnt && roomRow == -1; ++i)
					{
						int roomId = value.toInt();
						//QString strRoomId = QString::number(roomId);
						int tableRowID = ui.tableReport->item(i, 0)->text().toInt();
						if (tableRowID == roomId)	//找到报表中该房间id所在行
						{
							roomRow = i;
						}
					}
				}
				if (rootObj.contains("TimesOfOnOff"))
				{
					//取出key为TimesOfOnOff的值
					QJsonValue value = rootObj.value("TimesOfOnOff");
					int timesOfOnOff = value.toInt();
					QString strTimesOfOnOff = QString::number(timesOfOnOff);
					ui.tableReport->setItem(roomRow, 1, new QTableWidgetItem(strTimesOfOnOff));
				}
				if (rootObj.contains("Duration"))
				{
					//取出key为Duration的值
					QJsonValue value = rootObj.value("Duration");
					int duration = value.toInt();
					QString strDuration = QString::number(duration);
					ui.tableReport->setItem(roomRow, 2, new QTableWidgetItem(strDuration));
				}
				if (rootObj.contains("TotalFee"))
				{
					//取出key为TotalFee的值
					QJsonValue value = rootObj.value("TotalFee");
					double totalFee = value.toDouble();
					QString strTotalFee = QString::number(totalFee);
					ui.tableReport->setItem(roomRow, 3, new QTableWidgetItem(strTotalFee));
				}
				if (rootObj.contains("TimesOfDispatch"))
				{
					//取出key为TimesOfDispatch的值
					QJsonValue value = rootObj.value("TimesOfDispatch");
					int timesOfDispatch = value.toInt();
					QString strTimesOfDispatch = QString::number(timesOfDispatch);
					ui.tableReport->setItem(roomRow, 4, new QTableWidgetItem(strTimesOfDispatch));
				}
				if (rootObj.contains("NumberOfRDR"))
				{
					//取出key为NumberOfRDR的值
					QJsonValue value = rootObj.value("NumberOfRDR");
					int numberOfRDR = value.toInt();
					QString strNumberOFRDR = QString::number(numberOfRDR);
					ui.tableReport->setItem(roomRow, 5, new QTableWidgetItem(strNumberOFRDR));
				}
				if (rootObj.contains("TimesOfChangeTemp"))
				{
					//取出key为TimesOfChangeTemp的值
					QJsonValue value = rootObj.value("TimesOfChangeTemp");
					int timesOfChangeTemp = value.toInt();
					QString strTimesOfChangeTemp = QString::number(timesOfChangeTemp);
					ui.tableReport->setItem(roomRow, 6, new QTableWidgetItem(strTimesOfChangeTemp));
				}
				if (rootObj.contains("TimesOfChangeFanSpeed"))
				{
					//取出key为TimesOfChangeFanSpeed的值
					QJsonValue value = rootObj.value("TimesOfChangeFanSpeed");
					int timesOfChangeFanSpeed = value.toInt();
					QString strTimesOfChangFanSpeed = QString::number(timesOfChangeFanSpeed);
					ui.tableReport->setItem(roomRow, 7, new QTableWidgetItem(strTimesOfChangFanSpeed));
				}
			}
		}
		else
		{
			ui.statusBar->showMessage(tr("解析错误"), 3000);
		}
	}
	else
	{
		ui.statusBar->showMessage(tr("错误代码：") + reply->errorString(), 3000);
	}
	reply->deleteLater();
	reply = 0;
	return 0;
}
