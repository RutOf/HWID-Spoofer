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


void PushToStack(CONTEXT &Context, const ULONG64 value)
{
    Context.Rsp -= 0x8;
    PULONG64 AddressToWrite = (PULONG64)(Context.Rsp);
    *AddressToWrite = value;
}

//
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
