#include "pes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "index.h"
#include "commit.h"
#include <inttypes.h>

static void print_log_entry(const ObjectID *id, const Commit *commit, void *ctx) {
    (void)ctx;
    char hex[HASH_HEX_SIZE + 1];
    hash_to_hex(id, hex);

    printf("commit %s\n", hex);
    printf("Author: %s\n", commit->author);
    printf("Date: %" PRIu64 "\n\n", commit->timestamp);
    printf("    %s\n\n", commit->message);
}

// ==========================
// COMMANDS
// ==========================

void cmd_init() {
    mkdir(".pes", 0755);
    mkdir(".pes/objects", 0755);
    mkdir(".pes/refs", 0755);
    mkdir(".pes/refs/heads", 0755);

    FILE *f = fopen(".pes/HEAD", "w");
    fprintf(f, "ref: refs/heads/main\n");
    fclose(f);

    printf("Initialized empty PES repository\n");
}

void cmd_add(int argc, char *argv[]) {
    if (argc < 3) {
        printf("usage: pes add <file>...\n");
        return;
    }

      Index index;
      memset(&index, 0, sizeof(Index));   // ✅ CRITICAL FIX
      index_load(&index);

    for (int i = 2; i < argc; i++) {
        if (index_add(&index, argv[i]) != 0) {
            printf("error adding %s\n", argv[i]);
        } else {
            printf("added: %s\n", argv[i]);
        }
    }
}

void cmd_status() {
    Index index;
    index_load(&index);
    index_status(&index);
}

void cmd_commit(int argc, char *argv[]) {
    if (argc < 3) {
        printf("usage: pes commit <message>\n");
        printf("   or: pes commit -m <message>\n");
        return;
    }

    const char *message = NULL;
    if (strcmp(argv[2], "-m") == 0) {
        if (argc < 4) {
            printf("usage: pes commit -m <message>\n");
            return;
        }
        message = argv[3];
    } else {
        message = argv[2];
    }

    ObjectID commit_id;
    if (commit_create(message, &commit_id) != 0) {
        printf("commit failed (is anything staged?)\n");
        return;
    }

    char hex[HASH_HEX_SIZE + 1];
    hash_to_hex(&commit_id, hex);
    printf("Committed as %s\n", hex);
}

void cmd_log() {
    if (commit_walk(print_log_entry, NULL) != 0) {
        printf("No commits yet\n");
    }
}

// ==========================
// MAIN
// ==========================

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: pes <command>\n");
        return 1;
    }

    const char *cmd = argv[1];

    if      (strcmp(cmd, "init") == 0)     cmd_init();
    else if (strcmp(cmd, "add") == 0)      cmd_add(argc, argv);
    else if (strcmp(cmd, "status") == 0)   cmd_status();
    else if (strcmp(cmd, "commit") == 0)   cmd_commit(argc, argv);
    else if (strcmp(cmd, "log") == 0)      cmd_log();
    else {
        printf("Unknown command: %s\n", cmd);
        return 1;
    }

    return 0;
}
