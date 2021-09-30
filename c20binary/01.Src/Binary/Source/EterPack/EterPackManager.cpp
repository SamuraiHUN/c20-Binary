search this.

	for( int i = 0; i < iPackageCnt; ++i )
	{
		int iRecvedCryptKeySize = 0;
		memcpy( &iRecvedCryptKeySize, pStream + iMemOffset, sizeof(iRecvedCryptKeySize) );
		iRecvedCryptKeySize -= sizeof(dwPackageNameHash);
		iMemOffset += sizeof(iRecvedCryptKeySize);

		memcpy( &dwPackageNameHash, pStream + iMemOffset, sizeof(dwPackageNameHash) );
		iMemOffset += sizeof(dwPackageNameHash);

		TEterPackMap::const_iterator cit;
		for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
		{
			std::string noPathName = CFileNameHelper::NoPath(string(cit->first));
			if( dwPackageNameHash == stringhash().GetHash(noPathName) )
			{
				EterPackPolicy_CSHybridCrypt* pCryptPolicy = cit->second->GetPackPolicy_HybridCrypt();
				int iHavedCryptKeySize = pCryptPolicy->ReadCryptKeyInfoFromStream( pStream + iMemOffset );
				if (iRecvedCryptKeySize != iHavedCryptKeySize)
				{
					TraceError("CEterPackManager::RetrieveHybridCryptPackKeys	cryptokey length of file(%s) is not matched. received(%d) != haved(%d)", noPathName.c_str(), iRecvedCryptKeySize, iHavedCryptKeySize);
				}
				break;
			}
		}
		iMemOffset += iRecvedCryptKeySize;
	}
	
modify to:

	for( int i = 0; i < iPackageCnt; ++i )
	{
		int iRecvedCryptKeySize = 0;
		memcpy( &iRecvedCryptKeySize, pStream + iMemOffset, sizeof(iRecvedCryptKeySize) );
		iRecvedCryptKeySize -= sizeof(dwPackageNameHash); // 서버에서 받은 key stream에는 filename hash가 포함되어 있으므로, hash 사이즈 만큼 배줌.
		iMemOffset += sizeof(iRecvedCryptKeySize);

		memcpy( &dwPackageNameHash, pStream + iMemOffset, sizeof(dwPackageNameHash) );
		iMemOffset += sizeof(dwPackageNameHash);

		TEterPackMap::const_iterator cit;
		for (cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit)
		{
			auto ssvv = std::string(cit->first);
			std::string noPathName = CFileNameHelper::NoPath(ssvv);
			if (dwPackageNameHash == stringhash().GetHash(noPathName))
			{
				EterPackPolicy_CSHybridCrypt* pCryptPolicy = cit->second->GetPackPolicy_HybridCrypt();
				int iHavedCryptKeySize = pCryptPolicy->ReadCryptKeyInfoFromStream(pStream + iMemOffset);
				if (iRecvedCryptKeySize != iHavedCryptKeySize)
				{
					TraceError("CEterPackManager::RetrieveHybridCryptPackKeys	cryptokey length of file(%s) is not matched. received(%d) != haved(%d)", noPathName.c_str(), iRecvedCryptKeySize, iHavedCryptKeySize);
				}
				break;
			}
		}
		iMemOffset += iRecvedCryptKeySize;
	}

search this:


	TEterPackMap::const_iterator cit;
	for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
	{
		EterPackPolicy_CSHybridCrypt* pPolicy = cit->second->GetPackPolicy_HybridCrypt();
		if( !pPolicy || !pPolicy->IsContainingCryptKey() )
			continue;

		iKeyPackageCount++;

		std::string noPathName = CFileNameHelper::NoPath(string(cit->first));

		DWORD dwPackNamehash = stringhash().GetHash(noPathName);

		CMakePackLog::GetSingleton().Writef("CEterPackManager::WriteHybridCryptPackInfo PackName : %s, Hash : %x", noPathName.c_str(), dwPackNamehash);
		keyFile.Write( &dwPackNamehash, sizeof(DWORD) );

		pPolicy->WriteCryptKeyToFile( keyFile );
	}

