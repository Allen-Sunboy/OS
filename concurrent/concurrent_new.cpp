#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

int count = 1;
bool IsADone = false;
bool IsBDone = false;

HANDLE s = CreateSemaphore(NULL, 1, 1, NULL);

static DWORD WINAPI TaskA(LPVOID lpParameter)
{
    // Sleep(50);
    WaitForSingleObject(s, INFINITE);

    int tmp1 = count;
    // Sleep(2000);
    tmp1++;
    count = tmp1;

    ReleaseSemaphore(s, 1, NULL);

    IsADone = true;

    return 0;
}

static DWORD WINAPI TaskB(LPVOID lpParameter)
{
    // Sleep(10);
    WaitForSingleObject(s, INFINITE);

    int tmp2 = count;
    // Sleep(1000);
    tmp2 = tmp2 + 2;
    count = tmp2;

    ReleaseSemaphore(s, 1, NULL);

    IsBDone = true;

    return 0;
}

int main()
{

    //保存线程的ID。
    DWORD dwThreadID = 0;

    //创建线程。
    CreateThread(
        NULL,               //安全属性使用缺省。
        0,                  //线程的堆栈大小。
        &TaskA,              //线程运行函数地址。
        NULL,               //传给线程函数的参数。
        0,                  //创建标志。
        &dwThreadID);       //成功创建后的线程标识码。

    //创建线程。
    CreateThread(
        NULL,               //安全属性使用缺省。
        0,                  //线程的堆栈大小。
        &TaskB,              //线程运行函数地址。
        NULL,               //传给线程函数的参数。
        0,                  //创建标志。
        &dwThreadID);       //成功创建后的线程标识码。

    while(!IsADone || !IsBDone);

    cout << count << endl;
    cout << "Press any key to continue..." << endl;

    char a;
    a = getch();
    cout << a;

    return 0;
}
