search this:

void CCamera::SetViewMatrix()
{
	m_v3View = m_v3Target - m_v3Eye;
	D3DXVECTOR3 v3CenterRay = -m_v3View;
 	CalculateRoll();
	m_fDistance = D3DXVec3Length(&m_v3View);
	assert(m_fDistance >= 0);
	D3DXVec3Normalize(&m_v3View , &m_v3View);

    D3DXVec3Cross(&m_v3Cross, &m_v3Up, &m_v3View);
	D3DXVec3Normalize(&m_v3Cross, &m_v3Cross);

    D3DXVec3Cross(&m_v3Up, &m_v3View, &m_v3Cross);
	D3DXVec3Normalize(&m_v3Up, &m_v3Up);

	m_fPitch = D3DXVec3Dot(&m_v3Up, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));// / D3DXVec2Length(&v2ViewYZ);
	if (m_fPitch >= 1)
		m_fPitch = 1;
	else if (m_fPitch <= -1)
		m_fPitch = -1;
	m_fPitch = acosf(m_fPitch);
	m_fPitch *= (180.0f / D3DX_PI);
	if ( 0 < m_v3View.z )
		m_fPitch = -m_fPitch;

	D3DXMatrixLookAtRH(&m_matView, &m_v3Eye, &m_v3Target, &m_v3Up);

	float fDeterminantD3DMatView = D3DXMatrixfDeterminant(&m_matView);
    D3DXMatrixInverse(&m_matInverseView, &fDeterminantD3DMatView, &m_matView);

	m_matBillboard = m_matInverseView;
    m_matBillboard._41 = 0.0f;
    m_matBillboard._42 = 0.0f;
    m_matBillboard._43 = 0.0f;

	m_ViewRay.SetStartPoint(m_v3Target);
	m_ViewRay.SetDirection(v3CenterRay, m_fDistance);

	m_kCameraBottomToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraFrontToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraBackToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraLeftToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraRightToTerrainRay.SetStartPoint(m_v3Eye);
	m_kTargetToCameraBottomRay.SetStartPoint(m_v3Target);

	m_kCameraBottomToTerrainRay.SetDirection(-m_v3Up, 2.0f * m_fTerrainCollisionRadius);
	m_kCameraFrontToTerrainRay.SetDirection(m_v3View, 4.0f * m_fTerrainCollisionRadius);
	m_kCameraBackToTerrainRay.SetDirection(-m_v3View, m_fTerrainCollisionRadius);
	m_kCameraLeftToTerrainRay.SetDirection(-m_v3Cross, 3.0f * m_fTerrainCollisionRadius);
	m_kCameraRightToTerrainRay.SetDirection(m_v3Cross, 3.0f * m_fTerrainCollisionRadius);
	m_kTargetToCameraBottomRay.SetDirection(v3CenterRay - m_fTerrainCollisionRadius * m_v3Up,
		D3DXVec3Length(&(v3CenterRay - m_fTerrainCollisionRadius * m_v3Up)));

	m_kLeftObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kTopObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kRightObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kBottomObjectCollisionRay.SetStartPoint(m_v3Target);

	m_kLeftObjectCollisionRay.SetDirection(v3CenterRay + m_fObjectCollisionRadius * m_v3Cross,
		D3DXVec3Length(&(v3CenterRay + m_fObjectCollisionRadius * m_v3Cross)));
	m_kRightObjectCollisionRay.SetDirection(v3CenterRay - m_fObjectCollisionRadius * m_v3Cross,
		D3DXVec3Length(&(v3CenterRay - m_fObjectCollisionRadius * m_v3Cross)));
	m_kTopObjectCollisionRay.SetDirection(v3CenterRay + m_fObjectCollisionRadius * m_v3Up,
		D3DXVec3Length(&(v3CenterRay + m_fObjectCollisionRadius * m_v3Up)));
	m_kBottomObjectCollisionRay.SetDirection(v3CenterRay - m_fObjectCollisionRadius * m_v3Up,
		D3DXVec3Length(&(v3CenterRay + m_fObjectCollisionRadius * m_v3Up)));
}


change to:


