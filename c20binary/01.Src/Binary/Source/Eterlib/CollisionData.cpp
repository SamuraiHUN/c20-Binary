search this:


D3DXVECTOR3 CSphereCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{
	if (D3DXVec3LengthSq(&(s.v3Position-m_attribute.v3Position))>=(s.fRadius+m_attribute.fRadius)*(m_attribute.fRadius+s.fRadius))
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 c;
	D3DXVec3Cross(&c, &(s.v3Position-s.v3LastPosition), &D3DXVECTOR3(0.0f,0.0f,1.0f) );

	float sum = - D3DXVec3Dot(&c,&(s.v3Position-m_attribute.v3Position));
	float mul = (s.fRadius+m_attribute.fRadius)*(s.fRadius+m_attribute.fRadius)-D3DXVec3LengthSq(&(s.v3Position-m_attribute.v3Position));

	if (sum*sum-4*mul<=0)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	float sq = sqrt(sum*sum-4*mul);
	float t1=-sum-sq, t2=-sum+sq;
	t1*=0.5f;
	t2*=0.5f;

	if (fabs(t1)<=fabs(t2))
	{
		return (gc_fReduceMove*t1)*c;
	}
	else
		return (gc_fReduceMove*t2)*c;

	/*
	D3DXVECTOR3 p1 = s.v3Position+t1*c;
	D3DXVECTOR3 p2 = s.v3Position+t2*c;

	if (D3DXVec3LengthSq(&(p2-s.v3Position))>D3DXVec3LengthSq(&(p1-s.v3Position)))
	{
		return p1-s.v3Position;
	}
	else
	{
		return p2-s.v3Position;
	}
	*/
}


change to:


D3DXVECTOR3 CSphereCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance& s) const
{
	const auto _vv__ = (s.v3Position - m_attribute.v3Position);
	if (D3DXVec3LengthSq(&_vv__) >= (s.fRadius + m_attribute.fRadius) * (m_attribute.fRadius + s.fRadius))
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 c;
	const auto _vv__2 = (s.v3Position - s.v3LastPosition);
	const auto _vv_s_2 = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Cross(&c, &_vv__2, &_vv_s_2);

	float sum = -D3DXVec3Dot(&c, &_vv__);
	float mul = (s.fRadius + m_attribute.fRadius) * (s.fRadius + m_attribute.fRadius) - D3DXVec3LengthSq(&_vv__);

	if (sum * sum - 4 * mul <= 0)
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float sq = sqrt(sum * sum - 4 * mul);
	float t1 = -sum - sq, t2 = -sum + sq;
	t1 *= 0.5f;
	t2 *= 0.5f;

	if (fabs(t1) <= fabs(t2))
	{
		return (gc_fReduceMove * t1) * c;
	}
	else
		return (gc_fReduceMove * t2) * c;

	/*
	D3DXVECTOR3 p1 = s.v3Position+t1*c;
	D3DXVECTOR3 p2 = s.v3Position+t2*c;

	if (D3DXVec3LengthSq(&(p2-s.v3Position))>D3DXVec3LengthSq(&(p1-s.v3Position)))
	{
		return p1-s.v3Position;
	}
	else
	{
		return p2-s.v3Position;
	}
	*/
}

search this:

bool CPlaneCollisionInstance::OnMovementCollisionDynamicSphere(const CDynamicSphereInstance & s) const
{
	D3DXVECTOR3 v3SpherePosition = s.v3Position - m_attribute.v3Position;
	D3DXVECTOR3 v3SphereLastPosition = s.v3LastPosition - m_attribute.v3Position;

	float fPosition1 = D3DXVec3Dot(&m_attribute.v3Normal, &v3SpherePosition);
	float fPosition2 = D3DXVec3Dot(&m_attribute.v3Normal, &v3SphereLastPosition);

	if (fPosition1 >0.0f && fPosition2 < 0.0f  || fPosition1 <0.0f && fPosition2 >0.0f
		|| (fPosition1) <= s.fRadius && fPosition1 >= -s.fRadius)
	{
		D3DXVECTOR3 v3QuadPosition1 = s.v3Position - m_attribute.v3QuadPosition[0];
		D3DXVECTOR3 v3QuadPosition2 = s.v3Position - m_attribute.v3QuadPosition[3];

		if (D3DXVec3Dot(&v3QuadPosition1, &m_attribute.v3InsideVector[0]) > - s.fRadius/*0.0f*/)
			if (D3DXVec3Dot(&v3QuadPosition1, &m_attribute.v3InsideVector[1]) > -s.fRadius/*0.0f*/)
				if (D3DXVec3Dot(&v3QuadPosition2, &m_attribute.v3InsideVector[2]) > - s.fRadius/*0.0f*/)
					if (D3DXVec3Dot(&v3QuadPosition2, &m_attribute.v3InsideVector[3]) > - s.fRadius/*0.0f*/)
					{
						if (fabs(D3DXVec3Dot(&(s.v3Position - m_attribute.v3Position), &m_attribute.v3Normal)) <
							fabs(D3DXVec3Dot(&(s.v3LastPosition - m_attribute.v3Position), &m_attribute.v3Normal)))
							return true;
					}
	}

	return false;
}


