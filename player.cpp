//----------------------------------------
//
//���f���\������[player.cpp]
//Author fuma sato
//
//----------------------------------------

#include"player.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"snowball.h"

//�O���[�o���ϐ��錾
Player g_Player;

static MOTION_INFO g_Motion[] =
{
	true,
	2,
	{
	   {
		  80,
		  {
			 {
				 0.0f,-2.3f,0.0f,-0.03f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.88f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.19f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.75f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.41f
			 },
			 {
			   0.0f,0.0f,0.0f,0.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,0.16f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
		  }
	   },
	   {
		  80,
		  {
			 {
			   0.0f,-3.2f,0.0f,-0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,1.13f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,-1.13f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,0.53f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.53f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
			 },
		  }
	   }
	},
	true,
	4,
	{
	   {
		  10,
		  {
			 {
				 0.0f,10.1f,0.0f,-0.6f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.25f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.38f,0.41f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,1.48f,2.95f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.53f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,2.2f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,0.0f
			 },
		  }
	   },
	   {
		  5,
		  {
			 {
			   0.0f,-6.3f,0.0f,-0.63f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.38f,0.69f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-1.35f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,1.48f,-2.98f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,1.57f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-1.23f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.85f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f
			 },
		  }
	   },
	   {
		  10,
		  {
			 {
				 0.0f,10.1f,0.0f,-0.6f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.25f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.7f,-3.14f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,1.51f,-0.35f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,2.14f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
			 },
			 {
				  0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,0.0f
			 },
		  }
	   },
	   {
		  5,
		  {
			 {
			   0.0f,-6.3f,0.0f,-0.63f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.38f,2.95f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,-1.35f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,1.48f,-0.94f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,1.57f
			 },
			 {
			   0.0f,0.0f,0.0f,1.85f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-1.41f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f
			 },
		  }
	   }
	},
	false,
	5,
	{
	   {
		   20,
		   {
				{
					0.0f,-5.3f,0.0f,-1.04f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.28f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.7f,0.72f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,-0.66f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.41f,-1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,2.14f
				},
				{
				  0.0f,0.0f,0.0f,1.98f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,1.98f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				},
		   }
	   },
	   {
		   20,
		   {
				{
				  0.0f,-5.3f,0.0f,-1.1f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.34f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,-1.7f,0.72f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,-0.66f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,1.41f,-1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.25f,0.0f,2.14f
				},
				{
				  0.0f,0.0f,0.0f,2.14f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,2.14f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.73f,0.0f,0.0f
				},
		   }
	   },
	   {
		   10,
		   {
				{
					0.0f,-5.3f,0.0f,-0.22f,0.79f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.28f,-0.53f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-2.42f,2.51f
				},
				 {
				  0.0f,0.0f,0.0f,0.0f,0.35f,-0.38f
				},
				{
				  0.0f,0.0f,0.0f,-0.85f,1.35f,-1.01f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,2.14f
				},
				{
				  0.0f,0.0f,0.0f,1.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,1.13f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.13f,0.0f,0.0f
				},
		   }
	   },
	   {
		   20,
		   {
				{
				  0.0f,-5.3f,0.0f,-0.22f,0.79f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.28f,-0.19f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.06f,-2.48f,-2.86f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.35f,-0.19f
				},
				{
				  0.0f,0.0f,0.0f,-0.85f,0.91f,-1.01f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,2.14f
				},
				{
				  0.0f,0.0f,0.0f,1.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
		   }
	   },
	   {
		   40,
		   {
				{
				  0.0f,0.0f,0.0f,-0.22f,-1.26f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.16f,1.01f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.41f,-2.32f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,-0.22f
				},
				{
				  0.0f,0.0f,0.0f,-0.85f,-0.09f,-1.01f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,2.14f
				},
				{
				  0.0f,0.0f,0.0f,-0.88f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.1f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
		   }
	   }
	},
	false,
	4,
	   {
		  {
			 5,
			 {
				{
					0.0f,-5.6f,0.0f,-0.63f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.06f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.35f,0.41f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,-1.1f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.35f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,1.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.94f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,1.6f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,-0.94f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.53f,0.0f,0.0f
				},
			 }
		  },
		  {
			 12,
			 {
				{
				  0.0f,0.0f,0.0f,-0.75f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.32f,-1.01f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,-0.16f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.32f,1.01f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.16f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				},
			 }
		  },
		  {
			 17,
			 {
				{
					0.0f,0.0f,0.0f,-2.07f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,0.91f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.32f,0.41f
				},
				 {
				  0.0f,0.0f,0.0f,0.0f,0.0f,-0.13f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.32f,-0.41f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.13f
				},
				{
				  0.0f,0.0f,0.0f,-0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.72f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,-0.6f,0.0f,0.0f
				},
				{
					 0.0f,0.0f,0.0f,-0.72f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.79f,0.0f,0.0f
				},
			 }
		  },
		  {
			 5,
			 {
				{
				  0.0f,0.0f,0.0f,1.41f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.16f,0.82f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,-0.5f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.16f,-0.82f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.5f
				},
				{
				  0.0f,0.0f,0.0f,0.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.29f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.29f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
				},
			 }
		  }
	   },
	   false,
		  2,
		  {
			 {
				20,
				{
				   {
					   0.0f,-6.7f,0.0f,-1.26f,0.0f,0.0f
				   },
				   {
					   0.0f,0.0f,0.0f,-0.31f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,-1.76f,0.53f
				   },
					{
					 0.0f,0.0f,0.0f,0.0f,0.0f,-1.29f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,1.76f,0.53f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,1.29f
				   },
				   {
					 0.0f,0.0f,0.0f,2.39f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
				   },
				   {
						0.0f,0.0f,0.0f,2.39f,0.0f,0.0f
				   },
				   {
						0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.66f,0.0f,0.0f
				   },
				}
			 },
			 {
				20,
				{
				   {
					 0.0f,-6.9f,0.0f,-0.6f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,-1.76f,1.07f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,-0.31f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,1.76f,-1.07f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.31f
				   },
				   {
					 0.0f,0.0f,0.0f,1.76f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.76f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,-1.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f
				   },
				}
			 }
		  }
};

//----------------------
//�|���S���̏���������
//----------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(START_X, 0.1f, START_Z);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.bJump = false;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.nIdxShadow = -1;
	g_Player.nIdxLife = -1;
	g_Player.pStage = NULL;

	g_Player.bLoopMotion = false;
	g_Player.motionType = MOTIONTYPE_NEUTRAL;
	g_Player.nCounterMotion = 0;
	g_Player.nKey = -1;
	g_Player.nNumKey = 0;
	g_Player.nNumMotion = NUM_MOTION;
	g_Player.bUse = true;

	LoadModel();

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_BODY_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].dwNumMat,
		&g_Player.aModel[0].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_HEAD_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].dwNumMat,
		&g_Player.aModel[1].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_RIGHTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMat,
		NULL,
		&g_Player.aModel[2].dwNumMat,
		&g_Player.aModel[2].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_RIGHTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMat,
		NULL,
		&g_Player.aModel[3].dwNumMat,
		&g_Player.aModel[3].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_LEFTARM_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMat,
		NULL,
		&g_Player.aModel[4].dwNumMat,
		&g_Player.aModel[4].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_LEFTHAND_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMat,
		NULL,
		&g_Player.aModel[5].dwNumMat,
		&g_Player.aModel[5].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_RIGHTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMat,
		NULL,
		&g_Player.aModel[6].dwNumMat,
		&g_Player.aModel[6].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_RIGHTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMat,
		NULL,
		&g_Player.aModel[7].dwNumMat,
		&g_Player.aModel[7].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_LEFTLEG_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMat,
		NULL,
		&g_Player.aModel[8].dwNumMat,
		&g_Player.aModel[8].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_LEFTFOOT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMat,
		NULL,
		&g_Player.aModel[9].dwNumMat,
		&g_Player.aModel[9].pMesh
	);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX
	(
		PLAYER_HAT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[10].pBuffMat,
		NULL,
		&g_Player.aModel[10].dwNumMat,
		&g_Player.aModel[10].pMesh
	);

	g_Player.nNumModel = NUM_MODEL;

	int nCntModel;
	for (nCntModel = 0;  nCntModel < g_Player.nNumModel; nCntModel++)
	{

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`��������
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//���_��
		g_Player.aModel[nCntModel].nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		//���_�T�C�Y
		g_Player.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		//���_�o�b�t�@�̎擾
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Player.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_Player.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Player.aModel[nCntModel].pVtxBuff;

			if (vtx.x > g_Player.aModel[nCntModel].vtxMax.x)
			{
				g_Player.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_Player.aModel[nCntModel].vtxMin.x)
			{
				g_Player.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_Player.aModel[nCntModel].vtxMax.y)
			{
				g_Player.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_Player.aModel[nCntModel].vtxMin.y)
			{
				g_Player.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_Player.aModel[nCntModel].vtxMax.z)
			{
				g_Player.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_Player.aModel[nCntModel].vtxMin.z)
			{
				g_Player.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_Player.aModel[nCntModel].pVtxBuff += g_Player.aModel[nCntModel].sizeFVF;
		}

		g_Player.aModel[nCntModel].vtxMinDef = g_Player.aModel[nCntModel].vtxMin;
		g_Player.aModel[nCntModel].vtxMaxDef = g_Player.aModel[nCntModel].vtxMax;
	}

	g_Player.aModel[0].nIdxModelParent = -1;
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 21.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[1].nIdxModelParent = 0;
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 24.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[2].nIdxModelParent = 0;
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.5f, 19.5f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[3].nIdxModelParent = 2;
	g_Player.aModel[3].pos = D3DXVECTOR3(-7.5f, 0.0f, 0.0f);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[4].nIdxModelParent = 0;
	g_Player.aModel[4].pos = D3DXVECTOR3(7.5f, 19.5f, 0.0f);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[5].nIdxModelParent = 4;
	g_Player.aModel[5].pos = D3DXVECTOR3(7.5f, 0.0f, 0.0f);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[6].nIdxModelParent = 0;
	g_Player.aModel[6].pos = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[7].nIdxModelParent = 6;
	g_Player.aModel[7].pos = D3DXVECTOR3(0.0f, -6.0f, 0.0f);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[8].nIdxModelParent = 0;
	g_Player.aModel[8].pos = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[9].nIdxModelParent = 8;
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -6.0f, 0.0f);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.aModel[10].nIdxModelParent = 1;
	g_Player.aModel[10].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		g_Player.aModel[nCnt].posDef = g_Player.aModel[nCnt].pos;
	}

	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot);
	g_Player.nIdxLife = LinkLife();
}

//-------------------
//�|���S���I������
//-------------------
void UninitPlayer(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (unsigned int i = 0; i < g_Player.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_Player.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_Player.aModel[nCntModel].apTexture[i]->Release();
				g_Player.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//���b�V���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse)
	{
		Camera* pCamera = GetCamera();
		float* pStick;

		//�ړ�����

		//X
		if (IsXInputControllerConnected(CONTROLLER_1))
		{
			//���X�e�B�b�N����
			pStick = GetJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + -atan2f(*(pStick + 1), *pStick);
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		//d
		else if (IsDirectInputControllerConnected(CONTROLLER_1))
		{

			//���X�e�B�b�N����
			pStick = GetdJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f + atan2f(*(pStick + 1), *pStick);
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (GetKeyboradPress(DIK_A) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//A�L�[
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//����
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//����
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_D) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//D�L�[
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//�E��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//�E��
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//�E
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
		{//��
			g_Player.move.x += sinf(pCamera->rot.y) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y) * SPEED;
			g_Player.Destrot.y = pCamera->rot.y + D3DX_PI;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
		{//��
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Player.Destrot.y = pCamera->rot.y;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}

		if (GetKeyboradTrigger(DIK_SPACE) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_1) == true)//S�L�[
		{//��
			if (!g_Player.bJump)
			{
				g_Player.move.y += JUMP;
				g_Player.bJump = true;
				g_Player.motionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetKeyboradTrigger(DIK_RETURN) == true || GetMouseTrigger(MOUSE_LEFT) == true || GetJoykeyTrigger(JOYKEY_X, CONTROLLER_1) == true)
		{
			g_Player.motionType = MOTIONTYPE_ACTION;
		}

		if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoyPov(POV_UP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTUP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHT, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_RIGHTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_DOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTDOWN, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.25f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFT, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.5f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetdJoyPov(POV_LEFTUP, 0, CONTROLLER_1) == true)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.Destrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (!strcmp(ControllerName(CONTROLLER_1), ELE_CON))
		{
			if (GetdJoykeyPress(ELEKEY_A, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(ELEKEY_X, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), PS_CON))
		{
			if (GetdJoykeyPress(PSKEY_CR, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(PSKEY_SQ, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), NIN_CON))
		{
			if (GetdJoykeyPress(NINKEY_B, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(NINKEY_Y, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}
		else if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoykeyPress(DKEY_A, CONTROLLER_1) == true)
			{//��
				if (!g_Player.bJump)
				{
					g_Player.move.y += JUMP;
					g_Player.bJump = true;
					g_Player.motionType = MOTIONTYPE_JUMP;
				}
			}

			if (GetdJoykeyTrigger(DKEY_X, CONTROLLER_1) == true)
			{
				g_Player.motionType = MOTIONTYPE_ACTION;
			}
		}

		g_Player.move.y += GRAVITY;

		if (g_Player.bJump)
		{
			g_Player.move.x *= JUMP_INA;
			g_Player.move.z *= JUMP_INA;
		}

		g_Player.posOld = g_Player.pos;

		if (g_Player.motionType == MOTIONTYPE_ACTION)
		{
			g_Player.move.x = 0.0f;
			g_Player.move.z = 0.0f;
		}

		//�ʒu�̍X�V
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		g_Player.pos.z += g_Player.move.z;

		//�ړ��ʂ̍X�V(����)
		g_Player.move.x += (SPEED_DEF - g_Player.move.x) * PLAYER_INA;
		g_Player.move.z += (SPEED_DEF - g_Player.move.z) * PLAYER_INA;

		g_Player.pStage = NULL;

		CollisionSnowBall(g_Player.pos, PLAYER_SIZE);

		g_Player.bJump = !CollisionStage(&g_Player.pStage);

		if (g_Player.pStage != NULL)
		{
			g_Player.pos += g_Player.pStage->move;
		}

		if (g_Player.pos.x < -GAME_WALL)
		{
			g_Player.pos.x = -GAME_WALL;
		}
		if (g_Player.pos.x > GAME_WALL)
		{
			g_Player.pos.x = GAME_WALL;
		}
		if (g_Player.pos.z < -GAME_WALL)
		{
			g_Player.pos.z = -GAME_WALL;
		}
		if (g_Player.pos.z > GAME_WALL)
		{
			g_Player.pos.z = GAME_WALL;
		}

		if (sqrtf(g_Player.move.x * g_Player.move.x + g_Player.move.z * g_Player.move.z) < 0.1f && g_Player.motionType == MOTIONTYPE_MOVE)
		{
			g_Player.move.x = 0.0f;
			g_Player.move.z = 0.0f;
			g_Player.motionType = MOTIONTYPE_NEUTRAL;
		}

		//���K��
		if (g_Player.Destrot.y > D3DX_PI)
		{
			g_Player.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.y < -D3DX_PI)
		{
			g_Player.Destrot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.y - g_Player.rot.y > D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.y - g_Player.rot.y < -D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) + D3DX_PI * 2.0f);
		}

		g_Player.rot.y += (g_Player.Destrot.y - g_Player.rot.y) * ROT_SPEED;

		//���K��
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.x > D3DX_PI)
		{
			g_Player.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.x < -D3DX_PI)
		{
			g_Player.Destrot.x += D3DX_PI * 2.0f;
		}

		//���K��
		if (g_Player.Destrot.x - g_Player.rot.x > D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.x - g_Player.rot.x < -D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) + D3DX_PI * 2.0f);
		}

		g_Player.rot.x += (g_Player.Destrot.x - g_Player.rot.x) * ROT_SPEED;

		//���K��
		if (g_Player.rot.x > D3DX_PI)
		{
			g_Player.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.x < -D3DX_PI)
		{
			g_Player.rot.x += D3DX_PI * 2.0f;
		}

		//�X�P�[������
		g_Player.scale.x = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.x));
		g_Player.scale.y = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.y));
		g_Player.scale.z = max(SCALE_MIN, min(SCALE_MAX, g_Player.scale.z));

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aModel[nCntModel].vtxMax.x = g_Player.aModel[nCntModel].vtxMaxDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMax.y = g_Player.aModel[nCntModel].vtxMaxDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMax.z = g_Player.aModel[nCntModel].vtxMaxDef.z * g_Player.scale.z;
			g_Player.aModel[nCntModel].vtxMin.x = g_Player.aModel[nCntModel].vtxMinDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMin.y = g_Player.aModel[nCntModel].vtxMinDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMin.z = g_Player.aModel[nCntModel].vtxMinDef.z * g_Player.scale.z;
		}

		UpdateMotion();

		if (g_Player.motionType == MOTIONTYPE_ACTION && g_Player.nKey == 3 && g_Player.nCounterMotion == 11)
		{
			SetBullet(g_Player.pos + g_Player.aModel[0].pos, D3DXVECTOR3(sinf(g_Player.rot.y + g_Player.aModel[0].rot.y + g_Player.aModel[2].rot.y + g_Player.aModel[3].rot.y) * cosf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x), sinf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x), cosf(g_Player.rot.y + g_Player.aModel[0].rot.y + g_Player.aModel[2].rot.y + g_Player.aModel[3].rot.y) * cosf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x)), g_Player.aModel[3].scale);
		}

		switch (g_Player.state)
		{
		case PLAYERSTATE_APPEAR:
			g_Player.bUse = false;
			break;
		case PLAYERSTATE_NORMAL:
			if (g_Player.nLife <= 0)
			{
				g_Player.state = PLAYERSTATE_DIE;
			}
			SetPositionShadow(g_Player.nIdxShadow, g_Player.pos, g_Player.scale, 200.0f);
			SetLife(g_Player.pos + g_Player.aModel[0].pos + g_Player.aModel[1].pos + g_Player.aModel[10].pos, (float)((float)g_Player.nLife / (float)PLAYER_LIFE), g_Player.nIdxLife);
			break;
		case PLAYERSTATE_DIE:
			g_Player.Destrot.x = D3DX_PI * 0.5f;
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{
				NullShadow(g_Player.nIdxShadow);
				NullLife(g_Player.nIdxLife);
				SetParticle(g_Player.pos, g_Player.scale);
				g_Player.state = PLAYERSTATE_APPEAR;
			}
			break;
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawPlayer(void)
{
	if (g_Player.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
		D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^


		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//�傫���̔��f
		D3DXMatrixScaling(&mtxScale, g_Player.scale.x, g_Player.scale.y, g_Player.scale.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScale);

		//�����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//�ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		int nCntModel;
		//�p�[�c����
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//�v�Z�}�g���b�N�X
			D3DXMATRIX mtxParent;
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScaleModel, g_Player.aModel[nCntModel].scale.x, g_Player.aModel[nCntModel].scale.y, g_Player.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
			if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
			{//�e���f��������
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//�e���f�����Ȃ�
				mtxParent = g_Player.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A���擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`��
				pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTexture[nCntMat]);

				//���f���`��
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//------------------------------
//�ʒu�擾
//------------------------------
Player* GetPlayer(void)
{
	return &g_Player;
}

