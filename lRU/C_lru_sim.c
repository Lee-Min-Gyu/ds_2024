#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListBasic.h"

#define MAX_CACHE_SIZE 1001

typedef struct {
    int cache_slots;
    int cache_hit;
    int tot_cnt;
} CacheSimulator;

void CacheSimulator_init(CacheSimulator* cache_sim, int cache_slots) {
    cache_sim->cache_slots = cache_slots;
    cache_sim->cache_hit = 0;
    cache_sim->tot_cnt = 1;
}

void CacheSimulator_do_sim(CacheSimulator* cache_sim, LinkedListBasic* cache, char* page) {
    int index = LinkedListBasic_index(cache, atoi(page));
    if (index != -2) {
        cache_sim->cache_hit++;
    } else {
        if (LinkedListBasic_size(cache) == cache_sim->cache_slots) {
            LinkedListBasic_pop(cache, 0);
        }
        LinkedListBasic_append(cache, atoi(page));
    }
    cache_sim->tot_cnt++;
}

void CacheSimulator_print_stats(CacheSimulator* cache_sim) {
    printf("cache_slot = %d, cache_hit = %d, hit ratio = %f\n", cache_sim->cache_slots, cache_sim->cache_hit, (float)cache_sim->cache_hit / cache_sim->tot_cnt);
}

int main() {
    FILE* data_file = fopen("C:/Users/jipo0/CLionProjects/untitled5/linkbench.trc", "r");
    if (data_file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[100];
    LinkedListBasic* cache = LinkedListBasic_create();

    for (int cache_slots = 100; cache_slots <= MAX_CACHE_SIZE; cache_slots += 100) {
        CacheSimulator cache_sim;
        CacheSimulator_init(&cache_sim, cache_slots);

        while (fgets(line, sizeof(line), data_file)) {
            char* page = strtok(line, " \t\n");
            CacheSimulator_do_sim(&cache_sim, cache, page);
        }

        CacheSimulator_print_stats(&cache_sim);
        LinkedListBasic_clear(cache);
        rewind(data_file);
    }

    fclose(data_file);
    return 0;
}
