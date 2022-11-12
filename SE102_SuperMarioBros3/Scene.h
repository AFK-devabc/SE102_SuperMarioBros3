#pragma once

#include "KeyEventHandler.h"
#include <vector>
/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	vector<LPKEYEVENTHANDLER> LPKeyHandler;

	int id;
	const char* sceneFilePath;

public:
	CScene(int id,const char* filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->LPKeyHandler.clear();
	}

	void GetKeyEventHandler(vector<LPKEYEVENTHANDLER> &LPKeyHandler)
	{
		for (int i = 0; i < this->LPKeyHandler.size(); i++)
		{
			LPKeyHandler.push_back(this->LPKeyHandler[i]);
		}
	}
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;


//class CSceneKeyHandler : public CKeyEventHandler
//{
//protected:
//
//	CScene* scence;
//
//public:
//	virtual void KeyState(BYTE* states) = 0;
//	virtual void OnKeyDown(int KeyCode) = 0;
//	virtual void OnKeyUp(int KeyCode) = 0;
//	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
//};
//
//typedef CSceneKeyHandler* LPSCENEKEYHANDLER;