change to:

bool CPlaneCollisionInstance::OnMovementCollisionDynamicSphere(const CDynamicSphereInstance & s) const
{
	D3DXVECTOR3 v3SpherePosition = s.v3Position - m_attribute.v3Position;
	D3DXVECTOR3 v3SphereLastPosition = s.v3LastPosition - m_attribute.v3Position;

	float fPosition1 = D3DXVec3Dot(&m_attribute.v3Normal, &v3SpherePosition);
	float fPosition2 = D3DXVec3Dot(&m_attribute.v3Normal, &v3SphereLastPosition);

	if (fPosition1 >0.0f && fPosition2 < 0.0f  || fPosition1 <0.0f && fPosition2 >0.0f
		|| (fPosition1) <= s.fRadius && fPosition1 >= -s.fRadius)
	{
		D3DXVECTOR3 v3QuadPosition1 = s.v3Position - m_attribute.v3QuadPosition[0];
		D3DXVECTOR3 v3QuadPosition2 = s.v3Position - m_attribute.v3QuadPosition[3];

		if (D3DXVec3Dot(&v3QuadPosition1, &m_attribute.v3InsideVector[0]) > - s.fRadius/*0.0f*/)
			if (D3DXVec3Dot(&v3QuadPosition1, &m_attribute.v3InsideVector[1]) > -s.fRadius/*0.0f*/)
				if (D3DXVec3Dot(&v3QuadPosition2, &m_attribute.v3InsideVector[2]) > - s.fRadius/*0.0f*/)
					if (D3DXVec3Dot(&v3QuadPosition2, &m_attribute.v3InsideVector[3]) > -s.fRadius/*0.0f*/)
					{
						// NOTE : 거리가 가까워 졌을때만.. - [levites]
						const auto _vv__3 = (s.v3Position - m_attribute.v3Position);
						const auto _vv__4 = (s.v3LastPosition - m_attribute.v3Position);
						if (fabs(D3DXVec3Dot(&_vv__3, &m_attribute.v3Normal)) <
							fabs(D3DXVec3Dot(&_vv__4, &m_attribute.v3Normal)))
							return true;
					}
	}

	return false;
}

search this:

