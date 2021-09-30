search this function:


		void Destroy()
		{
#ifdef _DEBUG
			if (!m_kVct_pkData.empty())
			{
				char szText[256];
				sprintf(szText, "--------------------------------------------------------------------- %s Pool Destroy\n", typeid(T).name());
				OutputDebugString(szText);
				printf(szText);
			}
#endif
			std::for_each(m_kVct_pkData.begin(), m_kVct_pkData.end(), Delete);
			m_kVct_pkData.clear();
			m_kVct_pkFree.clear();
		}


overwrite with this:

		void Destroy()
		{
#ifdef _DEBUG
			if (!m_kVct_pkData.empty())
			{
				char szText[256];
				sprintf(szText, "--------------------------------------------------------------------- %s Pool Destroy\n", typeid(T).name());
				OutputDebugString(szText);
				printf(szText);
			}
#endif
			for (auto v : m_kVct_pkData)
				Delete(v);
			m_kVct_pkData.clear();
			m_kVct_pkFree.clear();
		}

search this:

		void Destroy()
		{
/*
#ifdef _DEBUG
			if (!m_kVct_pkData.empty())
			{
				char szText[256];
				sprintf(szText, "--------------------------------------------------------------------- %s Pool Destroy\n", typeid(T).name());
				OutputDebugString(szText);
				printf(szText);
			}
#endif
*/
			std::for_each(m_kVct_pkData.begin(), m_kVct_pkData.end(), Delete);
			m_kVct_pkData.clear();
			m_kVct_pkFree.clear();
		}

overwrite with this:

		void Destroy()
		{
/*
#ifdef _DEBUG
			if (!m_kVct_pkData.empty())
			{
				char szText[256];
				sprintf(szText, "--------------------------------------------------------------------- %s Pool Destroy\n", typeid(T).name());
				OutputDebugString(szText);
				printf(szText);
			}
#endif
*/
			for (auto v : m_kVct_pkData)
				Delete(v);
			m_kVct_pkData.clear();
			m_kVct_pkFree.clear();
		}

