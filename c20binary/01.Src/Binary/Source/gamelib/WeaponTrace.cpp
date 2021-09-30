search this:

bool CWeaponTrace::SetWeaponInstance(CGraphicThingInstance * pInstance, DWORD dwModelIndex, const char * c_szBoneName)
{
	pInstance->Update();
	pInstance->DeformNoSkin();

	D3DXVECTOR3 v3Min;
	D3DXVECTOR3 v3Max;
	if (!pInstance->GetBoundBox(dwModelIndex, &v3Min, &v3Max))
		return false;

	m_iBoneIndex = 0;
	m_dwModelInstanceIndex = dwModelIndex;

	m_pInstance = pInstance;
	D3DXMATRIX * pmat;
	pInstance->GetBoneMatrix(dwModelIndex, 0, &pmat);
	D3DXVECTOR3 v3Bone(pmat->_41,pmat->_42,pmat->_43);

	m_fLength =
		sqrtf(
			fMAX(
				D3DXVec3LengthSq(&(v3Bone-v3Min)),
				D3DXVec3LengthSq(&(v3Bone-v3Max))
				)
			);

	return true;
}

modify to:

bool CWeaponTrace::SetWeaponInstance(CGraphicThingInstance * pInstance, DWORD dwModelIndex, const char * c_szBoneName)
{
	pInstance->Update();
	pInstance->DeformNoSkin();

	D3DXVECTOR3 v3Min;
	D3DXVECTOR3 v3Max;
	if (!pInstance->GetBoundBox(dwModelIndex, &v3Min, &v3Max))
		return false;

	m_iBoneIndex = 0;
	m_dwModelInstanceIndex = dwModelIndex;

	m_pInstance = pInstance;
	D3DXMATRIX * pmat;
	pInstance->GetBoneMatrix(dwModelIndex, 0, &pmat);
	D3DXVECTOR3 v3Bone(pmat->_41, pmat->_42, pmat->_43);

	const auto vv1 = (v3Bone - v3Min);
	const auto vv2 = (v3Bone - v3Max);
	m_fLength =
		sqrtf(
			fMAX(
				D3DXVec3LengthSq(&vv1),
				D3DXVec3LengthSq(&vv2)
			)
		);

	return true;
}