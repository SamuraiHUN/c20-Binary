search this:

	ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	if (ms_bUILessMode)
	{
		// For some reason ImmNotifyIME doesn't work on DaYi and Array CHT IMEs. Cancel composition string by setting zero-length string.
		ImmSetCompositionStringW(himc, SCS_SETSTR, L"", sizeof(wchar_t), L"", sizeof(wchar_t));
	}

modify to:

	ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	if (ms_bUILessMode)
	{
		// For some reason ImmNotifyIME doesn't work on DaYi and Array CHT IMEs. Cancel composition string by setting zero-length string.
		ImmSetCompositionStringW(himc, SCS_SETSTR, NULL, 0, NULL, 0);
	}