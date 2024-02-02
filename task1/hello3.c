#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *lib_so = dlopen("./libhello.so", RTLD_LAZY);
    if (lib_so == 0) {
        printf("No such library.\n");
        return 0;
    }
    void (*f)() = dlsym(lib_so, "hello_from_lib");
    f();
    dlclose(lib_so);
    return 0;
}