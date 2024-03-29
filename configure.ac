dnl Process this file with autoconf to produce a configure script.
AC_INIT(config/unix.mak)

OGDI_VERSION=4.1.1
OGDI_MAJOR=4
OGDI_MINOR=1

AC_SUBST(OGDI_VERSION)
AC_SUBST(OGDI_MAJOR)
AC_SUBST(OGDI_MINOR)

AC_CONFIG_MACRO_DIR(m4)

dnl ---------------------------------------------------------------------------
dnl	Check if we have a doomed configuration.
dnl ---------------------------------------------------------------------------

if test "$TOPDIR" = "" ; then
  AC_MSG_ERROR([Required TOPDIR environment variable not set, see README.])
fi

if test "$OS" = "Windows_NT" ; then
  AC_MSG_ERROR([Please don't use configure for Windows, see README.])
fi

dnl Checks for programs.
AC_PROG_CC
PKG_PROG_PKG_CONFIG

dnl We always want to check /usr/local for stuff.
dnl LIBS="$LIBS -L/usr/local/lib"
dnl CFLAGS="$CFLAGS -I/usr/local/include"

dnl Checks for libraries.
AC_CHECK_LIB(dl,dlopen,,,)
AC_CHECK_LIB(c,iconv_open,HAVE_ICONV=yes,,,)
AC_SUBST(HAVE_ICONV,$HAVE_ICONV)

dnl check for various compiler flags.
AC_COMPILER_WFLAGS
AC_COMPILER_PIC
AC_LD_SHARED

dnl ---------------------------------------------------------------------------
dnl	Do we have rpc/rpc.h
dnl ---------------------------------------------------------------------------
AC_CHECK_HEADERS([rpc/rpc.h],,
	[PKG_CHECK_MODULES([RPC], [libtirpc], [CPPFLAGS="$CPPFLAGS $RPC_CFLAGS"])])

dnl ---------------------------------------------------------------------------
dnl	Do we have rpc/pmap_clnt.h, float.h, dlfcn.h?
dnl ---------------------------------------------------------------------------
AC_CHECK_HEADERS(rpc/pmap_clnt.h float.h dlfcn.h)

if test "$ac_cv_header_rpc_pmap_clnt_h" = yes ; then
  RPC_INCLUDES=-DHAVE_STD_RPC_INCLUDES
else
  RPC_INCLUDES=
fi
AC_SUBST(RPC_INCLUDES,$RPC_INCLUDES)

if test "$ac_cv_header_float_h" = no ; then
  CFLAGS="$CFLAGS -DMISSING_FLOAT_H"
fi
if test "$ac_cv_header_dlfcn_h" = no ; then
  CFLAGS="$CFLAGS -DMISSING_DLFCN_H"
fi

dnl ---------------------------------------------------------------------------
dnl Check endian-ness.
dnl ---------------------------------------------------------------------------
AC_C_BIGENDIAN
if test $ac_cv_c_bigendian = yes ; then
  BIG_ENDIAN=1
else
  BIG_ENDIAN=0
fi
AC_SUBST(BIG_ENDIAN,$BIG_ENDIAN)

dnl ---------------------------------------------------------------------------
dnl Check for zlib override.
dnl ---------------------------------------------------------------------------

ZLIB_SETTING=internal
ZLIB_INCLUDE=
ZLIB_LIB=
export ZLIB_LIB ZLIB_INCLUDE ZLIB_SETTING

AC_ARG_WITH(zlib,[  --with-zlib[=ARG]       Utilize external ZLIB support],,)

if test "$with_zlib" = "yes" ; then

  AC_CHECK_LIB(z,deflateInit_,ZLIB_SETTING=external,ZLIB_SETTING=missing,)
  AC_CHECK_HEADERS(zlib.h)

  if test $ZLIB_SETTING = missing ; then
    AC_MSG_ERROR([Unable to find external ZLIB library, give path or use default internal library.])
  fi
  if test "$ac_cv_header_zlib_h" = no ; then
    AC_MSG_ERROR([Unable to find external ZLIB zlib.h file, give path or use default internal library.])
  fi

  ZLIB_SETTING=external
  ZLIB_LIB=-lz

elif test "$with_zlib" != "no" -a "$with_zlib" != "" ; then
  
  if test -r $with_zlib/include/zlib.h ; then
    AC_MSG_RESULT([checking for $with_zlib/include/zlib.h ... found])
    ZLIB_INCLUDE=-I$with_zlib/include
  elif test -r $with_zlib/zlib.h ; then
    AC_MSG_RESULT([checking for $with_zlib/zlib.h ... found])
    ZLIB_INCLUDE=-I$with_zlib
  else
    AC_MSG_ERROR([Unable to find $with_zlib/include/zlib.h])
  fi

  if test -r $with_zlib/lib/libz.so ; then
    ZLIB_LIB=$with_zlib/lib/libz.so
    AC_MSG_RESULT([checking for $ZLIB_LIB ... found])

  elif test -r $with_zlib/lib/libz.a ; then
    ZLIB_LIB=$with_zlib/lib/libz.a
    AC_MSG_RESULT([checking for $ZLIB_LIB ... found])

  elif test -r $with_zlib/libz.so ; then
    ZLIB_LIB=$with_zlib/libz.so
    AC_MSG_RESULT([checking for $ZLIB_LIB ... found])

  elif test -r $with_zlib/libz.a ; then
    ZLIB_LIB=$with_zlib/libz.a
    AC_MSG_RESULT([checking for $ZLIB_LIB ... found])

  else
    AC_MSG_ERROR([Unable to find $with_zlib/{lib/,}libz.{so,a}])
  fi

  ZLIB_SETTING=external
  
fi

AC_ARG_WITH(zliblib,[  --with-zliblib=path     Select ZLIB library],,)

if test "$with_zliblib" != "" ; then
  ZLIB_LIB=$with_zliblib
  ZLIB_SETTING=external
  AC_MSG_RESULT([Using ZLIB_LIB=$ZLIB_LIB for ZLIB library.])
fi

AC_ARG_WITH(zlibinc,[  --with-zlibinc=path     Select ZLIB include directory],,)

if test "$with_zlibinc" != "" ; then
  ZLIB_INCLUDE=-I${with_zlibinc}
  ZLIB_SETTING=external
  AC_MSG_RESULT([Using ZLIB_INCLUDE=$ZLIB_INCLUDE for ZLIB includes.])
fi

if test "$ZLIB_SETTING" = "internal" ; then
  AC_MSG_RESULT([Using internal ZLIB implementation.])
fi

AC_SUBST(ZLIB_SETTING,$ZLIB_SETTING)
AC_SUBST(ZLIB_INCLUDE,$ZLIB_INCLUDE)
AC_SUBST(ZLIB_LIB,$ZLIB_LIB)

dnl ---------------------------------------------------------------------------
dnl Check for expat override, or disabling.
dnl ---------------------------------------------------------------------------

EXPAT_SETTING=internal
EXPAT_INCLUDE=
EXPAT_LIB=
export EXPAT_LIB EXPAT_INCLUDE EXPAT_SETTING

AC_ARG_WITH(expat,[  --with-expat[=ARG]      Utilize external Expat library, or disable Expat.],,)

if test "$with_expat" = "yes" ; then

  AC_CHECK_LIB(expat,XML_ParserCreate,EXPAT_SETTING=external,EXPAT_SETTING=missing,)
  AC_CHECK_HEADERS(expat.h)

  if test $EXPAT_SETTING = missing ; then
    AC_MSG_ERROR([Unable to find external Expat library, give path or use default internal library.])
  fi
  if test "$ac_cv_header_expat_h" = no ; then
    AC_MSG_ERROR([Unable to find external expat.h file, give path or use default internal library.])
  fi

  EXPAT_SETTING=external
  EXPAT_LIB=-lexpat

elif test "$with_expat" = "no" ; then
  echo "Disabled use of Expat library, and XML capabilities parsing."
  EXPAT_SETTING=disabled

elif test "$with_expat" != "" ; then
  
  if test -r $with_expat/include/expat.h ; then
    echo "checking for $with_expat/include/expat.h ... found"
    EXPAT_INCLUDE=-I$with_expat/include
  elif test -r $with_expat/expat.h ; then
    echo "checking for $with_expat/expat.h ... found"
    EXPAT_INCLUDE=-I$with_expat
  else
    AC_MSG_ERROR([Unable to find $with_expat/include/expat.h])
  fi

  if test -r $with_expat/lib/libexpat.so ; then
    EXPAT_LIB=$with_expat/lib/libexpat.so
    echo "checking for $EXPAT_LIB ... found"

  elif test -r $with_expat/lib/libexpat.a ; then
    EXPAT_LIB=$with_expat/lib/libexpat.a
    echo "checking for $EXPAT_LIB ... found"

  elif test -r $with_expat/libexpat.so ; then
    EXPAT_LIB=$with_expat/libexpat.so
    echo "checking for $EXPAT_LIB ... found"

  elif test -r $with_expat/libexpat.a ; then
    EXPAT_LIB=$with_expat/libexpat.a
    echo "checking for $EXPAT_LIB ... found"

  else
    AC_MSG_ERROR([Unable to find $with_expat/{lib/,}libexpat.{so,a}])
  fi

  EXPAT_SETTING=external
fi

AC_ARG_WITH(expatlib,[  --with-expatlib=path    Select Expat library],,)

if test "$with_expatlib" != "" ; then
  EXPAT_LIB=$with_expatlib
  EXPAT_SETTING=external
  echo "Using EXPAT_LIB=$EXPAT_LIB for Expat library."
fi

AC_ARG_WITH(expatinc,[  --with-expatinc=path    Select Expat include directory],,)

if test "$with_expatinc" != "" ; then
  EXPAT_INCLUDE=-I${with_expatinc}
  EXPAT_SETTING=external
  echo "Using EXPAT_INCLUDE=$EXPAT_INCLUDE for Expat includes."
fi

if test "$EXPAT_SETTING" = "internal" ; then
  echo "Using internal Expat implementation." 
fi

AC_SUBST(EXPAT_SETTING,$EXPAT_SETTING)
AC_SUBST(EXPAT_INCLUDE,$EXPAT_INCLUDE)
AC_SUBST(EXPAT_LIB,$EXPAT_LIB)

# Allow the pkg-config directory to be set
AC_ARG_WITH(pkgconfigdir,
	AC_HELP_STRING([--with-pkgconfigdir],
	[Use the specified pkgconfig dir (default is libdir/pkgconfig)]),
	[pkgconfigdir=${withval}],
	[pkgconfigdir='${libdir}/pkgconfig'])
AC_SUBST([pkgconfigdir])
AC_MSG_NOTICE([pkgconfig directory is ${pkgconfigdir}])

# Make the *-config binary config scripts optional
AC_ARG_WITH(binconfigs,
	AC_HELP_STRING([--with-binconfigs],
		[Generate shell ogdi-config scripts as well as pkg-config data]
		[@<:@default=yes@:>@]),
	[if test "${withval}" = no; then
		binconfigs=
		AC_MSG_NOTICE([ogdi-config scripts will not be built])
	else
		binconfigs='${binconfigs}'
	fi],
	[binconfigs='${binconfigs}'])
AC_SUBST([binconfigs])

# Config files, substituting as above
AC_CONFIG_FILES([config/common.mak:config/common.mak.in])
AC_CONFIG_FILES([ogdi.pc:ogdi.pc.in])
AC_CONFIG_FILES([ogdi-config:ogdi-config.in],
		[chmod +x ogdi-config])

AC_OUTPUT(config/generic.mak)

target=`uname`
if test "$target" = "GNU/kFreeBSD" ; then
  target=Linux
fi
if test "$target" = "GNU" ; then
  target=Linux
fi
mv config/generic.mak config/$target.mak
