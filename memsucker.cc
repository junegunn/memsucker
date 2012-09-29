/*
Junegunn Choi (junegunn.c@gmail.com)
# 2012/09/30-
*/

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

int main(int argc, char *argv[]) {
#if _POSIX_MEMLOCK < 0
  cerr << "mlockall not available in this system. Cannot prevent paging out." << endl;
#endif

  const int MEGA = 1024 * 1024;
  vector<void*> megas;

  while (!cin.eof()) {
    string input;
    cout << "Current allocation: " << megas.size() << "MB" << endl;
    cout << "Input MB: ";
    cin >> input;

    int mb = atoi(input.c_str());
    if (mb < 0) {
      cerr << "Invalid number." << endl;
      continue;
    }

    while (mb < megas.size()) {
      void* ptr = megas.back();
      free(ptr);
      megas.pop_back();
    }
    while (mb > megas.size()) {
      void* ptr = malloc(MEGA);
#if _POSIX_MEMLOCK < 0
      memset(ptr, 0, MEGA);
#endif
      megas.push_back(ptr);
    }
#if _POSIX_MEMLOCK > 0
    if (mlockall(MCL_CURRENT)) {
      cerr << "mlockall failed. not root?" << endl;
      exit(1);
    }
#endif
  }
}

