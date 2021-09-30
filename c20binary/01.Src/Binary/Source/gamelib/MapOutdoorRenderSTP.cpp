search this:

	D3DXVECTOR3 kFogNearVector;
	D3DXVec3TransformCoord(&kFogNearVector, &D3DXVECTOR3(0.0f, 0.0f, -rkTPRS.m_fFogNearDistance), &rkTPRS.m_m4Proj);

	D3DXVECTOR3 kFogFarVector;
	D3DXVec3TransformCoord(&kFogFarVector, &D3DXVECTOR3(0.0f, 0.0f, -rkTPRS.m_fFogFarDistance), &rkTPRS.m_m4Proj);


modify to:

	D3DXVECTOR3 kFogNearVector;
	const auto farvv = D3DXVECTOR3(0.0f, 0.0f, -rkTPRS.m_fFogNearDistance);
	D3DXVec3TransformCoord(&kFogNearVector, &farvv, &rkTPRS.m_m4Proj);

	D3DXVECTOR3 kFogFarVector;
	const auto nearvv = D3DXVECTOR3(0.0f, 0.0f, -rkTPRS.m_fFogFarDistance);
	D3DXVec3TransformCoord(&kFogFarVector, &nearvv, &rkTPRS.m_m4Proj);