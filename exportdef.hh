#ifndef _INCLUDE__EXPORTDEF_H_
#define _INCLUDE__EXPORTDEF_H_

#if defined _MSC_VER
/* turn of some warnings on vc-compilers */

/* data conversion with possible loss of data */
# pragma warning( disable : 4244 )
/* identifier conversion with possible loss of data */
# pragma warning( disable : 4305 )
/* declspec without variable declaration */
# pragma warning( disable : 4091 )
/* M$DN classes exporting STL members... */
# pragma warning( disable : 4251 )
/* "switch" without "case" (just "default") */
# pragma warning( disable : 4065 )
/* Exception Specifications! */
# pragma warning (disable : 4290)
/* CRT deprecation warnings */
# define _CRT_SECURE_NO_WARNINGS 1

/* MSVC always uses dllimport/dllexport */
#define DLL_EXPORT

#endif /* _MSC_VER */


#ifdef DLL_EXPORT
// Windows requires explicit import and exporting of functions and classes.
// While this is a pain to do sometimes, in large software development
//      projects, it is very useful.
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)

# define DEPRECATED __declspec(deprecated)

#elif defined __GNUC__
# define EXPORT
# define IMPORT

# define DEPRECATED __attribute__ ((deprecated))

#else
/* unknown compiler */
# warning set up compiler specific defines
#endif




#ifdef INTERNAL
# define EXTERN EXPORT
#else
# define EXTERN IMPORT
#endif

#include <stdio.h>
#define MARK() printf("%s[%d]: %s\n", __FILE__, __LINE__, __func__)


#endif	// for header file
