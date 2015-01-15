#ifndef W_MAINWINDOW
#define W_MAINWINDOW
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QSerialPort>

class MainWindow: public QWidget{
	Q_OBJECT
public:
	MainWindow(QWidget *parent=0);
	~MainWindow();

public slots:
	void onStop();
	void onStartCW();
	void onStartCCW();
	void onOpenSerialPort();
	void readFromSerial();
private:
	QLabel *mLabelSpeed;
	QLabel *mLabelArc;
	QLineEdit *mEditSpeed;
	QLineEdit *mEditArc;
	QPushButton *mButtonStartCW;
	QPushButton *mButtonStartCCW;
	QPushButton *mButtonStop;
	QVBoxLayout *mMainLayout;
	QHBoxLayout *mUpLayout;
	QHBoxLayout *mMiddleLayout;
	QHBoxLayout *mLowLayout;
	QComboBox *mComboBoxPortList;
	QPushButton *mButtonOpenPort;
	QLabel *mLabelStatus;
	QSerialPort mSerial;

};

#endif
