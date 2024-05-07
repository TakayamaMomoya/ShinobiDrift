//*****************************************************
//
// ���C������[main.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "object.h"
#include "renderer.h"
//#include "backends/imgui_impl_win32.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define CLASS_NAME				"WindowClass"					// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME				"MotionEditor"				// �E�B���h�E�̖��O(�L���v�V����)

//*****************************************************
// �v���g�^�C�v�錾
//*****************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************
// �O���[�o���ϐ��錾
//*****************************************************
int g_nCountFPS;	// FPS�J�E���^�[

//=====================================================
// ���C���֐�
//=====================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	// �}�l�[�W���[�̐錾
	CManager *pManager = NULL;

	//�ϐ��錾
	DWORD dwCurrentTime;				//���ݎ���
	DWORD dwExecLastTime;				//�Ō�ɏ�����������
	DWORD dwFrameCount;					//�t���[���J�E���g
	DWORD dwFPSLastTime;				//�Ō��FPS���v����������

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�t�H���g�|�C���^�EFPS�J�E���^�̏�����
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
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;
	MSG msg;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���E�B���h�E�T�C�Y�ɍ��킹��
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (pManager == NULL)
	{
		// �C���X�^���X����
		pManager = new CManager;

		// �}�l�[�W���[�̏�����
		pManager->Init(hInstance, hWnd, TRUE);
	}

    // Imgui�̏�����
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
    bool bDisp = false;

    ImGui::StyleColorsDark();

    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
    ImGui_ImplDX9_Init(CRenderer::GetInstance()->GetDevice());
    ImGui_ImplWin32_Init(hWnd);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM�QQUIT���b�Z�[�W���󂯎�����烋�[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{// DeirectX�̏���
			
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS�v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPS�𑪒肵�����Ԃ�ۑ�����
				dwFPSLastTime = dwCurrentTime;

				//�t���[���J�E���g�̃N���A
				dwFrameCount = 0;
			}

			//���ݎ����̎擾
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				//�����J�n�̎������v�Z
				dwExecLastTime = dwCurrentTime;

				if (pManager != NULL)
				{
                    ImGui_ImplDX9_NewFrame();
                    ImGui::NewFrame();

                    ImGui::SetNextWindowPos(ImVec2(720, 60),ImGuiCond_Appearing);

                    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Appearing);

                    ImGui::Begin("Motion");

                    // �X�V����
                    pManager->Update();

                    ImGui::End();

					// �`�揈��
					pManager->Draw();
				}

				//FPS�J�E���^�o��
				dwFrameCount++;
			}

			
		}
	}

	if (pManager != NULL)
	{
        // imgui�I��
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX9_Shutdown();
        ImGui::DestroyContext();

		// �I������
		pManager->Uninit();

		// �C���X�^���X�̔j��
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=====================================================
// �E�B���h�E�v���V�[�W��
//=====================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
		// �E�B���h�E�j�����b�Z�[�W���󂯎�����ꍇ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:

		// �m�F���b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{// �C�G�X�̏ꍇ
			// �E�B���h�E�j��
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}

	case WM_KEYDOWN:

       

		switch (wParam)
		{
			// [ESC]�L�[�������ꂽ
		case VK_ESCAPE:

			// �m�F���b�Z�[�W
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{// �C�G�X�̏ꍇ
				// �E�B���h�E�j��
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
// FPS�̎擾
//=====================================================
int GetFPS(void)
{
	return g_nCountFPS;
}