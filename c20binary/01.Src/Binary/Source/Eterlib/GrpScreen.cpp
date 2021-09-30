void CScreen::BuildViewFrustum()
{
	const D3DXVECTOR3& c_rv3Eye=CCameraManager::Instance().GetCurrentCamera()->GetEye();
	const D3DXVECTOR3& c_rv3View=CCameraManager::Instance().GetCurrentCamera()->GetView();
	 ms_frustum.BuildViewFrustum2(
		 ms_matView*ms_matProj,
		 ms_fNearY,
		 ms_fFarY,
		 ms_fFieldOfView,
		 ms_fAspect,
		 c_rv3Eye, c_rv3View);
}

modify to:

void CScreen::BuildViewFrustum()
{
	const D3DXVECTOR3& c_rv3Eye = CCameraManager::Instance().GetCurrentCamera()->GetEye();
	const D3DXVECTOR3& c_rv3View = CCameraManager::Instance().GetCurrentCamera()->GetView();
	auto vv = ms_matView * ms_matProj;
	ms_frustum.BuildViewFrustum2(
		vv,
		ms_fNearY,
		ms_fFarY,
		ms_fFieldOfView,
		ms_fAspect,
		c_rv3Eye, c_rv3View);
}