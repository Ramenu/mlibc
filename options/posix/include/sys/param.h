
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#include <endian.h>
#include <limits.h>

#if !defined NGROUPS && defined NGROUPS_MAX
# define NGROUPS NGROUPS_MAX
#endif

// Report the same value as Linux here.
#define MAXPATHLEN 4096

#ifdef __cplusplus
extern "C" {
#endif

#undef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#undef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#ifdef __cplusplus
}
#endif

#endif // _SYS_PARAM_H

