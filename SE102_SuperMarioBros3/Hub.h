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
	bool isGameEnding;
	int newItem;

	D3DXVECTOR2 titlePosition;
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
		isGameEnding = false;
		titlePosition = D3DXVECTOR2(100, 60);

	}
	void Update(DWORD dt, LPGAMEOBJECT player);
	void Render();

	void ReloadHub(int time)
	{
		countDown = time;
		powerTickCount = 0;
		timeTickCount = 0;
		isGameEnding = false;
	}
	void AddPoint(int point) { this->point += point; }
	void AddCoin(int coin) { this->coin += coin; }
	void AddLife(int life) { this->life += life; }
	int GetLife() { return life; }
	void AddItems(int item) { if(checkpointItems.size() <3)  this->checkpointItems.push_back(item);
		isGameEnding = true;
		titlePosition = D3DXVECTOR2(100, 60);
		newItem = item;
	}

	static CHub* GetInstance();
};

string GetNumberID(int number);

string GetCharID(char character);

