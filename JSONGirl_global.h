#ifndef JSONGIRL_GLOBAL_H
#define JSONGIRL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JSONGIRL_LIBRARY)
#  define JSONGIRL_EXPORT Q_DECL_EXPORT
#else
#  define JSONGIRL_EXPORT Q_DECL_IMPORT
#endif

#endif // JSONGIRL_GLOBAL_H
