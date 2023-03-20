#include <iostream>
#include <Windows.h>
#include <string>
#include "color.hpp"
#include "driver.hpp"
#include "xorstr.h"
#include <thread>
#include "other.h"
#include "auth.hpp"

// A function that continuously checks for messages in the message queue and calls a function periodically
DWORD WINAPI fortnite_monitor(LPVOID lpParameter) {
    auto start_time = std::chrono::system_clock::now();
    const int check_interval_ms = 1000;

    while (true) {
        MSG msg;

        // Check for messages in the message queue
        while (PeekMessage(&msg, NULL, WM_APP, WM_APP, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return 0;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Check if it's time to call the function
        auto current_time = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);

        if (elapsed_time.count() > check_interval_ms) {
            start_time = current_time;

            try {
                fortnite_check();
            }
            catch (const std::exception& ex) {
                // Handle any exceptions that may occur
                std::cerr << "fortnite_check error: " << ex.what() << std::endl;
            }
        }
    }
}

// A struct that represents a string that is printed slowly, with a delay between each character
struct SlowlyPrintingString {
    std::string data;
    long int delay_ms;
};

// Example usage of the SlowlyPrintingString struct
void print_slowly(const SlowlyPrintingString& str) {
    for (char c : str.data) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(str.delay_ms));
    }
}

// Example usage of the fortnite_monitor function
int main() {
    HANDLE thread_handle = CreateThread(NULL, 0, fortnite_monitor, NULL, 0, NULL);

    // Wait for the user to press a key before exiting
    std::cout << "Press any key to exit" << std::endl;
    std::cin.get();

    // Signal the thread to exit and wait for it to exit
    PostThreadMessage(GetThreadId(thread_handle), WM_QUIT, 0, 0);
    WaitForSingleObject(thread_handle, INFINITE);
    CloseHandle(thread_handle);

    return 0;
}


std::ostream& operator<<(std::ostream& out, const slowly_printing_string& s) {
	for (const auto& c : s.data) {
		out << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
	}
	return out;
}

// Clear the console screen.
void clear() {
    system("cls");
}

// Initialize the console with the given title and color.
void Initialize(const std::wstring& title, const std::wstring& color) {
    // Set the console title.
    if (!SetConsoleTitle(title.c_str())) {
        throw std::runtime_error("Failed to set console title.");
    }

    // Convert the color string to integer.
    int colorInt = std::stoi(color, nullptr, 16);

    // Check if the color is valid.
    if (colorInt < 0 || colorInt > 0xFFFF) {
        throw std::invalid_argument("Invalid color.");
    }

    // Set the console text color.
    if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorInt)) {
        throw std::runtime_error("Failed to set console color.");
    }

    // Clear the console screen.
    clear();
}


int main()
{
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    system(E("color b"));
    SetConsoleTitle(E(L"Simply Coded A Perm Unban      discord.gg/simply"));
    system(E("cls"));

    std::cout << slowly_printing_string{ "\n\n\n Welcome To Simply's Coded Perm Spoofer",85 };
    std::cout << slowly_printing_string{ "\n\n Last Updated: 1/10/2023",75 };

    // Add error handling for thread creation
    auto thread1 = CreateThread(NULL, NULL, loopDbg, NULL, NULL, NULL);
    if (thread1 == NULL) {
        std::cerr << "Error creating first thread." << std::endl;
        return 1;
    }
    auto thread2 = CreateThread(NULL, NULL, loopDbg2, NULL, NULL, NULL);
    if (thread2 == NULL) {
        std::cerr << "Error creating second thread." << std::endl;
        return 1;
    }

    Sleep(500);
    std::cout << slowly_printing_string{ "...",50 };
    std::cout << slowly_printing_string{ "\n\n Succesfully Connected To (fake ip here)",140	 };
    std::cout << slowly_printing_string{ "\n\n Connected Users: (i put 3 question marks",140 };

    // Add error handling for thread creation
    auto thread3 = CreateThread(NULL, NULL, fortnitechkk, NULL, NULL, NULL);
    if (thread3 == NULL) {
        std::cerr << "Error creating third thread." << std::endl;
        return 1;
    }

    while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1) {
            Beep(500, 500);
            Spoof::Perm();
            system(E("start https://discord.gg/simply"));
            std::cout << slowly_printing_string{ "\n\n\n            Done Perm Spoofing\n\n\n",50 };
        }

        if (GetAsyncKeyState(VK_F2) & 2) {
            Check::checker();
            system(E("start https://discord.gg/simply"));
        }

        if (GetAsyncKeyState(VK_F3) & 3) {
            Check::checker();
            system(E("start https://discord.gg/simply"));
        }
    }

    return 0;
}


void PushToStack(CONTEXT& context, const ULONG64 value)
{
    if ((context.Rsp & 0x7) != 0)
        throw std::runtime_error("Stack pointer is not 8-byte aligned.");

    *(reinterpret_cast<PULONG64>(context.Rsp -= sizeof(ULONG64))) = value;
}

void InitialiseFakeThreadState(CONTEXT& context, const std::vector<StackFrame>& targetCallStack)
{
    ULONG64 childSp = 0;
    bool prevFrameSetUWOP_SET_FPREG = false;

    // Clear last RET address to stop further unwinding.
    PushToStack(context, 0);

    for (const auto& stackFrame : targetCallStack)
    {
        if (prevFrameSetUWOP_SET_FPREG && stackFrame.pushRbp)
        {
            // Find when RBP was pushed to the stack in function prologue.
            ULONG diff = stackFrame.countOfCodes - stackFrame.pushRbpIndex;
            ULONG64 tmpStackSizeCounter = 0;

            // Push any other non-volatile registers before RBP.
            for (ULONG i = 0; i < diff; ++i)
            {
                PushToStack(context, 0);
                tmpStackSizeCounter += 0x8;
            }

            // Push the correct RBP value.
            PushToStack(context, childSp);

            // Minus the remaining stack size and continue unwinding.
            context.Rsp -= (stackFrame.totalStackSize - (tmpStackSizeCounter + 0x8));
            *reinterpret_cast<PULONG64>(context.Rsp) = stackFrame.returnAddress;

            // Done resolving RBP for previous frame, set to false.
            prevFrameSetUWOP_SET_FPREG = false;
        }
        else
        {
            // Decrement stack size and write RET address.
            context.Rsp -= stackFrame.totalStackSize;
            *reinterpret_cast<PULONG64>(context.Rsp) = stackFrame.returnAddress;
        }

        // Check if current function sets frame pointer when unwinding.
        if (stackFrame.setsFramePointer)
        {
            childSp = context.Rsp + 0x8;
            prevFrameSetUWOP_SET_FPREG = true;
        }
    }
}
