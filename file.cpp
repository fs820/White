//---------------------------------------
//
//�Z�[�u�E���[�h����[file.cpp]
//Author fuma sato
//
//---------------------------------------

#include"file.h"
#include"stage.h"
#include"meshwall.h"
#include"line.h"
#include"billboard.h"
#include"player.h"

//------------------
//�\�[�g�֐�
//------------------
int *Soat(int* pData)
{
	//�ϐ���錾
	int nRam = 0;

	for (int i = 0; i < MAX_DATA; i++)
	{//��r�Ώ�1
		for (int i2 = i + 1; i2 < MAX_DATA+1; i2++)
		{//��r�Ώ�2
			if (pData[i] < pData[i2])
			{
				//�傫���ق��ɓ���ւ���
				nRam = pData[i];
				pData[i] = pData[i2];
				pData[i2] = nRam;
			}
		}
	}
	return &pData[0];
}
//---------------------------------------
//�Z�[�u����
//---------------------------------------
void SaveFile(int* pData)
{
	FILE* pFile;//�t�@�C���|�C���^��錾

	pFile = fopen(DATA_FILE, "wb");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		fwrite(pData, sizeof(int), MAX_DATA,pFile);//���l����������

		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "�Z�[�u�G���[", "�Z�[�u�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
int *LoadFile(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	static int aData[MAX_DATA] = { 0 };

	for (int i = 0; i < MAX_DATA; i++)
	{
		aData[i] = 0;
	}

	pFile = fopen(DATA_FILE, "rb");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		fread(&aData[0], sizeof(int), MAX_DATA, pFile);//���l����������

		fclose(pFile);//�t�@�C�������
		return &aData[0];
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
		return &aData[0];
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
void LoadStage(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	int nCount = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C��
	pFile = fopen(STAGE_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < STAGE_MAX; nCount++)
		{
			if (fscanf(pFile, "%63s", name) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
			//�I�u�W�F�N�g�ݒu
			SetStage(name, pos, rot, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//��
	pFile = fopen(WALL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < MESHWALL_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
			//�I�u�W�F�N�g�ݒu
			SetMeshWall(pos, rot, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//��
	pFile = fopen(LINE_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < LINE_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
			//�I�u�W�F�N�g�ݒu
			SetLine(pos, rot, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//�r���{�[�h
	pFile = fopen(BILL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < BILLBOARD_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�I�u�W�F�N�g�ݒu
			SetBillboard(pos, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//----------------------------
//
//----------------------------
void LoadModel(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	int nCount = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pFile = fopen(MODEL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < MAX_MODEL; nCount++)
		{
			if (fscanf(pFile, "%63s", name) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}