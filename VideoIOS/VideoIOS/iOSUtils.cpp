#include "iOSUtils.h"

std::string iOSUtils::getiOSPath(){
    char path[PATH_MAX_UTILS];
    
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    
    CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle);
    
    CFStringGetCString(str, path, PATH_MAX, kCFStringEncodingASCII);
    
    CFRelease(resourcesURL);
    CFRelease(str);
    
    std::string resultPath = std::string(path);

    return resultPath;
}