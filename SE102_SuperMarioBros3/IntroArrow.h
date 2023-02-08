#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
class CIntroArrow :
    public CGameObject,
    public CKeyEventHandler
{
protected:
    string sceneID = "WorldMapScene";
public:

    CIntroArrow() {};
    void GetBoundingBox(float& l, float& t, float& r, float& b) {
        l = t = r = b = 0;
    };
    virtual void Render()
    {
    }

    virtual int IsBlocking() { return 0; }


    void OnKeyDown(int KeyCode);
};

