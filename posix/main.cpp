#if defined(__nuttx__)
#include <nuttx/config.h>
#endif

#include "include/stdafx.h"
#include <nanoCLR_Application.h>
#include <iostream>
#include <vector>
#include <dirent.h>

#define NF_CLR_FEATURE_ALL

/////////////////////////////////////////////////////////////////////////////

// All solutions are expected to provide an implementation of this
bool Target_GetReleaseInfo(NFReleaseInfo &releaseInfo)
{
    NFReleaseInfo::Init(
        releaseInfo,
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_BUILD,
        VERSION_REVISION,
        OEMSYSTEMINFOSTRING,
        hal_strlen_s(OEMSYSTEMINFOSTRING),
        TARGETNAMESTRING,
        hal_strlen_s(TARGETNAMESTRING),
        PLATFORMNAMESTRING,
        hal_strlen_s(PLATFORMNAMESTRING));

    return true; // alternatively, return false if you didn't initialize the releaseInfo structure.
}

#if defined(__nuttx__)
extern "C"
{
#endif

int main(int argc, char *argv[])
{
    int i = 0;
    DIR *d;
    struct dirent *dir;
    std::vector<std::string> args;
    std::string path;

    if (argc == 2) {
        // check for the directory for assemblies to use
        path = std::string(argv[1]);
    } else {
#if defined(__nuttx__)
        // simple ignore and use default sdcard
        path = std::string("/mnt/sd0/");
#else
        // simple ignore and use current dir
        path = std::string("./");
#endif
    }

#if defined(DEBUG)
    printf(".NET nanoFramework nanoCLR Nuttx v%s", VERSION_STRING);
    printf("\nCopyright (c) 2021 .NET Foundation and Contributors\n");
    printf("\nCLR_RT_HeapBlock:  %d\r\n\n", sizeof(CLR_RT_HeapBlock));
    printf("\nCLR_RT_HeapBlock:  %d\r\n\n", sizeof(CLR_RT_HeapBlock_Raw));
#endif

    // prepare -load
    d = opendir(path.c_str());
    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, ".pe") != NULL) {
            args.push_back(dir->d_name);
        }
    }
    closedir(d);

    if(!CPU_GPIO_Initialize())
    {
        printf("Error trying to initialize GPIO\n");
        exit(-69);
    }

    nanoHAL_Initialize();

    CLR_SETTINGS clrSettings;
    memset(&clrSettings, 0, sizeof(clrSettings));

    clrSettings.MaxContextSwitches = 50;
    clrSettings.WaitForDebugger = false;
    clrSettings.EnterDebuggerLoopAfterExit = false;

    // fill arguments from command line
    clrSettings.StartArgs.resize(args.size() * 2);

    for (; i < args.size(); i++) {
        std::string argstring = std::string("-load");
        std::string argstringAss = std::string(path.c_str() + args.at(i));
        clrSettings.StartArgs[i+i] = argstring;
        clrSettings.StartArgs[(i+i)+1] = argstringAss;

#if defined(DEBUG)
        printf("passing argument :: %s %s\n", argstring.c_str(), argstringAss.c_str());
#endif
    }

    args.clear();
    args.shrink_to_fit();

    ClrStartup(clrSettings);

#if defined(DEBUG)
    CLR_Debug::Printf("Exiting.\r\n");
#endif

    return 0;
}

#if defined(__nuttx__)
}
#endif