void CCamera::SetViewMatrix()
{
	m_v3View = m_v3Target - m_v3Eye;
	D3DXVECTOR3 v3CenterRay = -m_v3View;
	CalculateRoll();
	m_fDistance = D3DXVec3Length(&m_v3View);
	assert(m_fDistance >= 0);
	D3DXVec3Normalize(&m_v3View, &m_v3View);

	D3DXVec3Cross(&m_v3Cross, &m_v3Up, &m_v3View);
	D3DXVec3Normalize(&m_v3Cross, &m_v3Cross);

	D3DXVec3Cross(&m_v3Up, &m_v3View, &m_v3Cross);
	D3DXVec3Normalize(&m_v3Up, &m_v3Up);
	const auto vv = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_fPitch = D3DXVec3Dot(&m_v3Up, &vv);// / D3DXVec2Length(&v2ViewYZ);
	if (m_fPitch >= 1)
		m_fPitch = 1;
	else if (m_fPitch <= -1)
		m_fPitch = -1;
	m_fPitch = acosf(m_fPitch);
	m_fPitch *= (180.0f / D3DX_PI);
	if (0 < m_v3View.z)
		m_fPitch = -m_fPitch;

	D3DXMatrixLookAtRH(&m_matView, &m_v3Eye, &m_v3Target, &m_v3Up);

	float fDeterminantD3DMatView = D3DXMatrixfDeterminant(&m_matView);
	D3DXMatrixInverse(&m_matInverseView, &fDeterminantD3DMatView, &m_matView);

	m_matBillboard = m_matInverseView;
	m_matBillboard._41 = 0.0f;
	m_matBillboard._42 = 0.0f;
	m_matBillboard._43 = 0.0f;

	m_ViewRay.SetStartPoint(m_v3Target);
	m_ViewRay.SetDirection(v3CenterRay, m_fDistance);

	m_kCameraBottomToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraFrontToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraBackToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraLeftToTerrainRay.SetStartPoint(m_v3Eye);
	m_kCameraRightToTerrainRay.SetStartPoint(m_v3Eye);
	m_kTargetToCameraBottomRay.SetStartPoint(m_v3Target);

	m_kCameraBottomToTerrainRay.SetDirection(-m_v3Up, 2.0f * m_fTerrainCollisionRadius);
	m_kCameraFrontToTerrainRay.SetDirection(m_v3View, 4.0f * m_fTerrainCollisionRadius);
	m_kCameraBackToTerrainRay.SetDirection(-m_v3View, m_fTerrainCollisionRadius);
	m_kCameraLeftToTerrainRay.SetDirection(-m_v3Cross, 3.0f * m_fTerrainCollisionRadius);
	m_kCameraRightToTerrainRay.SetDirection(m_v3Cross, 3.0f * m_fTerrainCollisionRadius);
	const auto vv2 = (v3CenterRay - m_fTerrainCollisionRadius * m_v3Up);
	m_kTargetToCameraBottomRay.SetDirection(v3CenterRay - m_fTerrainCollisionRadius * m_v3Up, D3DXVec3Length(&vv2));

	m_kLeftObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kTopObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kRightObjectCollisionRay.SetStartPoint(m_v3Target);
	m_kBottomObjectCollisionRay.SetStartPoint(m_v3Target);
	const auto vv3 = (v3CenterRay + m_fObjectCollisionRadius * m_v3Cross);
	const auto vv4 = (v3CenterRay - m_fObjectCollisionRadius * m_v3Cross);
	const auto vv5 = (v3CenterRay + m_fObjectCollisionRadius * m_v3Up);
	const auto vv6 = (v3CenterRay + m_fObjectCollisionRadius * m_v3Up);
	m_kLeftObjectCollisionRay.SetDirection(v3CenterRay + m_fObjectCollisionRadius * m_v3Cross, D3DXVec3Length(&vv3));
	m_kRightObjectCollisionRay.SetDirection(v3CenterRay - m_fObjectCollisionRadius * m_v3Cross, D3DXVec3Length(&vv4));
	m_kTopObjectCollisionRay.SetDirection(v3CenterRay + m_fObjectCollisionRadius * m_v3Up, D3DXVec3Length(&vv5));
	m_kBottomObjectCollisionRay.SetDirection(v3CenterRay - m_fObjectCollisionRadius * m_v3Up, D3DXVec3Length(&vv6));
}


