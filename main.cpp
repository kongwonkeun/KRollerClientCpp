//
//
//

#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#define MY_MESSAGE_SIZE 1024
#define MY_PIPE_FOO TEXT("\\\\.\\pipe\\foo")

int
main(void)
{
    HANDLE hFoo;
    char buf[MY_MESSAGE_SIZE];
    DWORD rCnt;
    char c;

    printf("c: pipe client\n");
    hFoo = CreateFile(
        MY_PIPE_FOO,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hFoo != INVALID_HANDLE_VALUE)
    {
        printf("c-foo: open pipe\n");
        while (ReadFile(hFoo, buf, sizeof(buf) - 1, &rCnt, NULL) != FALSE)
        {
            buf[rCnt] = '\0';
            printf("%s\n", buf);

            if (_kbhit()) {
                c = _getch();
                if (c == 'q') {
                    break;
                }
            }
        }
    }
    printf("c-foo: broken pipe, bye bye\n");

    return(0);
}


//
// eof
//