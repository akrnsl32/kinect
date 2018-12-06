// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#include <thread>
#include <mutex>

#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <list>
#include <string>
#include <set>

#include <d2d1.h>
#include <Kinect.h>
#include <iostream>
#include <fstream>

#pragma comment (lib, "d2d1.lib")

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
//using namespace std;

#include "commonMacroFrunction.h"
#include "imageManager.h"
#include "keyManager.h"
#include "timeManager.h"
//server
struct DataPacket {
	double x;
	double y;
};
#include "DataManager.h"

//������ ��Ÿ�� ����
#define WINNAME (LPTSTR)(TEXT("KinectSenssor"))
#define WINSTARTX 200
#define WINSTARTY 0
#define WINSIZEX 920
#define WINSIZEY 532
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define IMAGEMANAGER imageManager::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()

#define SAFE_DELETE(p)	{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = NULL;}}

//Ű��Ʈ ȭ��
#define		_Color_Width_			1920
#define		_Color_Height_			1080
#define		_WndTitle_Color_		"Window_for_RGB"

#define		_IR_Width_			512
#define		_IR_Height_			424
#define		_WndTitle_IR_		"Window_for_InfraRed(IR)"
#define		_WndTitle_Depth_		"Window_for_Depth"

#define Button_Width 60
#define Button_Height 30

#define Progress_Width 255
#define Progress_Height 6

#define ProgressBar_Width  20
#define ProgressBar_Height 20 

#define POINT_Width 20
#define POINT_Height 20

#define IMAGE_TOP_MAGIN 32
#define IMAGE_MAGIN 72
#define IMAGE_Width 352
#define IMAGE_HEIGHT 288

#define CHECKBOX_SIZE 20

#define DEFAULT_DEPTH_MIN 2
#define DEFAULT_DEPTH_MAX 30
#define DEFAULT_BLUR 4
#define DEFAULT_BLUR_CUT 128

#define MAX_DEPTH 255
#define MAX_BLUR 30
#define MAX_BLUR_CUT 255

#define MAX_SIZE 255
#define MIN_SIZE 0

#define InfraredSourceValueMaximum static_cast<float>(USHRT_MAX)

#define InfraredOutputValueMinimum 0.01f 

#define InfraredOutputValueMaximum 1.0f

#define InfraredSceneValueAverage 0.08f

#define InfraredSceneStandardDeviations 3.0f

extern HINSTANCE	_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern bool			_end;
extern std::mutex	_mtx;
extern bool			_LButtonDown;


template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