D3DXVECTOR3 CPlaneCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{
	D3DXVECTOR3 advance = s.v3Position-s.v3LastPosition;

	float d = D3DXVec3Dot(&m_attribute.v3Normal, &advance);
	if (d>=-0.0001 && d<=0.0001)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	float t= - D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position))/d;

	//D3DXVECTOR3 onplane = s.v3Position+t*advance;

	if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	{
		//return m_attribute.v3Normal*((-s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
		return t*advance -s.fRadius*m_attribute.v3Normal;
	}
	else
	{
		//return m_attribute.v3Normal*((s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
		return t*advance +s.fRadius*m_attribute.v3Normal;
	}



	/*if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	{
		Tracef("%f %f\n",s.fRadius,-(D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position))));
		return m_attribute.v3Normal*((-s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
	}
	else
	{
		Tracef("%f %f\n",(s.fRadius),(D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position))));
		return m_attribute.v3Normal*((s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
	}*/


	/*
	D3DXVECTOR3 advance = s.v3Position-s.v3LastPosition;
	D3DXVECTOR3 slide(-advance.y,advance.x,advance.z);
	slide = m_attribute.v3Normal;

	D3DXVECTOR3 radius_adjust = advance;
	D3DXVec3Normalize(&radius_adjust,&radius_adjust);
	radius_adjust*=s.fRadius;

	float d = D3DXVec3Dot(&m_attribute.v3Normal, &slide);
	if (d>=-0.0001 && d<=0.0001)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);

	float t= - D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position+radius_adjust-m_attribute.v3Position))
				/ d;*/

	//D3DXVECTOR3 nextposition;
	//nextposition = s.v3Position + t*slide;
	//Tracef("$T %f",t);
	//if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	//	return (t*slide - m_attribute.v3Normal * s.fRadius)/**gc_fReduceMove*/;
	//else
	//	return (t*slide + m_attribute.v3Normal * s.fRadius)/*gc_fReduceMove*/;
	//if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	//	return (t*slide + m_attribute.v3Normal * D3DXVec3Dot(&m_attribute.v3Normal,&(s.v3LastPosition-m_attribute.v3Position))/** s.fRadius*/)*gc_fReduceMove;
	//else
	//	return (t*slide + m_attribute.v3Normal * D3DXVec3Dot(&m_attribute.v3Normal,&(s.v3LastPosition-m_attribute.v3Position))/*s.fRadius*/)*gc_fReduceMove;
	//
}


modify to:

D3DXVECTOR3 CPlaneCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{
	D3DXVECTOR3 advance = s.v3Position-s.v3LastPosition;

	float d = D3DXVec3Dot(&m_attribute.v3Normal, &advance);
	if (d >= -0.0001 && d <= 0.0001)
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const auto vv = (s.v3Position - m_attribute.v3Position);
	float t = -D3DXVec3Dot(&m_attribute.v3Normal, &vv) / d;

	//D3DXVECTOR3 onplane = s.v3Position+t*advance;

	if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	{
		//return m_attribute.v3Normal*((-s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
		return t*advance -s.fRadius*m_attribute.v3Normal;
	}
	else
	{
		//return m_attribute.v3Normal*((s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
		return t*advance +s.fRadius*m_attribute.v3Normal;
	}



	/*if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	{
		Tracef("%f %f\n",s.fRadius,-(D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position))));
		return m_attribute.v3Normal*((-s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
	}
	else
	{
		Tracef("%f %f\n",(s.fRadius),(D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position))));
		return m_attribute.v3Normal*((s.fRadius+D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position-m_attribute.v3Position)))*gc_fReduceMove);
	}*/


	/*
	D3DXVECTOR3 advance = s.v3Position-s.v3LastPosition;
	D3DXVECTOR3 slide(-advance.y,advance.x,advance.z);
	slide = m_attribute.v3Normal;

	D3DXVECTOR3 radius_adjust = advance;
	D3DXVec3Normalize(&radius_adjust,&radius_adjust);
	radius_adjust*=s.fRadius;

	float d = D3DXVec3Dot(&m_attribute.v3Normal, &slide);
	if (d>=-0.0001 && d<=0.0001)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);

	float t= - D3DXVec3Dot(&m_attribute.v3Normal, &(s.v3Position+radius_adjust-m_attribute.v3Position))
				/ d;*/

	//D3DXVECTOR3 nextposition;
	//nextposition = s.v3Position + t*slide;
	//Tracef("$T %f",t);
	//if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	//	return (t*slide - m_attribute.v3Normal * s.fRadius)/**gc_fReduceMove*/;
	//else
	//	return (t*slide + m_attribute.v3Normal * s.fRadius)/*gc_fReduceMove*/;
	//if (D3DXVec3Dot(&m_attribute.v3Normal, &advance)>=0)
	//	return (t*slide + m_attribute.v3Normal * D3DXVec3Dot(&m_attribute.v3Normal,&(s.v3LastPosition-m_attribute.v3Position))/** s.fRadius*/)*gc_fReduceMove;
	//else
	//	return (t*slide + m_attribute.v3Normal * D3DXVec3Dot(&m_attribute.v3Normal,&(s.v3LastPosition-m_attribute.v3Position))/*s.fRadius*/)*gc_fReduceMove;
	//
}

search this:

