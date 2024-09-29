#include <abi-bits/mode_t.h>
#include <stddef.h>
#include <string.h>
#include <sys/syscall.h>

#define STDOUT 1
#define STDERR 2

namespace mlibc {
void sys_libc_log(const char *message) {
  int ret;
  SYSCALL_WRITE(ret, STDERR, message, strlen(message));
}
void sys_libc_panic() {
  int ret;
  const char *msg = "\nmlibc panic!\n";
  SYSCALL_WRITE(ret, STDERR, msg, strlen(msg));
  SYSCALL_EXIT(ret, 1);
}
int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, int offset,
               void **window) {
  void *ret;
  SYSCALL_MMAP(ret, hint, size, prot, flags, fd, offset);

  if (ret == nullptr)
    return ENOMEM;

  *window = ret;
  return 0;
}
int sys_vm_unmap(void *pointer, size_t size) {
  int ret;
  SYSCALL_MUNMAP(ret, pointer, size);
  return ret;
}
int sys_anon_allocate(size_t size, void **pointer) {
  return sys_vm_map(nullptr, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0, pointer);
}
int sys_anon_free(void *pointer, size_t size) {
  return sys_vm_unmap(pointer, size);
}
int sys_vm_protect(void *pointer, size_t size, int prot) {
  int ret;
  SYSCALL_MPROTECT(ret, pointer, size, prot);
  return ret;
}
int sys_tcb_set(void *) { return 0; }
int sys_futex_tid() { return 0; }
int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
  return 0;
}
int sys_futex_wake(int *pointer) { return 0; }
int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
  int ret = open(pathname, flags, mode);

  if (ret < 0)
    return -ret;

  *fd = ret;
  return 0;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
  ssize_t ret;
  SYSCALL_READ(ret, fd, buf, count);

  if (ret < 0)
    return -ret;

  *bytes_read = ret;
  return 0;
}

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
  off_t ret;
  SYSCALL_LSEEK(ret, fd, offset, whence);

  if (ret < 0)
    return -ret;

  *new_offset = ret;
  return 0;
}

int sys_close(int fd) {
  int ret;
  SYSCALL_CLOSE(ret, fd);

  if (ret < 0)
    return -ret;

  return 0;
}

int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf)
{
	int ret;
	switch (fsfdt) {
		case fsfd_target::fd: {
			SYSCALL_FSTAT(ret, fd, statbuf);
			break;
		},
		case fsfd_target::path: {
			SYSCALL_STAT(ret, path, statbuf);
			break;
		},
		default: {
			__ensure(!"stat: invalid fsfdt");
			__builtin_unreachable();
		}
	}

	return ret;
}

} // namespace mlibc
