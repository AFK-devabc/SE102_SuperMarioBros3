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
	int width;
	int height;
public:
	CTexture()
	{
		_tex = NULL;
		_rsview = NULL;
		width = height = -1;
	}

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);
		width= desc.Width;
		height = desc.Height;
	}



	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	int getWidth() { return this->width; }
	int getHeight() { return this->height; }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;
