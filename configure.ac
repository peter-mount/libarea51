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
LDFLAGS="$LDFLAGS -L../build"

# header files
CPPFLAGS="$CPPFLAGS -I../include"

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
],[AC_MSG_NOTICE(['No dependencies for this platform'])])
AC_SUBST([DEPENDENCIES],[$DEPENDENCIES])

AH_TEMPLATE(INSTALL_DEPENDENCIES, [Install required dependencies])
AC_ARG_WITH([dependencies],AS_HELP_STRING([--with-dependencies], [Install required dependencies during configuration]))
AS_IF([test "x$with_dependencies" != "xno" -a "x$DISTRIBUTION" != "x" -a -n "$APT_GET" ],[
    AC_MSG_NOTICE(['Installing dependencies'])
    AS_IF([test "x$APT_GET" != "x"],[$SUDO $APT_GET install -y $PKG_DEPENDENCIES])
    AS_IF([test "x$APK" != "x"],[$SUDO $APK add $PKG_DEPENDENCIES])
])

# ======================================================================
# libmicrohttpd needed for our webserver
# ======================================================================
AH_TEMPLATE(HAVE_MICROHTTPD, [microhttpd embedded webserver])
microhttpd=1
AC_CHECK_HEADER(microhttpd.h, [], [microhttpd=0])
AC_CHECK_LIB(microhttpd, MHD_start_daemon, [], [microhttpd=0])
if test $microhttpd == 1
then
    AC_DEFINE(HAVE_MICROHTTPD)
    LDFLAGS="$LDFLAGS -lmicrohttpd"
fi

# ======================================================================
# libsqlite optional for logging data
# ======================================================================
AH_TEMPLATE(HAVE_SQLITE, [sqlite embedded sql database])
AC_ARG_WITH([sqlite],
    AS_HELP_STRING([--without-sqlite], [disable sqlite support]))
AS_IF([test "x$with_sqlite" != "xno"],
    [
        sqlite=1
        AC_CHECK_HEADER(sqlite3.h, [], [sqlite=0])
        AC_CHECK_LIB(sqlite3, sqlite3_close, [], [sqlite=0])
    ],[
        sqlite=0
    ])
AS_IF([test $sqlite == 1],
    [
        AC_MSG_NOTICE([Enabling sqlite support])
        AC_DEFINE(HAVE_SQLITE)
        LDFLAGS="$LDFLAGS -lsqlite3"
    ],[
        AC_MSG_NOTICE([Disabled sqlite support])
    ])

# ======================================================================
# libcurl3 optional for logging data to 3rd party websites
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
# librabbitmq optional for logging data to a RabbitMQ server
#
# Note, the DIR in use here is rabbitmq-logger and not rabbitmq as thats
# the external libraries name
# ======================================================================
AH_TEMPLATE(HAVE_RABBITMQ, [RabbitMQ messaging server])
AC_ARG_WITH([rabbitmq],
    AS_HELP_STRING([--without-rabbitmq], [disable RabbitMQ support]))
AS_IF([test "x$with_rabbitmq" != "xno"],
    [
        rabbitmq=1
        AC_CHECK_HEADER(amqp.h, [], [rabbitmq=0])
        AC_CHECK_LIB(rabbitmq, amqp_new_connection, [], [rabbitmq=0])
    ],[
        rabbitmq=0
    ])
AS_IF([test $rabbitmq == 1],
    [
        AC_MSG_NOTICE([Enabling RabbitMQ support])
        AC_DEFINE(HAVE_RABBITMQ)
        LDFLAGS="$LDFLAGS -lrabbitmq"
    ],[
        AC_MSG_NOTICE([Disabled RabbitMQ support])
    ])
AC_SUBST([RABBITMQ],[${rabbitmq}])

# ======================================================================
# gd required for annotating images
# ======================================================================
AH_TEMPLATE(HAVE_LIB_GD, [GD for annotating images])
AC_CHECK_LIB([gd], [gdFreeFontCache], [gd=1], [gd=0])
if test $gd == 1
then
    AC_DEFINE(HAVE_LIB_GD)
    LDFLAGS="$LDFLAGS -lgd"
fi

# ======================================================================
# Work out what to compile
# ======================================================================

# Webserver support
#AS_IF([test $microhttpd == 1], [DIRS="$DIRS webserver"])

# Image Filter library
#DIRS="$DIRS imagefilter"

# RabbitMQ
#AS_IF([test $rabbitmq == 1],[DIRS="$DIRS rabbitmqapi"])

# logger's
#DIRS="$DIRS logger"

# sensors
#DIRS="$DIRS clouds sensors"

# ======================================================================
# Finish off generating all files

# add libraries based on the directory names, in reverse order to aid linking
for d in $DIRS
do
    LDFLAGS="-l$d $LDFLAGS"
done

#LDFLAGS="$LDFLAGS -lscheduler -lastro -lweather -lpthread -lm"

LDFLAGS="$LDFLAGS -lpthread -lm"

#DIRS="lib astro scheduler $DIRS"
DIRS="lib $DIRS"

AC_SUBST([DIRECTORIES],[$DIRS])
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
