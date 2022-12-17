#include "Plant.h"
#include "GameObjectType.h"
#include "PlayScene.h"
#include "Scenes.h"
#include "PlantBullet.h"
void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - PLANT_WIDTH / 2;
	t = position.y - PLANT_HEIGHT / 2;
	r = l + PLANT_WIDTH;
	b = t + PLANT_HEIGHT;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
		
	if (startTime >= GetTickCount64())
	{
		if (plantType != PLANT_STATE_BITE)
		{

			if (isDamage) {
				CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
				D3DXVECTOR2 playerPosi = playscene->GetPlayer()->GetPosition();

				if (playerPosi.y > position.y)
					isLookingTop = 0;
				else
					isLookingTop = 1;
				if (playerPosi.x > position.x)
					isLookingRight = 1;
				else
					isLookingRight = 0;

				if (GetTickCount64() - attackCount > PLANT_DELAY_TIME / 2 && isFiring)
				{
					D3DXVECTOR2 bulletSpeed;
					bulletSpeed.x = isLookingRight ? BULLET_SPEED_X : -BULLET_SPEED_X;
					bulletSpeed.y = isLookingTop ? -BULLET_SPEED_Y : BULLET_SPEED_Y;

					LPGAMEOBJECT plantbullet = new CPlantBullet(position, bulletSpeed);
					playscene->AddGameObject(plantbullet);
					attackCount = 0;
					isFiring = 0;
				}
			}
		}
	}
	else
	{
		if (isGoingUp)
		{
			velocity.y = -PLANT_SPEED;
			position += velocity * dt;
			if (pinePosition.y - position.y > 2.0f)
				isDamage = 1;
			if (position.y <= pinePosition.y - PLANT_HEIGHT)
			{
				position.y = pinePosition.y - PLANT_HEIGHT;
				startTime = GetTickCount64() + PLANT_DELAY_TIME;
				isGoingUp = !isGoingUp;
				isFiring = 1;
				attackCount = GetTickCount64();
			}
		}
		else
		{
			velocity.y = PLANT_SPEED;
			position += velocity * dt;		
			if (pinePosition.y - position.y < 2.0f)
				isDamage = 0;

			if (position.y >= pinePosition.y)
			{
				position.y = pinePosition.y;
				startTime = GetTickCount64() + PLANT_DELAY_TIME;
				isGoingUp = !isGoingUp;
			}
		}
	}

	//if (plantType != PLANET_STATE_BITE) {
	//	isLookingRight = playerPosi.x > position.x ? 0 : 1;
	//}
}

void CPlant::Render()
{
	if(plantType == PLANT_STATE_BITE)
		CAnimations::GetInstance()->Get(to_string(PLANT_STATE_BITE))->Render(position);
	else
	{
		if(isLookingTop)
			CAnimations::GetInstance()->Get(to_string(PLANT_STATE_LOOKINGBOT))->Render(position, isLookingRight);
		else 
			CAnimations::GetInstance()->Get(to_string(PLANT_STATE_LOOKINGTOP))->Render(position, isLookingRight);
	}

	CAnimations::GetInstance()->Get(to_string(GREEN_PIPE))->Render(pinePosition);
	RenderBoundingBox();
}


