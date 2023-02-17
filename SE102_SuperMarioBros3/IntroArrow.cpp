#include "IntroArrow.h"
#include "Scenes.h"
void CIntroArrow::Render()
{
}
void CIntroArrow::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		CScenes::GetInstance()->InitiateSwitchScene(sceneID);
		break;
	default: 
		break;
	}
}
