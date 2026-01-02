#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// cek kalo OS windows!
#ifdef _WIN32
	#define NOMINMAX // cegah konflik makro min/max
	#include <Windows.h>
	void update_title(const std::string& title) {
		SetConsoleTitleA(title.c_str());
	}
// kalo kagak jalanin kode dibawah!
#else
	#include <unistd.h>
	void update_title(const char* title) {
		std::cout << "\033]0;" << title << "\007" << std::flush;
	}
#endif

// fungsi untuk membuat string acak
std::string get_rand_string(size_t length) {
	const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, charset.size() - 1);

	std::string str;
	for (size_t i = 0; i < length; ++i) {
		str += charset[dis(gen)];
	}
	return str;
}

// fungsi yang berjalan di thread terpisah
void title_obfuscator() {
	while (true) {
		std::string rand_title = get_rand_string(15);
		update_title(rand_title);

		// jeda waktu
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

int main() {
	// panggil fungsi
	std::thread background_thread(title_obfuscator);
	background_thread.detach();

	std::cout << "\n [CONTOH AJE] Your Hacks / Cheats Program" << std::endl;
	std::cout << " F1: AIMBOT" << std::endl;
	std::cout << " F2: ESP BOX, LINE, HEALTH" << std::endl;
	std::cout << " F3: NO RECOIL" << std::endl;

	std::cin.get();

	return 0;
}