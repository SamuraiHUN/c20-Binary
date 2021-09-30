search this:

bool DetectCollisionDynamicZCylinderVSDynamicZCylinder(const CDynamicSphereInstance & c_rSphere1, const CDynamicSphereInstance & c_rSphere2)
{
	CDynamicSphereInstance c_rCylinder1=c_rSphere1;
	CDynamicSphereInstance c_rCylinder2=c_rSphere2;

	c_rCylinder1.v3Position.z=0;
	c_rCylinder1.v3LastPosition.z=0;

	c_rCylinder2.v3Position.z=0;
	c_rCylinder2.v3LastPosition.z=0;

	float r = c_rCylinder1.fRadius+c_rCylinder2.fRadius;
	float rsq = r*r;

	// AABB check
	D3DXVECTOR3 mi1=c_rCylinder1.v3LastPosition, mi2 = c_rCylinder1.v3Position;
	D3DXVECTOR3 mi3=c_rCylinder2.v3LastPosition, mi4 = c_rCylinder2.v3Position;
	if (mi1.x>mi2.x) std::swap(mi1.x,mi2.x);
	if (mi1.y>mi2.y) std::swap(mi1.y,mi2.y);
	if (mi1.z>mi2.z) std::swap(mi1.z,mi2.z);
	if (mi3.x>mi4.x) std::swap(mi3.x,mi4.x);
	if (mi3.y>mi4.y) std::swap(mi3.y,mi4.y);
	if (mi3.z>mi4.z) std::swap(mi3.z,mi4.z);
	mi1.x -= c_rCylinder1.fRadius; mi1.y -= c_rCylinder1.fRadius; mi1.z -= c_rCylinder1.fRadius;
	mi2.x += c_rCylinder1.fRadius; mi2.y += c_rCylinder1.fRadius; mi2.z += c_rCylinder1.fRadius;
	mi3.x -= c_rCylinder2.fRadius; mi3.y -= c_rCylinder2.fRadius; mi3.z -= c_rCylinder2.fRadius;
	mi4.x += c_rCylinder2.fRadius; mi4.y += c_rCylinder2.fRadius; mi4.z += c_rCylinder2.fRadius;
	if (mi4.x<mi1.x || mi2.x<mi3.x) return false;
	if (mi4.y<mi1.y || mi2.y<mi3.y) return false;
	if (mi4.z<mi1.z || mi2.z<mi3.z) return false;

	D3DXVECTOR3 vA, vB;
	IntersectLineSegments(c_rCylinder1.v3LastPosition, c_rCylinder1.v3Position,
		c_rCylinder2.v3LastPosition, c_rCylinder2.v3Position,
		vA, vB);
	return (D3DXVec3LengthSq(&(vA-vB))<=rsq);
}

bool DetectCollisionDynamicSphereVSDynamicSphere(const CDynamicSphereInstance & c_rSphere1, const CDynamicSphereInstance & c_rSphere2)
{
	float r = c_rSphere1.fRadius+c_rSphere2.fRadius;
	float rsq = r*r;

	/*if (D3DXVec3LengthSq(&(c_rSphere1.v3Position		-c_rSphere2.v3Position		))<=rsq) return true;
	if (D3DXVec3LengthSq(&(c_rSphere1.v3Position		-c_rSphere2.v3LastPosition	))<=rsq) return true;
	if (D3DXVec3LengthSq(&(c_rSphere1.v3LastPosition	-c_rSphere2.v3Position		))<=rsq) return true;
	if (D3DXVec3LengthSq(&(c_rSphere1.v3LastPosition	-c_rSphere2.v3LastPosition	))<=rsq) return true;*/


	//*/
	// using gpg line-collision

	// AABB check

	D3DXVECTOR3 mi1=c_rSphere1.v3LastPosition, mi2 = c_rSphere1.v3Position;
	D3DXVECTOR3 mi3=c_rSphere2.v3LastPosition, mi4 = c_rSphere2.v3Position;
	if (mi1.x>mi2.x) std::swap(mi1.x,mi2.x);
	if (mi1.y>mi2.y) std::swap(mi1.y,mi2.y);
	if (mi1.z>mi2.z) std::swap(mi1.z,mi2.z);
	if (mi3.x>mi4.x) std::swap(mi3.x,mi4.x);
	if (mi3.y>mi4.y) std::swap(mi3.y,mi4.y);
	if (mi3.z>mi4.z) std::swap(mi3.z,mi4.z);
	mi1.x -= c_rSphere1.fRadius; mi1.y -= c_rSphere1.fRadius; mi1.z -= c_rSphere1.fRadius;
	mi2.x += c_rSphere1.fRadius; mi2.y += c_rSphere1.fRadius; mi2.z += c_rSphere1.fRadius;
	mi3.x -= c_rSphere2.fRadius; mi3.y -= c_rSphere2.fRadius; mi3.z -= c_rSphere2.fRadius;
	mi4.x += c_rSphere2.fRadius; mi4.y += c_rSphere2.fRadius; mi4.z += c_rSphere2.fRadius;
	if (mi4.x<mi1.x || mi2.x<mi3.x) return false;
	if (mi4.y<mi1.y || mi2.y<mi3.y) return false;
	if (mi4.z<mi1.z || mi2.z<mi3.z) return false;

	D3DXVECTOR3 vA, vB;/*
	IntersectLineSegments(
		c_rSphere1.v3LastPosition.x,c_rSphere1.v3LastPosition.y,c_rSphere1.v3LastPosition.z,
		c_rSphere1.v3Position.x,	c_rSphere1.v3Position.y,	c_rSphere1.v3Position.z,
		c_rSphere2.v3LastPosition.x,c_rSphere2.v3LastPosition.y,c_rSphere2.v3LastPosition.z,
		c_rSphere2.v3Position.x,	c_rSphere2.v3Position.y,	c_rSphere2.v3Position.z,
		false, 1.e-1f, vA.x, vA.y, vA.z, vB.x, vB.y, vB.z);*/
	IntersectLineSegments(c_rSphere1.v3LastPosition, c_rSphere1.v3Position,
		c_rSphere2.v3LastPosition, c_rSphere2.v3Position,
		vA, vB);
	return (D3DXVec3LengthSq(&(vA-vB))<=rsq);
	//*/


}

