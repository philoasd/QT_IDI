#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_IDI.h"
#include <memory>

#include <BaslerCamera.h>
#include <BaseCmaera.h>
#include <pylon/PylonIncludes.h>


class QT_IDI : public QMainWindow
{
	Q_OBJECT

public:
	QT_IDI(QWidget* parent = nullptr);
	~QT_IDI();

private slots:
	void on_pushButton_ConnectedCamera_clicked();// 连接相机
	void on_pushButton_DisConnectedCamera_clicked();// 断开相机
	void on_pushButton_StartGrab_clicked();// 开始采集
	void on_pushButton_StopGrab_clicked();// 停止采集

private:
	Ui::QT_IDIClass ui;
	std::shared_ptr<BaseCmaera> m_Camera;// 相机对象
	std::shared_ptr<ImageEventHandler> m_ImageEventHandler;// 相机回调函数对象
private:
	void InitCameraDevices();// 初始化相机设备
	void ShowImage(const CGrabResultPtr& ptrGrabResult);// 显示图像
};