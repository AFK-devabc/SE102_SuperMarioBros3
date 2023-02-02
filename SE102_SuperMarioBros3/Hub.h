#pragma once
#include <vector>
#include<D3DX10math.h>
#include <unordered_map>

#include "Sprites.h"
#include "debug.h"
#include "GameObject.h"
class CHub
{
private:
	static CHub* __instance;
	int world;
	int life;
	int power;
	vector<int> checkpointItems;
	int coin;
	int countDown;
	int timeTickCount;
	int powerTickCount;
	DWORD point;
	bool whiteP;
public:
	CHub()
	{
		world = 1;
		life = 4;
		power = 0;
		countDown = 0;
		point = 0;
		coin = 0;
		powerTickCount = 0;
		timeTickCount = 0;
		checkpointItems.clear();
	}
	void Update(DWORD dt, LPGAMEOBJECT player);
	void Render();

	void SetGameTime(int time)
	{
		countDown = time;
		powerTickCount = 0;
		timeTickCount = 0;
	}
	void AddPoint(int point) { this->point += point; }
	void AddCoin(int coin) { this->coin += coin; }
	void AddLife(int life) { this->life += life; }
	int GetLife() { return life; }
	void AddItems(int item) { if(checkpointItems.size() <3) this->checkpointItems.push_back(item); }
	static CHub* GetInstance();
};

string GetNumberID(int number);


