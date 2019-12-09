#include <cstring>

#include <winrt/Windows.Security.Cryptography.h>
using namespace winrt::Windows::Security::Cryptography;

int
uwp_urandom(unsigned char* buffer, size_t size) {
	auto cryptoBuffer = CryptographicBuffer::GenerateRandom(size);
	winrt::com_array<uint8_t> buf(static_cast<uint32_t>(size));
	CryptographicBuffer::CopyToByteArray(cryptoBuffer, buf);
	std::memcpy(buffer, buf.data(), size);
	return 0;
}
