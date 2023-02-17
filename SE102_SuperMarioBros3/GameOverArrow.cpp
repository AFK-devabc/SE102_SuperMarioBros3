#include "GameOverArrow.h"
#include "Scenes.h"
#include "Sprites.h"
#include "Hub.h"
#include "WorldMapsScene.h"
void CGameOverArrow::Render()
{
	CSprites::GetInstance()->Get("Gameover_Title")->DrawHub(titleBoardPosition);

	CSprites::GetInstance()->Get("Arrow")->DrawHub(arrowPosition[arrow]);

}
void CGameOverArrow::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		if(arrow == 0)
		{ 
		dynamic_cast<CWorldMapsScene*>(	CScenes::GetInstance()->GetCurrentScene())->ResetGame();
		}
		else if (arrow == 1)
		{
			dynamic_cast<CWorldMapsScene*>(CScenes::GetInstance()->GetCurrentScene())->ResetGame();
			CScenes::GetInstance()->InitiateSwitchScene(sceneID);
		}
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
