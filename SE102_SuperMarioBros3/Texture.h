#pragma once

#include <d3d10.h>
#include <d3dx10.h>

//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class CTexture
{
protected:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _rsview;
	D3DXVECTOR2 size;
public:
	CTexture()
	{
		_tex = NULL;
		_rsview = NULL;
		size = D3DXVECTOR2(-1, -1);
	}

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);
		this->size.x= desc.Width;
		this->size.y = desc.Height;
		
	}

	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	D3DXVECTOR2 getSize() { return size; }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;
