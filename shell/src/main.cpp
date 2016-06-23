#include "Shell.h"

using namespace std;

int main() {
    Shell * shell = new Shell();
    int res = shell->run();
    if (res) {
        shell->printLog();
    }
    delete(shell);
    return res;
}