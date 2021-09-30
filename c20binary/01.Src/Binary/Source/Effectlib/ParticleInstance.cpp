search this:

		case BILLBOARD_TYPE_Y:
			{
				v3Up = D3DXVECTOR3(0.0f,0.0f,1.0f);
				//v3Up = D3DXVECTOR3(cosf(D3DXToRadian(m_fRotation)),0.0f,-sinf(D3DXToRadian(m_fRotation)));
				const D3DXVECTOR3 & c_rv3View = pCurrentCamera->GetView();
				if (v3Up.x * c_rv3View.y - v3Up.y * c_rv3View.x<0)
					v3Up*=-1;
				D3DXVec3Cross(&v3Cross, &v3Up, &D3DXVECTOR3(c_rv3View.x,c_rv3View.y,0));
				D3DXVec3Normalize(&v3Cross, &v3Cross);

				if (m_fRotation)
				{
					float fCos = -sinf(D3DXToRadian(m_fRotation)); // + 90
					float fSin = cosf(D3DXToRadian(m_fRotation));

					D3DXVECTOR3 v3Temp = v3Up * fCos - v3Cross * fSin;
					v3Cross = v3Cross * fCos + v3Up * fSin;
					v3Up = v3Temp;
				}

				//D3DXVECTOR3 v3Rotation;
				//D3DXVec3Cross(&v3Rotation, &v3Up, &v3Cross);

			}
			break;


rewrite with:

		case BILLBOARD_TYPE_Y:
		{
			v3Up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			//v3Up = D3DXVECTOR3(cosf(D3DXToRadian(m_fRotation)),0.0f,-sinf(D3DXToRadian(m_fRotation)));
			const D3DXVECTOR3& c_rv3View = pCurrentCamera->GetView();
			if (v3Up.x * c_rv3View.y - v3Up.y * c_rv3View.x < 0)
				v3Up *= -1;
			auto d3dd = D3DXVECTOR3(c_rv3View.x, c_rv3View.y, 0);
			D3DXVec3Cross(&v3Cross, &v3Up, &d3dd);
			D3DXVec3Normalize(&v3Cross, &v3Cross);

			if (m_fRotation)
			{
				float fCos = -sinf(D3DXToRadian(m_fRotation)); // + 90
				float fSin = cosf(D3DXToRadian(m_fRotation));

				D3DXVECTOR3 v3Temp = v3Up * fCos - v3Cross * fSin;
				v3Cross = v3Cross * fCos + v3Up * fSin;
				v3Up = v3Temp;
			}

			//D3DXVECTOR3 v3Rotation;
			//D3DXVec3Cross(&v3Rotation, &v3Up, &v3Cross);

		}
		break;

search this:

		case BILLBOARD_TYPE_ALL:
		default:
			{
				if (m_fRotation==0.0f)
				{
					v3Up = -c_rv3Cross;
					v3Cross = c_rv3Up;
				}
				else
				{
					const D3DXVECTOR3 & c_rv3View = pCurrentCamera->GetView();
					D3DXMATRIX matRotation;

					D3DXMatrixRotationAxis(&matRotation, &c_rv3View, D3DXToRadian(m_fRotation));
					D3DXVec3TransformCoord(&v3Up, &(-c_rv3Cross), &matRotation);
					D3DXVec3TransformCoord(&v3Cross, &c_rv3Up, &matRotation);
				}
			}
			break;


modify to:

			case BILLBOARD_TYPE_ALL:
			default:
			{
				// NOTE : Rotation Routine. Camera의 Up Vector와 Cross Vector 자체를 View Vector 기준으로
				//        Rotation 시킨다.
				// FIXME : 반드시 최적화 할 것!
				if (m_fRotation == 0.0f)
				{
					v3Up = -c_rv3Cross;
					v3Cross = c_rv3Up;
				}
				else
				{
					const D3DXVECTOR3& c_rv3View = pCurrentCamera->GetView();
					D3DXMATRIX matRotation;

					D3DXMatrixRotationAxis(&matRotation, &c_rv3View, D3DXToRadian(m_fRotation));
					auto d3dd = (-c_rv3Cross);
					D3DXVec3TransformCoord(&v3Up, &d3dd, &matRotation);
					D3DXVec3TransformCoord(&v3Cross, &c_rv3Up, &matRotation);
				}
			}
			break;