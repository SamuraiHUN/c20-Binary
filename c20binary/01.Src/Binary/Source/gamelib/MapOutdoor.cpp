search this:

	if (bObjectPick && bTerrainPick)
	{
		if ( D3DXVec3Length( &(v3ObjectPick - v3Start) ) >= D3DXVec3Length( &(v3TerrainPick - v3Start) ) )
			*v3IntersectPt = v3TerrainPick;
		else
			*v3IntersectPt = v3ObjectPick;
		return true;
	}
	
modify to:

	if (bObjectPick && bTerrainPick)
	{
		const auto vv = (v3TerrainPick - v3Start);
		const auto vv2 = (v3ObjectPick - v3Start);
		if (D3DXVec3Length(&vv2) >= D3DXVec3Length(&vv))
			*v3IntersectPt = v3TerrainPick;
		else
			*v3IntersectPt = v3ObjectPick;
		return true;
	}