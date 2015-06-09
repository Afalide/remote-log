
#ifndef RLOG_COMMON_HPP
#define RLOG_COMMON_HPP

#define RLOG_NS rlog
#define RLOG_NS_BEGIN namespace RLOG_NS {
#define RLOG_NS_END }

#ifdef RLOG_BUILDING_LIB
#define RLOG_API __declspec(dllexport)
#else
#define RLOG_API __declspec(dllimport)
#endif

#endif //RLOG_COMMON_HPP