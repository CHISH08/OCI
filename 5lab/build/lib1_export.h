
#ifndef LIB1_EXPORT_H
#define LIB1_EXPORT_H

#ifdef LIB1_STATIC_DEFINE
#  define LIB1_EXPORT
#  define LIB1_NO_EXPORT
#else
#  ifndef LIB1_EXPORT
#    ifdef lib1_EXPORTS
        /* We are building this library */
#      define LIB1_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIB1_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIB1_NO_EXPORT
#    define LIB1_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIB1_DEPRECATED
#  define LIB1_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIB1_DEPRECATED_EXPORT
#  define LIB1_DEPRECATED_EXPORT LIB1_EXPORT LIB1_DEPRECATED
#endif

#ifndef LIB1_DEPRECATED_NO_EXPORT
#  define LIB1_DEPRECATED_NO_EXPORT LIB1_NO_EXPORT LIB1_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIB1_NO_DEPRECATED
#    define LIB1_NO_DEPRECATED
#  endif
#endif

#endif /* LIB1_EXPORT_H */
