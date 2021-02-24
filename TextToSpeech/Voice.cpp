#include "Voice.h"

Voice::Voice(const std::wstring& text, const int& voiceGender,
			 const int& voiceSpeed, const int& voiceVolume)
{
	setText(text);
	setGender(voiceGender);
	setSpeed(voiceSpeed);
	setVolume(voiceVolume);
}

Voice::~Voice()
{
	Gender = NULL;
	Speed = NULL;
	Volume = NULL;
	winput.clear();
	wGender.clear();
	wSpeed.clear();
	wVolume.clear();

	/*
		https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-couninitialize
		
		Closes the COM library on the current thread, unloads all DLLs loaded by the thread,
		frees any other resources that the thread maintains,
		and forces all RPC connections on the thread to close.
	*/

	::CoUninitialize();
	delete pVoice;
	pVoice = NULL;
}

void Voice::initialize()
{
	pVoice = NULL;

	/*
	https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializeex

	LPVOID pvReserved, --> its reserved and must be NULL.

	DWORD  dwCoInit --> specifies the threading model that your program will use.
						COM supports two different threading models, apartment threaded and multithreaded.
	*/

	Test = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(Test)) {
		std::cerr << "\n[!] Faild to initialize.\r\n";
		exit(EXIT_FAILURE);
	}

	/*
	https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cocreateinstance

	REFCLSID  rclsid, --> rclsid The CLSID associated with the data and code that will be used to create the object.

	LPUNKNOWN pUnkOuter, --> if NULL, indicates that the object is not being created as part of an aggregate.
							 If non-NULL, pointer to the aggregate object's IUnknown interface (the controlling IUnknown).

	DWORD     dwClsContext, --> Context in which the code that manages the newly created object will run.
								The values are taken from the enumeration CLSCTX.

	REFIID    riid, --> a reference to the identifier of the interface to be used to communicate with the object.

	LPVOID    *ppv --> Address of pointer variable that receives the interface pointer requested in riid.
					   Upon successful return, *ppv contains the requested interface pointer. Upon failure, *ppv contains NULL.
	*/

	HResult = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (FAILED(HResult)) {
		std::cerr << "\n[!] Faild to initialize.\r\n";
		exit(EXIT_FAILURE);
	}
}

void Voice::setText(const std::wstring& text)
{
	winput = text;
}

void Voice::setGender(const int& voiceGender)
{
	/// Gender = 1   -->    Male
	/// Gender = 2   -->    Female

	if (voiceGender == 1) {
		Gender = voiceGender;
		wGender = L"<voice required='Gender = Male;'>";
	}
	else if (voiceGender == 2) {
		Gender = voiceGender;
		wGender = L"<voice required='Gender = Female;'>";
	}
	else {
		std::cerr << "\n[!] Unknown Gender.\r\n";
	}
}

void Voice::setSpeed(const int& voiceSpeed)
{
	if (voiceSpeed >= -30 && voiceSpeed <= 20) {
		Speed = voiceSpeed;
	}
	else {
		Speed = 0;
	}
	wSpeed = L"<rate absspeed=\"" + std::to_wstring(Speed) + L"\">";
}

void Voice::setVolume(const int& voiceVolume)
{
	if (voiceVolume >= 0 && voiceVolume <= 100) {
		Volume = voiceVolume;
	}
	else {
		Volume = 100;
	}
	wVolume = L"<volume level=\"" + std::to_wstring(Volume) + L"\">";
}

void Voice::playVoice()
{
	/*
	https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ms719820(v=vs.85)

	LPCWSTR	 *pwcs, --> [in, string] Pointer to the null-terminated text string (possibly containing XML markup)
						to be synthesized.

	DWORD	 dwFlags, --> [in] Flags used to control the rendering process for this call.
						  The flag values are contained in the SPEAKFLAGS enumeration.

	ULONG	 *pulStreamNumber -->  [out] Pointer to a ULONG which receives the current input stream number associated with this Speak request.
								   Each time a string is spoken, an associated stream number is returned.
								   Events queued back to the application related to this string will contain this number. If NULL, no value is passed back.
	*/

	if (SUCCEEDED(HResult)) {
		HResult = pVoice->Speak((wSpeed + wVolume + wGender + winput).c_str(), 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}
}