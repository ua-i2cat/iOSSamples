#ifndef IOS_UTILS_H
#define IOS_UTILS_H

#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>

#include <string>
#include <stdio.h>

#define PATH_MAX_UTILS 4096

namespace iOSUtils {
    std::string getiOSPath();
}

#endif
