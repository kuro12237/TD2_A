#include "WinApp.h"

WinApp *WinApp::GetInstance()
{
	static WinApp instance;
	return &instance;
}


void WinApp::Initialize()
{
	WinApp::GetInstance()->wc_.lpfnWndProc = WinApp::WindowProc;
	WinApp::GetInstance()->wc_.lpszClassName = L"CLEYERA";
	WinApp::GetInstance()->wc_.hInstance = GetModuleHandle(nullptr);
	WinApp::GetInstance()->wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&WinApp::GetInstance()->wc_);

	RECT wrc = { 0,0,
	WinApp::GetInstance()->kWindowWidth,
	WinApp::GetInstance()->kWindowHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	WinApp::GetInstance()->hwnd_=CreateWindow(
		WinApp::GetInstance()->wc_.lpszClassName,
		L"CLEYERA",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		WinApp::GetInstance()->wc_.hInstance,
		nullptr
	);

	ShowWindow(WinApp::GetInstance()->hwnd_, SW_SHOW);

	timeBeginPeriod(1);
}

bool WinApp::WinMsg()
{
	if (PeekMessage(&WinApp::GetInstance()->msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&WinApp::GetInstance()->msg);
		DispatchMessage(&WinApp::GetInstance()->msg);
	}

	if (WinApp::GetInstance()->msg.message != WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	CloseWindow(WinApp::GetInstance()->hwnd_);
}

HWND WinApp::CreateWIND(const int32_t kWidth, const int32_t kHeight, LPCTSTR title, WNDCLASS wc)
{
	wc.lpfnWndProc = WinApp::WindowProc;
	wc.lpszClassName = title;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&wc);

	RECT wrc = { 0,0,
	kWidth,
	kHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	return CreateWindow(
		wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}
	switch (msg)
	{
		//�E�C���h�E���j��
	case WM_DESTROY:
		//OS�ɑ΂��A�v���I����`����
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
