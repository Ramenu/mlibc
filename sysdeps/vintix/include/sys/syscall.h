/**
 * Copyright (C) 2023-2024 Abdur-Rahman Mansoor
 *
 * This file is part of Vintix.
 *
 * Vintix is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version
 * 3 of the License, or (at your option) any later version that is approved by Abdur-Rahman Mansoor.
 *
 * Vintix is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Vintix. If
 * not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VINTIX_USER_SYSCALL_H
#define VINTIX_USER_SYSCALL_H

#define __VINTIX_QUOTE(x) #x

#define __VINTIX_SYSCALL_NO_ARG(N, RET)                                                            \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "int 0x80\n\t"                             \
                     : "=a"(RET)                                                                   \
                     :                                                                             \
                     : "eax")

#define __VINTIX_SYSCALL_SINGLE_ARG(N, RET, X)                                                     \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "mov 	ebx, %0\n\t"                         \
                                                        "int 	0x80\n\t"                            \
                     : "=a"(RET)                                                                   \
                     : "r"(X)                                                                      \
                     : "eax", "ebx")

#define __VINTIX_SYSCALL_TWO_ARG(N, RET, X, Y)                                                     \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "mov 	ebx, %0\n\t"                         \
                                                        "mov 	ecx, %1\n\t"                         \
                                                        "int 	0x80\n\t"                            \
                     : "=a"(RET)                                                                   \
                     : "r"(X), "r"(Y)                                                              \
                     : "eax", "ebx", "ecx")

#define __VINTIX_SYSCALL_THREE_ARG(N, RET, X, Y, Z)                                                \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "mov 	ebx, %0\n\t"                         \
                                                        "mov 	ecx, %1\n\t"                         \
                                                        "mov 	edx, %2\n\t"                         \
                                                        "int 	0x80\n\t"                            \
                     : "=a"(RET)                                                                   \
                     : "r"(X), "r"(Y), "r"(Z)                                                      \
                     : "eax", "ebx", "ecx", "edx")

#define __VINTIX_SYSCALL_FOUR_ARG(N, RET, A, B, C, D)                                              \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "mov 	ebx, %0\n\t"                         \
                                                        "mov 	ecx, %1\n\t"                         \
                                                        "mov 	edx, %2\n\t"                         \
                                                        "mov 	esi, %3\n\t"                         \
                                                        "int 	0x80\n\t"                            \
                     : "=a"(RET)                                                                   \
                     : "r"(A), "r"(B), "r"(C), "r"(D)                                              \
                     : "eax", "ebx", "ecx", "edx", "esi")

#define __VINTIX_SYSCALL_SIX_ARG(N, RET, A, B, C, D, E, F)                                         \
    __asm__ volatile("mov 	eax," __VINTIX_QUOTE(N) "\n\t"                                     \
                                                        "mov 	ebx, %0\n\t"                         \
                                                        "mov 	ecx, %1\n\t"                         \
                                                        "mov 	edx, %2\n\t"                         \
                                                        "mov 	esi, %3\n\t"                         \
                                                        "mov 	edi, %4\n\t"                         \
                                                        "mov 	ebp, %5\n\t"                         \
                                                        "int 	0x80\n\t"                            \
                     : "=a"(RET)                                                                   \
                     : "r"(A), "r"(B), "r"(C), "r"(D), "r"(E), "r"(F)                              \
                     : "eax", "ebx", "ecx", "edx", "esi", "edi", "ebp")

#define SYSCALL_OPEN(RET, PATHNAME, OFLAGS, MODE)                                                  \
    __VINTIX_SYSCALL_THREE_ARG(1, RET, PATHNAME, OFLAGS, MODE)
#define SYSCALL_CREAT(RET, PATHNAME, MODE) __VINTIX_SYSCALL_TWO_ARG(2, RET, PATHNAME, MODE)
#define SYSCALL_MKDIR(RET, PATHNAME, MODE) __VINTIX_SYSCALL_TWO_ARG(3, RET, PATHNAME, MODE)
#define SYSCALL_READ(RET, FD, BUF, COUNT) __VINTIX_SYSCALL_THREE_ARG(4, RET, FD, BUF, COUNT)
#define SYSCALL_EXIT(RET, STATUS) __VINTIX_SYSCALL_SINGLE_ARG(5, RET, STATUS)
#define SYSCALL_WRITE(RET, FD, BUF, COUNT) __VINTIX_SYSCALL_THREE_ARG(6, RET, FD, BUF, COUNT)
#define SYSCALL_MOUNT(RET, SOURCE, TARGET, FS_TYPE, MOUNT_FLAGS)                                   \
    __VINTIX_SYSCALL_FOUR_ARG(7, RET, SOURCE, TARGET, FS_TYPE, MOUNT_FLAGS)
#define SYSCALL_UMOUNT(RET, TARGET) __VINTIX_SYSCALL_SINGLE_ARG(8, RET, TARGET)
#define SYSCALL_CLOSE(RET, FD) __VINTIX_SYSCALL_SINGLE_ARG(9, RET, FD)
#define SYSCALL_MMAP(RET, ADDR, LEN, PROT, FLAGS, FD, OFF)                                         \
    __VINTIX_SYSCALL_SIX_ARG(10, RET, ADDR, LEN, PROT, FLAGS, FD, OFF)
#define SYSCALL_GETUID(RET) __VINTIX_SYSCALL_NO_ARG(11, RET)
#define SYSCALL_GETGID(RET) __VINTIX_SYSCALL_NO_ARG(12, RET)
#define SYSCALL_GETPID(RET) __VINTIX_SYSCALL_NO_ARG(13, RET)
#define SYSCALL_LSEEK(RET, FD, OFF, WHENCE) __VINTIX_SYSCALL_THREE_ARG(14, RET, FD, OFF, WHENCE)
#define SYSCALL_CHDIR(RET, PATH) __VINTIX_SYSCALL_SINGLE_ARG(15, RET, PATH)
#define SYSCALL_CHROOT(RET, PATH) __VINTIX_SYSCALL_SINGLE_ARG(16, RET, PATH)
#define SYSCALL_SCHED_YIELD(RET) __VINTIX_SYSCALL_NO_ARG(17, RET)
#define SYSCALL_UMASK(RET, MASK) __VINTIX_SYSCALL_SINGLE_ARG(18, RET, MASK)
#define SYSCALL_MUNMAP(RET, ADDR, LEN) __VINTIX_SYSCALL_TWO_ARG(19, RET, ADDR, LEN)
#define SYSCALL_KILL(RET, PID, SIG) __VINTIX_SYSCALL_TWO_ARG(20, RET, PID, SIG)
#define SYSCALL_WAIT(RET, STATUS) __VINTIX_SYSCALL_SINGLE_ARG(21, RET, STATUS)
#define SYSCALL_WAITPID(RET, PID, STATUS, OPTIONS)                                                 \
    __VINTIX_SYSCALL_THREE_ARG(22, RET, PID, STATUS, OPTIONS)
#define SYSCALL_STAT(RET, PATH, BUF) __VINTIX_SYSCALL_TWO_ARG(23, RET, PATH, BUF)
#define SYSCALL_LSTAT(RET, PATH, BUF) __VINTIX_SYSCALL_TWO_ARG(24, RET, PATH, BUF)
#define SYSCALL_FSTAT(RET, FD, BUF) __VINTIX_SYSCALL_TWO_ARG(25, RET, FD, BUF)
#define SYSCALL_CHMOD(RET, PATH, MODE) __VINTIX_SYSCALL_TWO_ARG(26, RET, PATH, MODE)
#define SYSCALL_FCHMOD(RET, FD, MODE) __VINTIX_SYSCALL_TWO_ARG(27, RET, FD, MODE)
#define SYSCALL_CHOWN(RET, PATH, UID, GID) __VINTIX_SYSCALL_THREE_ARG(28, RET, PATH, UID, GID)
#define SYSCALL_LCHOWN(RET, PATH, UID, GID) __VINTIX_SYSCALL_THREE_ARG(29, RET, PATH, UID, GID)
#define SYSCALL_FCHOWN(RET, FD, UID, GID) __VINTIX_SYSCALL_THREE_ARG(30, RET, FD, UID, GID)
#define SYSCALL_MPROTECT(RET, ADDR, LEN, PROT) __VINTIX_SYSCALL_THREE_ARG(31, RET, ADDR, LEN, PROT)

#endif // VINTIX_USER_SYSCALL_H
