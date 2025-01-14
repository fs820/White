//------------------------------------------
//
//�^�C�g���̏���[title.cpp]
//Author fuma sato
//
//------------------------------------------

#include"title.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"cursor.h"
#include"camera.h"

#include"shadow.h"
#include"billboard.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"meshwall.h"
#include"line.h"
#include"snowball.h"

#define DEMO_TIME (600)
#define TITLE_MAX (3)
#define TITLE_TEX_MAX (4)
#define SELECT_WIDTH (512)//��
#define SELECT_HEIGHT (128)//����
#define TITLE_WIDTH (640)
#define TITLE_HEIGHT (360)
#define ROGO_WIDTH (640)
#define ROGO_HEIGHT (360)
#define U_MAX_T (1)
#define V_MAX_T (6)

typedef enum
{
	TITLESTATE_NONE = 0,
	TITLESTATE_NORMAL,
	TITLESTATE_SELECT,
	TITLESTATE_MAX
}TITLESTATE;

typedef enum
{
	SELECT_PLAY = 0,
	SELECT_VERSUS,
	SELECT_TUTO,
	SELECT_RANK,
	SELECT_OPTION,
	SELECT_EXIT,
	SELECT_MAX
}SELECT;

LPDIRECT3DTEXTURE9 g_apTextureTitle[TITLE_TEX_MAX] = { NULL };//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//�o�b�t�@�̃|�C���^
TITLESTATE g_TitleState=TITLESTATE_NONE;
D3DXVECTOR3 g_RogoPos;

