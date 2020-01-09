#include <intrin.h>
#include <stdio.h>
#include <Windows.h>

// Assert popup text class
class GAssertion
{
public:
    static void __cdecl PrintFailirePopupMessage(wchar_t const* message, wchar_t const* file, unsigned int line)
    {
        MessageBeep(MB_ICONSTOP);

        wchar_t _message[256] = {};
        swprintf_s(_message, L"Expression : %s\nFile : %s\nLine : %d\n", message, file, line);

        wchar_t _programName[MAX_PATH + 1] = {};
        GetModuleFileNameW(NULL, _programName, MAX_PATH);

        switch ( MessageBoxW(FindWindowW(_programName, nullptr), _message, L"Assertion failed!!", MB_ICONERROR | MB_ABORTRETRYIGNORE) )
        {
        case IDABORT:
        case IDIGNORE:
            exit(IDABORT);
        case IDRETRY:
        default:
            return;
        }
    }
};

// Assert macro define
#ifdef _DEBUG

#define __BREAK() (__nop( ), __debugbreak( ))
#define __MY_ASSERT_PRINT(expression) (GAssertion::PrintFailirePopupMessage(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)
#define MY_ASSERT(expression) (void)( (!!(expression)) || __MY_ASSERT_PRINT(expression) ); __BREAK( )

#else // NDEBUG

#define __BREAK() exit(IDABORT)
#define __MY_ASSERT_PRINT(expression) (void)(expression)
#define MY_ASSERT(expression) __assume(expression) // not recoverable error

#endif // _DEBUG end