change this:


void CCamera::RotateEyeAroundPoint(const D3DXVECTOR3 & v3Point, float fPitchDegree, float fRollDegree)
{
//	if (IsLock())
//		return;

	D3DXMATRIX matRot, matRotPitch, matRotRoll;

	D3DXMatrixRotationAxis(&matRotPitch, &m_v3Cross, D3DXToRadian(fPitchDegree));

	D3DXMatrixRotationZ(&matRotRoll, -D3DXToRadian(fRollDegree));
	matRot = matRotPitch * matRotRoll;

	D3DXVECTOR3 v3Temp = m_v3Eye - v3Point;
	D3DXVec3TransformCoord(&m_v3Eye, &v3Temp, &matRot);
	m_v3Eye += v3Point;

	D3DXVec3TransformCoord(&m_v3Up, &(v3Temp + m_v3Up), &matRot);
	m_v3Up -= (m_v3Eye - v3Point);

	v3Temp = m_v3Target - v3Point;
	D3DXVec3TransformCoord(&m_v3Target, &v3Temp, &matRot);
	m_v3Target += v3Point;

	SetViewMatrix();
}



to this:

void CCamera::RotateEyeAroundPoint(const D3DXVECTOR3& v3Point, float fPitchDegree, float fRollDegree)
{
	//	if (IsLock())
	//		return;

	D3DXMATRIX matRot, matRotPitch, matRotRoll;

	D3DXMatrixRotationAxis(&matRotPitch, &m_v3Cross, D3DXToRadian(fPitchDegree));

	D3DXMatrixRotationZ(&matRotRoll, -D3DXToRadian(fRollDegree));
	matRot = matRotPitch * matRotRoll;

	D3DXVECTOR3 v3Temp = m_v3Eye - v3Point;
	D3DXVec3TransformCoord(&m_v3Eye, &v3Temp, &matRot);
	m_v3Eye += v3Point;

	const auto vv2 = (v3Temp + m_v3Up);
	D3DXVec3TransformCoord(&m_v3Up, &vv2, &matRot);
	m_v3Up -= (m_v3Eye - v3Point);

	v3Temp = m_v3Target - v3Point;
	D3DXVec3TransformCoord(&m_v3Target, &v3Temp, &matRot);
	m_v3Target += v3Point;

	SetViewMatrix();
}



search this:



void CCamera::CalculateRoll()
{
	D3DXVECTOR2 v2ViewXY;
	v2ViewXY.x = m_v3View.x;
	v2ViewXY.y = m_v3View.y;
 	D3DXVec2Normalize(&v2ViewXY, &v2ViewXY);
	float fDot = D3DXVec2Dot(&v2ViewXY, &D3DXVECTOR2(0.0f, 1.0f));
	if (fDot >= 1)
		fDot = 1;
	else if (fDot <= -1)
		fDot = -1;
	fDot = acosf(fDot);
	fDot *= (180.0f / D3DX_PI);
	float fCross = D3DXVec2CCW (&v2ViewXY, &D3DXVECTOR2(0.0f, 1.0f));
	if ( 0 > fCross)
	{
		fDot = -fDot;
	}

	m_fRoll = fDot;

}


change with:


void CCamera::CalculateRoll()
{
	D3DXVECTOR2 v2ViewXY;
	v2ViewXY.x = m_v3View.x;
	v2ViewXY.y = m_v3View.y;
	D3DXVec2Normalize(&v2ViewXY, &v2ViewXY);
	const auto vv = D3DXVECTOR2(0.0f, 1.0f);
	float fDot = D3DXVec2Dot(&v2ViewXY, &vv);
	if (fDot >= 1)
		fDot = 1;
	else if (fDot <= -1)
		fDot = -1;
	fDot = acosf(fDot);
	fDot *= (180.0f / D3DX_PI);
	float fCross = D3DXVec2CCW(&v2ViewXY, &vv);
	if (0 > fCross)
	{
		fDot = -fDot;
	}

	m_fRoll = fDot;

}