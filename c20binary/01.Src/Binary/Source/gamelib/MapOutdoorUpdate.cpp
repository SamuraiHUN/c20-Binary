search this.

struct FPCBlockerDistanceSort
{
	D3DXVECTOR3 m_v3Eye;
	FPCBlockerDistanceSort(D3DXVECTOR3 & v3Eye) : m_v3Eye(v3Eye) { }

	bool operator () (CGraphicObjectInstance * plhs, CGraphicObjectInstance * prhs) const
	{
		return D3DXVec3LengthSq(&(plhs->GetPosition() - m_v3Eye)) > D3DXVec3LengthSq(&(prhs->GetPosition() - m_v3Eye));
	}
};

change to:

struct FPCBlockerDistanceSort
{
	D3DXVECTOR3 m_v3Eye;
	FPCBlockerDistanceSort(D3DXVECTOR3& v3Eye) : m_v3Eye(v3Eye) { }

	bool operator () (CGraphicObjectInstance* plhs, CGraphicObjectInstance* prhs) const
	{
		const auto vv = (plhs->GetPosition() - m_v3Eye);
		const auto vv2 = (prhs->GetPosition() - m_v3Eye);
		return D3DXVec3LengthSq(&vv) > D3DXVec3LengthSq(&vv2);
	}
};

overwrite this function (all)

void CMapOutdoor::UpdateAreaList(long lCenterX, long lCenterY)

with this:


void CMapOutdoor::UpdateAreaList(long lCenterX, long lCenterY)
{
	if (m_TerrainVector.size() <= AROUND_AREA_NUM && m_AreaVector.size() <= AROUND_AREA_NUM)
		return;

	__ClearGarvage();

	FPushToDeleteVector::EDeleteDir eDeleteLRDir, eDeleteTBDir;

	if (lCenterX > CTerrainImpl::XSIZE / 2)
		eDeleteLRDir = FPushToDeleteVector::DELETE_LEFT;
	else
		eDeleteLRDir = FPushToDeleteVector::DELETE_RIGHT;
	if (lCenterY > CTerrainImpl::YSIZE / 2)
		eDeleteTBDir = FPushToDeleteVector::DELETE_TOP;
	else
		eDeleteTBDir = FPushToDeleteVector::DELETE_BOTTOM;

	FPushTerrainToDeleteVector rPushTerrainToDeleteVector = std::for_each(m_TerrainVector.begin(), m_TerrainVector.end(),
		FPushTerrainToDeleteVector(eDeleteLRDir, eDeleteTBDir, m_CurCoordinate));
	FPushAreaToDeleteVector rPushAreaToDeleteVector = std::for_each(m_AreaVector.begin(), m_AreaVector.end(),
		FPushAreaToDeleteVector(eDeleteLRDir, eDeleteTBDir, m_CurCoordinate));

	if (!rPushTerrainToDeleteVector.m_ReturnTerrainVector.empty())
	{
		m_TerrainDeleteVector.resize(rPushTerrainToDeleteVector.m_ReturnTerrainVector.size());
		std::copy(rPushTerrainToDeleteVector.m_ReturnTerrainVector.begin(), rPushTerrainToDeleteVector.m_ReturnTerrainVector.end(), m_TerrainDeleteVector.begin());

		for (DWORD dwIndex = 0; dwIndex < rPushTerrainToDeleteVector.m_ReturnTerrainVector.size(); ++dwIndex)
		{
			bool isDel=false;
			TTerrainPtrVectorIterator aTerrainPtrItertor = m_TerrainVector.begin();
			while(aTerrainPtrItertor != m_TerrainVector.end())
			{
				CTerrain * pTerrain = *aTerrainPtrItertor;
				if (pTerrain == rPushTerrainToDeleteVector.m_ReturnTerrainVector[dwIndex])
				{
					aTerrainPtrItertor = m_TerrainVector.erase(aTerrainPtrItertor);
					isDel=true;
				}
				else
					++aTerrainPtrItertor;
			}
		}
	}
	if (!rPushAreaToDeleteVector.m_ReturnAreaVector.empty())
	{
		m_AreaDeleteVector.resize(rPushAreaToDeleteVector.m_ReturnAreaVector.size());
		std::copy(rPushAreaToDeleteVector.m_ReturnAreaVector.begin(), rPushAreaToDeleteVector.m_ReturnAreaVector.end(), m_AreaDeleteVector.begin());

		for (DWORD dwIndex = 0; dwIndex < rPushAreaToDeleteVector.m_ReturnAreaVector.size(); ++dwIndex)
		{
			TAreaPtrVectorIterator aAreaPtrItertor = m_AreaVector.begin();
			while(aAreaPtrItertor != m_AreaVector.end())
			{
				CArea * pArea = *aAreaPtrItertor;
				if (pArea == rPushAreaToDeleteVector.m_ReturnAreaVector[dwIndex])
					aAreaPtrItertor = m_AreaVector.erase(aAreaPtrItertor);
				else
					++aAreaPtrItertor;
			}
		}
	}
}