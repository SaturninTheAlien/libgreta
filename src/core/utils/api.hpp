#pragma once

//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#pragma once

#ifdef _WIN32
#ifdef GRETA_EXPORTS_DLL
#define GRETA_API __declspec(dllexport)
#else
#define GRETA_API __declspec(dllimport)
#endif

#else
#define GRETA_API
#endif