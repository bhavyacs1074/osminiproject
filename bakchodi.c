#include "types.h"
#include "stat.h"
#include "user.h"

/*
 * ASCII Art for "xv6"
 * * We have to "escape" all backslashes (\) by using two (\\)
 * and escape all double-quotes (") by using \".
 */
char *logo[] = {
"       __   ___  _  ",
"      / /  |__ \\(_)",
"     / /_   __) |    __ _ ",
"    | '_ \\ / __/ |  / _` |",
"    | (_) | |__| | | (_| |",
"     \\___/|____|_|  \\__,_|",
"                          ",
"   Welcome to xv6!        ",
0 // This '0' (null) tells us when the array ends
};

int
main(int argc, char *argv[])
{
  int i;

  // Loop through each line of the logo array
  // and print it to the console (file descriptor 1).
  for(i = 0; logo[i]; i++){
    printf(1, "%s\n", logo[i]);
  }

  // We're done, so exit.
  exit();
}
