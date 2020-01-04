#pragma once

#include <QtGlobal>
#ifndef QT_STATIC
#if defined(QTSKIA_LIBRARY)
    #define QtSkia_API Q_DECL_EXPORT
#else 
    #define QtSkia_API Q_DECL_IMPORT
#endif
#else
#define QtSkia_API
#endif
