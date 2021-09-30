search this:

	for (DWORD i = 0; i < m_v3HeightDataVector.size(); ++i)
		for (DWORD j = 0; j < m_v3HeightDataVector[i].size(); j+=3)
		{
			const D3DXVECTOR3 & cv0 = m_v3HeightDataVector[i][j];
			const D3DXVECTOR3 & cv2 = m_v3HeightDataVector[i][j+1];
			const D3DXVECTOR3 & cv1 = m_v3HeightDataVector[i][j+2];

			D3DXVECTOR3 n;
			D3DXVec3Cross(&n,&(cv1-cv0),&(cv2-cv0)); 
			D3DXVECTOR3 x;
			float t;
			t = - D3DXVec3Dot(&(v-cv0),&n)/D3DXVec3Dot(&dir,&n);

			x = v+t*dir;

			D3DXVECTOR3 temp;
			D3DXVec3Cross(&temp,&(cv1-cv0),&(x-cv0));
			if (D3DXVec3Dot(&temp,&n)<0) continue;
			D3DXVec3Cross(&temp,&(cv2-cv1),&(x-cv1));
			if (D3DXVec3Dot(&temp,&n)<0) continue;
			D3DXVec3Cross(&temp,&(cv0-cv2),&(x-cv2));
			if (D3DXVec3Dot(&temp,&n)<0) continue;

			if (bPicked)
			{
				if ((v.x-x.x)*(v.x-x.x)+(v.y-x.y)*(v.y-x.y)<(v.x-nx)*(v.x-nx)+(v.y-ny)*(v.y-ny))
				{
					nx=x.x;
					ny=x.y;
				}
			}
			else
			{
				nx = x.x;
				ny = x.y;
			}
			bPicked = true;
	}


overwrite with this:

	for (DWORD i = 0; i < m_v3HeightDataVector.size(); ++i)
		for (DWORD j = 0; j < m_v3HeightDataVector[i].size(); j += 3)
		{
			const D3DXVECTOR3& cv0 = m_v3HeightDataVector[i][j];
			const D3DXVECTOR3& cv2 = m_v3HeightDataVector[i][j + 1];
			const D3DXVECTOR3& cv1 = m_v3HeightDataVector[i][j + 2];

			D3DXVECTOR3 n;
			const auto vvv = (cv1 - cv0);
			const auto vvv2 = (cv2 - cv0);
			const auto vvv3 = (cv2 - cv1);
			D3DXVec3Cross(&n, &vvv, &vvv2);
			D3DXVECTOR3 x;
			float t;
			const auto _vv = (v - cv0);
			t = -D3DXVec3Dot(&_vv, &n) / D3DXVec3Dot(&dir, &n);

			x = v + t * dir;
			const auto vvv4 = (x - cv0);
			const auto vvv5 = (x - cv1);
			const auto vvv6 = (x - cv2);
			D3DXVECTOR3 temp;
			D3DXVec3Cross(&temp, &vvv, &vvv4);
			if (D3DXVec3Dot(&temp, &n) < 0) continue;
			D3DXVec3Cross(&temp, &vvv3, &vvv5);
			if (D3DXVec3Dot(&temp, &n) < 0) continue;
			const auto _vv_ = (cv0 - cv2);
			D3DXVec3Cross(&temp, &_vv_, &vvv6);
			if (D3DXVec3Dot(&temp, &n) < 0) continue;

			if (bPicked)
			{
				if ((v.x - x.x) * (v.x - x.x) + (v.y - x.y) * (v.y - x.y) < (v.x - nx) * (v.x - nx) + (v.y - ny) * (v.y - ny))
				{
					nx = x.x;
					ny = x.y;
				}
			}
			else
			{
				nx = x.x;
				ny = x.y;
			}
			bPicked = true;
		}

