search this:

	protected:
		struct FFindMapName
		{
			std::string strNametoFind;
			FFindMapName::FFindMapName(const std::string & c_rMapName)
			{
				strNametoFind = c_rMapName;
				stl_lowers(strNametoFind);
			}
			bool operator() (TMapInfo & rMapInfo)
			{
				if (rMapInfo.m_strName == strNametoFind)
					return true;
				return false;
			}
		};

modify to:

	protected:
		struct FFindMapName
		{
			std::string strNametoFind;
			FFindMapName(const std::string & c_rMapName)
			{
				strNametoFind = c_rMapName;
				stl_lowers(strNametoFind);
			}
			bool operator() (TMapInfo & rMapInfo)
			{
				if (rMapInfo.m_strName == strNametoFind)
					return true;
				return false;
			}
		};