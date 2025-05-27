#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int size;
} DisjointSetForest;

DisjointSetForest* createDSF(int n) {
    DisjointSetForest* dsf = (DisjointSetForest*)malloc(sizeof(DisjointSetForest));
    dsf->parent = (int*)malloc(n * sizeof(int));
    dsf->size = n;
    for (int i = 0; i < n; i++) {
        dsf->parent[i] = i;  // Each node is its own parent initially
    }
    return dsf;
}

int Find(DisjointSetForest* dsf, int x) {
    while (dsf->parent[x] != x) {
        x = dsf->parent[x];  // Climb up the tree
    }
    return x;
}

void Union(DisjointSetForest* dsf, int x, int y) {
    int rootX = Find(dsf, x);
    int rootY = Find(dsf, y);
    dsf->parent[rootY] = rootX;  // Arbitrarily attach rootY under rootX
}

void destroyDSF(DisjointSetForest* dsf) {
    free(dsf->parent);
    free(dsf);
}

int main() {
    int n = 5;
    DisjointSetForest* dsf = createDSF(n);

    Union(dsf, 0, 1);  // Merge {0} and {1}
    Union(dsf, 2, 3);  // Merge {2} and {3}
    Union(dsf, 1, 2);  // Merge {0,1} and {2,3}

    printf("Find(0) = %d\n", Find(dsf, 0));  // Output: 0
    printf("Find(3) = %d\n", Find(dsf, 3));  // Output: 0 (3 → 2 → 0)

    destroyDSF(dsf);
    return 0;
}