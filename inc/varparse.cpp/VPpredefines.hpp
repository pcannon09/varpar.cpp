/**
 * VPpredefines.h - pcannonProjectStandards
 * Predefines for C and C++ projects
 * STD Information: 20250723 - 1.0S
 * NOTES:
 *	Renamed to `VPpredefines.hpp`
 */

#pragma once

// Project setup
#define VP_DEFAULT_CPP_STD			201703L

// Versioning
#define VP_VERSION_MAJOR            1
#define VP_VERSION_MINOR            0
#define VP_VERSION_PATCH            0

#define VP_VERSION_STD              20251027

// Version states:
// * dev
// * beta
// * build
#define VP_VERSION_STATE          "build"

#define VP_VERSION                ((VP_VERSION_MAJOR<<16)|(VP_VERSION_MINOR<<8)|(VP_VERSION_PATCH)|(VP_VERSION_STATE << 24))

#define VP_VERSION_CHECK(VP_VERSION_MAJOR, VP_VERSION_MINOR, VP_VERSION_PATCH, VP_VERSION_STATE) \
    (((VP_VERSION_MAJOR)<<16)|((VP_VERSION_MINOR)<<8)|(VP_VERSION_PATCH)|((VP_VERSION_STATE) << 24))

// Macro utils
#define VP_STRINGIFY(x) #x
#define VP_TOSTRING(x) VP_STRINGIFY(x)

#ifndef VP_DEV
#   define VP_DEV true
#endif

#ifdef WIN32
#	define VP_OS_WIN32
#elif defined(__APPLE__) || defined(__MACH__) || defined(Macintosh)
#	define VP_OS_MACOS
#elif defined(__linux__) || defined(__unix) || defined(__unix__)
#	define VP_OS_UNIX_LINUX
#elif defined(__FreeBSD__)
#	define VP_OS_FREEBSD
#else
#	error "Current platform is not supported"
#endif // defined(WIN32) // Platform check