bool CCylinderCollisionInstance::CollideCylinderVSDynamicSphere(const TCylinderData & c_rattribute, const CDynamicSphereInstance & s) const
{
	if (s.v3Position.z + s.fRadius < c_rattribute.v3Position.z)
		return false;

	if (s.v3Position.z - s.fRadius > c_rattribute.v3Position.z + c_rattribute.fHeight)
		return false;

	/*D3DXVECTOR2 v2curDistance(s.v3Position.x - c_rattribute.v3Position.x, s.v3Position.y - c_rattribute.v3Position.y);
	float fDistance = D3DXVec2Length(&v2curDistance);
	if (fDistance <= s.fRadius + c_rattribute.fRadius)
		return true;
		*/

	D3DXVECTOR3 oa, ob;
	IntersectLineSegments(c_rattribute.v3Position, D3DXVECTOR3(c_rattribute.v3Position.x,c_rattribute.v3Position.y,c_rattribute.v3Position.z+c_rattribute.fHeight), s.v3LastPosition, s.v3Position, oa, ob);
	return (D3DXVec3LengthSq(&(oa-ob))<=(c_rattribute.fRadius+s.fRadius)*(c_rattribute.fRadius+s.fRadius));
}

modify to this:

bool CCylinderCollisionInstance::CollideCylinderVSDynamicSphere(const TCylinderData& c_rattribute, const CDynamicSphereInstance& s) const
{
	if (s.v3Position.z + s.fRadius < c_rattribute.v3Position.z)
		return false;

	if (s.v3Position.z - s.fRadius > c_rattribute.v3Position.z + c_rattribute.fHeight)
		return false;

	/*D3DXVECTOR2 v2curDistance(s.v3Position.x - c_rattribute.v3Position.x, s.v3Position.y - c_rattribute.v3Position.y);
	float fDistance = D3DXVec2Length(&v2curDistance);
	if (fDistance <= s.fRadius + c_rattribute.fRadius)
		return true;
		*/

	D3DXVECTOR3 oa, ob;
	IntersectLineSegments(c_rattribute.v3Position, D3DXVECTOR3(c_rattribute.v3Position.x, c_rattribute.v3Position.y, c_rattribute.v3Position.z + c_rattribute.fHeight), s.v3LastPosition, s.v3Position, oa, ob);
	const auto vv = (oa - ob);
	return (D3DXVec3LengthSq(&vv) <= (c_rattribute.fRadius + s.fRadius) * (c_rattribute.fRadius + s.fRadius));
}

search this:

D3DXVECTOR3 CCylinderCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{
	D3DXVECTOR3 v3Position = m_attribute.v3Position;
	v3Position.z = s.v3Position.z;
	if (D3DXVec3LengthSq(&(s.v3Position-v3Position))>=(s.fRadius+m_attribute.fRadius)*(m_attribute.fRadius+s.fRadius))
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 c;
	D3DXVECTOR3 advance = s.v3Position - s.v3LastPosition;
	advance.z = 0;
	D3DXVec3Cross(&c, &advance, &D3DXVECTOR3(0.0f,0.0f,1.0f) );

	float sum = - D3DXVec3Dot(&c,&(s.v3Position-v3Position));
	float mul = (s.fRadius+m_attribute.fRadius)*(s.fRadius+m_attribute.fRadius)-D3DXVec3LengthSq(&(s.v3Position-v3Position));

	if (sum*sum-4*mul<=0)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	float sq = sqrt(sum*sum-4*mul);
	float t1=-sum-sq, t2=-sum+sq;
	t1*=0.5f;
	t2*=0.5f;


	if (fabs(t1)<=fabs(t2))
	{
		return (gc_fReduceMove*t1)*c;
	}
	else
		return (gc_fReduceMove*t2)*c;

	/*D3DXVECTOR3 p1 = s.v3Position+t1*c;
	D3DXVECTOR3 p2 = s.v3Position+t2*c;

	if (D3DXVec3LengthSq(&(p2-s.v3Position))>D3DXVec3LengthSq(&(p1-s.v3Position)))
	{
		return p1-s.v3Position;
	}
	else
	{
		return p2-s.v3Position;
	}*/
}

modify to:

