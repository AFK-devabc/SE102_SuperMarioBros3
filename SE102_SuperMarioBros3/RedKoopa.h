#pragma once
#include "Koopa.h"
#include "KoopaEdgeDetect.h"
class CRedKoopa :
    public CKoopa
{
protected:
    LPGAMEOBJECT edgeDetect;
   
public :
    CRedKoopa(D3DXVECTOR2 position,LPGAMEOBJECT edgeDetect) : CKoopa(position) {
        velocity = D3DXVECTOR2(Goomba_Walking_Speed, 0);
        state = KOOPA_STATE_WALKING;
        this->edgeDetect = edgeDetect;
    };
    void SetEdgeDetectObject(LPGAMEOBJECT edgeDetect) { this->edgeDetect = edgeDetect; }

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Render();
  
};

