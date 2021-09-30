search this:

void CDecal::ClipMesh(DWORD dwPrimitiveCount, const D3DXVECTOR3 *c_pv3Vertex, const D3DXVECTOR3 *c_pv3Normal)
{
	D3DXVECTOR3		v3NewVertex[9];
	D3DXVECTOR3		v3NewNormal[9];

	// Clip one triangle at a time
	for(DWORD dwi = 0; dwi < dwPrimitiveCount; ++dwi)
	{
		const D3DXVECTOR3 & v3_1 = c_pv3Vertex[3 * dwi];
		const D3DXVECTOR3 & v3_2 = c_pv3Vertex[3 * dwi + 1];
		const D3DXVECTOR3 & v3_3 = c_pv3Vertex[3 * dwi + 2];

		D3DXVECTOR3 v3Cross;
		D3DXVec3Cross(&v3Cross, &(v3_2 - v3_1), &(v3_3 - v3_1));
		if (D3DXVec3Dot(&m_v3Normal, &v3Cross) > ( m_cfDecalEpsilon ) * D3DXVec3Length(&v3Cross))
		{
			v3NewVertex[0] = v3_1;
			v3NewVertex[1] = v3_2;
			v3NewVertex[2] = v3_3;

			v3NewNormal[0] = c_pv3Normal[3 * dwi];
			v3NewNormal[1] = c_pv3Normal[3 * dwi + 1];
			v3NewNormal[2] = c_pv3Normal[3 * dwi + 2];

			DWORD dwCount = ClipPolygon(3, v3NewVertex, v3NewNormal, v3NewVertex, v3NewNormal);
			if ((dwCount != 0) && (!AddPolygon(dwCount, v3NewVertex, v3NewNormal))) break;
 		}
	}
}

modify to:

void CDecal::ClipMesh(DWORD dwPrimitiveCount, const D3DXVECTOR3 *c_pv3Vertex, const D3DXVECTOR3 *c_pv3Normal)
{
	D3DXVECTOR3		v3NewVertex[9];
	D3DXVECTOR3		v3NewNormal[9];

	// Clip one triangle at a time
	for (DWORD dwi = 0; dwi < dwPrimitiveCount; ++dwi)
	{
		const D3DXVECTOR3& v3_1 = c_pv3Vertex[3 * dwi];
		const D3DXVECTOR3& v3_2 = c_pv3Vertex[3 * dwi + 1];
		const D3DXVECTOR3& v3_3 = c_pv3Vertex[3 * dwi + 2];

		D3DXVECTOR3 v3Cross;
		const auto vv_ = (v3_2 - v3_1);
		const auto vv_2 = (v3_3 - v3_1);
		D3DXVec3Cross(&v3Cross, &vv_, &vv_2);
		if (D3DXVec3Dot(&m_v3Normal, &v3Cross) > (m_cfDecalEpsilon) *D3DXVec3Length(&v3Cross))
		{
			v3NewVertex[0] = v3_1;
			v3NewVertex[1] = v3_2;
			v3NewVertex[2] = v3_3;

			v3NewNormal[0] = c_pv3Normal[3 * dwi];
			v3NewNormal[1] = c_pv3Normal[3 * dwi + 1];
			v3NewNormal[2] = c_pv3Normal[3 * dwi + 2];

			DWORD dwCount = ClipPolygon(3, v3NewVertex, v3NewNormal, v3NewVertex, v3NewNormal);
			if ((dwCount != 0) && (!AddPolygon(dwCount, v3NewVertex, v3NewNormal))) break;
		}
	}
}