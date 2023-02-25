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

void clear()
{
	system(E("cls"));
}


public:
    static void Initialize(const std::wstring& title, const std::wstring& color) {
        if (!SetConsoleTitle(title.c_str())) {
            throw std::runtime_error("Failed to set console title.");
        }
        if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::stoi(color, nullptr, 16))) {
            throw std::runtime_error("Failed to set console color.");
        }
        if (!Clear()) {
            throw std::runtime_error("Failed to clear console.");
        }
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
    // Check if the stack pointer (Rsp) is aligned to an 8-byte boundary
    if (context.Rsp % 8 != 0) // using modulus operator to check for alignment
    {
        // If not, throw an exception
        throw std::runtime_error("Stack pointer is not 8-byte aligned.");
    }

    // Allocate space for a 64-bit value on the stack
    context.Rsp -= sizeof(ULONG64);

    // Define a pointer, AddressToWrite, to a 64-bit unsigned integer
    // that points to the newly allocated stack space
    PULONG64 addressToWrite = reinterpret_cast<PULONG64>(context.Rsp);

    // Write the input value to the memory location pointed to by AddressToWrite
    *addressToWrite = value;
}


// Initialises the spoofed thread state before it begins
// to execute by building a fake call stack via modifying
// rsp and appropriate stack data.
//
void InitialiseFakeThreadState(CONTEXT& context, const std::vector<StackFrame> &targetCallStack)
{
    ULONG64 childSp = 0;
    BOOL bPreviousFrameSetUWOP_SET_FPREG = false;

    // [1] As an extra sanity check explicitly clear
    // the last RET address to stop any further unwinding.
    PushToStack(context, 0);

    // [2] Loop through target call stack *backwards*
    // and modify the stack so it resembles the fake
    // call stack e.g. essentially making the top of
    // the fake stack look like the diagram below:
    //      |                |
    //       ----------------
    //      |  RET ADDRESS   |
    //       ----------------
    //      |                |
    //      |     Unwind     |
    //      |     Stack      |
    //      |      Size      |
    //      |                |
    //       ----------------
    //      |  RET ADDRESS   |
    //       ----------------
    //      |                |
    //      |     Unwind     |
    //      |     Stack      |
    //      |      Size      |
    //      |                |
    //       ----------------
    //      |   RET ADDRESS  |
    //       ----------------   <--- RSP when NtOpenProcess is called
    //
    for (auto stackFrame = targetCallStack.rbegin(); stackFrame != targetCallStack.rend(); ++stackFrame)
    {
        // [2.1] Check if the last frame set UWOP_SET_FPREG.
        // If the previous frame uses the UWOP_SET_FPREG
        // op, it will reset the stack pointer to rbp.
        // Therefore, we need to find the next function in
        // the chain which pushes rbp and make sure it writes
        // the correct value to the stack so it is propagated
        // to the frame after that needs it (otherwise stackwalk
        // will fail). The required value is the childSP
        // of the function that used UWOP_SET_FPREG (i.e. the
        // value of RSP after it is done adjusting the stack and
        // before it pushes its RET address).
        if (bPreviousFrameSetUWOP_SET_FPREG && stackFrame->pushRbp)
        {
            // [2.2] Check when RBP was pushed to the stack in function
            // prologue. UWOP_PUSH_NONVOls will always be last:
            // "Because of the constraints on epilogs, UWOP_PUSH_NONVOL
            // unwind codes must appear first in the prolog and
            // correspondingly, last in the unwind code array."
            // Hence, subtract the push rbp code index from the
            // total count to work out when it is pushed onto stack.
            // E.g. diff will be 1 below, so rsp -= 0x8 then write childSP:
            // RPCRT4!LrpcIoComplete:
            // 00007ffd`b342b480 4053            push    rbx
            // 00007ffd`b342b482 55              push    rbp
            // 00007ffd`b342b483 56              push    rsi
            // If diff == 0, rbp is pushed first etc.
            auto diff = stackFrame->countOfCodes - stackFrame->pushRbpIndex;
            auto tmpStackSizeCounter = 0;
            for (ULONG i = 0; i < diff; i++)
            {
                // e.g. push rbx
                PushToStack(context, 0x0);
                tmpStackSizeCounter += 0x8;
            }
            // push rbp
            PushToStack(context, childSp);

            // [2.3] Minus off the remaining function stack size
            // and continue unwinding.
            context.Rsp -= (stackFrame->totalStackSize - (tmpStackSizeCounter + 0x8));
            PULONG64 fakeRetAddress = (PULONG64)(context.Rsp);
            *fakeRetAddress = (ULONG64)stackFrame->returnAddress;

            // [2.4] From my testing it seems you only need to get rbp
            // right for the next available frame in the chain which pushes it.
            // Hence, there can be a frame in between which does not push rbp.
            // Ergo set this to false once you have resolved rbp for frame
            // which needed it. This is pretty flimsy though so this assumption
            // may break for other more complicated examples.
            bPreviousFrameSetUWOP_SET_FPREG = false;
        }
        else
        {
            // [3] If normal frame, decrement total stack size
            // and write RET address.
            context.Rsp -= stackFrame->totalStackSize;
            PULONG64 fakeRetAddress = (PULONG64)(context.Rsp);
            *fakeRetAddress = (ULONG64)stackFrame->returnAddress;
        }

        // [4] Check if the current function sets frame pointer
        // when unwinding e.g. mov rsp,rbp / UWOP_SET_FPREG
        // and record its childSP.
        if (stackFrame->setsFramePointer)
        {
            childSp = context.Rsp;
            childSp += 0x8;
            bPreviousFrameSetUWOP_SET_FPREG = true;
        }
    }
}
