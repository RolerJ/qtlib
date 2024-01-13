#ifndef ROLER_GLOBAL_H
#define ROLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ROLER_LIBRARY)
#  define ROLER_EXPORT Q_DECL_EXPORT
#else
#  define ROLER_EXPORT Q_DECL_IMPORT
#endif

#endif // ROLER_GLOBAL_H