
AC_INIT(jaguar, 0.1.0-alpha, azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])
AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=jaguar
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT



dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin*)
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")


LT_INIT([win32-dll])


PKG_CHECK_MODULES(JAGUAR, [libcurl ])


AC_ARG_ENABLE([devel], AS_HELP_STRING([--enable-devel], [Soport de desarrollador activo]))
if test "x$enable_devel" = "xyes"; then 
	dnl AC_SUBST([ENABLE_DEVEL],[true])
	AC_DEFINE_UNQUOTED([ENABLE_DEVEL], [], [Soporte de desarrollador activo])
fi
dnl AM_CONDITIONAL(ENABLE_DEVEL, test x"$enable_devel" = "xyes")



AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