modify to:

	TEterPackMap::const_iterator cit;
	for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
	{
		EterPackPolicy_CSHybridCrypt* pPolicy = cit->second->GetPackPolicy_HybridCrypt();
		if( !pPolicy || !pPolicy->IsContainingCryptKey() )
			continue;

		iKeyPackageCount++;

		auto ssvv = std::string(cit->first);
		std::string noPathName = CFileNameHelper::NoPath(ssvv);

		DWORD dwPackNamehash = stringhash().GetHash(noPathName);

		CMakePackLog::GetSingleton().Writef("CEterPackManager::WriteHybridCryptPackInfo PackName : %s, Hash : %x", noPathName.c_str(), dwPackNamehash);
		keyFile.Write( &dwPackNamehash, sizeof(DWORD) );

		pPolicy->WriteCryptKeyToFile( keyFile );
	}


search this:

	for( int i = 0; i < iSDBInfoCount; ++i )
	{
		DWORD dwPackgeIdentifier;
		memcpy( &dwPackgeIdentifier, pStream+iReadOffset, sizeof(DWORD) );
		iReadOffset += sizeof(DWORD);

		TEterPackMap::const_iterator cit;
		for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
		{
			std::string noPathName = CFileNameHelper::NoPath(string(cit->first));
			if( dwPackgeIdentifier == stringhash().GetHash(noPathName) )
			{
				EterPackPolicy_CSHybridCrypt* pCryptPolicy = cit->second->GetPackPolicy_HybridCrypt();
				iReadOffset += pCryptPolicy->ReadSupplementatyDataBlockFromStream( pStream+iReadOffset );
				break;
			}
		}
	}

modify to:

	for( int i = 0; i < iSDBInfoCount; ++i )
	{
		DWORD dwPackgeIdentifier;
		memcpy( &dwPackgeIdentifier, pStream+iReadOffset, sizeof(DWORD) );
		iReadOffset += sizeof(DWORD);

		TEterPackMap::const_iterator cit;
		for (cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit)
		{
			auto ssvv = std::string(cit->first);
			std::string noPathName = CFileNameHelper::NoPath(ssvv);
			if (dwPackgeIdentifier == stringhash().GetHash(noPathName))
			{
				EterPackPolicy_CSHybridCrypt* pCryptPolicy = cit->second->GetPackPolicy_HybridCrypt();
				iReadOffset += pCryptPolicy->ReadSupplementatyDataBlockFromStream(pStream + iReadOffset);
				break;
			}
		}
	}

search this:


	//Write SDB PackageCnt Later
	keyFile.SeekCur(sizeof(int));
	for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
	{
		EterPackPolicy_CSHybridCrypt* pPolicy = cit->second->GetPackPolicy_HybridCrypt();
		if( !pPolicy || !pPolicy->IsContainingSDBFile() )
			continue;

		iSDBPackageCnt++;

		std::string noPathName = CFileNameHelper::NoPath(string(cit->first));

		DWORD dwPackNamehash = stringhash().GetHash(noPathName);
		keyFile.Write( &dwPackNamehash, sizeof(DWORD) );

		int iSDBSizeWriteOffset = keyFile.GetPosition();
		keyFile.SeekCur(sizeof(int));

		pPolicy->WriteSupplementaryDataBlockToFile( keyFile );
		int iSDBSizeAfterWrite = keyFile.GetPosition();

		keyFile.Seek(iSDBSizeWriteOffset);

		int iSDBSize = iSDBSizeAfterWrite-(iSDBSizeWriteOffset+4);
		keyFile.Write( &iSDBSize, sizeof(int) );

		keyFile.Seek(iSDBSizeAfterWrite);
	}

modify to:

	//Write SDB PackageCnt Later
	keyFile.SeekCur(sizeof(int));
	for( cit = m_PackMap.begin(); cit != m_PackMap.end(); ++cit )
	{
		EterPackPolicy_CSHybridCrypt* pPolicy = cit->second->GetPackPolicy_HybridCrypt();
		if( !pPolicy || !pPolicy->IsContainingSDBFile() )
			continue;

		iSDBPackageCnt++;

		auto ssvv1 = std::string(cit->first);
		auto noPathName = CFileNameHelper::NoPath(ssvv1);

		DWORD dwPackNamehash = stringhash().GetHash(noPathName);
		keyFile.Write( &dwPackNamehash, sizeof(DWORD) );

		int iSDBSizeWriteOffset = keyFile.GetPosition();
		keyFile.SeekCur(sizeof(int));

		pPolicy->WriteSupplementaryDataBlockToFile( keyFile );
		int iSDBSizeAfterWrite = keyFile.GetPosition();

		keyFile.Seek(iSDBSizeWriteOffset);

		int iSDBSize = iSDBSizeAfterWrite-(iSDBSizeWriteOffset+4);
		keyFile.Write( &iSDBSize, sizeof(int) );

		keyFile.Seek(iSDBSizeAfterWrite);
	}