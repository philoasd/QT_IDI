#include "QT_IDI.h"

QT_IDI::QT_IDI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_Camera = std::make_shared<BaslerCamera>();
	InitCameraDevices();
}

QT_IDI::~QT_IDI()
{}

void QT_IDI::on_pushButton_ConnectedCamera_clicked()
{
	int serialNumber = ui.comboBox_CameraDevices->currentIndex();
	m_Camera->ConnectedCamera(serialNumber);
}

void QT_IDI::on_pushButton_DisConnectedCamera_clicked()
{
	m_Camera->DisConnectedCamera();
}

void QT_IDI::on_pushButton_StartGrab_clicked()
{
	if (ui.radioButton_SingleGrab->isChecked())
		m_Camera->StartCapture(0);
	else if (ui.radioButton_ContinueGrab->isChecked())
		m_Camera->StartCapture(1);
}

void QT_IDI::on_pushButton_StopGrab_clicked()
{
	m_Camera->StopCapture();
}

void QT_IDI::InitCameraDevices()
{
	vector<string> devicesInfo = m_Camera->GetCameraDevices();
	for (int index = 0; index < devicesInfo.size(); index++)
	{
		ui.comboBox_CameraDevices->addItem(QString::fromStdString(devicesInfo[index]));
	}
}

void QT_IDI::ShowImage(const CGrabResultData ptrGrabResult)
{

}
