//------------------------------------------
//
//�����L���O�̏���[rank.cpp]
//Author fuma sato
//
//------------------------------------------

#include"rank.h"
#include"game.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"score.h"
#include"file.h"
#include"cursor.h"
#include"pause.h"
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

#define NUMBER_WIDTH (64)
#define NUMBER_HEIGHT (750)
#define RANK_MAX (2)
#define RANK_TIME (600)
#define NUMBER_SEPAESE (20)

LPDIRECT3DTEXTURE9 g_apTextureRank[RANK_MAX] = { NULL };//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;//�o�b�t�@�̃|�C���^
int g_nNewDataRank;
bool g_bRankin = false;

//--------------------
//����������
//--------------------
void InitRank(void)
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
	D3DXVECTOR3 posScore;//�X�R�A�̈ʒu
	D3DXVECTOR3 posScoreDef;//�X�R�A�̈ʒu
	int nScore[MAX_DATA+1] = { 0 };
	int aPosTexUr[MAX_DATA+1][SCORE_MAX];
	int* pData;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * (SCORE_MAX*MAX_DATA+1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NUMBER,
		&g_apTextureRank[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_RANK,
		&g_apTextureRank[1]
	);

	//�ߋ��̃X�R�A�̎擾
	pData = LoadFile();
	for (int i = 0; i < MAX_DATA; i++,pData++)
	{
		nScore[i] = *pData;
	}

	//����̃X�R�A�̎擾
	nScore[MAX_DATA] = GetClearTime();
	pData = Soat(&nScore[0]);
	for (int i = 0; i < MAX_DATA; i++, pData++)
	{
		nScore[i] = *pData;
	}
	//�Z�[�u����
	SaveFile(&nScore[0]);

	//�\������
	for (int i = 0; i < MAX_DATA; i++)
	{
		if (nScore[i] == GetClearTime()&&nScore[i]!=0)
		{
			g_nNewDataRank = i;
			g_bRankin=true;
			break;
		}
		else if (i==MAX_DATA-1)
		{
			g_nNewDataRank = 99;
			g_bRankin = false;
		}
	}
	for (int i = 0; i < MAX_DATA; i++)
	{
		for (int i2 = 0; i2 < 2; i2++)
		{
			aPosTexUr[i][i2] = Digit(nScore[i], i2);
		}
		aPosTexUr[i][2] = 10;
		for (int i2 = 3; i2 < 5; i2++)
		{
			aPosTexUr[i][i2] = Digit(nScore[i], i2 - 1);
		}
	}

	TimeReset();
	posScore = D3DXVECTOR3(SCREEN_WIDTH / 2 - (SCORE_WIDTH / SCORE_MAX) * (SCORE_MAX / 2), SCORE_HEIGHT, 0.0f);
	posScoreDef = posScore;

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

	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	for (int i = 0; i < MAX_DATA; i++)
	{
		for (int i2 = 0; i2 < SCORE_MAX; i2++)
		{
			//���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(posScore.x - (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y - SCORE_HEIGHT / 2, posScore.z);
			pVtx[1].pos = D3DXVECTOR3(posScore.x + (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y - SCORE_HEIGHT / 2, posScore.z);
			pVtx[2].pos = D3DXVECTOR3(posScore.x - (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y + SCORE_HEIGHT / 2, posScore.z);
			pVtx[3].pos = D3DXVECTOR3(posScore.x + (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y + SCORE_HEIGHT / 2, posScore.z);

			//rhw
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (i == 0)
			{
				//�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (i == g_nNewDataRank)
			{
				//�J���[
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				//�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2], UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S));
			pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2] + UV_DEF / U_MAX_S, UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S));
			pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2], UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S) + UV_DEF / V_MAX_S);
			pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2] + UV_DEF / U_MAX_S, UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S) + UV_DEF / V_MAX_S);

			posScore.x += SCORE_WIDTH / SCORE_MAX;
			pVtx += VT_MAX;
		}
		posScore = posScoreDef;
		posScore.y += SCORE_HEIGHT * (i+1);
	}

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2 - NUMBER_WIDTH- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 - NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 - NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2 - NUMBER_WIDTH- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 + NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 + NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);

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

	g_pVtxBuffRank->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
	PlaySound(SOUND_LABEL_BGM6);
	if (g_bRankin)
	{
		if (g_nNewDataRank==0)
		{
			PlaySound(SOUND_LABEL_BEST);
		}
		else
		{
			PlaySound(SOUND_LABEL_RANKIN);
		}
	}
	else
	{
		PlaySound(SOUND_LABEL_NORANKIN);
	}
}

//--------------------
//�I������
//--------------------
void UninitRank(void)
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
	for (int i = 0; i < RANK_MAX; i++)
	{
		if (g_apTextureRank[i] != NULL)
		{
			g_apTextureRank[i]->Release();
			g_apTextureRank[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//--------------------
//�X�V����
//--------------------
void UpdateRank(void)
{
	VERTEX_2D* pVtx;//���_���|�C���^
	static int nRankTime = 0;

	if (nRankTime % RANK_TIME == 0 && nRankTime != 0)
	{
		nRankTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//�T�E���h
			StopSound(SOUND_LABEL_BGM6);
			//�ؑ�
			SetFade(MODE_TITLE);
		}
	}

	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		nRankTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause(SOUND_LABEL_BGM6);
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM6);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				nRankTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM6);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
			{
				nRankTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM6);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM6);
			}
		}
	}

	if (g_bRankin)
	{
		static float Color = 0.0f;
		static float Speed = COLOR_SPEED;
		Color += Speed;
		if (Color >= 1.0f || Color <= 0.0f)
		{
			Speed = -Speed;
		}
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N
		pVtx += VT_MAX * g_nNewDataRank * MAX_DATA;

		for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
		{
			//�J���[
			pVtx[0].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);

			pVtx += VT_MAX;
		}
	}

	g_pVtxBuffRank->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N

	if (!bPause())
	{
		nRankTime++;

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
}

//--------------------
//�`�揈��
//--------------------
void DrawRank(void)
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
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntData = 0; nCntData < MAX_DATA; nCntData++)
	{
		for (int nCntScore = 0; nCntScore < SCORE_MAX; nCntScore++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRank[0]);

			//�w�i�̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				(nCntData * SCORE_MAX + nCntScore) * VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureRank[1]);

	//�w�i�̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//�^�C�v
		VT_MAX * SCORE_MAX * MAX_DATA,//�n�܂�̔ԍ�
		2//�|���S���̌�
	);
}