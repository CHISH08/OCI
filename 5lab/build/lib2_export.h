
#ifndef LIB2_EXPORT_H
#define LIB2_EXPORT_H

#ifdef LIB2_STATIC_DEFINE
#  define LIB2_EXPORT
#  define LIB2_NO_EXPORT
#else
#  ifndef LIB2_EXPORT
#    ifdef lib2_EXPORTS
        /* We are building this library */
#      define LIB2_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIB2_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIB2_NO_EXPORT
#    define LIB2_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIB2_DEPRECATED
#  define LIB2_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIB2_DEPRECATED_EXPORT
#  define LIB2_DEPRECATED_EXPORT LIB2_EXPORT LIB2_DEPRECATED
#endif

#ifndef LIB2_DEPRECATED_NO_EXPORT
#  define LIB2_DEPRECATED_NO_EXPORT LIB2_NO_EXPORT LIB2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIB2_NO_DEPRECATED
#    define LIB2_NO_DEPRECATED
#  endif
#endif

#endif /* LIB2_EXPORT_H */
