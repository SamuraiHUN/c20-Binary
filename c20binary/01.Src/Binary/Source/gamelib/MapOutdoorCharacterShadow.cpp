search this:

	D3DXMatrixLookAtRH(&matLightView,
					   &v3Eye,
					   &v3Target,
					   &D3DXVECTOR3(0.0f, 0.0f, 1.0f));


modify to:

	const auto vv = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtRH(&matLightView,
					   &v3Eye,
					   &v3Target,
					   &vv);