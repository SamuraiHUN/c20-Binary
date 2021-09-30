search this:

void CDungeonBlock::BuildBoundingSphere()
{
	D3DXVECTOR3 v3Min, v3Max;
	for_each(m_ModelInstanceContainer.begin(), m_ModelInstanceContainer.end(), FBoundBox(&v3Min, &v3Max));

	m_v3Center = (v3Min+v3Max) * 0.5f;
	m_fRadius = D3DXVec3Length(&(v3Max-v3Min))*0.5f + 150.0f; // extra length for attached objects
}

modify to:

void CDungeonBlock::BuildBoundingSphere()
{
	D3DXVECTOR3 v3Min, v3Max;
	for_each(m_ModelInstanceContainer.begin(), m_ModelInstanceContainer.end(), FBoundBox(&v3Min, &v3Max));

	m_v3Center = (v3Min + v3Max) * 0.5f;
	const auto vv = (v3Max - v3Min);
	m_fRadius = D3DXVec3Length(&vv) * 0.5f + 150.0f; // extra length for attached objects
}