#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/uio.h>
#include <elf.h>

void print_process_maps(pid_t pid) {
    char path[64];
    char line[256];
    FILE *maps_file;

    snprintf(path, sizeof(path), "/proc/%d/maps", pid);
    maps_file = fopen(path, "r");
    if (!maps_file) {
        perror("Could not read process maps");
        return;
    }

    printf("\n--- EXTENDED INFO: MEMORY MAPS (/proc/%d/maps) ---\n", pid);
    int lines = 0;
    while (fgets(line, sizeof(line), maps_file) && lines < 12) {
        printf("  %s", line);
        lines++;
    }
    if (lines >= 12) {
        printf("  ... [truncated] ...\n");
    }
    fclose(maps_file);
}

void monitor_existing_process(pid_t target_pid) {
    int status;

    printf("[Monitor] Attaching to process %d...\n", target_pid);
    if (ptrace(PTRACE_ATTACH, target_pid, NULL, NULL) < 0) {
        perror("PTRACE_ATTACH failed. Try running with 'sudo'");
        exit(1);
    }

    waitpid(target_pid, &status, 0);
    printf("[Monitor] Successfully attached. Monitoring for crashes...\n");

    if (ptrace(PTRACE_CONT, target_pid, NULL, NULL) < 0) {
        perror("PTRACE_CONT failed");
        exit(1);
    }

    waitpid(target_pid, &status, 0);

    if (WIFSTOPPED(status)) {
        int sig = WSTOPSIG(status);
        printf("\n==================================================\n");
        printf("[Monitor] INTERCEPTED CRASH SIGNAL: %s (%d)\n", strsignal(sig), sig);
        printf("[Monitor] Target Process PID: %d\n", target_pid);
        printf("==================================================\n");

        if (sig == SIGSEGV || sig == SIGILL || sig == SIGFPE || sig == SIGBUS) {
            struct user_regs_struct regs;
            struct iovec iov;
            iov.iov_base = &regs;
            iov.iov_len = sizeof(regs);

            if (ptrace(PTRACE_GETREGSET, target_pid, NT_PRSTATUS, &iov) >= 0) {
                printf(" CPU REGISTER DUMP (ARM64):\n");
                printf("--------------------------------------------------\n");
                printf("  PC (Program Counter)     : 0x%016llx\n", regs.pc);
                printf("  SP (Stack Pointer)       : 0x%016llx\n", regs.sp);
                printf("  LR (Link Register)       : 0x%016llx\n", regs.regs[30]);
                printf("  X0 (Parameter/Return)    : 0x%016llx\n", regs.regs[0]);
                printf("--------------------------------------------------\n");

                long instr = ptrace(PTRACE_PEEKTEXT, target_pid, (void*)regs.pc, NULL);
                if (instr != -1) {
                    printf(" Raw instruction code at PC: 0x%016lx\n", instr);
                }
            } else {
                perror("PTRACE_GETREGSET failed");
            }

            print_process_maps(target_pid);
            printf("==================================================\n");
        }
    }

    printf("[Monitor] Logging completed. Killing target process.\n");
    ptrace(PTRACE_KILL, target_pid, NULL, NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <PID_TO_MONITOR>\n", argv[0]);
        return 1;
    }

    pid_t target_pid = atoi(argv[1]);
    monitor_existing_process(target_pid);

    return 0;
}
