search this:


void CMapOutdoor::SetInverseViewAndDynamicShaodwMatrices()
{
	CCamera * pCamera = CCameraManager::Instance().GetCurrentCamera();

	if (!pCamera)
		return;

	m_matViewInverse = pCamera->GetInverseViewMatrix();

	D3DXVECTOR3 v3Target = pCamera->GetTarget();

	D3DXVECTOR3 v3LightEye(v3Target.x - 1.732f * 1250.0f,
						   v3Target.y - 1250.0f,
						   v3Target.z + 2.0f * 1.732f * 1250.0f);

	D3DXMatrixLookAtRH(&m_matLightView, &v3LightEye, &v3Target, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_matDynamicShadow = m_matViewInverse * m_matLightView * m_matDynamicShadowScale;
}

modify to:

void CMapOutdoor::SetInverseViewAndDynamicShaodwMatrices()
{
	CCamera* pCamera = CCameraManager::Instance().GetCurrentCamera();

	if (!pCamera)
		return;

	m_matViewInverse = pCamera->GetInverseViewMatrix();

	D3DXVECTOR3 v3Target = pCamera->GetTarget();

	D3DXVECTOR3 v3LightEye(v3Target.x - 1.732f * 1250.0f,
		v3Target.y - 1250.0f,
		v3Target.z + 2.0f * 1.732f * 1250.0f);

	const auto vv = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtRH(&m_matLightView, &v3LightEye, &v3Target, &vv);
	m_matDynamicShadow = m_matViewInverse * m_matLightView * m_matDynamicShadowScale;
}


search this:

struct CMapOutdoor_LessThingInstancePtrRenderOrder
{
	bool operator() (CGraphicThingInstance* pkLeft, CGraphicThingInstance* pkRight)
	{
		CCamera * pCurrentCamera = CCameraManager::Instance().GetCurrentCamera();
		const D3DXVECTOR3 & c_rv3CameraPos = pCurrentCamera->GetEye();
		const D3DXVECTOR3 & c_v3LeftPos  = pkLeft->GetPosition();
		const D3DXVECTOR3 & c_v3RightPos = pkRight->GetPosition();

		return D3DXVec3LengthSq(&D3DXVECTOR3(c_rv3CameraPos - c_v3LeftPos)) < D3DXVec3LengthSq(&D3DXVECTOR3(c_rv3CameraPos - c_v3RightPos) );
	}
};

modify to:

struct CMapOutdoor_LessThingInstancePtrRenderOrder
{
	bool operator() (CGraphicThingInstance* pkLeft, CGraphicThingInstance* pkRight)
	{
		//TODO : Camera위치기반으로 소팅
		CCamera* pCurrentCamera = CCameraManager::Instance().GetCurrentCamera();
		const D3DXVECTOR3& c_rv3CameraPos = pCurrentCamera->GetEye();
		const D3DXVECTOR3& c_v3LeftPos = pkLeft->GetPosition();
		const D3DXVECTOR3& c_v3RightPos = pkRight->GetPosition();
		const auto vv = D3DXVECTOR3(c_rv3CameraPos - c_v3RightPos);
		const auto vv2 = D3DXVECTOR3(c_rv3CameraPos - c_v3LeftPos);

		return D3DXVec3LengthSq(&vv2) < D3DXVec3LengthSq(&vv);
	}
};

search this:


	BuildViewFrustum(ms_matView * ms_matProj);
	
modify to:

	auto vv = ms_matView * ms_matProj;
	BuildViewFrustum(vv);