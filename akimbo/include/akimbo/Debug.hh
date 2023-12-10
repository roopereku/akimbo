#ifndef AKIMBO_DEBUG_HH
#define AKIMBO_DEBUG_HH

#if !defined(NDEBUG)
#define AKIMBO_DBG(...) __VA_ARGS__
#else
#define AKIMBO_DBG(...)
#endif

#endif
