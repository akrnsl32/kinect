// kinect_01.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "kinect_01.h"
#include "kinectSystem.h"


#define MAX_LOADSTRING 100



// ���� ����:
HINSTANCE	_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
HWND		_hWnd;
TCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

POINT _ptMouse;
bool _end = true;
std::mutex _mtx;
bool _LButtonDown = false;
SOCKET hServSock, hClntSock;
//MainSystem _main;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//void setWindowSize(int x, int y, int width, int height);

void thread1(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	kinectSystem _kinect;

	_kinect.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

void thread2()
{
	int portNum = 5000;

	WSADATA wsaData;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return;

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		return;

	//�񵿱� ��ȯ
	//u_long on = TRUE;

	//if(ioctlsocket(hServSock, FIONBIO, &on) == SOCKET_ERROR)
	//	return;
	//

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(portNum);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		return;

	if (listen(hServSock, 5) == SOCKET_ERROR)
		return;

	szClntAddr = sizeof(clntAddr);

	while (_end)
	{
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);

		if (hClntSock == INVALID_SOCKET)
		{
			////����Ȯ�� �񵿱⿡���� ��� ���
			//if (WSAGetLastError() != WSAEWOULDBLOCK)
			//	return;
			//printf(".");
			continue;
		}

		_mtx.lock();

		int i = DATAMANAGER->data.size();
		send(hClntSock, (char*)&i, sizeof(int), 0);
		if (i > 0)
			send(hClntSock, (char*)&DATAMANAGER->data[0], i * sizeof(DataPacket), 0);
		_mtx.unlock();
	}

	// ���� ���� 
	//printf("Closing Socket \n");
	//closesocket(hServSock);
	//closesocket(hClntSock);
	return;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
	//MSG msg;
	//HACCEL hAccelTable;

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_KINECT_01, szWindowClass, MAX_LOADSTRING);

	std::thread t1(thread1, hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	std::thread t2(thread2);

	t1.join();
	closesocket(hServSock);
	closesocket(hClntSock);
	t2.join();

	return 0;
}