//----------------------------------------
//
//���f���\������[Crow.cpp]
//Author fuma sato
//
//----------------------------------------

#include"Crow.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"hitshere.h"

//�O���[�o���ϐ��錾
Crow g_aCrow[MAX_CROW];

static MOTION_INFO g_Motion[] =
{
	true,
	2,
	{
	   {
		  80,
		  {
			 {
				 0.0f,1.2f,0.0f,-0.79f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,-0.66f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.09f,-1.1f,0.0f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,-1.73f,1.76f
			 },
			{
			   0.0f,0.0f,0.0f,0.0f,1.73f,1.76f
			 },
			 {
			   0.0f,0.0f,0.0f,0.75f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.75f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  80,
		  {
			 {
			   0.0f,1.2f,0.0f,-0.94f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.91f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.19f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.73f,1.41f
			 },
			{
			   0.0f,0.0f,0.0f,0.0f,1.73f,-1.41f
			 },
			 {
			   0.0f,0.0f,0.0f,0.97f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.07f,0.0f,0.0f
			 }
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
				 0.0f,0.0f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  20,
		  {
			 {
			   0.0f,0.0f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.82f,-0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-0.82f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.22f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.22f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  10,
		  {
			 {
				 0.0f,0.0f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.25f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.25f,0.0f,0.0f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,-0.82f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.82f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.22f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  40,
		  {
			 {
			   0.0f,0.0f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 }
		  }
	   }
	},
	false,
	11,
	{
	   {
		   20,
		   {
				{
					0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-1.48f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				}
		   }
	   },
	   {
		   20,
		   {
				{
					0.0f,0.0f,0.0f,0.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.51f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				},
			    {
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				}
		   }
	   },
	   {
		   20,
		   {
				{
					0.0f,0.0f,0.0f,-0.57f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-1.04f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
				},
				 {
				  0.0f,0.0f,0.0f,0.0f,0.19f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.19f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.19f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.19f,0.0f,0.0f
				}
		   }
	   },
	   {
		   20,
		   {
				{
					0.0f,-1.57f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				}
		   }
	   },
	   {
		   20,
		   {
				{
					0.0f,-1.57f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				}
		   }
	   },
			   {
		   5,
		   {
				{
					0.0f,0.0f,0.0f,0.09f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.48f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				}
		   }
		},
			   {
		   5,
		   {
				{
					0.0f,0.0f,0.0f,0.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.51f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				}
		   }
		},
	   {
		   5,
		   {
				{
					0.0f,0.0f,0.0f,-0.41f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.23f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.47f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.47f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.26f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.26f,0.0f,0.0f
				}
		   }
	   },
		{
		   5,
		   {
				{
					0.0f,0.0f,0.0f,0.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.51f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				}
		   }
		},
		{
		   5,
		   {
				{
					0.0f,0.0f,0.0f,-0.41f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.23f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.47f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.47f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.26f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.26f,0.0f,0.0f
				}
		   }
		},
		{
		   40,
		   {
				{
					0.0f,-0.2f,-16.9f,0.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-1.51f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.69f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.01f,0.0f,0.0f
				}
		   }
		}
	},
	false,
	4,
	   {
		  {
			 20,
			 {
				{
					0.0f,0.0f,0.0f,-1.63f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.25f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.88f,0.19f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.88f,-0.19f
				},
				{
				  0.0f,0.0f,0.0f,1.92f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.92f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.92f,0.0f,0.0f
				}
			 }
		  },
		  {
			 20,
			 {
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.82f,-1.45f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.88f,1.45f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				}
			 }
		  },
		  {
			 20,
			 {
				{
					0.0f,0.0f,0.0f,-1.7f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,-1.82f,-1.45f
				},
				 {
				  0.0f,0.0f,0.0f,0.6f,1.88f,1.45f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,0.0f,-0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,0.0f,0.0f
				}
			 }
		  },
		  {
			 20,
			 {
				{
				  0.0f,0.0f,0.0f,-2.01f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.82f,-1.13f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,1.88f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.47f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.47f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.47f,0.0f,0.0f
				}
			 }
		  }
	   },
	   false,
		  4,
		  {
			 {
				20,
				{
				   {
					   0.0f,16.1f,0.0f,-2.1f,0.0f,0.0f
				   },
				   {
					   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,-1.82f,-1.13f
				   },
					{
					 0.0f,0.0f,0.0f,-0.09f,1.88f,1.13f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   }
				}
			 },
			 {
				20,
				{
				   {
					 0.0f,8.7f,0.0f,-1.85f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,-1.88f,-0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,1.88f,0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   }
				}
			 },
						 {
				20,
				{
				   {
					   0.0f,16.1f,0.0f,-2.1f,0.0f,0.0f
				   },
				   {
					   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,-1.82f,-1.13f
				   },
					{
					 0.0f,0.0f,0.0f,-0.09f,1.88f,1.13f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   }
				}
			 },
			 {
				20,
				{
				   {
					 0.0f,8.7f,0.0f,-1.85f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,-1.88f,-0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,1.88f,0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   }
				}
			 }
		  }
};

//----------------------
//�|���S���̏���������
//----------------------
void InitCrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_CROW; nCnt++)
	{
		g_aCrow[nCnt].pos = D3DXVECTOR3(0.0f, 0.1f, START_Z_CROW);
		g_aCrow[nCnt].posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_aCrow[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aCrow[nCnt].Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aCrow[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].bJump = false;
		g_aCrow[nCnt].nLife = CROW_LIFE;
		g_aCrow[nCnt].state = CROWSTATE_NORMAL;
		g_aCrow[nCnt].nIdxShadow = -1;
		g_aCrow[nCnt].nIdxLife = -1;
		g_aCrow[nCnt].pStage = NULL;

		g_aCrow[nCnt].bLoopMotion = false;
		g_aCrow[nCnt].motionType = MOTIONTYPE_NEUTRAL;
		g_aCrow[nCnt].nCounterMotion = 0;
		g_aCrow[nCnt].nKey = -1;
		g_aCrow[nCnt].nNumKey = 0;
		g_aCrow[nCnt].nNumMotion = NUM_MOTION_CROW;
		g_aCrow[nCnt].bUse = false;


		LoadModel();

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_BODY_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[0].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[0].dwNumMat,
			&g_aCrow[nCnt].aModel[0].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_HEAD_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[1].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[1].dwNumMat,
			&g_aCrow[nCnt].aModel[1].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_BILL_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[2].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[2].dwNumMat,
			&g_aCrow[nCnt].aModel[2].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_RIGHTWING_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[3].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[3].dwNumMat,
			&g_aCrow[nCnt].aModel[3].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_LEFTWING_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[4].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[4].dwNumMat,
			&g_aCrow[nCnt].aModel[4].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_RIGHTFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[5].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[5].dwNumMat,
			&g_aCrow[nCnt].aModel[5].pMesh
		);

		//X�t�@�C���ǂݍ���
		D3DXLoadMeshFromX
		(
			CROW_LEFTFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aCrow[nCnt].aModel[6].pBuffMat,
			NULL,
			&g_aCrow[nCnt].aModel[6].dwNumMat,
			&g_aCrow[nCnt].aModel[6].pMesh
		);

		g_aCrow[nCnt].nNumModel = NUM_MODEL_CROW;

		int nCntModel;
		for (nCntModel = 0; nCntModel < g_aCrow[nCnt].nNumModel; nCntModel++)
		{

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aCrow[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aCrow[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`��������
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile
					(
						pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aCrow[nCnt].aModel[nCntModel].apTexture[nCntMat]
					);
				}
			}

			//���_��
			g_aCrow[nCnt].aModel[nCntModel].nNumVtx = g_aCrow[nCnt].aModel[nCntModel].pMesh->GetNumVertices();
			//���_�T�C�Y
			g_aCrow[nCnt].aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_aCrow[nCnt].aModel[nCntModel].pMesh->GetFVF());
			//���_�o�b�t�@�̎擾
			g_aCrow[nCnt].aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aCrow[nCnt].aModel[nCntModel].pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < g_aCrow[nCnt].aModel[nCntModel].nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aCrow[nCnt].aModel[nCntModel].pVtxBuff;

				if (vtx.x > g_aCrow[nCnt].aModel[nCntModel].vtxMax.x)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMax.x = vtx.x;
				}
				if (vtx.x < g_aCrow[nCnt].aModel[nCntModel].vtxMin.x)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMin.x = vtx.x;
				}
				if (vtx.y > g_aCrow[nCnt].aModel[nCntModel].vtxMax.y)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMax.y = vtx.y;
				}
				if (vtx.y < g_aCrow[nCnt].aModel[nCntModel].vtxMin.y)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMin.y = vtx.y;
				}
				if (vtx.z > g_aCrow[nCnt].aModel[nCntModel].vtxMax.z)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMax.z = vtx.z;
				}
				if (vtx.z < g_aCrow[nCnt].aModel[nCntModel].vtxMin.z)
				{
					g_aCrow[nCnt].aModel[nCntModel].vtxMin.z = vtx.z;
				}

				g_aCrow[nCnt].aModel[nCntModel].pVtxBuff += g_aCrow[nCnt].aModel[nCntModel].sizeFVF;
			}

			g_aCrow[nCnt].aModel[nCntModel].vtxMinDef = g_aCrow[nCnt].aModel[nCntModel].vtxMin;
			g_aCrow[nCnt].aModel[nCntModel].vtxMaxDef = g_aCrow[nCnt].aModel[nCntModel].vtxMax;
		}

		g_aCrow[nCnt].aModel[0].nIdxModelParent = -1;
		g_aCrow[nCnt].aModel[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		g_aCrow[nCnt].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[1].nIdxModelParent = 0;
		g_aCrow[nCnt].aModel[1].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		g_aCrow[nCnt].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[1].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[2].nIdxModelParent = 1;
		g_aCrow[nCnt].aModel[2].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
		g_aCrow[nCnt].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[2].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[3].nIdxModelParent = 0;
		g_aCrow[nCnt].aModel[3].pos = D3DXVECTOR3(-5.0f, 25.0f, 0.0f);
		g_aCrow[nCnt].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[3].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[4].nIdxModelParent = 0;
		g_aCrow[nCnt].aModel[4].pos = D3DXVECTOR3(5.0f, 25.0f, 0.0f);
		g_aCrow[nCnt].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[4].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[5].nIdxModelParent = 0;
		g_aCrow[nCnt].aModel[5].pos = D3DXVECTOR3(-2.0f, 1.0f, 0.0f);
		g_aCrow[nCnt].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[5].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aCrow[nCnt].aModel[6].nIdxModelParent = 0;
		g_aCrow[nCnt].aModel[6].pos = D3DXVECTOR3(2.0f, 1.0f, 0.0f);
		g_aCrow[nCnt].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCrow[nCnt].aModel[6].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			g_aCrow[nCnt].aModel[nCntModel].posDef = g_aCrow[nCnt].aModel[nCntModel].pos;
		}
	}
}

//-------------------
//�|���S���I������
//-------------------
void UninitCrow(void)
{
	for (int nCnt = 0; nCnt < MAX_CROW; nCnt++)
	{
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			for (unsigned int i = 0; i < g_aCrow[nCnt].aModel[nCntModel].dwNumMat; i++)
			{
				if (g_aCrow[nCnt].aModel[nCntModel].apTexture[i] != NULL)
				{
					g_aCrow[nCnt].aModel[nCntModel].apTexture[i]->Release();
					g_aCrow[nCnt].aModel[nCntModel].apTexture[i] = NULL;
				}
			}
			//���b�V���̔j��
			if (g_aCrow[nCnt].aModel[nCntModel].pMesh != NULL)
			{
				g_aCrow[nCnt].aModel[nCntModel].pMesh->Release();
				g_aCrow[nCnt].aModel[nCntModel].pMesh = NULL;
			}
			//�}�e���A���̔j��
			if (g_aCrow[nCnt].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aCrow[nCnt].aModel[nCntModel].pBuffMat->Release();
				g_aCrow[nCnt].aModel[nCntModel].pBuffMat = NULL;
			}
		}
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateCrow(void)
{
	for (int nCnt = 0; nCnt < MAX_CROW; nCnt++)
	{
		if (g_aCrow[nCnt].bUse)
		{
			//�ړ�����
			Player* pPlayer = GetPlayer();

			float Oldrot = atan2f(g_aCrow[nCnt].move.x, g_aCrow[nCnt].move.z);//���̕���
			float Xlong = pPlayer->pos.x - g_aCrow[nCnt].pos.x;
			float Zlong = pPlayer->pos.z - g_aCrow[nCnt].pos.z;
			float Destrot = atan2f(Xlong, Zlong);//�G�̕���

			float Diffrot = Destrot - Oldrot;//���̊p�x
			if (Diffrot > D3DX_PI)
			{//�C��
				Diffrot -= D3DX_PI * 2;
			}
			else if (Diffrot < -D3DX_PI)
			{//�C��
				Diffrot += D3DX_PI * 2;
			}

			Oldrot += Diffrot * TRACK_INA_CROW;//�p�x��␳

			if (Oldrot > D3DX_PI)
			{//�C��
				Oldrot -= D3DX_PI * 2;
			}
			else if (Oldrot < -D3DX_PI)
			{//�C��
				Oldrot += D3DX_PI * 2;
			}

			g_aCrow[nCnt].move.x += sinf(Oldrot) * SPEED_CROW;
			g_aCrow[nCnt].move.z += cosf(Oldrot) * SPEED_CROW;
			g_aCrow[nCnt].Destrot.y = Oldrot - D3DX_PI;
			if (g_aCrow[nCnt].motionType != MOTIONTYPE_JUMP && g_aCrow[nCnt].motionType != MOTIONTYPE_LANDING && g_aCrow[nCnt].motionType != MOTIONTYPE_ACTION)
			{
				g_aCrow[nCnt].motionType = MOTIONTYPE_MOVE;
			}

			if (sqrtf((pPlayer->pos.x - g_aCrow[nCnt].pos.x) * (pPlayer->pos.x - g_aCrow[nCnt].pos.x) + (pPlayer->pos.z - g_aCrow[nCnt].pos.z) * (pPlayer->pos.z - g_aCrow[nCnt].pos.z)) < CROW_ATTACK_SPACE)
			{
				g_aCrow[nCnt].motionType = MOTIONTYPE_ACTION;
			}

			g_aCrow[nCnt].move.y += GRAVITY;

			if (g_aCrow[nCnt].bJump)
			{
				g_aCrow[nCnt].move.x *= JUMP_INA_CROW;
				g_aCrow[nCnt].move.z *= JUMP_INA_CROW;
			}

			g_aCrow[nCnt].posOld = g_aCrow[nCnt].pos;

			if (g_aCrow[nCnt].motionType == MOTIONTYPE_ACTION)
			{
				g_aCrow[nCnt].move.x = 0.0f;
				g_aCrow[nCnt].move.z = 0.0f;
			}

			//�ʒu�̍X�V
			g_aCrow[nCnt].pos.x += g_aCrow[nCnt].move.x;
			g_aCrow[nCnt].pos.y += g_aCrow[nCnt].move.y;
			g_aCrow[nCnt].pos.z += g_aCrow[nCnt].move.z;

			//�ړ��ʂ̍X�V(����)
			g_aCrow[nCnt].move.x += (SPEED_CROW_DEF - g_aCrow[nCnt].move.x) * CROW_INA;
			g_aCrow[nCnt].move.z += (SPEED_CROW_DEF - g_aCrow[nCnt].move.z) * CROW_INA;

			CollisionPlayer(g_aCrow[nCnt].pos, CROW_SIZE);

			for (int nCntCrow = 0; nCntCrow < MAX_CROW; nCntCrow++)
			{
				if (g_aCrow[nCntCrow].bUse && nCntCrow != nCnt)
				{
					float Space = sqrtf((g_aCrow[nCntCrow].pos.x - g_aCrow[nCnt].pos.x) * (g_aCrow[nCntCrow].pos.x - g_aCrow[nCnt].pos.x) + (g_aCrow[nCntCrow].pos.y - g_aCrow[nCnt].pos.y) * (g_aCrow[nCntCrow].pos.y - g_aCrow[nCnt].pos.y) + (g_aCrow[nCntCrow].pos.z - g_aCrow[nCnt].pos.z) * (g_aCrow[nCntCrow].pos.z - g_aCrow[nCnt].pos.z));
					if (Space < CROW_SIZE)
					{
						Space = CROW_SIZE - Space;
						D3DXVECTOR3 Hitvec = g_aCrow[nCnt].pos - g_aCrow[nCntCrow].pos;
						D3DXVec3Normalize(&Hitvec, &Hitvec);
						g_aCrow[nCnt].move += Hitvec * Space;
					}
				}
			}

			g_aCrow[nCnt].pStage = NULL;

			g_aCrow[nCnt].bJump = !CollisionStage(&g_aCrow[nCnt].pStage);

			if (g_aCrow[nCnt].pStage != NULL)
			{
				g_aCrow[nCnt].pos += g_aCrow[nCnt].pStage->move;
			}

			if (g_aCrow[nCnt].pos.x < -GAME_WALL)
			{
				g_aCrow[nCnt].pos.x = -GAME_WALL;
			}
			if (g_aCrow[nCnt].pos.x > GAME_WALL)
			{
				g_aCrow[nCnt].pos.x = GAME_WALL;
			}
			if (g_aCrow[nCnt].pos.z < -GAME_WALL)
			{
				g_aCrow[nCnt].pos.z = -GAME_WALL;
			}
			if (g_aCrow[nCnt].pos.z > GAME_WALL)
			{
				g_aCrow[nCnt].pos.z = GAME_WALL;
			}

			if (sqrtf(g_aCrow[nCnt].move.x * g_aCrow[nCnt].move.x + g_aCrow[nCnt].move.z * g_aCrow[nCnt].move.z) < 0.1f && g_aCrow[nCnt].motionType == MOTIONTYPE_MOVE)
			{
				g_aCrow[nCnt].move.x = 0.0f;
				g_aCrow[nCnt].move.z = 0.0f;
				g_aCrow[nCnt].motionType = MOTIONTYPE_NEUTRAL;
			}

			//���K��
			if (g_aCrow[nCnt].Destrot.y > D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nCnt].Destrot.y < -D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.y += D3DX_PI * 2.0f;
			}

			//���K��
			if (g_aCrow[nCnt].Destrot.y - g_aCrow[nCnt].rot.y > D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.y = g_aCrow[nCnt].rot.y + ((g_aCrow[nCnt].Destrot.y - g_aCrow[nCnt].rot.y) - D3DX_PI * 2.0f);
			}
			else if (g_aCrow[nCnt].Destrot.y - g_aCrow[nCnt].rot.y < -D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.y = g_aCrow[nCnt].rot.y + ((g_aCrow[nCnt].Destrot.y - g_aCrow[nCnt].rot.y) + D3DX_PI * 2.0f);
			}

			g_aCrow[nCnt].rot.y += (g_aCrow[nCnt].Destrot.y - g_aCrow[nCnt].rot.y) * ROT_SPEED_CROW;

			//���K��
			if (g_aCrow[nCnt].rot.y > D3DX_PI)
			{
				g_aCrow[nCnt].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nCnt].rot.y < -D3DX_PI)
			{
				g_aCrow[nCnt].rot.y += D3DX_PI * 2.0f;
			}

			//���K��
			if (g_aCrow[nCnt].Destrot.x > D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nCnt].Destrot.x < -D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.x += D3DX_PI * 2.0f;
			}

			//���K��
			if (g_aCrow[nCnt].Destrot.x - g_aCrow[nCnt].rot.x > D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.x = g_aCrow[nCnt].rot.x + ((g_aCrow[nCnt].Destrot.x - g_aCrow[nCnt].rot.x) - D3DX_PI * 2.0f);
			}
			else if (g_aCrow[nCnt].Destrot.x - g_aCrow[nCnt].rot.x < -D3DX_PI)
			{
				g_aCrow[nCnt].Destrot.x = g_aCrow[nCnt].rot.x + ((g_aCrow[nCnt].Destrot.x - g_aCrow[nCnt].rot.x) + D3DX_PI * 2.0f);
			}

			g_aCrow[nCnt].rot.x += (g_aCrow[nCnt].Destrot.x - g_aCrow[nCnt].rot.x) * ROT_SPEED_CROW;

			//���K��
			if (g_aCrow[nCnt].rot.x > D3DX_PI)
			{
				g_aCrow[nCnt].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nCnt].rot.x < -D3DX_PI)
			{
				g_aCrow[nCnt].rot.x += D3DX_PI * 2.0f;
			}

			//�X�P�[������
			g_aCrow[nCnt].scale.x = max(SCALE_MIN, min(SCALE_MAX, g_aCrow[nCnt].scale.x));
			g_aCrow[nCnt].scale.y = max(SCALE_MIN, min(SCALE_MAX, g_aCrow[nCnt].scale.y));
			g_aCrow[nCnt].scale.z = max(SCALE_MIN, min(SCALE_MAX, g_aCrow[nCnt].scale.z));

			int nCntModel;
			//�p�[�c����
			for (nCntModel = 0; nCntModel < g_aCrow[nCnt].nNumModel; nCntModel++)
			{
				g_aCrow[nCnt].aModel[nCntModel].vtxMax.x = g_aCrow[nCnt].aModel[nCntModel].vtxMaxDef.x * g_aCrow[nCnt].scale.x;
				g_aCrow[nCnt].aModel[nCntModel].vtxMax.y = g_aCrow[nCnt].aModel[nCntModel].vtxMaxDef.y * g_aCrow[nCnt].scale.y;
				g_aCrow[nCnt].aModel[nCntModel].vtxMax.z = g_aCrow[nCnt].aModel[nCntModel].vtxMaxDef.z * g_aCrow[nCnt].scale.z;
				g_aCrow[nCnt].aModel[nCntModel].vtxMin.x = g_aCrow[nCnt].aModel[nCntModel].vtxMinDef.x * g_aCrow[nCnt].scale.x;
				g_aCrow[nCnt].aModel[nCntModel].vtxMin.y = g_aCrow[nCnt].aModel[nCntModel].vtxMinDef.y * g_aCrow[nCnt].scale.y;
				g_aCrow[nCnt].aModel[nCntModel].vtxMin.z = g_aCrow[nCnt].aModel[nCntModel].vtxMinDef.z * g_aCrow[nCnt].scale.z;
			}

			UpdateCrowMotion(nCnt);

			if (g_aCrow[nCnt].motionType == MOTIONTYPE_ACTION && g_aCrow[nCnt].nKey == 2 && g_aCrow[nCnt].nCounterMotion == 10)
			{
				SetHitShere(g_aCrow[nCnt].pos + g_aCrow[nCnt].aModel[0].pos + D3DXVECTOR3(sinf(g_aCrow[nCnt].rot.y + g_aCrow[nCnt].aModel[0].rot.y) * cosf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x), sinf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x), cosf(g_aCrow[nCnt].rot.y + g_aCrow[nCnt].aModel[0].rot.y) * cosf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x)) * sqrtf((g_aCrow[nCnt].aModel[1].pos.x - g_aCrow[nCnt].aModel[0].pos.x) * (g_aCrow[nCnt].aModel[1].pos.x - g_aCrow[nCnt].aModel[0].pos.x) + (g_aCrow[nCnt].aModel[1].pos.y - g_aCrow[nCnt].aModel[0].pos.y) * (g_aCrow[nCnt].aModel[1].pos.y - g_aCrow[nCnt].aModel[0].pos.y) + (g_aCrow[nCnt].aModel[1].pos.z - g_aCrow[nCnt].aModel[0].pos.z) * (g_aCrow[nCnt].aModel[1].pos.z - g_aCrow[nCnt].aModel[0].pos.z)) + D3DXVECTOR3(sinf(g_aCrow[nCnt].rot.y + g_aCrow[nCnt].aModel[0].rot.y + g_aCrow[nCnt].aModel[1].rot.y) * cosf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x + g_aCrow[nCnt].aModel[1].rot.x), sinf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x + g_aCrow[nCnt].aModel[1].rot.x), cosf(g_aCrow[nCnt].rot.y + g_aCrow[nCnt].aModel[0].rot.y + g_aCrow[nCnt].aModel[1].rot.y) * cosf(g_aCrow[nCnt].rot.x + g_aCrow[nCnt].aModel[0].rot.x + g_aCrow[nCnt].aModel[1].rot.x)) * sqrtf((g_aCrow[nCnt].aModel[1].vtxMax.x - g_aCrow[nCnt].aModel[1].vtxMin.x) * (g_aCrow[nCnt].aModel[1].vtxMax.x - g_aCrow[nCnt].aModel[1].vtxMin.x) + (g_aCrow[nCnt].aModel[1].vtxMax.y - g_aCrow[nCnt].aModel[1].vtxMin.y) * (g_aCrow[nCnt].aModel[1].vtxMax.y - g_aCrow[nCnt].aModel[1].vtxMin.y) + (g_aCrow[nCnt].aModel[1].vtxMax.z - g_aCrow[nCnt].aModel[1].vtxMin.z) * (g_aCrow[nCnt].aModel[1].vtxMax.z - g_aCrow[nCnt].aModel[1].vtxMin.z)), D3DXVECTOR3(100.0f, 100.0f, 100.0f), 10, ENEMY);
			}

			switch (g_aCrow[nCnt].state)
			{
			case CROWSTATE_APPEAR:
				g_aCrow[nCnt].bUse = false;
				break;
			case CROWSTATE_NORMAL:
				g_aCrow[nCnt].pos.y = 100.0f;
				if (g_aCrow[nCnt].nLife <= 0)
				{
					g_aCrow[nCnt].state = CROWSTATE_DIE;
				}
				SetLife(g_aCrow[nCnt].pos + g_aCrow[nCnt].aModel[0].pos + g_aCrow[nCnt].aModel[1].pos, (float)((float)g_aCrow[nCnt].nLife / (float)CROW_LIFE), g_aCrow[nCnt].nIdxLife);
				SetPositionShadow(g_aCrow[nCnt].nIdxShadow, g_aCrow[nCnt].pos, g_aCrow[nCnt].scale, 200.0f);
				break;
			case CROWSTATE_DIE:
				g_aCrow[nCnt].Destrot.x = D3DX_PI * 0.5f;
				static int nCntDie = 0;
				nCntDie++;
				if (nCntDie >= 20)
				{
					NullLife(g_aCrow[nCnt].nIdxLife);
					NullShadow(g_aCrow[nCnt].nIdxShadow);
					SetParticle(g_aCrow[nCnt].pos, g_aCrow[nCnt].scale);
					g_aCrow[nCnt].state = CROWSTATE_APPEAR;
				}
				break;
			}
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawCrow(void)
{
	for (int nCnt = 0; nCnt < MAX_CROW; nCnt++)
	{
		if (g_aCrow[nCnt].bUse)
		{
			LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�}�g���b�N�X
			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//�f�o�C�X�̎擾
			pDevice = GetDevice();

			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aCrow[nCnt].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aCrow[nCnt].scale.x, g_aCrow[nCnt].scale.y, g_aCrow[nCnt].scale.z);
			D3DXMatrixMultiply(&g_aCrow[nCnt].mtxWorld, &g_aCrow[nCnt].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCrow[nCnt].rot.y, g_aCrow[nCnt].rot.x, g_aCrow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aCrow[nCnt].mtxWorld, &g_aCrow[nCnt].mtxWorld, &mtxRot);

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTrans, g_aCrow[nCnt].pos.x, g_aCrow[nCnt].pos.y, g_aCrow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aCrow[nCnt].mtxWorld, &g_aCrow[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aCrow[nCnt].mtxWorld);

			int nCntModel;
			//�p�[�c����
			for (nCntModel = 0; nCntModel < g_aCrow[nCnt].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//�v�Z�}�g���b�N�X
				D3DXMATRIX mtxParent;
				//�}�g���b�N�X������
				D3DXMatrixIdentity(&g_aCrow[nCnt].aModel[nCntModel].mtxWorld);

				//�傫���̔��f
				D3DXMatrixScaling(&mtxScaleModel, g_aCrow[nCnt].aModel[nCntModel].scale.x, g_aCrow[nCnt].aModel[nCntModel].scale.y, g_aCrow[nCnt].aModel[nCntModel].scale.z);
				D3DXMatrixMultiply(&g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &mtxScaleModel);

				//�����̔��f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aCrow[nCnt].aModel[nCntModel].rot.y, g_aCrow[nCnt].aModel[nCntModel].rot.x, g_aCrow[nCnt].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�ʒu�̔��f
				D3DXMatrixTranslation(&mtxTransModel, g_aCrow[nCnt].aModel[nCntModel].pos.x, g_aCrow[nCnt].aModel[nCntModel].pos.y, g_aCrow[nCnt].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
				if (g_aCrow[nCnt].aModel[nCntModel].nIdxModelParent != -1)
				{//�e���f��������
					mtxParent = g_aCrow[nCnt].aModel[g_aCrow[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{//�e���f�����Ȃ�
					mtxParent = g_aCrow[nCnt].mtxWorld;
				}

				D3DXMatrixMultiply(&g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &g_aCrow[nCnt].aModel[nCntModel].mtxWorld, &mtxParent);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aCrow[nCnt].aModel[nCntModel].mtxWorld);

				//���݂̃}�e���A���擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aCrow[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aCrow[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					//�e�N�X�`��
					pDevice->SetTexture(0, g_aCrow[nCnt].aModel[nCntModel].apTexture[nCntMat]);

					//���f���`��
					g_aCrow[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//------------------------------
//�ʒu�擾
//------------------------------
Crow* GetCrow(void)
{
	return &g_aCrow[0];
}

//------------------------------
//�ݒ�
//------------------------------
void SetCrow(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_CROW; nCnt++)
	{
		if (!g_aCrow[nCnt].bUse)
		{
			g_aCrow[nCnt].pos = pos;
			g_aCrow[nCnt].posOld = pos;
			g_aCrow[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCrow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCrow[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aCrow[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aCrow[nCnt].bJump = false;
			g_aCrow[nCnt].nLife = CROW_LIFE;
			g_aCrow[nCnt].state = CROWSTATE_NORMAL;
			g_aCrow[nCnt].nIdxShadow = SetShadow(g_aCrow[nCnt].pos, g_aCrow[nCnt].rot);
			g_aCrow[nCnt].nIdxLife = LinkLife();
			g_aCrow[nCnt].pStage = NULL;

			g_aCrow[nCnt].bLoopMotion = false;
			g_aCrow[nCnt].motionType = MOTIONTYPE_NEUTRAL;
			g_aCrow[nCnt].nCounterMotion = 0;
			g_aCrow[nCnt].nKey = -1;
			g_aCrow[nCnt].nNumKey = 0;
			g_aCrow[nCnt].nNumMotion = NUM_MOTION_CROW;
			g_aCrow[nCnt].bUse = true;
			break;
		}
	}
}

//------------------------------
//���[�V����
//------------------------------
void UpdateCrowMotion(int nNumber)
{
	static MOTIONTYPE OldMotion[MAX_CROW] = { MOTIONTYPE_NEUTRAL };
	static int BlendCnt[MAX_CROW] = { 0 };

	if (OldMotion[nNumber] != g_aCrow[nNumber].motionType)
	{
		g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]] = g_Motion[OldMotion[nNumber]];
		g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType] = g_Motion[g_aCrow[nNumber].motionType];

		for (int nCntModel = 0; nCntModel < g_aCrow[nNumber].nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aCrow[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

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

			g_aCrow[nNumber].aModel[nCntModel].pos = g_aCrow[nNumber].aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt[nNumber] / BLEND_FRAME);
			g_aCrow[nNumber].aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt[nNumber] / BLEND_FRAME);

			//���K��
			if (g_aCrow[nNumber].aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nNumber].aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_aCrow[nNumber].aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nNumber].aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//���K��
			if (g_aCrow[nNumber].aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_aCrow[nNumber].aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_aCrow[nNumber].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt[nNumber] == (int)BLEND_FRAME)
		{
			BlendCnt[nNumber] = 0;
			OldMotion[nNumber] = g_aCrow[nNumber].motionType;
			return;
		}
		BlendCnt[nNumber]++;
		return;
	}
	g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType] = g_Motion[g_aCrow[nNumber].motionType];
	g_aCrow[nNumber].nNumKey = g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].nNumKey;
	g_aCrow[nNumber].bLoopMotion = g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].bLoop;
	static int nDestKey = g_aCrow[nNumber].nKey + 1;

	if (g_aCrow[nNumber].nCounterMotion >= g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].nFrame)
	{
		g_aCrow[nNumber].nCounterMotion = 0;
	}

	if (g_aCrow[nNumber].nCounterMotion == 0)
	{
		if (nDestKey >= g_aCrow[nNumber].nNumKey - 1)
		{
			if (g_aCrow[nNumber].bLoopMotion)
			{
				g_aCrow[nNumber].nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_aCrow[nNumber].nNumModel; nCntModel++)
				{
					g_aCrow[nNumber].aModel[nCntModel].pos = g_aCrow[nNumber].aModel[nCntModel].posDef + D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosZ);
					g_aCrow[nNumber].aModel[nCntModel].rot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_aCrow[nNumber].nKey = -1;
				nDestKey = g_aCrow[nNumber].nKey + 1;
				g_aCrow[nNumber].motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_aCrow[nNumber].nKey++;
			if (g_aCrow[nNumber].nKey > g_aCrow[nNumber].nNumKey - 1)
			{
				g_aCrow[nNumber].nKey = 0;
			}
			nDestKey = g_aCrow[nNumber].nKey + 1;

			for (int nCntModel = 0; nCntModel < g_aCrow[nNumber].nNumModel; nCntModel++)
			{
				g_aCrow[nNumber].aModel[nCntModel].pos = g_aCrow[nNumber].aModel[nCntModel].posDef + D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosZ);
				g_aCrow[nNumber].aModel[nCntModel].rot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotZ);
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_aCrow[nNumber].nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

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

		g_aCrow[nNumber].aModel[nCntModel].pos = g_aCrow[nNumber].aModel[nCntModel].posDef + Oldpos + posDif * (g_aCrow[nNumber].nCounterMotion / (float)g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].nFrame);
		g_aCrow[nNumber].aModel[nCntModel].rot = Oldrot + rotDif * (g_aCrow[nNumber].nCounterMotion / (float)g_aCrow[nNumber].aMotionInfo[g_aCrow[nNumber].motionType].aKeyInfo[g_aCrow[nNumber].nKey].nFrame);

		//���K��
		if (g_aCrow[nNumber].aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_aCrow[nNumber].aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_aCrow[nNumber].aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_aCrow[nNumber].aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//���K��
		if (g_aCrow[nNumber].aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_aCrow[nNumber].aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_aCrow[nNumber].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_aCrow[nNumber].nCounterMotion++;
}