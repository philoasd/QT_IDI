#pragma once
#include <pylon/PylonIncludes.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "BaseCmaera.h"

using namespace Pylon;
using namespace std;

class __declspec(dllexport) BaslerCamera : public BaseCmaera
{
public:
	BaslerCamera();
	vector<string> GetCameraDevices() override;
	void ConnectedCamera(int serialNumber) override;
	void DisConnectedCamera() override;
	void StartCapture(int flag) override;
	void StopCapture() override;

public:


private:
	CInstantCamera Camera;
	DeviceInfoList_t Devices;
};

/// <summary>
/// 相机回调函数
/// </summary>
class ImageEventHandler : public CImageEventHandler
{
public:
	virtual void OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult) override
	{
		if (ptrGrabResult->GrabSucceeded())
		{
			
		}
	}
};