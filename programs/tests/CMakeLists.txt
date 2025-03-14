# List of programs.
set(TEST_LIST
    t_exit.c
    t_time.c
    t_chdir.c
    t_grp.c
    t_pwd.c
    t_mkdir.c
    t_dup.c
    t_creat.c
    t_write_read.c
    t_gid.c
    t_alarm.c
    t_periodic3.c
    t_environ.c
    t_itimer.c
    t_fork.c
    t_semget.c
    t_exec.c
    t_sleep.c
    t_periodic2.c
    t_pipe_blocking.c
    t_pipe_non_blocking.c
    t_sigfpe.c
    t_sigmask.c
    t_sigusr.c
    t_shmget.c
    t_stopcont.c
    t_semop.c
    t_sigaction.c
    t_schedfb.c
    t_siginfo.c
    t_groups.c
    t_semflg.c
    t_abort.c
    t_msgget.c
    t_periodic1.c
    t_kill.c
    t_shm.c
    t_mem.c
    t_spwd.c
    t_big_write.c
    t_syslog.c
    t_ndtree.c
    t_list.c
    t_hashmap.c
)

# Set the directory where the compiled binaries will be placed.
set(MENTOS_TESTS_DIR ${CMAKE_SOURCE_DIR}/files/bin/tests)

foreach(FILE_NAME ${TEST_LIST})
    # =========================================================================
    # TARGET NAMING
    # =========================================================================
    # Prepare the program name.
    string(REPLACE ".c" "" EXECUTABLE_NAME ${FILE_NAME})
    # Set the name of the target.
    set(TARGET_NAME test_${EXECUTABLE_NAME})

    # =========================================================================
    # TEXT ADDRESS
    # =========================================================================
    # Randomize .text section address so when debugging symbols don't clash.
    # The allowed range is from 256MB to 2.75GB
    # Minimum allowed address: 0x10000000
    # Max allowed address: 0xB0000000
    string(MD5 RAND_HASH ${FILE_NAME})
    string(SUBSTRING ${RAND_HASH} 1 3 TEXADDR_INFIX)
    string(RANDOM LENGTH 1 ALPHABET 0123456789AB RANDOM_SEED ${RAND_HASH} TEXADDR_FIRST)
    set(TEXT_ADDR 0x${TEXADDR_FIRST}${TEXADDR_INFIX}0000)

    # =========================================================================
    # EXECUTABLE
    # =========================================================================
    # Create the target.
    add_executable(${TARGET_NAME} ${CMAKE_SOURCE_DIR}/programs/tests/${FILE_NAME})
    # Add the dependency to libc.
    add_dependencies(${TARGET_NAME} libc)
    # Add the includes.
    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libc/inc)
    # Link the libc library.
    target_link_libraries(${TARGET_NAME} libc)
    # We need to specify the name of the entry function.
    target_compile_options(${TARGET_NAME} PRIVATE -u_start)
    # Add the linking properties.
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "-Wl,-Ttext=${TEXT_ADDR},-e_start,-melf_i386")
    # Set the output directory.
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${MENTOS_TESTS_DIR}")
    # Set the output name.
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")

    # Append the program name to the list of all the executables.
    list(APPEND ALL_EXECUTABLES ${TARGET_NAME})
endforeach()

# Add the overall target that builds all the programs.
add_custom_target(tests ALL DEPENDS ${ALL_EXECUTABLES})