modify to:

bool DetectCollisionDynamicZCylinderVSDynamicZCylinder(const CDynamicSphereInstance & c_rSphere1, const CDynamicSphereInstance & c_rSphere2)
{
	CDynamicSphereInstance c_rCylinder1=c_rSphere1;
	CDynamicSphereInstance c_rCylinder2=c_rSphere2;

	c_rCylinder1.v3Position.z=0;
	c_rCylinder1.v3LastPosition.z=0;

	c_rCylinder2.v3Position.z=0;
	c_rCylinder2.v3LastPosition.z=0;

	float r = c_rCylinder1.fRadius+c_rCylinder2.fRadius;
	float rsq = r*r;

	// AABB check
	D3DXVECTOR3 mi1=c_rCylinder1.v3LastPosition, mi2 = c_rCylinder1.v3Position;
	D3DXVECTOR3 mi3=c_rCylinder2.v3LastPosition, mi4 = c_rCylinder2.v3Position;
	if (mi1.x>mi2.x) std::swap(mi1.x,mi2.x);
	if (mi1.y>mi2.y) std::swap(mi1.y,mi2.y);
	if (mi1.z>mi2.z) std::swap(mi1.z,mi2.z);
	if (mi3.x>mi4.x) std::swap(mi3.x,mi4.x);
	if (mi3.y>mi4.y) std::swap(mi3.y,mi4.y);
	if (mi3.z>mi4.z) std::swap(mi3.z,mi4.z);
	mi1.x -= c_rCylinder1.fRadius; mi1.y -= c_rCylinder1.fRadius; mi1.z -= c_rCylinder1.fRadius;
	mi2.x += c_rCylinder1.fRadius; mi2.y += c_rCylinder1.fRadius; mi2.z += c_rCylinder1.fRadius;
	mi3.x -= c_rCylinder2.fRadius; mi3.y -= c_rCylinder2.fRadius; mi3.z -= c_rCylinder2.fRadius;
	mi4.x += c_rCylinder2.fRadius; mi4.y += c_rCylinder2.fRadius; mi4.z += c_rCylinder2.fRadius;
	if (mi4.x<mi1.x || mi2.x<mi3.x) return false;
	if (mi4.y<mi1.y || mi2.y<mi3.y) return false;
	if (mi4.z<mi1.z || mi2.z<mi3.z) return false;

	D3DXVECTOR3 vA, vB;
	IntersectLineSegments(c_rCylinder1.v3LastPosition, c_rCylinder1.v3Position,
		c_rCylinder2.v3LastPosition, c_rCylinder2.v3Position,
		vA, vB);
	const auto vv = (vA - vB);
	return (D3DXVec3LengthSq(&vv) <= rsq);
}

bool DetectCollisionDynamicSphereVSDynamicSphere(const CDynamicSphereInstance & c_rSphere1, const CDynamicSphereInstance & c_rSphere2)
{
	float r = c_rSphere1.fRadius+c_rSphere2.fRadius;
	float rsq = r*r;


	//*/
	// using gpg line-collision

	// AABB check

	D3DXVECTOR3 mi1=c_rSphere1.v3LastPosition, mi2 = c_rSphere1.v3Position;
	D3DXVECTOR3 mi3=c_rSphere2.v3LastPosition, mi4 = c_rSphere2.v3Position;
	if (mi1.x>mi2.x) std::swap(mi1.x,mi2.x);
	if (mi1.y>mi2.y) std::swap(mi1.y,mi2.y);
	if (mi1.z>mi2.z) std::swap(mi1.z,mi2.z);
	if (mi3.x>mi4.x) std::swap(mi3.x,mi4.x);
	if (mi3.y>mi4.y) std::swap(mi3.y,mi4.y);
	if (mi3.z>mi4.z) std::swap(mi3.z,mi4.z);
	mi1.x -= c_rSphere1.fRadius; mi1.y -= c_rSphere1.fRadius; mi1.z -= c_rSphere1.fRadius;
	mi2.x += c_rSphere1.fRadius; mi2.y += c_rSphere1.fRadius; mi2.z += c_rSphere1.fRadius;
	mi3.x -= c_rSphere2.fRadius; mi3.y -= c_rSphere2.fRadius; mi3.z -= c_rSphere2.fRadius;
	mi4.x += c_rSphere2.fRadius; mi4.y += c_rSphere2.fRadius; mi4.z += c_rSphere2.fRadius;
	if (mi4.x<mi1.x || mi2.x<mi3.x) return false;
	if (mi4.y<mi1.y || mi2.y<mi3.y) return false;
	if (mi4.z<mi1.z || mi2.z<mi3.z) return false;

	D3DXVECTOR3 vA, vB;

	IntersectLineSegments(c_rSphere1.v3LastPosition, c_rSphere1.v3Position,
		c_rSphere2.v3LastPosition, c_rSphere2.v3Position,
		vA, vB);
	const auto vvv = (vA - vB);
	return (D3DXVec3LengthSq(&vvv) <= rsq);
}