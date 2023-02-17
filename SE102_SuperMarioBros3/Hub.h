#pragma once
#include <vector>
#include<D3DX10math.h>
#include <unordered_map>
#include "GameOverArrow.h"

#include "Sprites.h"
#include "debug.h"
#include "GameObject.h"
#include "KeyEventHandler.h"
class CHub : public CKeyEventHandler
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

	DWORD startEndingTime;

	D3DXVECTOR2 titlePosition;
	int state;
	bool isGameOver;
public:
	CHub()
	{
		ResetHub();
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
	void AddLife(int life) {
		this->life += life; 
		if (this->life < 0)
		{
			isGameOver = true;
			life = 0;
		}
	}

	void ResetHub()
	{
		world = 1;
		life = 0;
		power = 0;
		countDown = 0;
		point = 0;
		coin = 0;
		powerTickCount = 0;
		timeTickCount = 0;
		checkpointItems.clear();
		isGameEnding = false;
		titlePosition = D3DXVECTOR2(100, 60);
		isGameOver = false;

	}
	int GetLife() { return life; }
	void AddItems(int item) { if(checkpointItems.size() <3)  this->checkpointItems.push_back(item);
		isGameEnding = true;
		startEndingTime = GetTickCount64();
		titlePosition = D3DXVECTOR2(100, 60);
		newItem = item;
	}


	bool IsGameOver() { return isGameOver; }
	static CHub* GetInstance();

	    void OnKeyDown(int KeyCode);

};

string GetNumberID(int number);

string GetCharID(char character);

