search this:

void CFlyingInstance::AdjustDirectionForHoming(const D3DXVECTOR3 & v3TargetPosition)
{
	D3DXVECTOR3 vTargetDir(v3TargetPosition);
	vTargetDir -= m_v3Position;
	D3DXVec3Normalize(&vTargetDir,&vTargetDir);
	D3DXVECTOR3 vVel;
	D3DXVec3Normalize(&vVel, &m_v3Velocity);

	if (D3DXVec3LengthSq(&(vVel - vTargetDir)) < 0.001f)
		return;

	D3DXQUATERNION q = SafeRotationNormalizedArc(vVel,vTargetDir);

	if (m_pData->m_fHomingMaxAngle > 180)
	{
		Vec3TransformQuaternionSafe(&m_v3Velocity, &m_v3Velocity, &q);
		Vec3TransformQuaternionSafe(&m_v3Accel, &m_v3Accel, &q);
		D3DXQuaternionMultiply(&m_qRot, &q, &m_qRot);
		return;
	}

	float c = cosf(D3DXToRadian(m_pData->m_fHomingMaxAngle));
	float s = sinf(D3DXToRadian(m_pData->m_fHomingMaxAngle));

	if (q.w <= -1.0f + 0.0001f)
	{
		q.x = 0;
		q.y = 0;
		q.z = s;
		q.w = c;
	}
	else if (q.w <= c && q.w <= 1.0f - 0.0001f)
	{
		float factor = s / sqrtf(1.0f - q.w * q.w);
		q.x *= factor;
		q.y *= factor;
		q.z *= factor;
		q.w = c;
	}
	/*else
	{
	}*/
	Vec3TransformQuaternionSafe(&m_v3Velocity, &m_v3Velocity, &q);
	Vec3TransformQuaternionSafe(&m_v3Accel, &m_v3Accel, &q);
	D3DXQuaternionMultiply(&m_qRot, &m_qRot, &q);
}

change to:

void CFlyingInstance::AdjustDirectionForHoming(const D3DXVECTOR3& v3TargetPosition)
{
	D3DXVECTOR3 vTargetDir(v3TargetPosition);
	vTargetDir -= m_v3Position;
	D3DXVec3Normalize(&vTargetDir, &vTargetDir);
	D3DXVECTOR3 vVel;
	D3DXVec3Normalize(&vVel, &m_v3Velocity);

	const auto vv1 = (vVel - vTargetDir);
	if (D3DXVec3LengthSq(&vv1) < 0.001f)
		return;

	D3DXQUATERNION q = SafeRotationNormalizedArc(vVel, vTargetDir);

	if (m_pData->m_fHomingMaxAngle > 180)
	{
		Vec3TransformQuaternionSafe(&m_v3Velocity, &m_v3Velocity, &q);
		Vec3TransformQuaternionSafe(&m_v3Accel, &m_v3Accel, &q);
		D3DXQuaternionMultiply(&m_qRot, &q, &m_qRot);
		return;
	}

	float c = cosf(D3DXToRadian(m_pData->m_fHomingMaxAngle));
	float s = sinf(D3DXToRadian(m_pData->m_fHomingMaxAngle));

	if (q.w <= -1.0f + 0.0001f)
	{
		q.x = 0;
		q.y = 0;
		q.z = s;
		q.w = c;
	}
	else if (q.w <= c && q.w <= 1.0f - 0.0001f)
	{
		float factor = s / sqrtf(1.0f - q.w * q.w);
		q.x *= factor;
		q.y *= factor;
		q.z *= factor;
		q.w = c;
	}
	/*else
	{
	}*/
	Vec3TransformQuaternionSafe(&m_v3Velocity, &m_v3Velocity, &q);
	Vec3TransformQuaternionSafe(&m_v3Accel, &m_v3Accel, &q);
	D3DXQuaternionMultiply(&m_qRot, &m_qRot, &q);
}

search this:

void CFlyingInstance::__SetDataPointer(CFlyingData * pData, const D3DXVECTOR3 & v3StartPosition)
{
	m_pData = pData;
	m_qRot = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
	m_v3Position = (v3StartPosition);
	m_bAlive = (true);

	m_fStartTime = CTimer::Instance().GetCurrentSecond();

	D3DXQuaternionRotationYawPitchRoll(&m_qRot,D3DXToRadian(pData->m_fRollAngle-90.0f),0.0f,D3DXToRadian(pData->m_fConeAngle));
	if (pData->m_bSpreading)
	{
		D3DXQUATERNION q1, q2;
		D3DXQuaternionRotationAxis(&q2, &D3DXVECTOR3(0.0f,0.0f,1.0f),(frandom(-3.141592f/3,+3.141592f/3)+frandom(-3.141592f/3,+3.141592f/3))/2);
		D3DXQuaternionRotationAxis(&q1, &D3DXVECTOR3(0.0f,-1.0f,0.0f), frandom(0,2*3.1415926535897931f));
		D3DXQuaternionMultiply(&q1,&q2,&q1);
		D3DXQuaternionMultiply(&m_qRot,&q1,&m_qRot);
	}
	m_v3Velocity = m_v3LocalVelocity = D3DXVECTOR3(0.0f,-pData->m_fInitVel,0.0f);
	m_v3Accel = pData->m_v3Accel;
	m_fRemainRange = pData->m_fRange;
	m_qAttachRotation = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	BuildAttachInstance();
	UpdateAttachInstance();

	m_iPierceCount = pData->m_iPierceCount;
}

change to:

void CFlyingInstance::__SetDataPointer(CFlyingData* pData, const D3DXVECTOR3& v3StartPosition)
{
	m_pData = pData;
	m_qRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f),
		m_v3Position = (v3StartPosition);
	m_bAlive = (true);

	m_fStartTime = CTimer::Instance().GetCurrentSecond();

	D3DXQuaternionRotationYawPitchRoll(&m_qRot, D3DXToRadian(pData->m_fRollAngle - 90.0f), 0.0f, D3DXToRadian(pData->m_fConeAngle));
	if (pData->m_bSpreading)
	{
		D3DXQUATERNION q1, q2;
		const auto vv1 = D3DXVECTOR3(0.0f, 0.0f, 1.0f), vv2 = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		D3DXQuaternionRotationAxis(&q2, &vv1, (frandom(-3.141592f / 3, +3.141592f / 3) + frandom(-3.141592f / 3, +3.141592f / 3)) / 2);
		D3DXQuaternionRotationAxis(&q1, &vv2, frandom(0, 2 * 3.1415926535897931f));
		D3DXQuaternionMultiply(&q1, &q2, &q1);
		D3DXQuaternionMultiply(&m_qRot, &q1, &m_qRot);
	}
	m_v3Velocity = m_v3LocalVelocity = D3DXVECTOR3(0.0f, -pData->m_fInitVel, 0.0f);
	m_v3Accel = pData->m_v3Accel;
	m_fRemainRange = pData->m_fRange;
	m_qAttachRotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	BuildAttachInstance();
	UpdateAttachInstance();

	m_iPierceCount = pData->m_iPierceCount;
}