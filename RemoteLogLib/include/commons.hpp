
#pragma once

//dll export symbols macro definition

#ifdef RLOG_BUILDING_DLL
#define RLOGAPI __declspec(dllexport)
#else
#define RLOGAPI __declspec(dllimport)
#endif
