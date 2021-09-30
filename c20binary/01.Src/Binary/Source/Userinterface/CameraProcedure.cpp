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

search this:

		if (bCollide)
		{
			if (m_v3AngularVelocity.y > 0.0f)
			{
				m_v3AngularVelocity.y = 0.0f;
				m_v3AngularVelocity.z += fMoveAmountLarge;
			}
	//		m_v3AngularVelocity.y = fMAX(fMoveAmountSmall, m_v3AngularVelocity.y);
	//// 		m_v3AngularVelocity.y += fMoveAmountSmall;

			if (kVct_kPosition.size() > 1)
			{
	//			m_v3AngularVelocity.z = fMAX(fMoveAmountSmall, m_v3AngularVelocity.z);
 				m_v3AngularVelocity.z += fMoveAmountSmall;
			}
			else
			{
				D3DXVec3Cross(&v3CheckVector, &(kVct_kPosition[0] - m_v3Eye), &m_v3View);
				float fDot = D3DXVec3Dot(&v3CheckVector, &m_v3Up);
				if (fDot < 0)
				{
	//				m_v3AngularVelocity.x = fMIN(-fMoveAmountSmall, m_v3AngularVelocity.x);
 					m_v3AngularVelocity.x -= fMoveAmountSmall;
				}
				else if(fDot > 0)
				{
	//				m_v3AngularVelocity.x = fMAX(fMoveAmountSmall, m_v3AngularVelocity.x);
 					m_v3AngularVelocity.x += fMoveAmountSmall;
				}
				else
				{
	//				m_v3AngularVelocity.z = fMAX(fMoveAmountSmall, m_v3AngularVelocity.z);
 					m_v3AngularVelocity.z += fMoveAmountSmall;
				}
			}
		}


change to:

		if (bCollide)
		{
			if (m_v3AngularVelocity.y > 0.0f)
			{
				m_v3AngularVelocity.y = 0.0f;
				m_v3AngularVelocity.z += fMoveAmountLarge;
			}
	//		m_v3AngularVelocity.y = fMAX(fMoveAmountSmall, m_v3AngularVelocity.y);
	//// 		m_v3AngularVelocity.y += fMoveAmountSmall;

			if (kVct_kPosition.size() > 1)
			{
	//			m_v3AngularVelocity.z = fMAX(fMoveAmountSmall, m_v3AngularVelocity.z);
 				m_v3AngularVelocity.z += fMoveAmountSmall;
			}
			else
			{
				auto d3dd = (kVct_kPosition[0] - m_v3Eye);
				D3DXVec3Cross(&v3CheckVector, &d3dd, &m_v3View);
				float fDot = D3DXVec3Dot(&v3CheckVector, &m_v3Up);
				if (fDot < 0)
				{
	//				m_v3AngularVelocity.x = fMIN(-fMoveAmountSmall, m_v3AngularVelocity.x);
 					m_v3AngularVelocity.x -= fMoveAmountSmall;
				}
				else if(fDot > 0)
				{
	//				m_v3AngularVelocity.x = fMAX(fMoveAmountSmall, m_v3AngularVelocity.x);
 					m_v3AngularVelocity.x += fMoveAmountSmall;
				}
				else
				{
	//				m_v3AngularVelocity.z = fMAX(fMoveAmountSmall, m_v3AngularVelocity.z);
 					m_v3AngularVelocity.z += fMoveAmountSmall;
				}
			}
		}
