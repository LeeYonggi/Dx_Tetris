#include "DXUT.h"
#include "ImageManager.h"


HRESULT ImageManager::AddImage(string str, LPCWSTR route)
{
	auto iter = m_Texture.find(str);
	if (iter != m_Texture.end()) return E_FAIL;
	Texture *tex = new Texture;
	D3DXCreateTextureFromFileEx
	(
		DEVICE,
		route,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0, &tex->info, nullptr, &tex->tex
	);
	m_Texture.insert(make_pair(str, tex));

	return S_OK;
}

HRESULT ImageManager::DrawImage(string str, D3DXVECTOR2 pos, float scale, float angle, Color color)
{
	auto iter = m_Texture.find(str);
	if (iter == m_Texture.end()) return E_NOTIMPL;
	
	D3DXMATRIX matWorld, matS, matR, matT;

	D3DXMatrixScaling(&matS, scale, scale, 1);
	D3DXMatrixRotationZ(&matR, angle);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matWorld = matS * matR * matT;

	sprite->SetTransform(&matWorld);

	D3DXVECTOR3 center = { (FLOAT)iter->second->info.Width / 2, (FLOAT)iter->second->info.Height / 2, 0 };

	sprite->Draw(iter->second->tex, nullptr, &center, nullptr, D3DCOLOR_RGBA(color.r, color.g, color.b, color.alpha));
	return S_OK;
}

ImageManager::ImageManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
}


ImageManager::~ImageManager()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
	sprite->Release();
}
