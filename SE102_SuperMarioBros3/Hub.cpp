#include "Hub.h"

void CHub::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get("Black")->DrawHub(D3DXVECTOR2(200, 220));
	sprites->Get("Black")->DrawHub(D3DXVECTOR2(100, 220));

	sprites->Get("InfoBar")->DrawHub(D3DXVECTOR2(150, 220));

	sprites->Get("M_Info")->DrawHub(D3DXVECTOR2(46, 225));

	sprites->Get("Char_0")->DrawHub(D3DXVECTOR2(67, 225));
	sprites->Get("Char_0")->DrawHub(D3DXVECTOR2(75, 225));

	for(int i = 0; i< 7;i++)
		sprites->Get("Char_0")->DrawHub(D3DXVECTOR2(88+ i * 8, 225));

	for (int i = 0; i < 6;i++)
		sprites->Get("Black_Power")->DrawHub(D3DXVECTOR2(88 + i * 8, 217));
		sprites->Get("Black_P")->DrawHub(D3DXVECTOR2(140, 217));

		for (int i = 0; i < 2;i++)
			sprites->Get("Char_0")->DrawHub(D3DXVECTOR2(170 + i * 8, 217));

	for (int i = 0; i < 3;i++)
		sprites->Get("Char_0")->DrawHub(D3DXVECTOR2(162 + i*8, 225));

	sprites->Get("Mushroom")->DrawHub(D3DXVECTOR2(206, 220));
	sprites->Get("Mushroom")->DrawHub(D3DXVECTOR2(206 + 24, 220));

}