//------------------------------
//���[�V����
//------------------------------
void UpdateMotion(void)
{
	static MOTIONTYPE OldMotion = MOTIONTYPE_NEUTRAL;
	static int BlendCnt = 0;
	if (OldMotion != g_Player.motionType)
	{
		g_Player.aMotionInfo[OldMotion] = g_Motion[OldMotion];
		g_Player.aMotionInfo[g_Player.motionType] = g_Motion[g_Player.motionType];

		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosX, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosY, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotX, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotY, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

			//���K��
			if (Destrot.x - Oldrot.x > D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
			}
			else if (Destrot.x - Oldrot.x < -D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
			}
			//���K��
			if (Destrot.y - Oldrot.y > D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
			}
			else if (Destrot.y - Oldrot.y < -D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
			}
			//���K��
			if (Destrot.z - Oldrot.z > D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
			}
			else if (Destrot.z - Oldrot.z < -D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
			}

			D3DXVECTOR3 rotDif = Destrot - Oldrot;

			g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / BLEND_FRAME);
			g_Player.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / BLEND_FRAME);

			//���K��
			if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt == (int)BLEND_FRAME)
		{
			BlendCnt = 0;
			OldMotion = g_Player.motionType;
			return;
		}
		BlendCnt++;
		return;
	}
	g_Player.aMotionInfo[g_Player.motionType] = g_Motion[g_Player.motionType];
	g_Player.nNumKey = g_Player.aMotionInfo[g_Player.motionType].nNumKey;
	g_Player.bLoopMotion = g_Player.aMotionInfo[g_Player.motionType].bLoop;
	static int nDestKey = g_Player.nKey + 1;

	if (g_Player.nCounterMotion >= g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame)
	{
		g_Player.nCounterMotion = 0;
	}

	if (g_Player.nCounterMotion == 0)
	{
		if (nDestKey >= g_Player.nNumKey - 1)
		{
			if (g_Player.bLoopMotion)
			{
				g_Player.nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
				{
					g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
					g_Player.aModel[nCntModel].rot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_Player.nKey = -1;
				nDestKey = g_Player.nKey + 1;
				g_Player.motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_Player.nKey++;
			if (g_Player.nKey > g_Player.nNumKey - 1)
			{
				g_Player.nKey = 0;
			}
			nDestKey = g_Player.nKey + 1;

			for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
			{
				g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
				g_Player.aModel[nCntModel].rot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
			}
		}
	}
	
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

		//���K��
		if (Destrot.x - Oldrot.x > D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
		}
		else if (Destrot.x - Oldrot.x < -D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
		}
		//���K��
		if (Destrot.y - Oldrot.y > D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
		}
		else if (Destrot.y - Oldrot.y < -D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
		}
		//���K��
		if (Destrot.z - Oldrot.z > D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
		}
		else if (Destrot.z - Oldrot.z < -D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
		}

		D3DXVECTOR3 rotDif = Destrot - Oldrot;

		g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + Oldpos + posDif * (g_Player.nCounterMotion / (float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);
		g_Player.aModel[nCntModel].rot = Oldrot + rotDif * (g_Player.nCounterMotion / (float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//���K��
		if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_Player.nCounterMotion++;
}

//------------------------------------------------
//�Փ�
//------------------------------------------------
void CollisionPlayer(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_Player.pos.x) * (pos.x - g_Player.pos.x) + (pos.y - g_Player.pos.y) * (pos.y - g_Player.pos.y) + (pos.z - g_Player.pos.z) * (pos.z - g_Player.pos.z));
	if (Space < PLAYER_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (PLAYER_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_Player.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_Player.move += Hitvec * Space;
	}
}