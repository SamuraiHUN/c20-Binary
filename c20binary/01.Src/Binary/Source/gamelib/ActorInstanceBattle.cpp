search this:

BOOL CActorInstance::IsClickableDistanceDestInstance(CActorInstance& rkInstDst, float fDistance)
{
	TPixelPosition kPPosSrc;
	GetPixelPosition(&kPPosSrc);

	D3DXVECTOR3 kD3DVct3Src(kPPosSrc);

	TCollisionPointInstanceList& rkLstkDefPtInst = rkInstDst.m_DefendingPointInstanceList;
	TCollisionPointInstanceList::iterator i;

	for (i = rkLstkDefPtInst.begin(); i != rkLstkDefPtInst.end(); ++i)
	{
		CDynamicSphereInstanceVector& rkVctkDefSphere = (*i).SphereInstanceVector;

		CDynamicSphereInstanceVector::iterator j;
		for (j = rkVctkDefSphere.begin(); j != rkVctkDefSphere.end(); ++j)
		{
			CDynamicSphereInstance& rkSphere = (*j);

			float fMovDistance = D3DXVec3Length(&D3DXVECTOR3(rkSphere.v3Position - kD3DVct3Src));
			float fAtkDistance = rkSphere.fRadius + fDistance;

			if (fAtkDistance > fMovDistance)
				return TRUE;
		}
	}

	return FALSE;
}


modify to:

BOOL CActorInstance::IsClickableDistanceDestInstance(CActorInstance & rkInstDst, float fDistance)
{
	TPixelPosition kPPosSrc;
	GetPixelPosition(&kPPosSrc);

	D3DXVECTOR3 kD3DVct3Src(kPPosSrc);

	TCollisionPointInstanceList& rkLstkDefPtInst=rkInstDst.m_DefendingPointInstanceList;
	TCollisionPointInstanceList::iterator i;

	for (i=rkLstkDefPtInst.begin(); i!=rkLstkDefPtInst.end(); ++i)
	{
		CDynamicSphereInstanceVector& rkVctkDefSphere = (*i).SphereInstanceVector;

		CDynamicSphereInstanceVector::iterator j;
		for (j=rkVctkDefSphere.begin(); j!=rkVctkDefSphere.end(); ++j)
		{
			CDynamicSphereInstance& rkSphere = (*j);

			const auto vv = D3DXVECTOR3(rkSphere.v3Position - kD3DVct3Src);
			float fMovDistance = D3DXVec3Length(&vv);
			float fAtkDistance = rkSphere.fRadius + fDistance;

			if (fAtkDistance > fMovDistance)
				return TRUE;
		}
	}

	return FALSE;
}