/* vpr/vprDefines.h.in.  Generated from configure.ac by autoheader.  */

/* Define if the GLIBC backtrace() function is available. */
/* #undef HAVE_BACKTRACE */

/* Define to 1 if you have the <bstring.h> header file. */
/* #undef HAVE_BSTRING_H */

/* Define if TCP_CORK or TCP_NOPUSH is defined in netint/tcp.h */
/* #undef HAVE_CORKABLE_TCP */

/* Define to 1 if you have the <ext/hash_map> header file. */
/* #undef HAVE_EXT_HASH_MAP */

/* Define to 1 if you have the <ext/hash_set> header file. */
/* #undef HAVE_EXT_HASH_SET */

/* Define to 1 if you have the <ext/numeric> header file. */
/* #undef HAVE_EXT_NUMERIC */

/* Define to 1 if you have the `getifaddrs' function. */
/* #undef HAVE_GETIFADDRS */

/* Define to 1 if you have the <hash_map> header file. */
#define HAVE_HASH_MAP

/* Define to 1 if you have the <hash_map.h> header file. */
/* #undef HAVE_HASH_MAP_H */

/* Define to 1 if you have the <hash_set> header file. */
#define HAVE_HASH_SET

/* Define to 1 if you have the <hash_set.h> header file. */
/* #undef HAVE_HASH_SET_H */

/* Define to 1 if you have the `sigaction' function. */
/* #undef HAVE_SIGACTION */

/* Define to 1 if you have the `sigaddset' function. */
/* #undef HAVE_SIGADDSET */

/* Define to 1 if you have the `sigdelset' function. */
/* #undef HAVE_SIGDELSET */

/* Define to 1 if you have the `sigemptyset' function. */
/* #undef HAVE_SIGEMPTYSET */

/* Define to 1 if you have the `sigfillset' function. */
/* #undef HAVE_SIGFILLSET */

/* Define to 1 if you have the `sigismember' function. */
/* #undef HAVE_SIGISMEMBER */

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H

/* Define if struct sockaddr_in has sin_len */
/* #undef HAVE_SIN_LEN */

/* Define to 1 if you have the `snprintf' function. */
/* #undef HAVE_SNPRINTF */

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR

/* Define to 1 if you have the `strerror_r' function. */
/* #undef HAVE_STRERROR_R */

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <sys/capability.h> header file. */
/* #undef HAVE_SYS_CAPABILITY_H */

/* Define to 1 if you have the <sys/file.h> header file. */
/* #undef HAVE_SYS_FILE_H */

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H

/* Define to 1 if you have the <sys/uuid.h> header file. */
/* #undef HAVE_SYS_UUID_H */

/* Define if the timeval type is available. */
/* #undef HAVE_TIMEVAL */

/* Define if the timezone type is available. */
/* #undef HAVE_TIMEZONE */

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Define to 1 if you have the <uuid.h> header file. */
/* #undef HAVE_UUID_H */

/* Define to 1 if you have the <uuid/uuid.h> header file. */
/* #undef HAVE_UUID_UUID_H */

/* define to \"IRIX5\" or \"IRIX6\" depending on IRIX version */
/* #undef IRIXREL */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* The size of `char', as computed by sizeof. */


/* The size of `int', as computed by sizeof. */


/* The size of `long', as computed by sizeof. */


/* The size of `long long', as computed by sizeof. */


/* The size of `short', as computed by sizeof. */


/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
/* #undef TIME_WITH_SYS_TIME */

/* Define if unnamed POSIX semaphores are available. */
/* #undef VPR_HAVE_UNNAMED_POSIX_SEMAPHORE */

/* Define to the major version number of your HP-UX installation. */
/* #undef VPR_HPUX_VERSION */

/* Define if building on AIX. */
/* #undef VPR_OS_AIX */

/* Define if building on Digital UNIX. */
/* #undef VPR_OS_DUX */

/* Define if building on Darwin. */
/* #undef VPR_OS_Darwin */

/* Define if building on DragonFly. */
/* #undef VPR_OS_DragonFly */

/* Define if building on FreeBSD. */
/* #undef VPR_OS_FreeBSD */

/* Define if the target OS does not match anything else. */
/* #undef VPR_OS_GENERIC */

/* Define if building on HP-UX. */
/* #undef VPR_OS_HPUX */

/* Define if building on IRIX. */
/* #undef VPR_OS_IRIX */

/* Define if building on Linux. */
/* #undef VPR_OS_Linux */

/* Define to match the output of running 'uname -r'. */
#define VPR_OS_RELEASE 6.1

/* Define to match the numeric major version number of the target OS. */
#define VPR_OS_RELEASE_MAJOR 6

/* Define to match the numeric minor version number of the target OS. */
#define VPR_OS_RELEASE_MINOR 1

/* Define if building on Solaris/SunOS. */
/* #undef VPR_OS_Solaris */

/* Define if building on a Win32 platform. */
#define VPR_OS_Windows

/* Define if using POSIX semaphores. */
/* #undef VPR_POSIX_SEMAPHORES */

/* Define if VPR simulated sockets will be used. */
/* #undef VPR_SIMULATOR */

/* Define if Boost socket code will be used. */
#define VPR_USE_BOOST

/* Define to be the POSIX threads constant for thread scoping. */
/* #undef VPR_THREAD_SCOPE */

/* Define to 1 if you have the DCE 1.1 UUID functions (uuid_create(3), etc.).
   */
/* #undef VPR_USE_DCE_1_1_UUID */

/* Define to 1 if neither uuid_create(3) nor uuid_generate(3) are available.
   */
/* #undef VPR_USE_LEACH_UUID */

/* Define to 1 if you have the e2fsprogs libuuid funcs (uuid_generate(3),
   etc.). */
/* #undef VPR_USE_LIBUUID */

/* Define if using the Netscape Portable Runtime. */
/* #undef VPR_USE_NSPR */

/* Define if using POSIX threads. */
/* #undef VPR_USE_PTHREADS */

/* Define if using Windows threads. */
#define VPR_USE_WINTHREADS

/* Library directory */
#define VPR_LIBDIR "lib"

#ifdef VPR_OS_Windows
/* Define to unsigned int if the sigset_t type is not available. */
#  define sigset_t unsigned int
#endif

#ifdef WIN64
/* Define if building on the Win64 platform. */
#  define VPR_OS_Win64
#elif defined(WIN32)
#  define VPR_OS_Win32
#endif

#ifdef VPR_USE_PTHREADS
#  if defined(VPR_OS_IRIX) || defined(VPR_OS_Linux) || defined(VPR_OS_Solaris)
#    define VPR_POSIX_C_SOURCE 199506L
#  else
#    define VPR_POSIX_C_SOURCE 2
#  endif
#endif

#ifdef VPR_OS_Darwin
#  define _BSD_TYPES 1
#endif

