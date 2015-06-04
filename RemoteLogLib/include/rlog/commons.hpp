
#pragma once

//dll export symbols macro definition

#ifdef RLOG_BUILDING_DLL
#define RLOGAPI __declspec(dllexport)
#else
#define RLOGAPI __declspec(dllimport)
#endif

//namespace definition

#define RLOG_NS rlog
#define RLOG_NAMESPACE namespace RLOG_NS {
#define RLOG_NAMESPACE_END }

//user-friendly singleton declaration

#define RLOG_SINGLETON(class_name) template <> class_name* RLOG_NS::singleton<class_name>::_instance = nullptr;
