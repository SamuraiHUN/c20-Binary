#include <cryptopp/cryptlib.h>
#pragma warning(pop)

add under this.

using CryptoPP::byte;

search this:

  void Encrypt(void* buffer, size_t length) {
    assert(activated_);
    if (!activated_) {
      return;
    }
    encoder_->ProcessData((CryptoPP::byte*)buffer, (const CryptoPP::byte*)buffer, length);
  }
  // Decrypts the given block of data. (no padding required)
  void Decrypt(void* buffer, size_t length) {
    assert(activated_);
    if (!activated_) {
      return;
    }
    decoder_->ProcessData((CryptoPP::byte*)buffer, (const CryptoPP::byte*)buffer, length);
  }
  
 
modify to:

	void Encrypt(void* buffer, size_t length) {
		assert(activated_);
		if (!activated_) {
			return;
		}
		encoder_->ProcessData((CryptoPP::byte*)buffer, (const CryptoPP::byte*)buffer, length);
	}
	// Decrypts the given block of data. (no padding required)
	void Decrypt(void* buffer, size_t length) {
		assert(activated_);
		if (!activated_) {
			return;
		}
		decoder_->ProcessData((CryptoPP::byte*)buffer, (const CryptoPP::byte*)buffer, length);
	}