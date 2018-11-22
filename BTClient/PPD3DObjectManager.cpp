#include "PPD3DObjectManager.h"



PPD3DObjectManager::PPD3DObjectManager()
{
}


PPD3DObjectManager::~PPD3DObjectManager()
{
}

bool PPD3DObjectManager::Init()
{
	return false;
}

bool PPD3DObjectManager::Frame()
{
	for (auto& iter : m_map) {
		iter.second->Frame();
	}
	return true;
}

bool PPD3DObjectManager::Render()
{
	for (auto& iter : m_map) {
		iter.second->Render();
	}
	return true;
}

bool PPD3DObjectManager::Release()
{
	return false;
}

bool PPD3DObjectManager::SetID3D11Device(ID3D11Device * ID3D11Device)
{
	m_pd3dDevice = ID3D11Device;
	return true;
}

bool PPD3DObjectManager::SetID3D11DeviceContext(ID3D11DeviceContext * ID3D11DeviceContext)
{
	m_pd3dContext = ID3D11DeviceContext;
	return true;
}

int PPD3DObjectManager::insert(uint64_t Handle, const TCHAR* texture, long x, long y, long ObjWidth, long ObjHeight, long u, long v, long uvWidth, long uvHeight) {
	PPD3DObject* pObject = new PPD3DObject;
	pObject->SetID3D11Device(this->m_pd3dDevice);
	pObject->SetID3D11DeviceContext(this->m_pd3dContext);
	pObject->m_SetPositionAndSize(x, y, ObjWidth, ObjHeight);
	pObject->m_LoadTexture(texture);
	//pObject->m_LoadTexture(L"../Texture/LegalWarning.png");
	pObject->m_SetTexelPositionAndSize(u, v, uvWidth, uvHeight);
	pObject->Init();

	m_map.insert(std::pair<uint64_t, PPD3DObject*>(Handle, pObject));

	return 0;
}
