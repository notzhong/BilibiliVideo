#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DOWNLOADMANAGE_LIB)
#  define DOWNLOADMANAGE_EXPORT Q_DECL_EXPORT
# else
#  define DOWNLOADMANAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define DOWNLOADMANAGE_EXPORT
#endif
