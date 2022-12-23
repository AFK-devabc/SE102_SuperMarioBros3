#pragma once
#include <vector>
#include "Collision.h"
#include "GameObject.h"
struct  cell
{
	vector<LPGAMEOBJECT> lpGameObjects;
};
class CGrid
{
private:
	vector<cell> lpCells;
    int cellSize;
    int mapWidth;
    int mapHeight;
    int numXCells;
    int numYCells;
    int startX, startY, endX, endY;
public:
    CGrid(int width, int height, int cellSize);
    ~CGrid();

    /// Adds a ball and determines which cell it belongs to
    void AddGameObject(LPGAMEOBJECT gameObject);
    /// Adds a ball to the specified cell
    void AddGameObject(LPGAMEOBJECT gameObject, LPCELL cell);
    /// Gets cell based on cell coordinates
    LPCELL GetCell(int x, int y);
    /// Gets cell based on window coordinates
    LPCELL GetCell(D3DXVECTOR2 pos);
    D3DXVECTOR2 GetWorldSize() { return D3DXVECTOR2(mapWidth, mapHeight); }
    void SetCellUpdate( D3DXVECTOR2 start, D3DXVECTOR2 end);

    void Update(DWORD dt);
    void PurgeDeletedObjects();
    void Render();

    void RemoveGameObjectFromCell(LPGAMEOBJECT gameObject);
};

