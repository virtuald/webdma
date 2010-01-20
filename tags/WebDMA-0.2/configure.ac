#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([WebDMA], [0.2])
AC_PREREQ([2.63])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([demo/Normal/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_REVISION($Revision$)

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AC_PROG_LIBTOOL

BOOST_REQUIRE([1.38])
BOOST_ASIO()
BOOST_SYSTEM()
BOOST_THREADS()

# add debug stuff here
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug],[enable verbose debugging output]))
AC_ARG_ENABLE(shadow, AS_HELP_STRING([--disable-shadow],[disable warnings for shadowed variables]),[], [enable_shadow=yes])
AC_ARG_ENABLE(checks, AS_HELP_STRING([--enable-checks], [enables strict glibc runtime checks (useful for STL debugging, but big performance hit)]))

AC_ARG_ENABLE(productionbuild, AS_HELP_STRING([--enable-productionbuild],[enable production build flags (no asserts, optimizations on)]))


if test x$enable_debug = xyes; then

	# override the global CFLAGS/CXXFLAGS, we're debugging and don't need any O flags
	CFLAGS="-DDEBUG -g -ggdb"
	CPPFLAGS="-DDEBUG -g -ggdb"
	CXXFLAGS="-DDEBUG -g -ggdb"
else
	
	if test x$enable_productionbuild = xyes; then
		CFLAGS="${CFLAGS-} -DNDEBUG -O2"
		CPPFLAGS="${CPPFLAGS-} -DNDEBUG -O2"
		CXXFLAGS="${CXXFLAGS-} -DNDEBUG -O2"
	fi
fi

# enable glibc runtime checks for STL
if test x$enable_checks = xyes; then
	CFLAGS="${CFLAGS-} -D_GLIBCXX_DEBUG -D_GLIBCXX_CONCEPT_CHECKS"
	CPPFLAGS="${CPPFLAGS-} -D_GLIBCXX_DEBUG -D_GLIBCXX_CONCEPT_CHECKS"
	CXXFLAGS="${CXXFLAGS-} -D_GLIBCXX_DEBUG -D_GLIBCXX_CONCEPT_CHECKS"
fi


CFLAGS="${CFLAGS-} -Wall -Wextra -Wno-unused-parameter -Werror"
CPPFLAGS="${CPPFLAGS-} ${BOOST_CPPFLAGS} -Wall -Wextra -Wno-unused-parameter -Werror"
CXXFLAGS="${CXXFLAGS-} ${BOOST_CPPFLAGS} -Wall -Wextra -Wno-unused-parameter -Werror"

if test x$enable_shadow = xyes; then
	CFLAGS="${CFLAGS-} -Wshadow"
	CPPFLAGS="${CPPFLAGS-} -Wshadow"
	CXXFLAGS="${CXXFLAGS-} -Wshadow"
fi

# setup library path
WebDMAincludedir="\$(includedir)/WebDMA"
AC_SUBST(WebDMAincludedir)


# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([socket])

AC_CONFIG_FILES([
	Makefile
	include/Makefile
	include/WebDMA/Makefile
	src/Makefile
	demo/Makefile
	demo/Normal/Makefile
])

AC_OUTPUT
