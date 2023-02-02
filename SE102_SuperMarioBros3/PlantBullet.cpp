#include "PlantBullet.h"
#include "DefineInfo.h"
#include "GameObjectType.h"

void CPlantBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - PLANT_BULLET_SIZE / 2;
	t = position.y - PLANT_BULLET_SIZE / 2;
	r = l + PLANT_BULLET_SIZE;
	b = t + PLANT_BULLET_SIZE;

}

void CPlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	position += velocity * dt;
	lifeTime -= dt;
	DebugOut(L"%d\n", lifeTime);
	if (lifeTime <= 0)
		this->Delete();
}

void CPlantBullet::Render()
{
	CAnimations::GetInstance()->Get(to_string(PLANT_BULLET))->Render(position);
}
