search this:

template<typename TContainer>
inline void stl_wipe(TContainer& container)
{
	for (TContainer::iterator i = container.begin(); i != container.end(); ++i)
	{
		delete *i;
		*i = NULL;
	}

	container.clear();
}

overwrite with this:

template<typename TContainer>
inline void stl_wipe(TContainer& container)
{
	for (auto i = container.begin(); i != container.end(); ++i)
	{
		delete* i;
		*i = NULL;
	}

	container.clear();
}

search this:

template<typename TContainer>
inline void stl_wipe_second(TContainer& container)
{
	for (TContainer::iterator i = container.begin(); i != container.end(); ++i)
	{
		delete i->second;
	}

	container.clear();
}

overwrite with this:

template<typename TContainer>
inline void stl_wipe_second(TContainer& container)
{
	for (auto i = container.begin(); i != container.end(); ++i)
	{
		delete i->second;
	}

	container.clear();
}

search this:

template <typename T>
void DeleteVectorItem(std::vector<T> * pVector, unsigned long dwIndex)
{
	if (dwIndex >= pVector->size())
	{
		assert(!"Wrong index to delete!");
		return;
	}
	if (1 == pVector->size())
	{
		pVector->clear();
		return;
	}

	std::vector<T>::iterator itor = pVector->begin();
	for (unsigned long i = 0; i < dwIndex; ++i)
		++itor;

	pVector->erase(itor);
}

overwrite with this:

template <typename T>
void DeleteVectorItem(std::vector<T> * pVector, unsigned long dwIndex)
{
	if (dwIndex >= pVector->size())
	{
		assert(!"Wrong index to delete!");
		return;
	}
	if (1 == pVector->size())
	{
		pVector->clear();
		return;
	}

	auto itor = pVector->begin();
	for (unsigned long i = 0; i < dwIndex; ++i)
		++itor;

	pVector->erase(itor);
}

search this:

template <typename T>
void DeleteVectorItem(T * pVector, unsigned long dwStartIndex, unsigned long dwEndIndex)
{
	if (dwStartIndex >= pVector->size())
	{
		assert(!"Wrong start index to delete!");
		return;
	}
	if (dwEndIndex >= pVector->size())
	{
		assert(!"Wrong end index to delete!");
		return;
	}

	T::iterator itorStart = pVector->begin();
	for (unsigned long i = 0; i < dwStartIndex; ++i)
		++itorStart;
	T::iterator itorEnd = pVector->begin();
	for (unsigned long j = 0; j < dwEndIndex; ++j)
		++itorEnd;

	pVector->erase(itorStart, itorEnd);
}

overwrite with this:

template <typename T>
void DeleteVectorItem(T * pVector, unsigned long dwStartIndex, unsigned long dwEndIndex)
{
	if (dwStartIndex >= pVector->size())
	{
		assert(!"Wrong start index to delete!");
		return;
	}
	if (dwEndIndex >= pVector->size())
	{
		assert(!"Wrong end index to delete!");
		return;
	}

	auto itorStart = pVector->begin();
	for (unsigned long i = 0; i < dwStartIndex; ++i)
		++itorStart;
	auto itorEnd = pVector->begin();
	for (unsigned long j = 0; j < dwEndIndex; ++j)
		++itorEnd;

	pVector->erase(itorStart, itorEnd);
}

search this:

template <typename T>
void DeleteVectorItem(std::vector<T> * pVector, T pItem)
{
	std::vector<T>::iterator itor = pVector->begin();
	for (; itor != pVector->end(); ++itor)
	{
		if (pItem == *itor)
		{
			if (1 == pVector->size())
			{
				pVector->clear();
			}
			else
			{
				pVector->erase(itor);
			}
			break;
		}
	}
}

overwrite with this:

template <typename T>
void DeleteVectorItem(std::vector<T> * pVector, T pItem)
{
	auto itor = pVector->begin();
	for (; itor != pVector->end(); ++itor)
	{
		if (pItem == *itor)
		{
			if (1 == pVector->size())
			{
				pVector->clear();
			}
			else
			{
				pVector->erase(itor);
			}
			break;
		}
	}
}

search this:

template <typename T>
void DeleteListItem(std::list<T> * pList, T pItem)
{
	std::list<T>::iterator itor = pList->begin();
	for (; itor != pList->end(); ++itor)
	{
		if (pItem == *itor)
		{
			if (1 == pList->size())
			{
				pList->clear();
			}
			else
			{
				pList->erase(itor);
			}
			break;
		}
	}
}

overwrite with this:

template <typename T>
void DeleteListItem(std::list<T> * pList, T pItem)
{
	auto itor = pList->begin();
	for (; itor != pList->end(); ++itor)
	{
		if (pItem == *itor)
		{
			if (1 == pList->size())
			{
				pList->clear();
			}
			else
			{
				pList->erase(itor);
			}
			break;
		}
	}
}