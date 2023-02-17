#include "IntroArrow.h"
#include "Scenes.h"
void CIntroArrow::Render()
{
	CSprites::GetInstance()->Get("1_Player_Title")->DrawHub(menuPosition + D3DXVECTOR2(0,-8));
	CSprites::GetInstance()->Get("2_Player_Title")->DrawHub(menuPosition + D3DXVECTOR2(0, 8));

	CSprites::GetInstance()->Get("Arrow")->DrawHub(arrowPosition[arrow]);

}
void CIntroArrow::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		CScenes::GetInstance()->InitiateSwitchScene(sceneID);
		break;
	case DIK_UP:
	{
		arrow -= 1;
		if (arrow < 0)
			arrow = arrowPosition.size() - 1;
		break;
	}
	case DIK_DOWN:
	{
		arrow += 1;
		if (arrow > arrowPosition.size() - 1)
			arrow = 0;
		break;
	}
	default: 
		break;
	}
}
