#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
class CIntroArrow :
    public CKeyEventHandler
{
protected:
    string sceneID;
    D3DXVECTOR2 menuPosition;

    int arrow;
    vector<D3DXVECTOR2> arrowPosition;
public:

    CIntroArrow() {
        menuPosition = D3DXVECTOR2(151, 176);
        arrow = 0;
         sceneID = "WorldMapScene";

        arrowPosition.clear();
        arrowPosition.push_back(D3DXVECTOR2(menuPosition + D3DXVECTOR2(-64, -8)));
        arrowPosition.push_back(D3DXVECTOR2(menuPosition + D3DXVECTOR2(-64, 8)));
        

    }

    void Render();
    void OnKeyDown(int KeyCode);
};

