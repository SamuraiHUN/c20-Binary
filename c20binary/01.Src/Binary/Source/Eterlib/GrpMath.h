search this:


inline float square_distance_between_linesegment_and_point(const D3DXVECTOR3& p1,const D3DXVECTOR3& p2,const D3DXVECTOR3& x)
{
	float l = D3DXVec3LengthSq(&(p2-p1));
	float d = D3DXVec3Dot(&(x-p1),&(p2-p1));
	if (d<=0.0f)
	{
		return D3DXVec3LengthSq(&(x-p1));
	}
	else if (d>=l)
	{
		return D3DXVec3LengthSq(&(x-p2));
	}
	else
	{
		D3DXVECTOR3 c;
		return D3DXVec3LengthSq(D3DXVec3Cross(&c,&(x-p1),&(p2-p1)))/l;
	}
}


overwrite with this:

inline float square_distance_between_linesegment_and_point(const D3DXVECTOR3& p1,const D3DXVECTOR3& p2,const D3DXVECTOR3& x)
{
	const auto v1 = p2 - p1;
	float l = D3DXVec3LengthSq(&v1);
	const auto v2 = x - p1;
	const auto v3 = p2 - p1;
	float d = D3DXVec3Dot(&(v2), &(v3));
	if (d <= 0.0f)
	{
		return D3DXVec3LengthSq(&(v2));
	}
	else if (d >= l)
	{
		const auto v4 = x - p2;
		return D3DXVec3LengthSq(&(v4));
	}
	else
	{
		D3DXVECTOR3 c;
		return D3DXVec3LengthSq(D3DXVec3Cross(&c, &(v2), &(v3))) / l;
	}
}