// YUVPlayer

#include <olectl.h>
#include <Windows.h>
#include <Commdlg.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <Gdiplus.h>
#include<math.h>
#include<string.h>
#include <atlstr.h>
#pragma comment(lib, "gdiplus.lib")
#define MAX_LOADSTRING 100

int                 YUV420(HWND);
errno_t             err=0;
int					Loop,Frame_Count,No_OF_FRAMES,sel,index1=-1,index2=-1,index3=-1;