
#ifndef LIB1_SO_EXPORT_H
#define LIB1_SO_EXPORT_H

#ifdef LIB1_SO_STATIC_DEFINE
#  define LIB1_SO_EXPORT
#  define LIB1_SO_NO_EXPORT
#else
#  ifndef LIB1_SO_EXPORT
#    ifdef lib1_so_EXPORTS
        /* We are building this library */
#      define LIB1_SO_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIB1_SO_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIB1_SO_NO_EXPORT
#    define LIB1_SO_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIB1_SO_DEPRECATED
#  define LIB1_SO_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIB1_SO_DEPRECATED_EXPORT
#  define LIB1_SO_DEPRECATED_EXPORT LIB1_SO_EXPORT LIB1_SO_DEPRECATED
#endif

#ifndef LIB1_SO_DEPRECATED_NO_EXPORT
#  define LIB1_SO_DEPRECATED_NO_EXPORT LIB1_SO_NO_EXPORT LIB1_SO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIB1_SO_NO_DEPRECATED
#    define LIB1_SO_NO_DEPRECATED
#  endif
#endif

#endif /* LIB1_SO_EXPORT_H */
