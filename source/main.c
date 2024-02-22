// base: hello-world example
#include <3ds.h>
#include <stdio.h>
#include <3ds/os.h>

int main(int argc, char **argv)
{
    osKernelConfig_s const *oskconf = OS_KernelConfig;
	
	gfxInitDefault();

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	//To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
	//the row and column where you want your cursor to move
	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
	printf("\x1b[1;1Hkernel version: 0x%lx"
            "\x1b[2;1Hkernel syscore version: 0x%lx"
            "\x1b[3;1Hkernel ctr sdk version: 0x%lx"
            "\x1b[4;1Hns tid: 0x%llx"
            "\x1b[5;1Hfw version: 0x%lx"
            "\x1b[6;1Hfw version major: 0x%lx"
            "\x1b[7;1Hfw version minor: 0x%lx"
            "\x1b[8;1Hfw version revision: 0x%lx"
            "\x1b[9;1Hfw syscore version: 0x%lx"
            "\x1b[10;1Hfw ctr sdk version: 0x%lx",

            osGetKernelVersion(),
            osGetSystemCoreVersion(),
            oskconf->kernel_ctrsdk_ver,
            oskconf->ns_tid,
            osGetFirmVersion(),
            GET_VERSION_MAJOR(oskconf->firm_ver),
            GET_VERSION_MINOR(oskconf->firm_ver),
            GET_VERSION_REVISION(oskconf->firm_ver),
            oskconf->firm_syscore_ver,
            oskconf->firm_ctrsdk_ver
        );

	printf("\x1b[30;16HPress Start to exit.");

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
