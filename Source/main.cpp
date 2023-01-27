#include <iostream>
#include <Windows.h>
#include <string>
#include "color.hpp"
#include "driver.hpp"
#include "xorstr.h"
#include <thread>
#include "other.h"
#include "auth.hpp"

DWORD WINAPI fortnitechkk(LPVOID in) {
    auto start_time = std::chrono::system_clock::now();
    while (true) {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            auto current_time = std::chrono::system_clock::now();
            auto elapsed_time = current_time - start_time;
            if (elapsed_time.count() > 1) {
                start_time = current_time;
                fortnitechk();
            }
        }
    }
    return 0;
}


struct slowly_printing_string {
	std::string data;
	long int delay;
};

std::ostream& operator<<(std::ostream& out, const slowly_printing_string& s) {
	for (const auto& c : s.data) {
		out << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
	}
	return out;
}

void clear()
{
	system(E("cls"));
}

using namespace std;

int main()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	system(E("color b"));
	SetConsoleTitle(E(L"Simply Coded A Perm Unban      discord.gg/simply"));
	system(E("cls"));
	std::cout << slowly_printing_string{ "\n\n\n Welcome To Simply's Coded Perm Spoofer",85 };
	std::cout << slowly_printing_string{ "\n\n Last Updated: 1/10/2023",75 };
	CreateThread(NULL, NULL, loopDbg, NULL, NULL, NULL);
	CreateThread(NULL, NULL, loopDbg2, NULL, NULL, NULL);
	Sleep(500);
	std::cout << slowly_printing_string{ "...",50 };
	std::cout << slowly_printing_string{ "\n\n Succesfully Connected To (fake ip here)",140	 };
	std::cout << slowly_printing_string{ "\n\n Connected Users: (i put 3 question marks",140 };
	CreateThread(NULL, NULL, fortnitechkk, NULL, NULL, NULL);

mainn:
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	clear();
	cout << dye::light_blue("\n [ ");
	cout << dye::light_blue("");
	std::cout << slowly_printing_string{ "F1",50 };
	std::cout << dye::light_blue(" ]");
	std::cout << slowly_printing_string{ " -> ",50 };
	std::cout << dye::light_blue("[ ");
	std::cout << slowly_printing_string{ "SPOOF & CLEAN",50 };
	std::cout << dye::light_blue(" ]");

	cout << dye::light_blue("\n [ ");
	cout << dye::light_blue("");
	std::cout << slowly_printing_string{ "F2",50 };
	std::cout << dye::light_blue(" ]");
	std::cout << slowly_printing_string{ " -> ",50 }; 
	std::cout << dye::light_blue("[ ");
	std::cout << slowly_printing_string{ "CHECK SERIALS",50 };
	std::cout << dye::light_blue(" ]");


	cout << dye::light_blue("\n [ ");
	cout << dye::light_blue("");
	std::cout << slowly_printing_string{ "F3",50 };
	std::cout << dye::light_blue(" ]");
	std::cout << slowly_printing_string{ " -> ",50 };
	std::cout << dye::light_blue("[ ");
	std::cout << slowly_printing_string{ "RUN VIRUS.EXE",50 };
	std::cout << dye::light_blue(" ]");
   /*this is joke btw, clicking f3 make you check ur serials*/

	while (true)
	{
		if (GetAsyncKeyState(VK_F1) & 1) {
			Beep(500, 500);
			Spoof::Perm();
			system(E("start https://discord.gg/simply"));
			std::cout << slowly_printing_string{ "\n\n\n            Done Perm Spoofing\n\n\n",50 };
			goto mainn;
		}

		if (GetAsyncKeyState(VK_F2) & 2) {
			Check::checker();
			system(E("start https://discord.gg/simply"));
			goto mainn;

		}
		if (GetAsyncKeyState(VK_F3) & 3) {
			Check::checker();
			system(E("start https://discord.gg/simply"));
			goto mainn;
		}

	}
	return main();
}