D3DXVECTOR3 CCylinderCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance& s) const
{
	D3DXVECTOR3 v3Position = m_attribute.v3Position;
	v3Position.z = s.v3Position.z;
	const auto vv = (s.v3Position - v3Position);
	if (D3DXVec3LengthSq(&vv) >= (s.fRadius + m_attribute.fRadius) * (m_attribute.fRadius + s.fRadius))
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 c;
	D3DXVECTOR3 advance = s.v3Position - s.v3LastPosition;
	advance.z = 0;
	const auto vssa = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Cross(&c, &advance, &vssa);

	const auto svsvs = (s.v3Position - v3Position);
	float sum = -D3DXVec3Dot(&c, &svsvs);
	float mul = (s.fRadius + m_attribute.fRadius) * (s.fRadius + m_attribute.fRadius) - D3DXVec3LengthSq(&svsvs);

	if (sum * sum - 4 * mul <= 0)
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float sq = sqrt(sum * sum - 4 * mul);
	float t1 = -sum - sq, t2 = -sum + sq;
	t1 *= 0.5f;
	t2 *= 0.5f;


	if (fabs(t1) <= fabs(t2))
	{
		return (gc_fReduceMove * t1) * c;
	}
	else
		return (gc_fReduceMove * t2) * c;

	/*D3DXVECTOR3 p1 = s.v3Position+t1*c;
	D3DXVECTOR3 p2 = s.v3Position+t2*c;

	if (D3DXVec3LengthSq(&(p2-s.v3Position))>D3DXVec3LengthSq(&(p1-s.v3Position)))
	{
		return p1-s.v3Position;
	}
	else
	{
		return p2-s.v3Position;
	}*/
}


search this:

D3DXVECTOR3 CAABBCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{

	//Tracef("OnGetCollisionMovementAdjust	v3Min.x = %f, v3Max.x = %f\n", m_attribute.v3Min.x, m_attribute.v3Max.x);
	/*
	float fARadius = D3DXVec3Length(&(m_attribute.v3Min - m_attribute.v3Max));
	if (D3DXVec3LengthSq(&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)))>=(s.fRadius+fARadius)*(fARadius+s.fRadius))
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 c;
	D3DXVec3Cross(&c, &(s.v3Position-s.v3LastPosition), &D3DXVECTOR3(0.0f,0.0f,1.0f) );

	float sum = - D3DXVec3Dot(&c,&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)));
	float mul = (s.fRadius+fARadius)*(s.fRadius+fARadius)-D3DXVec3LengthSq(&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)));

	if (sum*sum-4*mul<=0)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	float sq = sqrt(sum*sum-4*mul);
	float t1=-sum-sq, t2=-sum+sq;
	t1*=0.5f;
	t2*=0.5f;

	if (fabs(t1)<=fabs(t2))
	{
		return (gc_fReduceMove*t1)*c;
	}
	else
		return (gc_fReduceMove*t2)*c;
	*/

	D3DXVECTOR3 v3Temp;
	if(s.v3Position.x + s.fRadius <= m_attribute.v3Min.x)		{ v3Temp.x = m_attribute.v3Min.x; }
	else if(s.v3Position.x - s.fRadius >= m_attribute.v3Max.x)	{ v3Temp.x = m_attribute.v3Max.x; }
	else if(s.v3Position.x + s.fRadius >= m_attribute.v3Min.x && s.v3Position.x + s.fRadius <= m_attribute.v3Max.x) { v3Temp.x = s.v3Position.x + s.fRadius; }
	else																											{ v3Temp.x = s.v3Position.x - s.fRadius; }

	if(s.v3Position.y + s.fRadius <= m_attribute.v3Min.y)		{ v3Temp.y = m_attribute.v3Min.y; }
	else if(s.v3Position.y - s.fRadius >= m_attribute.v3Max.y)	{ v3Temp.y = m_attribute.v3Max.y; }
	else if(s.v3Position.y + s.fRadius >= m_attribute.v3Min.y && s.v3Position.y + s.fRadius <= m_attribute.v3Max.y) { v3Temp.y = s.v3Position.y + s.fRadius; }
	else																											{ v3Temp.y = s.v3Position.y - s.fRadius; }

	if(s.v3Position.z + s.fRadius <= m_attribute.v3Min.z)		{ v3Temp.z = m_attribute.v3Min.z; }
	else if(s.v3Position.z - s.fRadius >= m_attribute.v3Max.z)	{ v3Temp.z = m_attribute.v3Max.z; }
	else if(s.v3Position.z + s.fRadius >= m_attribute.v3Min.z && s.v3Position.z + s.fRadius <= m_attribute.v3Max.z) { v3Temp.z = s.v3Position.z + s.fRadius; }
	else																											{ v3Temp.z = s.v3Position.z - s.fRadius; }


	if(D3DXVec3LengthSq(&(v3Temp - s.v3Position)) < s.fRadius * s.fRadius)
		return D3DXVECTOR3(.0f, .0f, .0f);

	return D3DXVECTOR3(.0f, .0f, .0f);

}

