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
	state = WMMARIO_STATE_IDLE;
}

void CWorldMapMario::SetMario(int type)
{
	this->marioType = type;
	CWorldMap::GetInstance()->GetCurrentNodePosition(currentX, currentY);
	NextPosition = CWorldMap::GetInstance()->GetNode(currentX, currentY)->position;

	int nextX, nextY;
	CWorldMap::GetInstance()->GetCurrentMarioPosition(nextX,nextY);
	position = CWorldMap::GetInstance()->GetNode(nextX, nextY)->position;

}

void CWorldMapMario::Update(DWORD dt)
{

	if (position.x > NextPosition.x)
	{
		position.x -= WMMARIO_WALKING_SPEED * dt;
		if (position.x <= NextPosition.x)
		{
			position.x = NextPosition.x;
		}
	}
	else if (position.x < NextPosition.x)
	{
		position.x += WMMARIO_WALKING_SPEED * dt;
		if (position.x >= NextPosition.x)
		{
			position.x = NextPosition.x;
		}
	}

	if (position.y > NextPosition.y)
	{
		position.y -= WMMARIO_WALKING_SPEED * dt;
		if (position.y <= NextPosition.y)
		{
			position.y = NextPosition.y;
		}
	}
	else 		if (position.y < NextPosition.y)
	{
		position.y += WMMARIO_WALKING_SPEED * dt;
		if (position.y >= NextPosition.y)
		{
			position.y = NextPosition.y;
		}
	}

}



void CWorldMapMario::Render()
{
	CAnimations::GetInstance()->Get(to_string(marioType))->Render(position);
}


void CWorldMapMario::OnKeyDown(int KeyCode)
{
	if (position != NextPosition)
		return;

	if (KeyCode == DIK_S)
	{
		MapNode* currentNode= CWorldMap::GetInstance()->GetNode(currentX, currentY);
		if (currentNode->sceneID != "none" && !currentNode->isCompleted)
		{
			CScenes::GetInstance()->InitiateSwitchScene(currentNode->sceneID);
			CWorldMap::GetInstance()->SetCurrentNode(currentX, currentY);
			SetState(WMMARIO_STATE_IDLE);
			position = NextPosition;
		}
		return;
	}
	switch (KeyCode)
	{
	case DIK_UP:

		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->top)
		{
			currentY--;
			SetState(WMMARIO_STATE_TOP);

			NextPosition = CWorldMap::GetInstance()->GetNode(currentX, currentY)->position;
		}
		break;
	case DIK_DOWN:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->bottom)
		{
			currentY++;
			SetState(WMMARIO_STATE_BOTTOM);
			NextPosition = CWorldMap::GetInstance()->GetNode(currentX, currentY)->position;
		}
		break;
	case DIK_LEFT:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->left)
		{
			currentX--;
			SetState(WMMARIO_STATE_LEFT);

			NextPosition = CWorldMap::GetInstance()->GetNode(currentX, currentY)->position;
		}
		break;
	case DIK_RIGHT:
		if (CWorldMap::GetInstance()->GetNode(currentX, currentY)->right)
		{
			currentX++;

			SetState(WMMARIO_STATE_RIGHT);

			NextPosition = CWorldMap::GetInstance()->GetNode(currentX, currentY)->position;

		}
		break;
	default:
		break;
	}
}
