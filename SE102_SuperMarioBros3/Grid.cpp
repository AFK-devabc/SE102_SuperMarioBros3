#include "Grid.h"


CGrid::CGrid(int width, int height, int cellSize)
{
    mapWidth = width;
    mapHeight = height;
    this->cellSize = cellSize;
    numXCells = (int)ceil((float)mapWidth / cellSize);
    numYCells = (int)ceil((float)mapHeight / cellSize);

    lpCells.resize(numXCells * numYCells);
}

CGrid::~CGrid()
{
    for (size_t i = 0; i < lpCells.size(); i++)
    {
        for (size_t j = 0; j < lpCells[i].lpGameObjects.size(); j++)
        {
            delete lpCells[i].lpGameObjects[j];
        }
        lpCells[i].lpGameObjects.clear();
    }
    lpCells.clear();
}

void CGrid::AddGameObject(LPGAMEOBJECT gameObject)
{
    LPCELL cell = GetCell(gameObject->GetPosition());
    cell->lpGameObjects.push_back(gameObject);
    gameObject->SetOwnerCell(cell);
    gameObject->SetCellVectorIndex( cell->lpGameObjects.size() - 1);

}

void CGrid::AddGameObject(LPGAMEOBJECT gameObject, LPCELL cell)
{
    cell->lpGameObjects.push_back(gameObject);
    gameObject->SetOwnerCell(cell);
    gameObject->SetCellVectorIndex(cell->lpGameObjects.size() - 1);
}

LPCELL CGrid::GetCell(int x, int y)
{
    if (x < 0) x = 0;
    if (x > numXCells -1) x = numXCells - 1;
    if (y < 0) y = 0;
    if (y > numYCells -1) y = numYCells - 1;

    return &lpCells[y * numXCells + x];
}

LPCELL CGrid::GetCell(D3DXVECTOR2 pos)
{
    int cellX = (int)(pos.x / cellSize);
    int cellY = (int)(pos.y / cellSize);

    return GetCell(cellX, cellY);
}

void CGrid::SetCellUpdate(D3DXVECTOR2 start, D3DXVECTOR2 end)
{
    //convet to lower 
     startX = (int)(start.x / cellSize);
     startY = (int)(start.y / cellSize);

     if (startX < 0) startX = 0;
     else if (startX > numXCells - 1) startX = numXCells - 1;
     if (startY < 0) startY = 0;
     else if (startY > numYCells -1) startY = numYCells - 1;
     //convert to upper
     endX = (int)ceil(end.x / cellSize);
     endY = (int)ceil(end.y / cellSize);

     if (endX < 0) endX = 0;
     else if (endX > numXCells -1 ) endX = numXCells -1;
     if (endY < 0) endY = 0;
     else if (endY > numYCells -1) endY = numYCells - 1;


     //DebugOut(L"\n Start : %d,%d,         End : %d, %d ",startX, startY, endX, endY);

}

