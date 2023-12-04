#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(URLMANAGE_LIB)
#  define URLMANAGE_EXPORT Q_DECL_EXPORT
# else
#  define URLMANAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define URLMANAGE_EXPORT
#endif
