/* #define C78 0/1 */
/* #define C89 0/1 */
/* #define C95 0/1 */
/* #define C99 0/1 */
/* #define C11 0/1 */
/* #define C17 0/1 */
/* #define C2X 0/1 */
#ifndef C_EDITION_DEFINED
  #define C_EDITION_DEFINED
  
  #ifndef __STDC__
    /* C78: K&R */
    #define C78 1
    #define C89 0
    #define C95 0
    #define C99 0
    #define C11 0
    #define C17 0
    #define C2X 0
  #else
    #if __STDC__ == 0
      /* C78: K&R (emulation) */
      #define C78 1
      #define C89 0
      #define C95 0
      #define C99 0
      #define C11 0
      #define C17 0
      #define C2X 0
    #else
      #ifndef __STD_VERSION__
        /* C89/C90: ANSI */
        #define C78 1
        #define C89 1
        #define C95 0
        #define C99 0
        #define C11 0
        #define C17 0
        #define C2X 0
      #else
        #if __STDC_VERSION__ <= 199409L
          /* C95: ANSI + ISO Amendment 1 */
          #define C78 1
          #define C89 1
          #define C95 1
          #define C99 0
          #define C11 0
          #define C17 0
          #define C2X 0
        #else
          #if __STDC_VERSION__ <= 199901L
            /* C99: POSIX */
            #define C78 1
            #define C89 1
            #define C95 1
            #define C99 1
            #define C11 0
            #define C17 0
            #define C2X 0
          #else
            #if __STDC_VERSION__ <= 201112L
              /* C11 */
              #define C78 1
              #define C89 1
              #define C95 1
              #define C99 1
              #define C11 1
              #define C17 0
              #define C2X 0
            #else
              #if __STDC_VERSION__ <= 201710L
                /* C17 */
                #define C78 1
                #define C89 1
                #define C95 1
                #define C99 1
                #define C11 1
                #define C17 1
                #define C2X 0
              #else
                /* C2X */
                #define C78 1
                #define C89 1
                #define C95 1
                #define C99 1
                #define C11 1
                #define C17 1
                #define C2X 1
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
#endif

/* #define WINDOWS 0/1 */
/* #define UNIX 0/1 */
/* #define POSIX 0/1 */
#ifndef OS_DEFINED
  #define OS_DEFINED
  
  #ifdef _MSC_VER
    #define WINDOWS 1
  #else
    #ifdef _WIN32
      #define WINDOWS 1
    #else
      #define WINDOWS 0
    #endif
  #endif
  
  #ifdef __unix__
    #define UNIX 1
    #include <unistd.h>
    #ifdef _POSIX_VERSION
      #define POSIX 1
    #else
      #define POSIX 0
    #endif
  #else
    #ifdef __APPLE__
      #ifdef __MACH__
        #define UNIX 1
        #include <unistd.h>
        #ifdef _POSIX_VERSION
          #define POSIX 1
        #else
          #define POSIX 0
        #endif
      #else
        #define UNIX 0
        #define POSIX 0
      #endif
    #else
      #define UNIX 0
      #define POSIX 0
    #endif
  #endif
#endif

/* #define BITS 32/64 */
#ifndef BITS_DEFINED
  #define BITS_DEFINED
  
  #if WINDOWS
    #ifdef _M_X64
      #define BITS 64
    #else
      #define BITS 32
    #endif
  #else
    #ifdef __clang__
      #ifdef __x86_64
        #define BITS 64
      #else
        #define BITS 32
      #endif
    #else
      #ifdef __GNUC__
        #ifdef __x86_64
          #define BITS 64
        #else
          #define BITS 32
        #endif
      #else
        #ifdef __x86_64
          #define BITS 64
        #else
          #define BITS 32
        #endif
      #endif
    #endif
  #endif
#endif
