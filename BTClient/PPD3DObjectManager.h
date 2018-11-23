#pragma once
#include <map>
#include "C:\Users\User\source\repos\BTClient\libppcore\PPCore.h"

class PPD3DObjectManager : public PPBasis {
public:
	std::map<uint64_t, PPD3DObject*> m_map;
	ID3D11Device*							m_pd3dDevice;
	ID3D11DeviceContext*					m_pd3dContext;
public:
	PPD3DObjectManager();
	virtual ~PPD3DObjectManager();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	bool SetID3D11Device(ID3D11Device* ID3D11Device);
	bool SetID3D11DeviceContext(ID3D11DeviceContext* ID3D11DeviceContext);
	int insert(uint64_t Handle, const TCHAR* texture, long x, long y, long ObjWidth, long ObjHeight, long u, long v, long uvWidth, long uvHeight);
};

