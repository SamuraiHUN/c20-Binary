search this:


		// load branch textures
		LoadTexture((CFileNameHelper::GetPath(string(pszSptFile)) + CFileNameHelper::NoExtension(string(m_pTextureInfo->m_pBranchTextureFilename)) + ".dds").c_str(), m_BranchImageInstance);

#ifdef WRAPPER_RENDER_SELF_SHADOWS
		if (m_pTextureInfo->m_pSelfShadowFilename != NULL)
			LoadTexture((CFileNameHelper::GetPath(string(pszSptFile)) + CFileNameHelper::NoExtension(string(m_pTextureInfo->m_pSelfShadowFilename)) + ".dds").c_str(), m_ShadowImageInstance);
#endif
		if (m_pTextureInfo->m_pCompositeFilename)
			LoadTexture((CFileNameHelper::GetPath(string(pszSptFile)) + CFileNameHelper::NoExtension(string(m_pTextureInfo->m_pCompositeFilename)) + ".dds").c_str(), m_CompositeImageInstance);

		// setup the index and vertex buffers
		SetupBuffers();

		// everything appeared to go well
		bSuccess = true;
	}
	else // tree failed to compute
		fprintf(stderr, "\nFatal Error, cannot compute tree [%s]\n\n", CSpeedTreeRT::GetCurrentError());

    return bSuccess;


modify to:

		// load branch textures
		auto vs1 = std::string(pszSptFile);
		auto vs2 = std::string(m_pTextureInfo->m_pBranchTextureFilename);
		LoadTexture((CFileNameHelper::GetPath(vs1) + CFileNameHelper::NoExtension(vs2) + ".dds").c_str(), m_BranchImageInstance);

#ifdef WRAPPER_RENDER_SELF_SHADOWS
		if (m_pTextureInfo->m_pSelfShadowFilename != NULL)
		{
			auto vss = std::string(m_pTextureInfo->m_pSelfShadowFilename);
			LoadTexture((CFileNameHelper::GetPath(vs1) + CFileNameHelper::NoExtension(vss) + ".dds").c_str(), m_ShadowImageInstance);
		}
#endif
		if (m_pTextureInfo->m_pCompositeFilename)
		{
			auto vss = std::string(m_pTextureInfo->m_pCompositeFilename);
			LoadTexture((CFileNameHelper::GetPath(vs1) + CFileNameHelper::NoExtension(vss) + ".dds").c_str(), m_CompositeImageInstance);
		}

		// setup the index and vertex buffers
		SetupBuffers();

		// everything appeared to go well
		bSuccess = true;
	}
	else // tree failed to compute
		fprintf(stderr, "\nFatal Error, cannot compute tree [%s]\n\n", CSpeedTreeRT::GetCurrentError());

    return bSuccess;