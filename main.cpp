//------------------------------------------
//
//�e�N�X�`���\���v���O�����̃��C���̏���[main.cpp]
//Author fuma sato
//
//------------------------------------------

#include"main.h"
#include"camera.h"
#include"light.h"
#include"cursor.h"
#include"fade.h"
#include"rank.h"
#include"result.h"
#include"sound.h"
#include"title.h"
#include"game.h"
#include"shadow.h"
#include"ground.h"
#include"wall.h"
#include"player.h"
#include"input.h"
#include"pause.h"

#define IDI_ICON1 (WORD)"IDI_ICON1"

LPDIRECT3D9 g_pD3D = NULL;//�_�C���N�gX�I�u�W�F�N�g�̃O���[�o���|�C���^��錾
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//�_�C���N�gX�f�o�C�X�̃O���[�o���|�C���^��錾
MODE g_mode = MODE_TITLE;
HINSTANCE g_hInstance;
HWND g_hWnd;
bool g_bStop = false;
bool g_bFullScreen = false;
LPD3DXFONT g_pFont = NULL;//�t�H���g�|�C���^
int g_nCountFPS = 0;//FPS�J�E���^
bool g_bDebug = true;

//------------------------
//���C���֐�
//------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	//�E�C���h�E�ݒ�
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//�������T�C�Y
		CS_CLASSDC,//�X�^�C��
		WindowProc,//�v���V�[�W��
		0,//0
		0,//0
		hInstance,//�C���X�^���X�n���h��
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 3),//�w�i�F
		NULL,//���j���[�o�[
		CLASS_NAME,//�N���X�̖��O
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1))//�A�C�R��
	};

	srand((int)time(NULL));//�����ݒ�
	HWND hWnd = nullptr;//�n���h��
	MSG msg = { 0 };//���b�Z�[�W
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//�E�C���h�E�T�C�Y�̐ݒ�
	DWORD dwCurrntTime;//���݂̃V�X�e������
	DWORD dwExceLastTime;//�O��̃V�X�e������

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈�̃T�C�Y����
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx
	(
		0,//�X�^�C��
		CLASS_NAME,//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�X�^�C��
		CW_USEDEFAULT,//������W
		CW_USEDEFAULT,//�E�����W
		(rect.right - rect.left),//��
		(rect.bottom - rect.top),//����
		NULL,//�e
		NULL,//���j���[ID
		hInstance,//�C���X�^���X�n���h��
		NULL//�쐬�f�[�^
	);
	// �E�B���h�E�̃A�C�R����ݒ�
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

	g_hInstance = hInstance;
	g_hWnd = hWnd;

	while (ShowCursor(FALSE) >= 0);
	ConfineCursorToWindow(hWnd);

	//�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#ifdef _DEBUG

	if (FAILED(Init(hInstance, hWnd, TRUE)))//����������
	{
		return E_FAIL;
	}

#endif

#ifndef _DEBUG

	if (FAILED(Init(hInstance, hWnd, FALSE)))//����������
	{
		return E_FAIL;
	}

#endif

	timeBeginPeriod(1);//����\�̐ݒ�
	dwCurrntTime = 0;//��������
	dwExceLastTime = timeGetTime();//�J�n�������L�^

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)//�I�����b�Z�[�W
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (!g_bStop)
			{
				dwCurrntTime = timeGetTime();//�������擾
				if ((dwCurrntTime-dwFPSLastTime)>=FPS_TIME)
				{//0.5�b
					//FPS�Z�o
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrntTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrntTime;
					dwFrameCount = 0;
				}

				if ((dwCurrntTime - dwExceLastTime) >= FPS)//�ݒ肵���Ԋu���󂢂���
				{//60����1
					dwExceLastTime = dwCurrntTime;//����̍X�V�������L�^

					Update();//�X�V����
					Draw();//�`�揈��

					dwFrameCount++;
				}
			}
		}
	}

	Uninit();//�I������

	//�E�C���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);//����\��߂�

	ReleaseCursor();
	while (ShowCursor(TRUE) < 0);

	//�I��
	return (int)msg.wParam;
}

