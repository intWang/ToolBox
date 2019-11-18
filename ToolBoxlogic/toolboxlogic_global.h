#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TOOLBOXLOGIC_LIB)
#  define TOOLBOXLOGIC_EXPORT Q_DECL_EXPORT
# else
#  define TOOLBOXLOGIC_EXPORT Q_DECL_IMPORT
# endif
#else
# define TOOLBOXLOGIC_EXPORT
#endif
