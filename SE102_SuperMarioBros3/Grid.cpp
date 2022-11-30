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
        for (size_t j = 0; j < lpCells[i]->lpGameObjects.size(); j++)
        {
            delete lpCells[i]->lpGameObjects[j];
        }
        lpCells[i]->lpGameObjects.clear();
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
    if (x >= numXCells) x = numXCells - 1;
    if (y < 0) y = 0;
    if (y >= numYCells) y = numYCells - 1;

    return lpCells[y * numXCells + x];
}

LPCELL CGrid::GetCell(D3DXVECTOR2 pos)
{
    int cellX = (int)(pos.x / cellSize);
    int cellY = (int)(pos.y / cellSize);

    return GetCell(cellX, cellY);
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
    // Set the index of ball to -1
    gameObject->SetCellVectorIndex(-1);
    gameObject->SetOwnerCell(nullptr);

}
