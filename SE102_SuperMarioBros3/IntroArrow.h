#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
class CIntroArrow :
    public CKeyEventHandler
{
protected:
    string sceneID = "WorldMapScene";
public:

    CIntroArrow() {};

    void Render();
    void OnKeyDown(int KeyCode);
};

