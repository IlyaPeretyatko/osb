#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

//директории

void create_dir(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *dir_path = argv[2];
    mkdir(dir_path, S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IXOTH);
}

void remove_dir(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *dir_path = argv[2];
    rmdir(dir_path);
}

void dir_content(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *dir_path = argv[2];
    DIR *dir = NULL;
    struct dirent *dir_entry = NULL;
    dir = opendir(dir_path);
    if (dir == NULL) {
        return;
    }
    dir_entry = readdir(dir);
    while (dir_entry != NULL) {
        printf("%s\n", dir_entry->d_name);
        dir_entry = readdir(dir);
    }
    closedir(dir);
}

// жёсткие ссылки

void create_hard_link(int argc, char **argv) {
    if (argc < 4) {
        return;
    }
    char *target_path = argv[2];
    char *link_path = argv[3];
    link(target_path, link_path);
}

void remove_hard_link(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *file_path = argv[2];
    unlink(file_path);
}

// файлы

void create_file(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *file_path = argv[2];
    creat(file_path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
}

void remove_file(int argc, char **argv) {
    remove_hard_link(argc, argv);
}

void file_content(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *file_path = argv[2];
    char symb;
    FILE *file_stream = NULL;
    file_stream = fopen(file_path, "r");
    if (file_stream == NULL) {
        return;
    }
    while (fread(&symb, sizeof(char), 1, file_stream)) {
        printf("%c", symb);
    }
    fclose(file_stream);
}

// символьные ссылки

void create_sym_link(int argc, char **argv) {
    if (argc < 4) {
        return;
    }
    char *target_path = argv[2];
    char *link_path = argv[3];
    symlink(target_path, link_path);
}

void remove_sym_link(int argc, char **argv) {
    remove_hard_link(argc, argv);
}

void display_sym_link_content(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *link_path = argv[2];
    char target_path[PATH_MAX] = {};
    readlink(link_path, target_path, BUFFER_SIZE);
    printf("%s\n", target_path);
}

void display_file_content_by_sym_link(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *link_path = argv[2];
    char target_path[PATH_MAX] = {};
    char *new_argv[3] = {};
    readlink(link_path, target_path, BUFFER_SIZE);
    new_argv[2] = target_path;
    file_content(3, new_argv);
}

// права доступа

void change_file_permissions(int argc, char **argv) {
    if (argc < 4) {
        return;
    }
    char *file_path = argv[2];
    char *endptr = NULL;
    mode_t permissions = strtol(argv[3], &endptr, 8);
    chmod(file_path, permissions);
}

void display_file_permissions(int argc, char **argv) {
    if (argc < 3) {
        return;
    }
    char *file_path = argv[2];
    struct stat file_info;
    stat(file_path, &file_info);
    printf("Permissions: %o\n", file_info.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    printf("Hard links: %ld\n", file_info.st_nlink);
}

int main(int argc, char **argv) {
    char* utilitname = argv[1];
    if (strcmp(utilitname, "change_file_permissions") == 0) {
        change_file_permissions(argc, argv);
    } else if (strcmp(utilitname, "create_dir") == 0) {
        create_dir(argc, argv);
    } else if (strcmp(utilitname, "create_file") == 0) {
        create_file(argc, argv);
    } else if (strcmp(utilitname, "create_hard_link") == 0) {
        create_hard_link(argc, argv);
    } else if (strcmp(utilitname, "create_sym_link") == 0) {
        create_sym_link(argc, argv);
    } else if (strcmp(utilitname, "display_file_content_by_sym_link") == 0) {
        display_file_content_by_sym_link(argc, argv);
    } else if (strcmp(utilitname, "file_content") == 0) {
        file_content(argc, argv);
    } else if (strcmp(utilitname, "display_file_permissions") == 0) {
        display_file_permissions(argc, argv);
    } else if (strcmp(utilitname, "display_sym_link_content") == 0) {
        display_sym_link_content(argc, argv);
    } else if (strcmp(utilitname, "dir_content") == 0) {
        dir_content(argc, argv);
    } else if (strcmp(utilitname, "remove_dir") == 0) {
        remove_dir(argc, argv);
    } else if (strcmp(utilitname, "remove_file") == 0) {
        remove_file(argc, argv);
    } else if (strcmp(utilitname, "remove_hard_link") == 0) {
        remove_hard_link(argc, argv);
    } else if (strcmp(utilitname, "remove_sym_link") == 0) {
        remove_sym_link(argc, argv);
    } else {
        printf("Utilits not found.");
    }
    return 0;
}