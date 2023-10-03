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
	}
}

void BaslerCamera::RegisterImageEvent(ImageEventHandler* imageEventHandler)
{
	Camera.RegisterImageEventHandler(imageEventHandler, RegistrationMode_Append, Cleanup_Delete);
	Camera.GrabCameraEvents = true;
}

void BaslerCamera::DeregisterImageEvent(ImageEventHandler* imageEventHandler)
{
	try {
		Camera.DeregisterImageEventHandler(imageEventHandler);
	}
	catch (const GenericException& e) {
		cerr << "Error: " << e.GetDescription() << endl;
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

void BaslerCamera::SaveImage(const string& path, const CGrabResultPtr& ptrGrabResult)
{
	CImagePersistence::Save(ImageFileFormat_Bmp, path.c_str(), ptrGrabResult);
}
