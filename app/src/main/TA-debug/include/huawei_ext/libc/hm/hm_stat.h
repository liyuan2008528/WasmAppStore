#ifndef __STAT_H_
#define __STAT_H_

#ifndef HM_HOST_BUILD

#define __NEED_gid_t
#define __NEED_uid_t
#include <bits/alltypes.h>
typedef struct _cred_t {
	uid_t uid;
	gid_t gid;
} cred_t;
#define MKUID(val) ((uid_t)val)
#define MKGID(val) ((gid_t)val)
static inline int uid_eq(uid_t uid1, uid_t uid2)
{
	return (uid1 == uid2);
}

static inline int gid_eq(gid_t gid1, gid_t gid2)
{
	return (gid1 == gid2);
}

#ifndef S_IRWXU
#define S_IRWXU 00700
#endif
#ifndef S_IRUSR
#define S_IRUSR 00400
#endif
#ifndef S_IWUSR
#define S_IWUSR 00200
#endif
#ifndef S_IXUSR
#define S_IXUSR 00100
#endif
#ifndef S_IRWXG
#define S_IRWXG 00070
#endif
#ifndef S_IRGRP
#define S_IRGRP 00040
#endif
#ifndef S_IWGRP
#define S_IWGRP 00020
#endif
#ifndef S_IXGRP
#define S_IXGRP 00010
#endif
#ifndef S_IRWXO
#define S_IRWXO 00007
#endif
#ifndef S_IROTH
#define S_IROTH 00004
#endif
#ifndef S_IWOTH
#define S_IWOTH 00002
#endif
#ifndef S_IXOTH
#define S_IXOTH 00001
#endif
#ifndef S_ISUID
#define S_ISUID 04000
#endif
#ifndef S_ISGID
#define S_ISGID 02000
#endif
#ifndef S_ISVTX
#define S_ISVTX 01000
#endif





#define S_IRWXUGO	(S_IRWXU|S_IRWXG|S_IRWXO)
#define S_IALLUGO	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
#define S_IRUGO		(S_IRUSR|S_IRGRP|S_IROTH)
#define S_IWUGO		(S_IWUSR|S_IWGRP|S_IWOTH)
#define S_IXUGO		(S_IXUSR|S_IXGRP|S_IXOTH)

struct stat {
	uid_t uid;
	gid_t gid;
	mode_t mode;
};
#endif //ifndef HM_HOST_BUILD
#endif
