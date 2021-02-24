#include <iostream>
#include "Voice.h"

int main() {
	char Breaker{ '\0' };
	std::wstring input{ '\0' };
	int voiceGender{ 0 }, voiceSpeed{ 0 }, voiceVolume{ 0 };

	Voice* voice = new Voice();

	std::cout << "[+] Enter Your Text :\n";
	std::getline(std::wcin, input);
	voice->setText(input);
	std::cout << "[!] Done.\n";

	std::cout << "\n\n[+] Enter Voice Gender : [1] For male, [2] For female\n";
	std::cin >> voiceGender;
	voice->setGender(voiceGender);
	std::cout << "[!] Done.\n";

	std::cout << "\n\n[+] Enter Voice Speed : Value beetwen [-30] & [+20], [0] for default\n";
	std::cin >> voiceSpeed;
	voice->setSpeed(voiceSpeed);
	std::cout << "[!] Done.\n";

	std::cout << "\n\n[+] Enter Voice Volume : Value beetwen [0] & [+100], [100] for default\n";
	std::cin >> voiceVolume;
	voice->setVolume(voiceVolume);
	std::cout << "[!] Done.\n";

	std::cout << "\n\n[+] Playing Voice ...\n";
	voice->initialize();
	voice->playVoice();
	std::cout << "[!] Done.\n" << std::endl;

	delete voice;
	voice = NULL;

	system("pause");
	return 0;
}