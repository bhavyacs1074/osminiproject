#include "types.h"
#include "stat.h"
#include "user.h"

/*
 * pstree_test.c
 * This program builds a process tree of depth 2 to test the pstree() syscall.
 *
 * Tree structure:
 *
 * pstree_test (root)
 * |
 * +-- Child A (depth 1)
 * |   |
 * |   +-- Grandchild A1 (depth 2)
 * |   +-- Grandchild A2 (depth 2)
 * |
 * +-- Child B (depth 1)
 *
 */

int
main(int argc, char *argv[])
{
  int pid_a, pid_b;

  printf(1, "pstree_test: Starting test...\n");

  // Fork Child A
  pid_a = fork();

  if (pid_a == 0) {
    // --- We are in Child A (Depth 1) ---
    // This child will have its own children (grandchildren)
    
    int gpid_a1, gpid_a2;

    // Fork Grandchild A1
    gpid_a1 = fork();
    if (gpid_a1 == 0) {
      // --- We are in Grandchild A1 (Depth 2) ---
      sleep(200); // Sleep long enough to be seen by pstree
      exit();
    }

    // Fork Grandchild A2
    gpid_a2 = fork();
    if (gpid_a2 == 0) {
      // --- We are in Grandchild A2 (Depth 2) ---
      sleep(200); // Sleep long enough to be seen by pstree
      exit();
    }

    // Child A waits for its children to finish
    wait();
    wait();
    exit(); // Child A exits

  } else {
    // --- We are in the Parent (Root) process ---
    
    // Fork Child B
    pid_b = fork();

    if (pid_b == 0) {
      // --- We are in Child B (Depth 1) ---
      // This child will NOT have children
      sleep(150); // Sleep long enough to be seen by pstree
      exit();
    }

    // --- Parent (Root) process continues ---
    
    // Give all children and grandchildren time to fork and settle
    printf(1, "pstree_test: Building process tree (sleeping 50 ticks)...\n");
    sleep(50); 

    // Now, call the system call
    printf(1, "\n--- Calling pstree() ---\n");
    pstree(); // <<< YOUR SYSTEM CALL IS EXECUTED HERE
    printf(1, "--- pstree() complete ---\n\n");

    // Parent waits for its direct children (Child A and Child B) to exit
    printf(1, "pstree_test: Cleaning up child processes...\n");
    wait();
    wait();
    
    printf(1, "pstree_test: Test finished.\n");
    exit();
  }
}
