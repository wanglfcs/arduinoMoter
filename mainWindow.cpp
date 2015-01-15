#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>

#include <QDebug>

#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent):QWidget(parent)
{
	mLabelArc = new QLabel("角度");
	mLabelSpeed = new QLabel("速度");
	mEditArc = new QLineEdit();
	mEditSpeed = new QLineEdit();
	mButtonStartCW = new QPushButton("正转");
	mButtonStartCCW = new QPushButton("反转");
	mButtonStop = new QPushButton("停止");
	mLabelStatus = new QLabel();
	mLabelStatus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	mMainLayout = new QVBoxLayout();
	mUpLayout = new QHBoxLayout();
	mMiddleLayout = new QHBoxLayout();
	mLowLayout = new QHBoxLayout();

	mComboBoxPortList = new QComboBox();
	mButtonOpenPort = new QPushButton("打开");
	QHBoxLayout *firstLayout = new QHBoxLayout();
	firstLayout->addWidget(mComboBoxPortList);
	firstLayout->addWidget(mButtonOpenPort);


	mUpLayout->addWidget(mLabelArc);
	mUpLayout->addWidget(mEditArc);
	mUpLayout->addWidget(mButtonStartCW);

	mMiddleLayout->addWidget(mLabelSpeed);
	mMiddleLayout->addWidget(mEditSpeed);
	mMiddleLayout->addWidget(mButtonStartCCW);

	mLowLayout->addWidget(mLabelStatus);
	mLowLayout->addWidget(mButtonStop);
	mMainLayout->addLayout(firstLayout);
	mMainLayout->addLayout(mUpLayout);
	mMainLayout->addLayout(mMiddleLayout);
	mMainLayout->addLayout(mLowLayout);

	setLayout(mMainLayout);

	connect(mButtonStartCW, SIGNAL(clicked()), this, SLOT(onStartCW()));
	connect(mButtonStartCCW, SIGNAL(clicked()), this, SLOT(onStartCCW()));
	connect(mButtonStop, SIGNAL(clicked()), this, SLOT(onStop()));
	connect(mButtonOpenPort, SIGNAL(clicked()), this, SLOT(onOpenSerialPort()));

	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
		{
			mComboBoxPortList->addItem(info.portName());
		}

}

MainWindow::~MainWindow()
{
	if (mSerial.isOpen())
		mSerial.close();
}

void MainWindow::onStartCW()
{
	qDebug()<<"on clicked start cw";
	QString res = "3,";
	res.append(mEditSpeed->text());
	res.append(",");
	res.append(mEditArc->text());
	if (mSerial.write(res.toLatin1().data()) > 2)
		mLabelStatus->setText("电机正转");
	else
		mLabelStatus->setText("指令输入失败");

	
}

void MainWindow::onStartCCW()
{
	qDebug()<<"on clicked start ccw";
	QString res = "4,";
	res.append(mEditSpeed->text());
	res.append(",");
	res.append(mEditArc->text());
	if(mSerial.write(res.toLatin1().data())> 2)
		mLabelStatus->setText("电机反转");
	else
		mLabelStatus->setText("指令输入失败");

}

void MainWindow::onStop()
{
	qDebug()<<"on clicked start stop";
	char data[10] = "5,-1";
	if(mSerial.write(data)>1)
		mLabelStatus->setText("停止转动");
	else
		mLabelStatus->setText("指令输入失败");
}

void MainWindow::onOpenSerialPort()
{
	qDebug()<<"you open:"<<mComboBoxPortList->currentText();
	mSerial.setPortName(mComboBoxPortList->currentText());
	mSerial.setBaudRate(QSerialPort::Baud9600);
	mSerial.setDataBits(QSerialPort::Data8);
	mSerial.setParity(QSerialPort::NoParity);
	mSerial.setFlowControl(QSerialPort::NoFlowControl);
	mSerial.setStopBits(QSerialPort::OneStop);
	if (mSerial.open(QIODevice::ReadWrite))
	{
		connect(&mSerial, SIGNAL(readyRead()), this, SLOT(readFromSerial()));
		qDebug()<<"open success";
		mLabelStatus->setText("串口打开成功");
	}
	else {
		qDebug() << "open port fail";
		mLabelStatus->setText("串口打开失败");
	}
}

void MainWindow::readFromSerial() {
	while (!mSerial.atEnd())
	{
		qDebug()<<mSerial.readAll();
	}
}
