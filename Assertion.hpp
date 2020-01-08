/******* Define assertion macros *******/
#pragma once

#include <intrin.h>
#include <corecrt_terminate.h>
#include <stdio.h>

//#define POPUP_ASSERT_WINDOW // NOTE : If you use "popup assertion", enable it.

#if defined(_DEBUG) && defined(POPUP_ASSERT_WINDOW)
#include <Windows.h>
#endif

// Assert text printer class
class GAssertion
{
public:
	static void __cdecl PrintFailireMessage(wchar_t const* message, wchar_t const* file, unsigned line)
	{
		wprintf_s(L"Assertion failed!! %s\nFile : %s, Line : %d\n", message, file, line);
	}

	static void __cdecl PrintUserMessage(wchar_t const* message)
	{
		wprintf_s(L"[LOG] %s\n", message);
	}

#if defined(_DEBUG) && defined(POPUP_ASSERT_WINDOW)
	void __cdecl PrintFailirePopupMessage(wchar_t const* message, wchar_t const* file, unsigned line)
	{
		MessageBeep(MB_ICONSTOP);

		wchar_t __message[256] = {};
		swprintf_s(__message, L"Expression : %s\nFile : %s, Line : %d\n", message, file, line);

		wchar_t programName[MAX_PATH + 1] = {};
		GetModuleFileNameW(NULL, programName, MAX_PATH);

		MessageBoxW(FindWindowW(programName, nullptr), __message, L"Assertion failed!!", MB_ICONERROR | MB_OK);
	}
#endif
};

#undef _BREAK
#undef ASSERT
#undef ASSERT_M
#undef check
#undef checkm


// Assert macro define
#ifdef NDEBUG


#define _BREAK() abort()
#define __ASSERT_PRINT(expression)

#define ASSERT(expression) __assume(expression)
#define ASSERT_M(expression, Message) ASSERT(expression)

#define check(expression) ASSERT(expression)
#define checkm(expression, Message) ASSERT_M(expression, Message)


#else // _DEBUG


#define _BREAK() (__nop(), __debugbreak())
#define __ASSERT_PRINT(expression) (GAssertion::PrintFailireMessage(_WIDE_STR(#expression), _WIDE_STR(__FILE__), (unsigned)(__LINE__)), 0)

#define ASSERT(expression) (void)( (!!(expression)) || __ASSERT_PRINT(expression) ); _BREAK( )
#define ASSERT_M(expression, Message) (void)(GAssertion::PrintUserMessage(_WIDE_STR(Message))); ASSERT(expression)

#define check(expression) ASSERT(expression)
#define checkm(expression, Message) ASSERT_M(expression, Message)

#endif // NDEBUG

// Popup assertion macro
#ifdef POPUP_ASSERT_WINDOW

#define __ASSERT_POPUP_PRINT(expression) (GAssertion::PrintFailirePopupMessage(_WIDE_STR(#expression), _WIDE_STR(__FILE__), (unsigned)(__LINE__)), 0)
#define ASSERT_POPUP(expression) (void)( (!!(expression)) || __ASSERT_POPUP_PRINT(expression) ); _BREAK( )

#else // !POPUP_ASSERT_WINDOW

#define __ASSERT_POPUP_PRINT(expression) __ASSERT_PRINT(expression)
#define ASSERT_POPUP(expression) ASSERT(expression)

#endif // POPUP_ASSERT_WINDOW


// Break point & print error log
#define DEBUG_PRINT_ERROR(text, ...) printf_s("[ERR] File : %s, Line : %d\n[LOG] " text, __FILE__, __LINE__, __VA_ARGS__); _BREAK( ) 
