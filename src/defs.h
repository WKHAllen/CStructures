#ifndef _DEFS_H_
#define _DEFS_H_

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

#endif // _DEFS_H_