modify to:

D3DXVECTOR3 CAABBCollisionInstance::OnGetCollisionMovementAdjust(const CDynamicSphereInstance & s) const
{

	//Tracef("OnGetCollisionMovementAdjust	v3Min.x = %f, v3Max.x = %f\n", m_attribute.v3Min.x, m_attribute.v3Max.x);
	/*
	float fARadius = D3DXVec3Length(&(m_attribute.v3Min - m_attribute.v3Max));
	if (D3DXVec3LengthSq(&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)))>=(s.fRadius+fARadius)*(fARadius+s.fRadius))
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 c;
	D3DXVec3Cross(&c, &(s.v3Position-s.v3LastPosition), &D3DXVECTOR3(0.0f,0.0f,1.0f) );

	float sum = - D3DXVec3Dot(&c,&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)));
	float mul = (s.fRadius+fARadius)*(s.fRadius+fARadius)-D3DXVec3LengthSq(&(s.v3Position-(m_attribute.v3Max + m_attribute.v3Min)));

	if (sum*sum-4*mul<=0)
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
	float sq = sqrt(sum*sum-4*mul);
	float t1=-sum-sq, t2=-sum+sq;
	t1*=0.5f;
	t2*=0.5f;

	if (fabs(t1)<=fabs(t2))
	{
		return (gc_fReduceMove*t1)*c;
	}
	else
		return (gc_fReduceMove*t2)*c;
	*/

	D3DXVECTOR3 v3Temp;
	if(s.v3Position.x + s.fRadius <= m_attribute.v3Min.x)		{ v3Temp.x = m_attribute.v3Min.x; }
	else if(s.v3Position.x - s.fRadius >= m_attribute.v3Max.x)	{ v3Temp.x = m_attribute.v3Max.x; }
	else if(s.v3Position.x + s.fRadius >= m_attribute.v3Min.x && s.v3Position.x + s.fRadius <= m_attribute.v3Max.x) { v3Temp.x = s.v3Position.x + s.fRadius; }
	else																											{ v3Temp.x = s.v3Position.x - s.fRadius; }

	if (s.v3Position.y + s.fRadius <= m_attribute.v3Min.y) { v3Temp.y = m_attribute.v3Min.y; }
	else if (s.v3Position.y - s.fRadius >= m_attribute.v3Max.y) { v3Temp.y = m_attribute.v3Max.y; }
	else if (s.v3Position.y + s.fRadius >= m_attribute.v3Min.y && s.v3Position.y + s.fRadius <= m_attribute.v3Max.y) { v3Temp.y = s.v3Position.y + s.fRadius; }
	else { v3Temp.y = s.v3Position.y - s.fRadius; }

	if (s.v3Position.z + s.fRadius <= m_attribute.v3Min.z) { v3Temp.z = m_attribute.v3Min.z; }
	else if (s.v3Position.z - s.fRadius >= m_attribute.v3Max.z) { v3Temp.z = m_attribute.v3Max.z; }
	else if (s.v3Position.z + s.fRadius >= m_attribute.v3Min.z && s.v3Position.z + s.fRadius <= m_attribute.v3Max.z) { v3Temp.z = s.v3Position.z + s.fRadius; }
	else { v3Temp.z = s.v3Position.z - s.fRadius; }


	const auto vv = (v3Temp - s.v3Position);
	if (D3DXVec3LengthSq(&vv) < s.fRadius * s.fRadius)
		return D3DXVECTOR3(.0f, .0f, .0f);

	return D3DXVECTOR3(.0f, .0f, .0f);

}