//--------------------------
//�E�C���h�E�v���V�[�W��
//--------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID = 0;//�Ԃ�l�̊i�[
	static bool bFreeMause=false;

	switch (uMsg)
	{
	case WM_DESTROY://�j��
		//WM_QUIT���b�Z�[�W
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://�L�[����
		switch (wParam)
		{
		case VK_ESCAPE://ESC�L�[
			ReleaseCursor();
			while (ShowCursor(TRUE) < 0);
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W....�����??...���Ԃ�...............�����炭...............", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//�j��(WM_DESTROY)
				DestroyWindow(hWnd);
			}
			else
			{
				while (ShowCursor(FALSE) >= 0);
				ConfineCursorToWindow(hWnd);
			}
			break;
		case VK_F2:
			g_bDebug = !g_bDebug;
			break;
		case VK_F4:
			if (bFreeMause)
			{
				bFreeMause = false;

				while (ShowCursor(FALSE) >= 0);
				ConfineCursorToWindow(hWnd);
			}
			else
			{
				bFreeMause = true;

				ReleaseCursor();
				while (ShowCursor(TRUE) < 0);
			}
			break;
		case VK_F5:
			CrCursor(!GetCursorIn()->bUse);
			break;
		}
		break;
	case WM_SETFOCUS:
		g_bStop = false;
		ConfineCursorToWindow(hWnd);
		break;
	case WM_KILLFOCUS:
		g_bStop = true;
		break;
	}
	//�K�v�f�[�^��Ԃ�
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//------------------------------
//����������
//------------------------------
HRESULT Init(HINSTANCE hInstanse, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�_�C���N�gX�f�B�X�v���C���[�h�̕ϐ��錾
	D3DPRESENT_PARAMETERS d3dpp;//�_�C���N�gX�p�����[�^�̕ϐ��錾

	//�I�u�W�F�N�g����
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));//0��~���l�߂�

	//�o�b�N�o�b�t�@�̐ݒ�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//�f�o�C�X����
	if (FAILED(g_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{
		if (FAILED(g_pD3D->CreateDevice
		(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice
		)))
		{
			if (FAILED(g_pD3D->CreateDevice
			(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice
			)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�����x
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�p�t�H���g����
	D3DXCreateFont
	(
	    g_pD3DDevice,
		FONT_SIZE, 0,0,0,
		FALSE,SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		"Terminal",
		&g_pFont
	);

	//�I�u�W�F�N�g�̏���������
	if (FAILED(InitKeyboard(hInstanse, hWnd)))//�L�[����
	{
		return E_FAIL;
	}
	if (FAILED(InitMouse(hInstanse, hWnd)))//�L�[����
	{
		return E_FAIL;
	}
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}
	if (FAILED(InitdJoypad(hInstanse, hWnd)))//�L�[����
	{
		return E_FAIL;
	}
	InitSound(hWnd);
	InitLight();
	InitCamera();
	InitCursor();
	InitPause();

	InitFade(g_mode);

	return S_OK;
}

//------------------------------
//�I������
//------------------------------
void Uninit(void)
{
	EndSound();

	UninitPause();
	UninitCursor();
	UninitSound();
	UninitCamera();
	UninitLight();
	UninitFade();

	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRank();
		break;
	}

	UninitdJoypad();//d�p�b�h����
	UninitJoypad();//�p�b�h����
	UninitMouse();//�}�E�X����
	UninitKeyborad();//�L�[����

	//�f�o�b�O�t�H���g�j��
	if (g_pFont!=NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//�f�o�C�X�j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//�I�u�W�F�N�g�j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//------------------------------
//�X�V����
//------------------------------
void Update(void)
{
	UpdateKeyborad();//�L�[����
	UpdateMouse();//�}�E�X����
	UpdateJoypad();//�p�b�h����
	UpdatedJoypad();//d�p�b�h����

	UpdateFade();
	UpdateCursor();
	UpdateLight();
	UpdatePause();
	UpdateCamera();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANK:
		UpdateRank();
		break;
	}
}

//------------------------------
//�`�揈��
//------------------------------
void Draw(void)
{
	Camera* pCamera = GetCamera();

	for (int nCount = 0; nCount < CAMERA_NUM; nCount++, pCamera++)
	{
		g_pD3DDevice->SetViewport(&pCamera->viewport);

		g_pD3DDevice->Clear//�t�����g�o�b�t�@�̃N���A
		(
			0,
			NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0),
			1.0f,
			0
		);

		if (SUCCEEDED(g_pD3DDevice->BeginScene()))//�`��J�n
		{
			SetCamera(nCount);

			//�I�u�W�F�N�g�`��
			switch (g_mode)
			{
			case MODE_TITLE:
				DrawTitle();
				break;
			case MODE_GAME:
				DrawGame();
				break;
			case MODE_RESULT:
				DrawResult();
				break;
			case MODE_RANK:
				DrawRank();
				break;
			}

			DrawPause();
			DrawCursor();
			DrawFade();


#ifdef _DEBUG

			if (g_bDebug)
			{
				DrawDebug();
			}

#endif

			g_pD3DDevice->EndScene();//�`��I��
		}
		//�o�b�N�o�b�t�@�ɕ\����؂�ւ���
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

//------------------------
//���[�h�̐؂�ւ�
//------------------------
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRank();
		break;
	}

	g_mode = mode;

	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_RANK:
		InitRank();
		break;
	}
}

//------------------------
//�f�o�C�X�̎擾
//------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//-----------------
//���[�h�̎擾
//-----------------
MODE GetMode(void)
{
	return g_mode;
}

//-----------------
//�n���h���̎擾
//-----------------
HWND GethWnd(void)
{
	return g_hWnd;
}

//-----------------
//�C���X�^���X�n���h���擾
//-----------------
HINSTANCE GethInstanse(void)
{
	return g_hInstance;
}

//------------------
//�}�E�X����
//------------------
void ConfineCursorToWindow(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	rect.left += 10;
	rect.top += 10;
	rect.right -= 10;
	rect.bottom -= 10;

	MapWindowPoints(hWnd, NULL, (POINT*)&rect, 2);
	ClipCursor(&rect);
}

//-----------------
//�}�E�X���
//-----------------
void ReleaseCursor(void)
{
	ClipCursor(NULL); // ����������
}

//--------------------
//
//�f�o�b�O�p
//
//--------------------

//--------------------
//�f�o�b�O�\��
//--------------------
void DrawDebug(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024] = { '\0' };
	float LightAngle = GetLightAngle();
	Camera* pCamera = GetCamera();
	Player* pPlayer = GetPlayer();

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���C�g�A���O��:%f\n", LightAngle);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�J�����A���O��Y:%f\n", pCamera->rot.y);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�J�����A���O��X:%f\n", pCamera->rot.x);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���_:%f %f %f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�ڕW���_:%f %f %f\n", pCamera->posVDest.x, pCamera->posVDest.y, pCamera->posVDest.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�����_:%f %f %f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�ڕW�����_:%f %f %f\n", pCamera->posRDest.x, pCamera->posRDest.y, pCamera->posRDest.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "����:%f\n", pCamera->fDistance);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�ʒu:%f %f %f\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�ߋ��ʒu:%f %f %f\n", pPlayer->posOld.x, pPlayer->posOld.y, pPlayer->posOld.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�ړ�:%f %f %f\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[��]:%f %f %f\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[��]�ڕW:%f %f %f\n", pPlayer->Destrot.x, pPlayer->Destrot.y, pPlayer->Destrot.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�X�P�[��:%f %f %f\n", pPlayer->scale.x, pPlayer->scale.y, pPlayer->scale.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�̗�:%d\n", pPlayer->nLife);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�̗�:%f\n", (float)((float)pPlayer->nLife / (float)PLAYER_LIFE));

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[���:%d\n", pPlayer->state);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�ő咸�_:%f %f %f\n", pPlayer->aModel[0].vtxMax.x, pPlayer->aModel[0].vtxMax.y, pPlayer->aModel[0].vtxMax.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�v���C���[�ŏ����_:%f %f %f\n", pPlayer->aModel[0].vtxMin.x, pPlayer->aModel[0].vtxMin.y, pPlayer->aModel[0].vtxMin.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�e:%d\n", pPlayer->nIdxShadow);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���_��:%d\n", pPlayer->aModel[0].nNumVtx);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���[�V�������[�v:%s\n", pPlayer->bLoopMotion ? "true" : "false");

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���[�V�����^�C�v:%d\n", pPlayer->motionType);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���[�V������:%d\n", pPlayer->nNumMotion);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�L�[��:%d\n", pPlayer->nNumKey);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "�L�[�ԍ�:%d\n", pPlayer->nKey);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "���[�V�����J�E���g:%d\n", pPlayer->nCounterMotion);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//������̑��
	snprintf(&aStr[0], sizeof(aStr), "����:%d\n", GetClearTime());

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;
}