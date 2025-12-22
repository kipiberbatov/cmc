#ifndef _cmc_dynamic_library_h
#define _cmc_dynamic_library_h
#ifdef _WIN32
#include <windows.h>
#define cmc_dynamic_library_open(name) LoadLibrary(name)
#define cmc_dynamic_library_get_symbol_address(handle, name) \
  GetProcAddress(handle, name)
#define cmc_dynamic_library_error() (GetLastError() ? "cannot load" : NULL)
#define cmc_dynamic_library_close(handle) FreeLibrary(handle)
#else /* Unix-like systems */
#include <dlfcn.h>
#define cmc_dynamic_library_open(name) dlopen(name, RTLD_LAZY)
#define cmc_dynamic_library_get_symbol_address(handle, name) dlsym(handle, name)
#define cmc_dynamic_library_error() dlerror()
#define cmc_dynamic_library_close(handle) dlclose(handle)
#endif /* _WIN32 */
#endif /* _cmc_dynamic_library_h */
