#include "pch.h"
#include "BaslerCamera.h"

BaslerCamera::BaslerCamera()
{
	PylonInitialize();
}

vector<string> BaslerCamera::GetCameraDevices()
{
	vector<string> devicesInfo;
	if (CTlFactory::GetInstance().EnumerateDevices(Devices) > 0)
	{
		for (int index = 0; index < Devices.size(); index++)
		{
			Camera.Attach(CTlFactory::GetInstance().CreateDevice(Devices[index]));
			string serialNumber = (string)Camera.GetDeviceInfo().GetSerialNumber();
			devicesInfo.push_back((string)Camera.GetDeviceInfo().GetModelName() + "(" + serialNumber + ")");
		}
	}
	return devicesInfo;
}

void BaslerCamera::ConnectedCamera(int serialNumber)
{
	if (serialNumber >= 0) {
		// 连接相机
		Camera.Attach(CTlFactory::GetInstance().CreateDevice(Devices[serialNumber]));

		// 注册相机回调函数
		Camera.RegisterImageEventHandler(new ImageEventHandler, RegistrationMode_Append, Cleanup_Delete);
		Camera.GrabCameraEvents = true;
	}
}

void BaslerCamera::DisConnectedCamera()
{
	if (Camera.IsGrabbing())
	{
		Camera.StopGrabbing();
	}
	if (Camera.IsOpen())
	{
		Camera.Close();
	}
}

void BaslerCamera::StartCapture(int flag)
{
	if (!Camera.IsOpen())
	{
		Camera.Open();
	}
	if (Camera.IsGrabbing())
	{
		Camera.StopGrabbing();
	}

	if (flag)
	{
		Camera.StartGrabbing(GrabStrategy_LatestImageOnly, GrabLoop_ProvidedByInstantCamera);
	}
	else
	{
		Camera.StartGrabbing(1, GrabStrategy_LatestImageOnly, GrabLoop_ProvidedByInstantCamera);
	}
}

void BaslerCamera::StopCapture()
{
	Camera.StopGrabbing();
}
