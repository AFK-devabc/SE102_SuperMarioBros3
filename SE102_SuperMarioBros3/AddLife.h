#pragma once
#include "GameEffect.h"
#include "Hub.h"

class CAddLife :
    public CGameEffect
{
private:
	int life;
	vector<string> NumberList;
public:
	CAddLife(D3DXVECTOR2 position, int life = 0) : CGameEffect(position, 500) {
		this->velocity = D3DXVECTOR2(0, -POINT_START_SPEEDY);
		this->life = life;
		NumberList.clear();
		int temp = life;
		int number;
		CSprites* sprites = CSprites::GetInstance();
		string a = "PU";
		for (int i = 0; i < a.length(); i++)
			NumberList.push_back(GetCharID(a[i]));

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
		CHub::GetInstance()->AddLife(life);
	}

};