void CGrid::Update(DWORD dt)
{
    //DebugOut(L"\n");
    for(int i = startX; i<=endX; i++)
        for (int j = startY; j < endY;j++)
        {
            cell cell = lpCells[i + numXCells * j];
            //DebugOut(L"%d, %d \t", i, j);
            for (int k = 0; k < cell.lpGameObjects.size(); k++)  //Updating gameobject
            {
              
                LPGAMEOBJECT gameObject = cell.lpGameObjects[k];


                vector<LPGAMEOBJECT> cellLPGameObject;
                cellLPGameObject.clear();
                //Get object in objectCell
                cellLPGameObject.insert(cellLPGameObject.end(), cell.lpGameObjects.begin(), cell.lpGameObjects.end());
                int flag = 1;
                if (i > 0)
                {
                    flag = 0;
                    //Get object in objectCell left
                    cellLPGameObject.insert(cellLPGameObject.end(), 
                        lpCells[i -1 + numXCells * j].lpGameObjects.begin(), 
                        lpCells[i -1 + numXCells * j].lpGameObjects.end());
                    if (j > 0)
                    {
                        //Get object in objectCell topleft, top
                        cellLPGameObject.insert(cellLPGameObject.end(),
                            lpCells[i + numXCells * (j - 1)].lpGameObjects.begin(),
                            lpCells[i + numXCells * (j - 1)].lpGameObjects.end());
                        cellLPGameObject.insert(cellLPGameObject.end(),
                            lpCells[i - 1 + numXCells * (j - 1)].lpGameObjects.begin(),
                            lpCells[i - 1 + numXCells * (j - 1)].lpGameObjects.end());
                    }
                    if (j <numYCells -1)
                    {
                        //Get object in objectCell bottomLeft, bottom
                        cellLPGameObject.insert(cellLPGameObject.end(), 
                            lpCells[i + numXCells * (j + 1)].lpGameObjects.begin(),
                            lpCells[i + numXCells * (j + 1)].lpGameObjects.end());
                        cellLPGameObject.insert(cellLPGameObject.end(),
                            lpCells[i - 1 + numXCells * (j + 1)].lpGameObjects.begin(),
                            lpCells[i - 1 + numXCells * (j + 1)].lpGameObjects.end());
                    }
                }
                if (i < numXCells -1 )
                {
                    //Get object in objectCell right
                    cellLPGameObject.insert(cellLPGameObject.end(), 
                        lpCells[i + 1 + numXCells * j].lpGameObjects.begin(), 
                        lpCells[i + 1 + numXCells * j].lpGameObjects.end());
                    if (j > 0)
                    {
                        //Get object in objectCell top, righttop
                        if (flag)
                            cellLPGameObject.insert(cellLPGameObject.end(),
                                lpCells[i + numXCells * (j - 1)].lpGameObjects.begin(),
                                lpCells[i + numXCells * (j - 1)].lpGameObjects.end());

                            cellLPGameObject.insert(cellLPGameObject.end(), 
                                lpCells[i + 1 + numXCells * (j - 1)].lpGameObjects.begin(),
                                lpCells[i + 1 + numXCells * (j - 1)].lpGameObjects.end());
                    }
                    if (j < numYCells -1 )
                    {
                        //Get object in objectCell bottom, rightbottom
                        if (flag)
                            cellLPGameObject.insert(cellLPGameObject.end(),
                                lpCells[i + numXCells * (j + 1)].lpGameObjects.begin(), 
                                lpCells[i + numXCells * (j + 1)].lpGameObjects.end());

                            cellLPGameObject.insert(cellLPGameObject.end(),
                                lpCells[i + 1 + numXCells * (j + 1)].lpGameObjects.begin(), 
                                lpCells[i + 1 + numXCells * (j + 1)].lpGameObjects.end());
                    }
                }

                gameObject->Update(dt, &cellLPGameObject);

                LPCELL gOCell = this->GetCell(gameObject->GetPosition());
                if (gOCell != gameObject->GetOwnerCell())
                {
                    RemoveGameObjectFromCell(gameObject);
                    AddGameObject(gameObject, gOCell);
                }
            }
        }
}

void CGrid::PurgeDeletedObjects()
{
    for (size_t i = 0; i < lpCells.size(); i++)
    {
        for (int j = 0; j < lpCells[i].lpGameObjects.size(); j++)
        {
            LPGAMEOBJECT o = lpCells[i].lpGameObjects[j];
            if (o->IsDeleted())
            {
                RemoveGameObjectFromCell(o);
                delete o;
            }

        }
    }
}

void CGrid::Render()
{
    vector<LPGAMEOBJECT> lateRender;
    lateRender.clear();
    for (int i = startX; i <= endX; i++)
        for (int j = startY; j < endY;j++)
        {
            LPCELL cell = &lpCells[i + numXCells * j];
            for (int k = 0; k < cell->lpGameObjects.size(); k++)
            {
                if (cell->lpGameObjects[k]->IsLateRender())
                    lateRender.push_back(cell->lpGameObjects[k]);
                else
                    cell->lpGameObjects[k]->Render();
            }
        }
    for (int i = 0; i < lateRender.size();i++)
        lateRender[i]->Render();

}



void CGrid::RemoveGameObjectFromCell(LPGAMEOBJECT gameObject)
{
    vector<LPGAMEOBJECT>& lpGameObject = gameObject->GetOwnerCell()->lpGameObjects;
    // Normal vector swap
    lpGameObject[gameObject->GetCellVectorIndex()] = lpGameObject.back();
        
    lpGameObject.pop_back();
    // Update vector index
    if ((size_t)gameObject->GetCellVectorIndex() < lpGameObject.size()) {
        lpGameObject[gameObject->GetCellVectorIndex()]->SetCellVectorIndex(  gameObject->GetCellVectorIndex());
    }
    // Set the index of gameobject to -1
    gameObject->SetCellVectorIndex(-1);
    gameObject->SetOwnerCell(nullptr);

}
