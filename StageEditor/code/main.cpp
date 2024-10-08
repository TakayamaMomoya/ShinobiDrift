//*****************************************************
//
// メイン処理[main.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "object.h"
#include "renderer.h"
#include <time.h>

//*****************************************************
// マクロ定義
//*****************************************************
#define CLASS_NAME				"WindowClass"					// ウィンドウクラスの名前
#define WINDOW_NAME				"Jaganbie"				// ウィンドウの名前(キャプション)

//*****************************************************
// プロトタイプ宣言
//*****************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************
// グローバル変数宣言
//*****************************************************
int g_nCountFPS;	// FPSカウンター

//=====================================================
// メイン関数
//=====================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//乱数シード値の設定
	srand((unsigned int)time(0));

	ShowCursor(true);

	// マネージャーの宣言
	CManager *pManager = nullptr;
	
	DWORD dwCurrentTime;				//現在時刻
	DWORD dwExecLastTime;				//最後に処理した時刻
	DWORD dwFrameCount;					//フレームカウント
	DWORD dwFPSLastTime;				//最後にFPSを計測した時間

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//フォントポインタ・FPSカウンタの初期化
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		CLASS_NAME,
		LoadIcon(nullptr,IDI_APPLICATION),
	};

	HWND hWnd;
	MSG msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域をウィンドウサイズに合わせる
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (pManager == nullptr)
	{
		// インスタンス生成
		pManager = new CManager;

		// マネージャーの初期化
		pManager->Init(hInstance, hWnd, TRUE);
	}

	// Imguiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	bool bDisp = false;

	// imgui設定
	ImGui::StyleColorsDark();

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// Setup Platform/Renderer backends
	ImGui_ImplDX9_Init(CRenderer::GetInstance()->GetDevice());
	ImGui_ImplWin32_Init(hWnd);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// WM＿QUITメッセージを受け取ったらループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DeirectXの処理
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPS計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSを測定した時間を保存する
				dwFPSLastTime = dwCurrentTime;

				//フレームカウントのクリア
				dwFrameCount = 0;
			}

			//現在時刻の取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				float fDeltaTime = ((float)dwCurrentTime - (float)dwExecLastTime) * 0.001f;

				//処理開始の時刻を計算
				dwExecLastTime = dwCurrentTime;

				if (pManager != nullptr)
				{
					// ティックの設定
					CManager::SetTick(fDeltaTime);

					ImGui_ImplDX9_NewFrame();
					ImGui::NewFrame();

					ImGui::SetNextWindowPos(ImVec2(720, 60), ImGuiCond_Appearing);

					ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Appearing);

					// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
					{
						static float f = 0.0f;
						static int counter = 0;

						ImGui::Begin("Edit");

						// 更新処理
						pManager->Update();

						ImGui::End();
					}

					// 描画処理
					pManager->Draw();
				}

				//FPSカウンタ経過
				dwFrameCount++;
			}
		}
	}

	if (pManager != NULL)
	{
		// imgui終了
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();

		// 終了処理
		pManager->Uninit();

		// インスタンスの破棄
		delete pManager;
		pManager = NULL;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=====================================================
// ウィンドウプロシージャ
//=====================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
		// ウィンドウ破棄メッセージを受け取った場合
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// 確認メッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{// イエスの場合
			// ウィンドウ破棄
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}

	case WM_KEYDOWN:
		switch (wParam)
		{
			// [ESC]キーが押された
		case VK_ESCAPE:

			// 確認メッセージ
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{// イエスの場合
				// ウィンドウ破棄
				DestroyWindow(hWnd);
			}
			break;
		}

		break;
	}

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=====================================================
// FPSの取得
//=====================================================
int GetFPS(void)
{
	return g_nCountFPS;
}