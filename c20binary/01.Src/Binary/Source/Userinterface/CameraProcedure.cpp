search this:

	if (rPythonBackground.GetPickingPointWithRayOnlyTerrain(m_kCameraBottomToTerrainRay, &v3CollisionPoint))
	{
		SetCameraState(CAMERA_STATE_CANTGODOWN);
		if (D3DXVec3Length(&(m_v3Eye - v3CollisionPoint)) < 2.0f * m_fTerrainCollisionRadius)
		{
			D3DXVECTOR3 v3NewEye = v3CollisionPoint + 2.0f * m_fTerrainCollisionRadius * m_v3Up;
			//printf("CameraBottomToTerrain new %f > old %f", v3NewEye.z, m_v3Eye.z);
			SetEye(v3NewEye);
		}
	}
	else
		SetCameraState(CAMERA_STATE_NORMAL);

change to:

	if (rPythonBackground.GetPickingPointWithRayOnlyTerrain(m_kCameraBottomToTerrainRay, &v3CollisionPoint))
	{
		SetCameraState(CAMERA_STATE_CANTGODOWN);
		auto d3dd = (m_v3Eye - v3CollisionPoint);
		if (D3DXVec3Length(&d3dd) < 2.0f * m_fTerrainCollisionRadius)
		{
			D3DXVECTOR3 v3NewEye = v3CollisionPoint + 2.0f * m_fTerrainCollisionRadius * m_v3Up;
			//printf("CameraBottomToTerrain new %f > old %f", v3NewEye.z, m_v3Eye.z);
			SetEye(v3NewEye);
		}
	}
	else
		SetCameraState(CAMERA_STATE_NORMAL);