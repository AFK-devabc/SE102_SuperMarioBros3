#include "Hub.h"
#include "DefineInfo.h"
#include "Animations.h"
CHub* CHub::__instance = NULL;

CHub* CHub::GetInstance()
{
	if (__instance == NULL) __instance = new CHub();
	return __instance;
}


void CHub::Update(DWORD dt, LPGAMEOBJECT player)
{
	timeTickCount += dt;
	powerTickCount += dt;

	if (timeTickCount >= 1000)
	{
		timeTickCount -=1000;
		countDown -= 1;
	}
	if (powerTickCount >= 500)
	{
		powerTickCount -= 500;
		if (power > 0) power -= 1;
		whiteP = !whiteP;
	}
	if(player->GetState() == MARIO_STATE_RUNNING )
	{
		power = (abs(player->GetVelocity().x) - MARIO_WALKING_SPEED) / SPEED_PER_POW;
	}
}

void CHub::Render()
{
	int temp = 0;
	int number;
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get("Black")->DrawHub(D3DXVECTOR2(200, 220));
	sprites->Get("Black")->DrawHub(D3DXVECTOR2(100, 220));
	sprites->Get("InfoBar")->DrawHub(D3DXVECTOR2(150, 220));
	sprites->Get("M_Info")->DrawHub(D3DXVECTOR2(46, 225));
	sprites->Get("Char_1")->DrawHub(D3DXVECTOR2(75, 217));

	temp = life;
	for (int i = 0; i < 2;i++)
	{
		number = temp % 10;
		temp = temp / 10;
		sprites->Get(GetNumberID(number))->DrawHub(D3DXVECTOR2(75 - i * 8, 225));
	}


	temp = point;
	for (int i = 0; i < 7;i++)
	{
		number = temp % 10;
		temp = temp / 10;

		sprites->Get(GetNumberID(number))->DrawHub(D3DXVECTOR2(136 - i * 8, 225));
	}

	for (int i = 0; i < 6;i++)
		sprites->Get("Black_Power")->DrawHub(D3DXVECTOR2(88 + i * 8, 217));

	for (int i = 0; i < power;i++)
		sprites->Get("White_Power")->DrawHub(D3DXVECTOR2(88 + i * 8, 217));
	if (power == 6 &&	whiteP 	)
		sprites->Get("White_P")->DrawHub(D3DXVECTOR2(140, 217));

		else
		sprites->Get("Black_P")->DrawHub(D3DXVECTOR2(140, 217));


		temp = coin;
		DebugOut(L"%d", coin);
		for (int i = 0; i < 2;i++)
		{
			number = temp % 10;
			temp = temp / 10;

			sprites->Get(GetNumberID(number))->DrawHub(D3DXVECTOR2(178 - i * 8, 217));

		}



		temp = countDown;
		for (int i = 0; i < 3;i++)
		{
			number = temp % 10;
			temp = temp / 10;
			sprites->Get(GetNumberID(number))->DrawHub(D3DXVECTOR2(178 - i * 8, 225));
		}

		for (int i = 0; i < checkpointItems.size();i++)
		{
			switch (checkpointItems[i])
			{
			case CHECKPOINT_FLOWER:
				sprites->Get("Flower")->DrawHub(D3DXVECTOR2(206 + 24 * i, 220));
				break;
			case CHECKPOINT_MUSHROOM:
				sprites->Get("Mushroom")->DrawHub(D3DXVECTOR2(206 + 24 * i, 220));
				break;
			case CHECKPOINT_STAR:
				sprites->Get("Star")->DrawHub(D3DXVECTOR2(206 + 24 * i, 220));
				break;

			default:
				sprites->Get("Mushroom")->DrawHub(D3DXVECTOR2(206 + 24 * i, 220));
				break;
			}

		}
}

string GetNumberID(int number)
{
	switch (number)
	{
	case 0 :
		return "Char_0";
		break;
	case 1:
		return "Char_1";
		break;
	case 2:
		return "Char_2";
		break;
	case 3:
		return "Char_3";
		break;
	case 4:
		return "Char_4";
		break;
	case 5:
		return "Char_5";
		break;
	case 6:
		return "Char_6";
		break;
	case 7:
		return "Char_7";
		break;
	case 8:
		return "Char_8";
		break;
	case 9:
		return "Char_9";
		break;

	default:
		return "Char_0";
	}
}
