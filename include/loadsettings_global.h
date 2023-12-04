#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOADSETTINGS_LIB)
#  define LOADSETTINGS_EXPORT Q_DECL_EXPORT
# else
#  define LOADSETTINGS_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOADSETTINGS_EXPORT
#endif
