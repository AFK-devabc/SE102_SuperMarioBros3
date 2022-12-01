#pragma once
#include "GameObject.h"
class CPlatform :
    public CGameObject
{
	protected:
		int length;				// Unit: cell 
		float cellWidth;
		float cellHeight;
		string spriteIdBegin, spriteIdMiddle, spriteIdEnd;

	public:
		CPlatform(float x, float y,
			float cell_width, float cell_height, int length,
			string sprite_id_begin, string sprite_id_middle, string sprite_id_end) :CGameObject(D3DXVECTOR2(x, y))
		{
			this->length = length;
			this->cellWidth = cell_width;
			this->cellHeight = cell_height;
			this->spriteIdBegin = sprite_id_begin;
			this->spriteIdMiddle = sprite_id_middle;
			this->spriteIdEnd = sprite_id_end;
		}

		void GetBoundingBox(float& l, float& t, float& r, float& b);

		void Render();

		virtual int IsCollidable() { return 0; };
		virtual int IsBlocking() { return 1; }

	};

	typedef CPlatform* LPPLATFORM;

