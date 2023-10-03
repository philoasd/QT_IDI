#include "QT_IDI.h"

QT_IDI::QT_IDI(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_Camera = std::make_shared<BaslerCamera>();// 实例化相机对象

	m_ImageEventHandler = std::make_shared<ImageEventHandler>(callback);// 实例化相机回调函数对象
	InitCameraDevices();
}

QT_IDI::~QT_IDI()
{

}

void QT_IDI::on_pushButton_ConnectedCamera_clicked()
{
	int serialNumber = ui.comboBox_CameraDevices->currentIndex();
	m_Camera->ConnectedCamera(serialNumber);
	callback = [&](const CGrabResultPtr& ptrGrabResult) {
		ShowImage(ptrGrabResult);
		};

	m_Camera->RegisterImageEvent(m_ImageEventHandler.get());
}

void QT_IDI::on_pushButton_DisConnectedCamera_clicked()
{
	m_Camera->DisConnectedCamera();
	//m_Camera->DeregisterImageEvent(m_ImageEventHandler.get());
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

void QT_IDI::ShowImage(const CGrabResultPtr& ptrGrabResult)
{
	if (ptrGrabResult->GrabSucceeded())
	{
		int width = ptrGrabResult->GetWidth();
		int height = ptrGrabResult->GetHeight();
		void* buffer = ptrGrabResult->GetBuffer();

		QImage image((uchar*)buffer, width, height, QImage::Format_Mono);

		// 图片自适应窗口大小
		QSize size = ui.label_Image->size();
		QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(size, Qt::KeepAspectRatio);
		ui.label_Image->setPixmap(scaledPixmap);
	}
}
