/// @file termios-struct.h
/// @brief Definition of the `termios` structure.
/// @copyright (c) 2014-2023 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#pragma once

/// Type for control characters.
typedef unsigned char cc_t;
/// Type for speed.
typedef unsigned int speed_t;
/// Type for flags.
typedef unsigned int tcflag_t;
/// The number of control characters.
#define NCCS 32

/// @brief Stores information about a terminal IOs.
typedef struct termios {
    tcflag_t c_iflag; ///< input mode flags
    tcflag_t c_oflag; ///< output mode flags
    tcflag_t c_cflag; ///< control mode flags
    tcflag_t c_lflag; ///< local mode flags
    cc_t c_line;      ///< line discipline
    cc_t c_cc[NCCS];  ///< control characters
    speed_t c_ispeed; ///< input speed
    speed_t c_ospeed; ///< output speed
} termios_t;

//These flags generally control higher-level aspects of input processing than
// the input modes flags described in Input Modes, such as echoing, signals, and
// the choice of canonical or noncanonical input.

#define ISIG    0x00000080 ///< Controls whether the INTR, QUIT, and SUSP characters are recognized.
#define ICANON  0x00000100 ///< Enables canonical input processing mode.
#define ECHO    0x00000008 ///< Echo input characters.
#define ECHOE   0x00000002 ///< If ICANON is set, the ERASE character erases the preceding character.
#define ECHOK   0x00000004 ///< If ICANON is set, the KILL character erases the current line.
#define ECHONL  0x00000010 ///< If ICANON is set, echo the NL character even if ECHO is not set.
#define NOFLSH  0x80000000 ///< Do not clear in/out queues when receiving INTR, QUIT, and SUSP.
#define TOSTOP  0x00400000 ///< Allows SIGTTOU signals generated by background processes.
#define ECHOCTL 0x00000040 ///< If this and ECHO are set, control characters with ‘^’ are echoed.
#define ECHOKE  0x00000001 ///< If ICANON is set, KILL is echoed by erasing each character on the line.
#define IEXTEN  0x00000400 ///< Enables implementation-defined input processing.

/// @brief Mask for extracting control values.
#define CTRL(x) ((x) & 037)
