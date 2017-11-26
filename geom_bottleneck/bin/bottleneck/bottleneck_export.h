
#ifndef bottleneck_EXPORT_H
#define bottleneck_EXPORT_H

#ifdef bottleneck_BUILT_AS_STATIC
#  define bottleneck_EXPORT
#  define BOTTLENECK_NO_EXPORT
#else
#  ifndef bottleneck_EXPORT
#    ifdef bottleneck_EXPORTS
        /* We are building this library */
#      define bottleneck_EXPORT 
#    else
        /* We are using this library */
#      define bottleneck_EXPORT 
#    endif
#  endif

#  ifndef BOTTLENECK_NO_EXPORT
#    define BOTTLENECK_NO_EXPORT 
#  endif
#endif

#ifndef BOTTLENECK_DEPRECATED
#  define BOTTLENECK_DEPRECATED __declspec(deprecated)
#endif

#ifndef BOTTLENECK_DEPRECATED_EXPORT
#  define BOTTLENECK_DEPRECATED_EXPORT bottleneck_EXPORT BOTTLENECK_DEPRECATED
#endif

#ifndef BOTTLENECK_DEPRECATED_NO_EXPORT
#  define BOTTLENECK_DEPRECATED_NO_EXPORT BOTTLENECK_NO_EXPORT BOTTLENECK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BOTTLENECK_NO_DEPRECATED
#    define BOTTLENECK_NO_DEPRECATED
#  endif
#endif

#endif
