	for (i = 0; i < strlen(resultStr); i++)
	{
		char c = resultStr[i];
		int xor = i + 5;
		resultStr[i] = char(c ^ xor);
	}

modify to:

	for (i = 0; i < strlen(resultStr); i++)
	{
		char c = resultStr[i];
		int xx = i + 5;
		resultStr[i] = char(c ^ xx);
	}