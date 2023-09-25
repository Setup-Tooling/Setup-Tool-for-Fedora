#include <stdio.h>
#include <stdlib.h>

int main() {
    // Make setup.sh executable
    system("chmod +x setup.sh");

    // Execute setup.sh
    system("./setup.sh");

    return 0;
}
