// THIS FILE IS AUTOMATICALLY GENERATED!
// ANY MODIFICATIONS WILL BE LOST!
// Generated on Wed Oct 23 23:56:51 UTC 2013

#ifndef _FLEKSYSDKVERSION_H
#define _FLEKSYSDKVERSION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Git full commit hash, including "-dirty" if there are uncommitted local changes.
extern const char *fleksySDKBuildGitCommit;

// Git short hash, including "-dirty" if there are uncommitted local changes.
extern const char *fleksySDKBuildGitShortHash;

// The user id that performed the build.
extern const char *fleksySDKBuildUser;

// The UTC date and time when the build was performed.  Example: 'Thu Apr 11 19:18:56 UTC 2013'.  This is the same date and time as fleksySDKBuildDateUnix.
extern const char *fleksySDKBuildDate;

// The UTC date and time when the build was performed as the number of seconds since the Unix epoch.  This is the same date and time as fleksySDKBuildDate.
extern const unsigned int fleksySDKBuildDateUnix;

#ifdef __cplusplus
}
#endif

#endif /* _FLEKSYSDKVERSION_H */
