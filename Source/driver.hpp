#include <iostream>
#include <thread>
#include <Windows.h>
#include <string>
#include "xorstr.h"

namespace Check {

	void checker()
	{
		Beep(500, 500);
		Sleep(200);
		system(E("cls"));
		system("color b");
		system(E("echo BaseBoard SN:"));
		Sleep(200);
		system(E("wmic baseboard get serialnumber"));
		Sleep(200);
		system(E("echo Bios SN:"));
		Sleep(200);
		system(E("wmic bios get serialnumber"));
		Sleep(200);
		system(E("echo Cpu SN:"));
		Sleep(200);
		system(E("wmic cpu get serialnumber"));
		Sleep(200);
		system(E("echo DiskDrive SN:"));
		Sleep(200);
		system(E("wmic diskdrive get serialnumber"));
		Sleep(200);
		std::cout << E("  ") << '\n';
		Sleep(200);
		system(E("echo -----------------------------------------------"));
		Sleep(200);
		system(E("echo Going back to Dashboard in 10 Seconds..."));
		Sleep(200);
		system(E("echo -----------------------------------------------"));
		Sleep(10000);
	}
}

typedef struct _INQUIRYDATA
{
	union
	{
		struct
		{
			CHAR DeviceType : 5;
			CHAR DeviceTypeQualifier : 3;
			CHAR DeviceTypeModifier : 7;
			CHAR RemovableMedia : 1;
			CHAR ANSIVersion : 3;
			CHAR ECMAVersion : 3;
			CHAR ISOVersion : 2;
			CHAR ResponseDataFormat : 4;
			CHAR HiSupport : 1;
			CHAR NormACA : 1;
			CHAR TerminateTask : 1;
			CHAR AERC : 1;
		} s0;

		struct
		{
			BYTE gap0[2];
			CHAR Versions;
		} s1;
	} u0;

	CHAR AdditionalLength;

	union
	{
		CHAR Reserved;
		struct
		{
			CHAR Protect : 1;
			CHAR Reserved_1 : 2;
			CHAR ThirdPartyCoppy : 1;
			CHAR TPGS : 2;
			CHAR ACC : 1;
			CHAR SCCS : 1;
			CHAR Addr16 : 1;
			CHAR Addr32 : 1;
			CHAR AckReqQ : 1;
			CHAR MediumChanger : 1;
			CHAR MultiPort : 1;
			CHAR ReservedBit2 : 1;
			CHAR EnclosureServices : 1;
			CHAR ReservedBit3 : 1;
			CHAR SoftReset : 1;
			CHAR CommandQueue : 1;
			CHAR TransferDisable : 1;
			CHAR LinkedCommands : 1;
			CHAR Synchronous : 1;
			CHAR Wide16Bit : 1;
			CHAR Wide32Bit : 1;
			CHAR RelativeAddressing : 1;
		} s0;
	} u1;

	CHAR VendorId[8];
	CHAR ProductId[16];
	CHAR ProductRevisionLevel[4];
	CHAR VendorSpecific[20];
	CHAR Reserved3[2];
	USHORT VersionDescriptors[8];
	CHAR Reserved4[30];
} INQUIRYDATA, * PINQUIRYDATA;

// 1903
typedef struct _VendorInfo1903
{
	char pad_0x0000[0x8];
	char Info[64];
} VendorInfo1903;

typedef struct _HDD_EXTENSION1903
{
	char pad_0x0000[0x68];
	VendorInfo1903* pVendorInfo;
	char pad_0x0068[0x8];
	char* pHDDSerial;
} *PHDD_EXTENSION1903;

typedef struct _VendorInfo1809
{
	char pad_0x0000[0x8];
	char Info[64];
} VendorInfo1809;

typedef struct _HDD_EXTENSION1809
{
	char pad_0x0000[0x60];
	VendorInfo1809* pVendorInfo;
	char pad_0x0068[0x8];
	INQUIRYDATA* InquiryData;
	char* pHDDSerial;
	char pad_0x0078[0x30];
} *PHDD_EXTENSION1809;

// 1803
typedef struct _VendorInfo1803
{
	char pad_0x0000[0x8];
	char Info[64];
} VendorInfo1803;

typedef struct _HDD_EXTENSION1803
{
	char pad_0x0000[0x60];
	VendorInfo1803* pVendorInfo;
	char pad_0x0068[0x8];
	char* pHDDSerial;
	char pad_0x0078[0x30];
} *PHDD_EXTENSION1803;

typedef struct _VendorInfo
{
	char pad_0x0000[0x8];
	char Info[64];
} VendorInfo;

typedef struct _HDD_EXTENSION
{
	char pad_0x0000[0x60];
	VendorInfo* pVendorInfo;
	char pad_0x0068[0x8];
	char* pHDDSerial;
	char pad_0x0078[0x30];
} HDD_EXTENSION, * PHDD_EXTENSION;

typedef __int64(__fastcall* RaidUnitRegisterInterfaces1903)(PHDD_EXTENSION1903 a1);
typedef __int64(__fastcall* RaidUnitRegisterInterfaces1809)(PHDD_EXTENSION1809 a1);
typedef __int64(__fastcall* RaidUnitRegisterInterfaces1803)(PHDD_EXTENSION1803 a1);
typedef __int64(__fastcall* RaidUnitRegisterInterfaces)(PHDD_EXTENSION a1);

extern "C" NTSYSAPI ULONG RtlRandomEx(
	PULONG Seed
);
