# autoconf script for building the pi weather station
#
AC_INIT([area51], [0.1], [peter@retep.org])
AC_MSG_NOTICE([libarea51])

# Check for gcc
AC_PROG_CC
AC_LANG(C)

# Math library
#AC_CHECK_LIB(m, cos)

# ======================================================================
DIRS=""

# Project base for include paths
LDFLAGS="$LDFLAGS -L../build/package/usr/lib"

# header files
CPPFLAGS="$CPPFLAGS -I../include"

# This is a shared library so compile position independent code
CCFLAGS="$CCFLAGS -fPIC"

# ======================================================================
# Package generation

# Debian if DPKG_DEB is not ""
AC_PATH_PROG([DPKG_DEB], [dpkg-deb])
AC_PATH_PROG([DPKG_ARCH], [dpkg-architecture])
AS_IF([test -n "$DPKG_ARCH" ],[ARCHITECTURE=$($DPKG_ARCH | grep DEB_BUILD_ARCH= | cut -f2 -d '=')],[])

# ARCHITECTURE for package, "" if not known
AS_IF([test -n "$ARCHITECTURE"],[
    AC_SUBST([ARCHITECTURE],[$ARCHITECTURE])
    AC_MSG_NOTICE(['Build architecture $ARCHITECTURE'])
],[
    AC_MSG_NOTICE(['Build architecture unknown'])
]);

# ======================================================================
# Distribution detection and dependencies
AC_PATH_PROG([SUDO],[sudo])
AC_PATH_PROG([APT_GET],[apt-get])
AC_PATH_PROG([APK],[apk])

AC_CHECK_FILE([/etc/os-release],[
    DISTRIBUTION=$(. /etc/os-release;echo $ID)
    AC_MSG_NOTICE(['Build distribution $DISTRIBUTION ($(. /etc/os-release;echo $VERSION_ID))'])
])

AC_CHECK_FILE([dependencies/$DISTRIBUTION],[
    PKG_DEPENDENCIES=$(<dependencies/$DISTRIBUTION)
    DEPENDENCIES=$(echo $PKG_DEPENDENCIES|sed "s/ /, /g")
],[
    PKG_DEPENDENCIES=
    DEPENDENCIES=
])
AC_SUBST([DEPENDENCIES],[$DEPENDENCIES])

# ======================================================================
# libcurl
# ======================================================================
AH_TEMPLATE(HAVE_CURL, [Curl HTTP client])
AC_ARG_WITH([curl],
    AS_HELP_STRING([--without-curl], [disable Curl HTTP support]))
AS_IF([test "x$with_curl" != "xno"],
    [
        curl=1
        AC_CHECK_HEADER(curl/curl.h, [], [curl=0])
        AC_CHECK_LIB(curl, curl_easy_cleanup, [], [curl=0])
    ],[
        curl=0
    ])
AS_IF([test $curl == 1],
    [
        AC_MSG_NOTICE([Enabling Curl HTTP support])
        AC_DEFINE(HAVE_CURL)
        LDFLAGS="$LDFLAGS -lcurl"
    ],[
        AC_MSG_NOTICE([Disabled Curl HTTP support])
    ])
AC_SUBST([CURL],[${curl}])

# ======================================================================
# Work out what to compile
# ======================================================================

# add libraries based on the directory names, in reverse order to aid linking
for d in $DIRS
do
    LDFLAGS="-l$d $LDFLAGS"
done

LDFLAGS="$LDFLAGS -lpthread -lm"

DIRS="lib $DIRS"

AC_SUBST([DIRECTORIES],[$DIRS])
AC_SUBST([CCFLAGS],[$CCFLAGS])
AC_SUBST([CPPFLAGS],[$CPPFLAGS])
AC_SUBST([LDFLAGS],[$LDFLAGS])

# Build make files
MAKEFILES="SubMakefile $(find . -type f -name Makefile.in|sed s/\\.in//g)"
# custom .h files
MAKEFILES="$MAKEFILES $(find . -type f -name '*.h.in'|sed s/\\.in//g)"
# Package files
MAKEFILES="$MAKEFILES $(find package -type f -name '*.in'|sed s/\\.in//g)"
AC_CONFIG_FILES([$MAKEFILES])

AC_OUTPUT()

AC_MSG_NOTICE([Now run make clean;make])
