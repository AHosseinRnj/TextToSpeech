#ifndef VOICE_H
#define VOICE_H

#include <iostream>
#include <string>
#include <sapi.h>

class Voice {
public:
	Voice(const std::wstring& text = L"", const int& voiceGender = 1,
	      const int& voiceSpeed = 0, const int& voiceVolume = 100);
	~Voice();

	void initialize();

	void setText(const std::wstring& text);
	void setGender(const int& voiceGender);
	void setSpeed(const int& voiceSpeed);
	void setVolume(const int& voiceVolume);

	void playVoice();

private:
	ISpVoice* pVoice;
	HRESULT HResult, Test;
	std::wstring winput;

	int Gender;
	std::wstring wGender;

	int Speed;
	std::wstring wSpeed;

	int Volume;
	std::wstring wVolume;
};

#endif // !VOICE_H
