search this:

	virtual SymmetricCipher* CreateEncoder(const byte* key, size_t keylen,
		const byte* iv) const = 0;
	virtual SymmetricCipher* CreateDecoder(const byte* key, size_t keylen,
		const byte* iv) const = 0;
		
modify to:

	virtual SymmetricCipher* CreateEncoder(const CryptoPP::byte* key, size_t keylen,
		const CryptoPP::byte* iv) const = 0;
	virtual SymmetricCipher* CreateDecoder(const CryptoPP::byte* key, size_t keylen,
		const CryptoPP::byte* iv) const = 0;

search this:

	virtual SymmetricCipher* CreateEncoder(const byte* key, size_t keylen,
		const byte* iv) const {
			return new CTR_Mode<T>::Encryption(key, keylen, iv);
	}
	virtual SymmetricCipher* CreateDecoder(const byte* key, size_t keylen,
		const byte* iv) const {
			return new CTR_Mode<T>::Decryption(key, keylen, iv);
	}

modify to:

	virtual SymmetricCipher* CreateEncoder(const CryptoPP::byte* key, size_t keylen,
		const CryptoPP::byte* iv) const 
	{
		return new typename CTR_Mode<T>::Encryption(key, keylen, iv);
	}
	virtual SymmetricCipher* CreateDecoder(const CryptoPP::byte* key, size_t keylen,
		const CryptoPP::byte* iv) const 
	{
		return new typename CTR_Mode<T>::Decryption(key, keylen, iv);
	}


search this:

	*length = data_length;
	byte* buf = (byte*)buffer;
	memcpy(buf, spub_key.BytePtr(), spub_key_length);
	memcpy(buf + spub_key_length, epub_key.BytePtr(), epub_key_length);
	
overwrite with:

	*length = data_length;
	CryptoPP::byte* buf = (CryptoPP::byte*)buffer;
	memcpy(buf, spub_key.BytePtr(), spub_key_length);
	memcpy(buf + spub_key_length, epub_key.BytePtr(), epub_key_length);

search this:

bool DH2KeyAgreement::Agree(size_t agreed_length, const void* buffer, size_t length) {
	if (agreed_length != dh2_.AgreedValueLength()) {
		// Shared secret size mismatch
		return false;
	}
	const size_t spub_key_length = dh2_.StaticPublicKeyLength();
	const size_t epub_key_length = dh2_.EphemeralPublicKeyLength();
	if (length != (spub_key_length + epub_key_length)) {
		// Wrong data length
		return false;
	}
	shared_.New(dh2_.AgreedValueLength());
	const byte* buf = (const byte*)buffer;
	if (!dh2_.Agree(shared_, spriv_key_, epriv_key_, buf, buf + spub_key_length)) {
		// Failed to reach shared secret
		return false;
	}
	return true;
}

overwrite with:

bool DH2KeyAgreement::Agree(size_t agreed_length, const void* buffer, size_t length) {
	if (agreed_length != dh2_.AgreedValueLength()) {
		// Shared secret size mismatch
		return false;
	}
	const size_t spub_key_length = dh2_.StaticPublicKeyLength();
	const size_t epub_key_length = dh2_.EphemeralPublicKeyLength();
	if (length != (spub_key_length + epub_key_length)) {
		// Wrong data length
		return false;
	}
	shared_.New(dh2_.AgreedValueLength());
	const CryptoPP::byte* buf = (const CryptoPP::byte*)buffer;
	if (!dh2_.Agree(shared_, spriv_key_, epriv_key_, buf, buf + spub_key_length)) {
		// Failed to reach shared secret
		return false;
	}
	return true;
}