//--------------------
//����������
//--------------------
void InitTitle(void)
{
	InitShadow();
	InitStage();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitMeshWall();
	InitBillboard();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_2D* pVtx;//���_���|�C���^
	D3DXVECTOR3 posSelect;//�X�R�A�̈ʒu

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX*TITLE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_ROGO,
		&g_apTextureTitle[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_ROGOTXT,
		&g_apTextureTitle[1]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_START,
		&g_apTextureTitle[2]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SELECT,
		&g_apTextureTitle[3]
	);

	g_TitleState = TITLESTATE_NONE;
	g_RogoPos = D3DXVECTOR3(SCREEN_WIDTH/2,-TITLE_HEIGHT,0.0f);
	posSelect= D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT * (3.2f/4.0f), 0.0f);

	//���
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��
	SetSnowBall(D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//�X�e�[�W
	LoadStage();

	//�J����
	ViewCamera(CAMERA_NUM);

	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += VT_MAX;

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += VT_MAX;

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`��
	if (g_TitleState == TITLESTATE_SELECT)
	{
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, UV_DEF / V_MAX_T);
	pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T, UV_DEF / V_MAX_T);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	PlaySound(SOUND_LABEL_BGM);

	g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//------------------
//�I������
//------------------
void UninitTitle(void)
{
	//�T�E���h
	EndSound();

	UninitShadow();
	UninitStage();
	UninitMeshField();
	UninitLine();
	UninitCylinder();
	UninitSphere();
	UninitSnowBall();
	UninitMeshWall();
	UninitBillboard();

	//�e�N�X�`���̔j��
	for (int i = 0; i < TITLE_TEX_MAX; i++)
	{
		if (g_apTextureTitle[i] != NULL)
		{
			g_apTextureTitle[i]->Release();
			g_apTextureTitle[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//--------------
//�X�V����
//--------------
void UpdateTitle(void)
{
	static int DemoCnt = 0;
	static SELECT SelectNew = SELECT_PLAY;
	VERTEX_2D* pVtx;//���_���|�C���^

	if (g_TitleState==TITLESTATE_NONE)
	{
		g_RogoPos.y += 3;

		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


		pVtx += VT_MAX;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
		g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

		if (g_RogoPos.y >= SCREEN_HEIGHT / 4)
		{
			g_TitleState = TITLESTATE_NORMAL;
			PlaySound(SOUND_LABEL_TITLE);
		}

		if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true)
		{
			FADE fade;
			fade = GetFade();
			if (fade == FADE_NONE)
			{
				g_RogoPos.y = SCREEN_HEIGHT / 4;
				g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

				//���W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


				pVtx += VT_MAX;

				//���W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
				g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
				g_TitleState = TITLESTATE_NORMAL;
				PlaySound(SOUND_LABEL_TITLE);
			}
		}
		else if (GetMouseTrigger(MOUSE_LEFT) == true)
		{
			FADE fade;
			fade = GetFade();
			if (fade == FADE_NONE)
			{
				g_RogoPos.y = SCREEN_HEIGHT / 4;
				g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

				//���W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


				pVtx += VT_MAX;

				//���W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
				g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
				g_TitleState = TITLESTATE_NORMAL;
				PlaySound(SOUND_LABEL_TITLE);
			}
		}

		for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
		{
			if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
			{
				if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i) == true || GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						g_RogoPos.y = SCREEN_HEIGHT / 4;
						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


						pVtx += VT_MAX;

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
						g_TitleState = TITLESTATE_NORMAL;
						PlaySound(SOUND_LABEL_TITLE);
					}
				}

			}
			else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
			{
				if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i) == true|| GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) == true)
				{
					FADE fade;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						g_RogoPos.y = SCREEN_HEIGHT / 4;
						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


						pVtx += VT_MAX;

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
						g_TitleState = TITLESTATE_NORMAL;
						PlaySound(SOUND_LABEL_TITLE);
					}
				}
			}
			else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
			{
				if (GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i) == true|| GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						g_RogoPos.y = SCREEN_HEIGHT / 4;
						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


						pVtx += VT_MAX;

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
						g_TitleState = TITLESTATE_NORMAL;
						PlaySound(SOUND_LABEL_TITLE);
					}
				}
			}
			else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
			{
				if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i) == true|| GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						g_RogoPos.y = SCREEN_HEIGHT / 4;
						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y - TITLE_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + TITLE_WIDTH / 2, g_RogoPos.y + TITLE_HEIGHT / 2, 0.0f);


						pVtx += VT_MAX;

						//���W�ݒ�
						pVtx[0].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[1].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 - ROGO_HEIGHT / 2, 0.0f);
						pVtx[2].pos = D3DXVECTOR3(g_RogoPos.x - ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						pVtx[3].pos = D3DXVECTOR3(g_RogoPos.x + ROGO_WIDTH / 2, g_RogoPos.y + ROGO_WIDTH / 2 + ROGO_HEIGHT / 2, 0.0f);
						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
						g_TitleState = TITLESTATE_NORMAL;
						PlaySound(SOUND_LABEL_TITLE);
					}
				}
			}
		}
	}

	if (g_TitleState == TITLESTATE_NORMAL)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_START,CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true)
			{
				g_TitleState = TITLESTATE_SELECT;
				DemoCnt = 0;

				g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

				pVtx += VT_MAX*2;
				//�e�N�X�`��
				pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
				pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
				pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
				pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

				g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
			}
			else if (GetMouseTrigger(MOUSE_LEFT) == true)
			{
				CURSOR* pCursor;

				g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

				pCursor = GetCursorIn();
				if (pCursor->pos.x >= (pVtx + VT_MAX*2)[0].pos.x && pCursor->pos.x <= (pVtx + VT_MAX*2)[3].pos.x && pCursor->pos.y >= (pVtx + VT_MAX*2)[0].pos.y && pCursor->pos.y <= (pVtx + VT_MAX*2)[3].pos.y)
				{
					g_TitleState = TITLESTATE_SELECT;
					DemoCnt = 0;

					pVtx += VT_MAX*2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
				}
				g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
			}

			DemoCnt++;
		}
	}
	else if (g_TitleState == TITLESTATE_SELECT)
	{
		if (GetKeyboradTrigger(DIK_BACK) == true || GetJoykeyTrigger(JOYKEY_BACK, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_B, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_RIGHT) == true)
		{
			g_TitleState = TITLESTATE_NORMAL;

			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

			pVtx += VT_MAX*2;
			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

		}
		else if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
		{
			FADE fade;
			switch (SelectNew)
			{
			case SELECT_PLAY:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM);
					//�ؑ�
					SetFade(MODE_GAME);
				}
				break;
			case SELECT_VERSUS:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM);
					//�ؑ�
					SetFade(MODE_VS);
				}
				break;
			case SELECT_TUTO:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM);
					//�ؑ�
					SetFade(MODE_TUTO);

				}
				break;
			case SELECT_RANK:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM);
					//�ؑ�
					SetFade(MODE_RANK);

				}
				break;
			case SELECT_OPTION:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM);
					//�ؑ�
					SetFade(MODE_OPTION);

				}
				break;
			case SELECT_EXIT:
				DemoCnt = 0;
				fade = GetFade();
				if (fade == FADE_NONE)
				{

					//�ؑ�
					HWND hWnd;
					hWnd = GethWnd();
					PostMessage(hWnd, WM_QUIT, 0, 0);
				}
				break;
			}
		}
		else if (GetMouseTrigger(MOUSE_LEFT) == true)
		{
			CURSOR* pCursor;

			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

			pCursor = GetCursorIn();
			if (pCursor->pos.x >= (pVtx + VT_MAX*2)[0].pos.x && pCursor->pos.x <= (pVtx + VT_MAX * 2)[3].pos.x && pCursor->pos.y >= (pVtx + VT_MAX * 2)[0].pos.y && pCursor->pos.y <= (pVtx + VT_MAX * 2)[3].pos.y)
			{
				FADE fade;
				switch (SelectNew)
				{
				case SELECT_PLAY:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						SetFade(MODE_GAME);
					}

					break;
				case SELECT_VERSUS:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						SetFade(MODE_VS);
					}
					break;
				case SELECT_TUTO:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						SetFade(MODE_TUTO);

					}
					break;
				case SELECT_RANK:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						SetFade(MODE_RANK);

					}
					break;
				case SELECT_OPTION:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						SetFade(MODE_OPTION);

					}
					break;
				case SELECT_EXIT:
					DemoCnt = 0;
					fade = GetFade();
					if (fade == FADE_NONE)
					{
						//�T�E���h
						StopSound(SOUND_LABEL_BGM);
						//�ؑ�
						HWND hWnd;
						hWnd = GethWnd();
						PostMessage(hWnd, WM_QUIT, 0, 0);
					}
					break;
				}
			}
			g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

		}
		else if (GetKeyboradTrigger(DIK_UP) == true || GetKeyboradTrigger(DIK_W) == true || GetJoykeyTrigger(JOYKEY_UP, CONTROLLER_MAX) == true || JoyStickTrigger(DIRESTICK_UP,STICK_LEFT,CONTROLLER_MAX) || GetMouseWheel() > 0.0f)
		{
			switch (SelectNew)
			{
			case SELECT_PLAY:
				SelectNew = SELECT_EXIT;
				break;
			case SELECT_VERSUS:
				SelectNew = SELECT_PLAY;
				break;
			case SELECT_TUTO:
				SelectNew = SELECT_VERSUS;
				break;
			case SELECT_RANK:
				SelectNew = SELECT_TUTO;
				break;
			case SELECT_OPTION:
				SelectNew = SELECT_RANK;
				break;
			case SELECT_EXIT:
				SelectNew = SELECT_OPTION;
				break;
			}

			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

			pVtx += VT_MAX * 2;
			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
			pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
			pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
			pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

			g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

		}
		else if (GetKeyboradTrigger(DIK_DOWN) == true || GetKeyboradTrigger(DIK_S) == true || GetJoykeyTrigger(JOYKEY_DOWN, CONTROLLER_MAX) == true || JoyStickTrigger(DIRESTICK_DOWN, STICK_LEFT, CONTROLLER_MAX) || GetMouseWheel() < 0.0f)
		{
			switch (SelectNew)
			{
			case SELECT_PLAY:
				SelectNew = SELECT_VERSUS;
				break;
			case SELECT_VERSUS:
				SelectNew = SELECT_TUTO;
				break;
			case SELECT_TUTO:
				SelectNew = SELECT_RANK;
				break;
			case SELECT_RANK:
				SelectNew = SELECT_OPTION;
				break;
			case SELECT_OPTION:
				SelectNew = SELECT_EXIT;
				break;
			case SELECT_EXIT:
				SelectNew = SELECT_PLAY;
				break;
			}

			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

			pVtx += VT_MAX * 2;
			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
			pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
			pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
			pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

			g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

		}
	}

	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (g_TitleState == TITLESTATE_NORMAL)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i) == true)
					{
						g_TitleState = TITLESTATE_SELECT;
						DemoCnt = 0;

						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						pVtx += VT_MAX * 2;
						//�e�N�X�`��
						pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
						pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
					}

					DemoCnt++;
				}
			}
			else
			{
				if (GetdJoykeyTrigger(ELEKEY_BACK, (CONTROLLER)i) == true)
				{
					g_TitleState = TITLESTATE_NORMAL;

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					switch (SelectNew)
					{
					case SELECT_PLAY:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_GAME);
						}
						break;
					case SELECT_VERSUS:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_VS);
						}
						break;
					case SELECT_TUTO:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_TUTO);

						}
						break;
					case SELECT_RANK:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_RANK);

						}
						break;
					case SELECT_OPTION:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_OPTION);

						}
						break;
					case SELECT_EXIT:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							HWND hWnd;
							hWnd = GethWnd();
							PostMessage(hWnd, WM_QUIT, 0, 0);
						}
						break;
					}
				}
				else if (GetdJoyPovTrigger(POV_UP, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_UP, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_PLAY;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_OPTION;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoyPovTrigger(POV_DOWN, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_DOWN, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_OPTION;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_PLAY;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (g_TitleState == TITLESTATE_NORMAL)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i) == true)
					{
						g_TitleState = TITLESTATE_SELECT;
						DemoCnt = 0;

						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						pVtx += VT_MAX * 2;
						//�e�N�X�`��
						pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
						pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
					}

					DemoCnt++;
				}
			}
			else
			{
				if (GetdJoykeyTrigger(PSKEY_BACK, (CONTROLLER)i) == true)
				{
					g_TitleState = TITLESTATE_NORMAL;

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) == true)
				{
					FADE fade;
					switch (SelectNew)
					{
					case SELECT_PLAY:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_GAME);
						}
						break;
					case SELECT_VERSUS:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_VS);
						}
						break;
					case SELECT_TUTO:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_TUTO);

						}
						break;
					case SELECT_RANK:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_RANK);

						}
						break;
					case SELECT_OPTION:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_OPTION);

						}
						break;
					case SELECT_EXIT:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							HWND hWnd;
							hWnd = GethWnd();
							PostMessage(hWnd, WM_QUIT, 0, 0);
						}
						break;
					}
				}
				else if (GetdJoyPovTrigger(POV_UP, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_UP, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_PLAY;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_OPTION;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoyPovTrigger(POV_DOWN, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_DOWN, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_OPTION;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_PLAY;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (g_TitleState == TITLESTATE_NORMAL)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					if (GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i) == true)
					{
						g_TitleState = TITLESTATE_SELECT;
						DemoCnt = 0;

						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						pVtx += VT_MAX * 2;
						//�e�N�X�`��
						pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
						pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
					}

					DemoCnt++;
				}
			}
			else
			{
				if (GetdJoykeyTrigger(NINKEY_�|, (CONTROLLER)i) == true)
				{
					g_TitleState = TITLESTATE_NORMAL;

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					switch (SelectNew)
					{
					case SELECT_PLAY:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_GAME);
						}
						break;
					case SELECT_VERSUS:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_VS);
						}
						break;
					case SELECT_TUTO:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_TUTO);

						}
						break;
					case SELECT_RANK:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_RANK);

						}
						break;
					case SELECT_OPTION:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_OPTION);

						}
						break;
					case SELECT_EXIT:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							HWND hWnd;
							hWnd = GethWnd();
							PostMessage(hWnd, WM_QUIT, 0, 0);
						}
						break;
					}
				}
				else if (GetdJoyPovTrigger(POV_UP, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_UP, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_PLAY;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_OPTION;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoyPovTrigger(POV_DOWN, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_DOWN, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_OPTION;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_PLAY;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (g_TitleState == TITLESTATE_NORMAL)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i) == true)
					{
						g_TitleState = TITLESTATE_SELECT;
						DemoCnt = 0;

						g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

						pVtx += VT_MAX * 2;
						//�e�N�X�`��
						pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
						pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
						pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

						g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
					}

					DemoCnt++;
				}
			}
			else
			{
				if (GetdJoykeyTrigger(DKEY_BACK, (CONTROLLER)i) == true)
				{
					g_TitleState = TITLESTATE_NORMAL;

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) == true)
				{
					FADE fade;
					switch (SelectNew)
					{
					case SELECT_PLAY:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_GAME);
						}
						break;
					case SELECT_VERSUS:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_VS);
						}
						break;
					case SELECT_TUTO:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_TUTO);

						}
						break;
					case SELECT_RANK:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_RANK);

						}
						break;
					case SELECT_OPTION:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							SetFade(MODE_OPTION);

						}
						break;
					case SELECT_EXIT:
						DemoCnt = 0;
						fade = GetFade();
						if (fade == FADE_NONE)
						{
							//�T�E���h
							StopSound(SOUND_LABEL_BGM);
							//�ؑ�
							HWND hWnd;
							hWnd = GethWnd();
							PostMessage(hWnd, WM_QUIT, 0, 0);
						}
						break;
					}
				}
				else if (GetdJoyPovTrigger(POV_UP, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_UP, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_PLAY;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_OPTION;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
				else if (GetdJoyPovTrigger(POV_DOWN, 0, (CONTROLLER)i) == true || dJoyStickTrigger(DIRESTICK_DOWN, STICK_LEFT, (CONTROLLER)i))
				{
					switch (SelectNew)
					{
					case SELECT_PLAY:
						SelectNew = SELECT_VERSUS;
						break;
					case SELECT_VERSUS:
						SelectNew = SELECT_TUTO;
						break;
					case SELECT_TUTO:
						SelectNew = SELECT_RANK;
						break;
					case SELECT_RANK:
						SelectNew = SELECT_OPTION;
						break;
					case SELECT_OPTION:
						SelectNew = SELECT_EXIT;
						break;
					case SELECT_EXIT:
						SelectNew = SELECT_PLAY;
						break;
					}

					g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

					pVtx += VT_MAX * 2;
					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T));
					pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);
					pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_T * SelectNew + UV_DEF / U_MAX_T, UV_DEF / V_MAX_T * (SelectNew / U_MAX_T) + UV_DEF / V_MAX_T);

					g_pVtxBuffTitle->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

				}
			}
		}
	}

	UpdateShadow();
	UpdateStage();
	UpdateMeshField();
	UpdateLine();
	UpdateCylinder();
	UpdateSphere();
	UpdateSnowBall();
	UpdateMeshWall();
	UpdateBillboard();
}

//-------------------
//�`�揈��
//-------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	DrawMeshField();
	DrawLine();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawBillboard();
	DrawMeshWall();
	DrawSnowBall();
	DrawAlphaMeshWall();

    //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTitle[0]);

	//�w�i�̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//�^�C�v
		0,//�n�܂�̔ԍ�
		2//�|���S���̌�
	);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTitle[1]);

	//�w�i�̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//�^�C�v
		VT_MAX,//�n�܂�̔ԍ�
		2//�|���S���̌�
	);

	if (g_TitleState != TITLESTATE_NONE)
	{
		if (g_TitleState == TITLESTATE_SELECT)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTitle[3]);
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTitle[2]);
		}

		//�w�i�̕`��
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//�^�C�v
			VT_MAX * 2,//�n�܂�̔ԍ�
			2//�|���S���̌�
		);
	}
}
