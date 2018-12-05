// kinect_01.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "kinect_01.h"
#include "kinectSystem.h"


#define MAX_LOADSTRING 100



// 전역 변수:
HINSTANCE	_hInstance;                                // 현재 인스턴스입니다.
HWND		_hWnd;
TCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

POINT _ptMouse;
bool _end = true;
std::mutex _mtx;
bool _LButtonDown = false;
SOCKET hServSock, hClntSock;
//MainSystem _main;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

	//비동기 전환
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
			////에러확인 비동기에러일 경우 통과
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

	// 소켓 종료 
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

    // TODO: 여기에 코드를 입력합니다.
	//MSG msg;
	//HACCEL hAccelTable;

    // 전역 문자열을 초기화합니다.
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