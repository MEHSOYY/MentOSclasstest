/// @file signal.c
/// @brief
/// @copyright (c) 2014-2024 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include "errno.h"
#include "system/syscall_types.h"
#include "unistd.h"

#include "signal.h"
#include "sys/bitops.h"

// _syscall0(int, sigreturn)

/// @brief Handles the return from a signal handler.
/// @details
/// This function is used to transition control back to the point where a signal
/// handler was invoked. It performs the necessary system call to complete the
/// signal return process.
/// @return int The result of the signal return system call.
int sigreturn(void)
{
    long __res;
    __inline_syscall_0(__res, sigreturn);
    __syscall_return(int, __res);
}

// _syscall3(int, sigprocmask, int, how, const sigset_t *, set, sigset_t *, oldset)
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    long __res;
    __inline_syscall_3(__res, sigprocmask, how, set, oldset);
    __syscall_return(int, __res);
}

/// @brief List of signals names.
static const char *sys_siglist[] = {
    "HUP",  "INT",  "QUIT", "ILL",  "TRAP", "ABRT",   "EMT",  "FPE",  "KILL",  "BUS", "SEGV",
    "SYS",  "PIPE", "ALRM", "TERM", "USR1", "USR2",   "CHLD", "PWR",  "WINCH", "URG", "POLL",
    "STOP", "TSTP", "CONT", "TTIN", "TTOU", "VTALRM", "PROF", "XCPU", "XFSZ",  NULL,
};

sighandler_t signal(int signum, sighandler_t handler)
{
    long __res;
    __inline_syscall_3(__res, signal, signum, handler, (unsigned int)sigreturn);
    __syscall_return(sighandler_t, __res);
}

int sigaction(int signum, const sigaction_t *act, sigaction_t *oldact)
{
    long __res;
    __inline_syscall_4(__res, sigaction, signum, act, oldact, (unsigned int)sigreturn);
    __syscall_return(int, __res);
}

const char *strsignal(int sig)
{
    if ((sig >= SIGHUP) && (sig < NSIG)) {
        return sys_siglist[sig - 1];
    }
    return NULL;
}

int sigemptyset(sigset_t *set)
{
    if (set) {
        set->sig[0] = 0;
        return 0;
    }
    return -1;
}

int sigfillset(sigset_t *set)
{
    if (set) {
        set->sig[0] = ~0UL;
        return 0;
    }
    return -1;
}

int sigaddset(sigset_t *set, int signum)
{
    if (set && ((signum))) {
        bit_set_assign(set->sig[(signum - 1) / 32], ((signum - 1) % 32));
        return 0;
    }
    return -1;
}

int sigdelset(sigset_t *set, int signum)
{
    if (set) {
        bit_clear_assign(set->sig[(signum - 1) / 32], ((signum - 1) % 32));
        return 0;
    }
    return -1;
}

int sigismember(sigset_t *set, int signum)
{
    if (set) {
        return bit_check(set->sig[(signum - 1) / 32], (signum - 1) % 32);
    }
    return -1;
}
