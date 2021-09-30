search this:

bool CDXTCImage::LoadFromFile(const char * filename)
{
	// only understands .dds files for now
	// return true if success
	char * exts[] = { ".DDS" };
	int next = 1;

	static char fileupper[MAX_PATH+1];

	strncpy(fileupper, filename, MAX_PATH);
	_strupr(fileupper);

	int i;
	bool knownformat = false;

	for (i = 0; i < next; ++i)
	{
		char * found = strstr(fileupper, exts[0]);

		if (found != NULL)
		{
			knownformat = true;
			break;
		}
	}

	if (knownformat == false)
	{
		Tracef("Unknown file format encountered! [%s]\n", filename);
		return(false);
	}

	CMappedFile mappedFile;
	LPCVOID pvMap;

	if (!mappedFile.Create(filename, &pvMap, 0, 0))
	{
		Tracef("Can't open file for reading! [%s]\n", filename);
		return false;
	}

	return LoadFromMemory((const BYTE*) pvMap);
}

overwrite the function:


bool CDXTCImage::LoadFromFile(const char * filename)
{
	// only understands .dds files for now
	// return true if success
	int next = 1;

	static char fileupper[MAX_PATH+1];

	strncpy(fileupper, filename, MAX_PATH);
	_strupr(fileupper);

	int i;
	bool knownformat = false;

	for (i = 0; i < next; ++i)
	{
		char* found = strstr(fileupper, ".DDS");

		if (found != NULL)
		{
			knownformat = true;
			break;
		}
	}

	if (knownformat == false)
	{
		Tracef("Unknown file format encountered! [%s]\n", filename);
		return(false);
	}

	CMappedFile mappedFile;
	LPCVOID pvMap;

	if (!mappedFile.Create(filename, &pvMap, 0, 0))
	{
		Tracef("Can't open file for reading! [%s]\n", filename);
		return false;
	}

	return LoadFromMemory((const BYTE*) pvMap);
}
