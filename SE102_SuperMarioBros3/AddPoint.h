#pragma once
#include "GameEffect.h"
#include "Hub.h"

class CAddPoint :
    public CGameEffect
{
private:
	int point;
	vector<string> NumberList;
public:
	CAddPoint(D3DXVECTOR2 position, int point = 0) : CGameEffect(position, 300) {
		this->velocity = D3DXVECTOR2(0, -POINT_START_SPEEDY);
		this->point = point;
		NumberList.clear();
		int temp = point;
		int number;
		CSprites* sprites = CSprites::GetInstance();
		while (temp != 0)
		{
			number = temp % 10;
			temp = temp / 10;
			NumberList.push_back(GetNumberID(number));
		}
		this->position.x += 4 * NumberList.size();
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{

		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
	}



	virtual void Render() {

		CSprites* sprites = CSprites::GetInstance();
		for (int i = 0;i < NumberList.size(); i++)
			sprites->Get(NumberList[i])->Draw(D3DXVECTOR2(this->position.x - i * 8, this->position.y));

	};
	virtual void Delete() {
		isDeleted = true;
		CHub::GetInstance()->AddPoint(point);
	}

};

