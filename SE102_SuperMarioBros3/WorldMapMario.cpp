#include "WorldMapMario.h"
#include "Animations.h"
#include "Scenes.h"
#include "WorldMapsScene.h"

#define WMMARIO_STATE_IDLE			100000
#define WMMARIO_STATE_LEFT			100001
#define WMMARIO_STATE_TOP			100002
#define WMMARIO_STATE_RIGHT			100003
#define WMMARIO_STATE_BOTTOM		100004
#define WMMARIO_WORLDMAP_SPEED		0.1f

CWorldMapMario::CWorldMapMario()
{
	velocity = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2(63, 64);
	NextPosition = position;
	currentY = 1;
	currentX = 0;
	state = WMMARIO_STATE_IDLE;
}

void CWorldMapMario::Update(DWORD dt)
{
	position += velocity * dt;
	switch (state)
	{
	case WMMARIO_STATE_LEFT:
		if (position.x <= NextPosition.x)
		{
			SetState(WMMARIO_STATE_IDLE);
			velocity.x = 0;
			position = NextPosition;
		}
		break;
	case WMMARIO_STATE_RIGHT:
		if (position.x >= NextPosition.x)
		{
			SetState(WMMARIO_STATE_IDLE);
			velocity.x = 0;
			position = NextPosition;
		}
		break;
	case WMMARIO_STATE_TOP:
		if (position.y <= NextPosition.y)
		{
			SetState(WMMARIO_STATE_IDLE);
			velocity.y = 0;
			position = NextPosition;
		}
		break;
	case WMMARIO_STATE_BOTTOM:
		if (position.y >= NextPosition.y)
		{
			SetState(WMMARIO_STATE_IDLE);
			velocity.y = 0;
			position = NextPosition;
		}
		break;

	default:
		break;
	}
}

void CWorldMapMario::Render()
{
	CAnimations::GetInstance()->Get(to_string(marioType))->Render(position);
}


void CWorldMapMario::OnKeyDown(int KeyCode)
{

	if (KeyCode == DIK_S)
	{
		string sceneID = CWorldMap::GetInstance()->GetNode(currentX, currentY)->sceneID;
		if (sceneID != "none")
		{
			CScenes::GetInstance()->InitiateSwitchScene(sceneID);
			CWorldMap::GetInstance()->SetCurrentNode(currentX, currentY);
			SetState(WMMARIO_STATE_IDLE);
			velocity.x = 0;
			position = NextPosition;

		}
		return;
	}
	if (state != WMMARIO_STATE_IDLE)
		return;
	switch (KeyCode)
	{
	case DIK_UP:

		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->top)
		{
			NextPosition.y = position.y - 32;
			SetState(WMMARIO_STATE_TOP);
			velocity.y = -WMMARIO_WORLDMAP_SPEED;

			currentY--;
		}
		break;
	case DIK_DOWN:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->bottom)
		{
			NextPosition.y = position.y + 32;
			SetState(WMMARIO_STATE_BOTTOM);
			velocity.y = WMMARIO_WORLDMAP_SPEED;
			currentY++;
		}
		break;
	case DIK_LEFT:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->left)
		{
			NextPosition.x = position.x - 32;
			SetState(WMMARIO_STATE_LEFT);
			velocity.x = -WMMARIO_WORLDMAP_SPEED;

			currentX--;
		}
		break;
	case DIK_RIGHT:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->right)
		{
			NextPosition.x = position.x + 32;
			SetState(WMMARIO_STATE_RIGHT);
			velocity.x = WMMARIO_WORLDMAP_SPEED;

			currentX++;
		}
		break;
	default:
		break;
	}
}
