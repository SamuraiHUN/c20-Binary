search this:

		{
			D3DXVec3Normalize(&pInstance->m_v3Velocity, &(pInstance->m_v3Position-v3TimePosition));
			pInstance->m_v3Velocity *= -100.0f;
		}
		else if (CEmitterProperty::EMITTER_ADVANCED_TYPE_OUTER == m_pEmitterProperty->GetEmitterAdvancedType())
		{
			if (m_pEmitterProperty->GetEmitterShape() == CEmitterProperty::EMITTER_SHAPE_POINT)
			{
				pInstance->m_v3Velocity.x = frandom(-100.0f, 100.0f);
				pInstance->m_v3Velocity.y = frandom(-100.0f, 100.0f);
				pInstance->m_v3Velocity.z = frandom(-100.0f, 100.0f);
			}
			else
			{
				D3DXVec3Normalize(&pInstance->m_v3Velocity, &(pInstance->m_v3Position-v3TimePosition));
				pInstance->m_v3Velocity *= 100.0f;
			}
		}

change to:

		if (CEmitterProperty::EMITTER_ADVANCED_TYPE_INNER == m_pEmitterProperty->GetEmitterAdvancedType())
		{
			auto d3dd = (pInstance->m_v3Position - v3TimePosition);
			D3DXVec3Normalize(&pInstance->m_v3Velocity, &d3dd);
			pInstance->m_v3Velocity *= -100.0f;
		}
		else if (CEmitterProperty::EMITTER_ADVANCED_TYPE_OUTER == m_pEmitterProperty->GetEmitterAdvancedType())
		{
			if (m_pEmitterProperty->GetEmitterShape() == CEmitterProperty::EMITTER_SHAPE_POINT)
			{
				pInstance->m_v3Velocity.x = frandom(-100.0f, 100.0f);
				pInstance->m_v3Velocity.y = frandom(-100.0f, 100.0f);
				pInstance->m_v3Velocity.z = frandom(-100.0f, 100.0f);
			}
			else
			{
				auto d3dd = (pInstance->m_v3Position - v3TimePosition);
				D3DXVec3Normalize(&pInstance->m_v3Velocity, &d3dd);
				pInstance->m_v3Velocity *= 100.0f;
			}
		}

search this:

	if (fAngularVelocity && !m_pParticleProperty->m_bAttachFlag)
	{
		D3DXVec3TransformNormal(&m_pParticleProperty->m_v3ZAxis,&D3DXVECTOR3(0.0f,0.0f,1.0f),mc_pmatLocal);
	}

modify to:

	if (fAngularVelocity && !m_pParticleProperty->m_bAttachFlag)
	{
		auto d3dd = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3TransformNormal(&m_pParticleProperty->m_v3ZAxis, &d3dd, mc_pmatLocal);
	}


search this:


void CParticleSystemInstance::OnRender()
{
	CScreen::Identity();
	STATEMANAGER.SetRenderState(D3DRS_SRCBLEND, m_pParticleProperty->m_bySrcBlendType);
	STATEMANAGER.SetRenderState(D3DRS_DESTBLEND, m_pParticleProperty->m_byDestBlendType);
	STATEMANAGER.SetTextureStageState(0,D3DTSS_COLOROP,m_pParticleProperty->m_byColorOperationType);
	if (m_pParticleProperty->m_byBillboardType < BILLBOARD_TYPE_2FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			ForEachParticleRendering(NParticleRenderer::NormalRenderer());
		}
		else
		{
			ForEachParticleRendering(NParticleRenderer::AttachRenderer(mc_pmatLocal));
		}
	}
	else if (m_pParticleProperty->m_byBillboardType == BILLBOARD_TYPE_2FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			ForEachParticleRendering(NParticleRenderer::TwoSideRenderer());
		}
		else
		{
			ForEachParticleRendering(NParticleRenderer::TwoSideRenderer(mc_pmatLocal));
		}
	}
	else if (m_pParticleProperty->m_byBillboardType == BILLBOARD_TYPE_3FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			ForEachParticleRendering(NParticleRenderer::ThreeSideRenderer());
		}
		else
		{
			ForEachParticleRendering(NParticleRenderer::ThreeSideRenderer(mc_pmatLocal));
		}
	}
}


modify to:


void CParticleSystemInstance::OnRender()
{
	CScreen::Identity();
	STATEMANAGER.SetRenderState(D3DRS_SRCBLEND, m_pParticleProperty->m_bySrcBlendType);
	STATEMANAGER.SetRenderState(D3DRS_DESTBLEND, m_pParticleProperty->m_byDestBlendType);
	STATEMANAGER.SetTextureStageState(0, D3DTSS_COLOROP, m_pParticleProperty->m_byColorOperationType);
	if (m_pParticleProperty->m_byBillboardType < BILLBOARD_TYPE_2FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			auto obj = NParticleRenderer::NormalRenderer();
			ForEachParticleRendering(obj);
		}
		else
		{
			auto obj = NParticleRenderer::AttachRenderer(mc_pmatLocal);
			ForEachParticleRendering(obj);
		}
	}
	else if (m_pParticleProperty->m_byBillboardType == BILLBOARD_TYPE_2FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			auto obj = NParticleRenderer::TwoSideRenderer();
			ForEachParticleRendering(obj);
		}
		else
		{
			auto obj = NParticleRenderer::TwoSideRenderer(mc_pmatLocal);
			ForEachParticleRendering(obj);
		}
	}
	else if (m_pParticleProperty->m_byBillboardType == BILLBOARD_TYPE_3FACE)
	{
		if (!m_pParticleProperty->m_bAttachFlag)
		{
			auto obj = NParticleRenderer::ThreeSideRenderer();
			ForEachParticleRendering(obj);
		}
		else
		{
			auto obj = NParticleRenderer::ThreeSideRenderer(mc_pmatLocal);
			ForEachParticleRendering(obj);
		}
	}
}