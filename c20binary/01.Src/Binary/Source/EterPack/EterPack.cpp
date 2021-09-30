search this:

	else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
	{
#ifdef __THEMIDA__
		VM_START
#endif

		CLZObject * zObj = new CLZObject;

		if( !m_pCSHybridCryptPolicy->DecryptMemory(string(filename), static_cast<const BYTE*>(*data), index->data_size, *zObj) )
		{
			return false;
		}

		out_file.BindLZObjectWithBufferedSize(zObj);
		if( COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
			BYTE* pSDBData;
			int   iSDBSize;

			if( !m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(string(filename), pSDBData, iSDBSize) )
			{
				return false;
			}

			*data = out_file.AppendDataBlock( pSDBData, iSDBSize );
		}
		else
		{
			*data = zObj->GetBuffer();
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}

	return true;

overwrite with this:

	else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
	{
#ifdef __THEMIDA__
		VM_START
#endif

		CLZObject * zObj = new CLZObject;

		auto ssvv = std::string(filename);
		if (!m_pCSHybridCryptPolicy->DecryptMemory(ssvv, static_cast<const BYTE*>(*data), index->data_size, *zObj))
		{
			delete zObj;
			return false;
		}

		out_file.BindLZObjectWithBufferedSize(zObj);
		if( COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
			BYTE* pSDBData;
			int   iSDBSize;

			if( !m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(ssvv, pSDBData, iSDBSize) )
			{
				return false;
			}

			*data = out_file.AppendDataBlock( pSDBData, iSDBSize );
		}
		else
		{
			*data = zObj->GetBuffer();
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}

	return true;
	
	


search this:


	else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
	{
#ifdef __THEMIDA__
		VM_START
#endif

		CLZObject * zObj = new CLZObject;

		if( !m_pCSHybridCryptPolicy->DecryptMemory(string(filename), static_cast<const BYTE*>(*data), index->data_size, *zObj) )
		{
			return false;
		}
		out_file.BindLZObjectWithBufferedSize(zObj);

		if( COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
			BYTE* pSDBData;
			int   iSDBSize;

			if( !m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(string(filename), pSDBData, iSDBSize) )
			{
				return false;
			}
			*data = out_file.AppendDataBlock( pSDBData, iSDBSize );
		}
		else
		{
			*data = zObj->GetBuffer();
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}
	return true;
	
	
overwrite with this:


	else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
	{
#ifdef __THEMIDA__
		VM_START
#endif

		CLZObject* zObj = new CLZObject;
		auto ssvv = std::string(filename);
		if (!m_pCSHybridCryptPolicy->DecryptMemory(ssvv, static_cast<const BYTE*>(*data), index->data_size, *zObj))
		{
			delete zObj;
			return false;
		}

		out_file.BindLZObjectWithBufferedSize(zObj);

		if( COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
			BYTE* pSDBData;
			int   iSDBSize;

			if (!m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(ssvv, pSDBData, iSDBSize))
			{
				delete zObj;
				return false;
			}

			*data = out_file.AppendDataBlock( pSDBData, iSDBSize );
		}
		else
		{
			*data = zObj->GetBuffer();
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}
	return true;


search this:


		else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
#ifdef __THEMIDA__
			VM_START
#endif
			if( !m_pCSHybridCryptPolicy->DecryptMemory(string(index->filename), (const BYTE *) data + index->data_position, index->data_size, zObj) )
				return false;

			if( COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
			{
				dataMapFile.BindLZObjectWithBufferedSize(&zObj);

				BYTE* pSDBData;
				int   iSDBSize;

				if( !m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(string(index->filename), pSDBData, iSDBSize) )
					return false;

				dataMapFile.AppendDataBlock( pSDBData, iSDBSize );
				writeFile.Write(dataMapFile.AppendDataBlock( pSDBData, iSDBSize ),dataMapFile.Size());
			}
			else
			{
				writeFile.Write(zObj.GetBuffer(), zObj.GetBufferSize());
			}
			zObj.Clear();
#ifdef __THEMIDA__
			VM_END
#endif
		}


overwrite with this:


		else if (COMPRESSED_TYPE_HYBRIDCRYPT == index->compressed_type || COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
		{
#ifdef __THEMIDA__
			VM_START
#endif

			auto ssvv = std::string(index->filename);
			if (!m_pCSHybridCryptPolicy->DecryptMemory(ssvv, (const BYTE*)data + index->data_position, index->data_size, zObj))
				return false;

			if (COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB == index->compressed_type)
			{
				dataMapFile.BindLZObjectWithBufferedSize(&zObj);

				BYTE* pSDBData;
				int   iSDBSize;

				if (!m_pCSHybridCryptPolicy->GetSupplementaryDataBlock(ssvv, pSDBData, iSDBSize))
					return false;

				dataMapFile.AppendDataBlock(pSDBData, iSDBSize);
				writeFile.Write(dataMapFile.AppendDataBlock(pSDBData, iSDBSize), dataMapFile.Size());
			}
			else
			{
				writeFile.Write(zObj.GetBuffer(), zObj.GetBufferSize());
			}
			zObj.Clear();
#ifdef __THEMIDA__
			VM_END
#endif
		}


search this:

	if( packType == COMPRESSED_TYPE_HYBRIDCRYPT || packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB )
	{
#ifdef __THEMIDA__
		VM_START
#endif
		m_pCSHybridCryptPolicy->GenerateCryptKey( string(filename) );

		if( packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB )
		{
			if( !m_pCSHybridCryptPolicy->GenerateSupplementaryDataBlock( string(filename), strRelateMapName, (const BYTE*)data, mapFile.Size(), pMappedData, iMappedDataSize ))
			{
				return false;
			}
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}


overwrite the function with this:

	if (packType == COMPRESSED_TYPE_HYBRIDCRYPT || packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB)
	{
#ifdef __THEMIDA__
		VM_START
#endif
		auto ssvvv = std::string(filename);
		m_pCSHybridCryptPolicy->GenerateCryptKey(ssvvv);

		if (packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB)
		{
			if (!m_pCSHybridCryptPolicy->GenerateSupplementaryDataBlock(ssvvv, strRelateMapName, (const BYTE*)data, mapFile.Size(), pMappedData, iMappedDataSize))
			{
				return false;
			}
		}
#ifdef __THEMIDA__
		VM_END
#endif
	}

search this:

	else if (packType == COMPRESSED_TYPE_HYBRIDCRYPT || packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB )
	{
#ifdef __THEMIDA__
		VM_START
#endif

		if( !m_pCSHybridCryptPolicy->EncryptMemory( string(filename), (const BYTE *)data, len, zObj ) )
		{
			return false;
		}

		data = zObj.GetBuffer();
		len = zObj.GetBufferSize();
#ifdef __THEMIDA__
		VM_END
#endif

	}


overwrite the function:

	else if (packType == COMPRESSED_TYPE_HYBRIDCRYPT || packType == COMPRESSED_TYPE_HYBRIDCRYPT_WITHSDB )
	{
#ifdef __THEMIDA__
		VM_START
#endif

		auto ssvv = std::string(filename);
		if (!m_pCSHybridCryptPolicy->EncryptMemory(ssvv, (const BYTE*)data, len, zObj))
		{
			return false;
		}

		data = zObj.GetBuffer();
		len = zObj.GetBufferSize();
		len = zObj.GetBufferSize();
#ifdef __THEMIDA__
		VM_END
#endif
	}