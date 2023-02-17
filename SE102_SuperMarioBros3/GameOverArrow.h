#pragma once
#include "KeyEventHandler.h"
#include "D3DX10.h"
#include <vector>
class CGameOverArrow :
    public CKeyEventHandler
{
protected:
    string sceneID = "IntroScene";
    D3DXVECTOR2 titleBoardPosition;
    
    int arrow;
    vector<D3DXVECTOR2> arrowPosition;
public:

    CGameOverArrow() {
        titleBoardPosition = D3DXVECTOR2(151, 100);
        arrow = 0;
        arrowPosition.clear();
        arrowPosition.push_back(D3DXVECTOR2(titleBoardPosition + D3DXVECTOR2(-16, 12)));
        arrowPosition.push_back(D3DXVECTOR2(titleBoardPosition + D3DXVECTOR2(-16, 20)));

    };

    void Render();

    void OnKeyDown(int KeyCode);

};

