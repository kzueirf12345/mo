#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <vector>

// https://codeforces.com/problemset/problem/86/D

int main() {
    size_t n = 0, m = 0;

    if (scanf("%zu %zu", &n, &m) != 2) {
        perror("scanf n and m");
        return EXIT_FAILURE;
    }

    std::vector<size_t> arr(n + 1, 0);
    size_t maxElem = 0;

    for (size_t i = 1; i <= n; ++i) {
        if (scanf("%zu", &arr[i]) != 1) {
            perror("Can't scanf arr[i]");
            return EXIT_FAILURE;
        }
        maxElem = std::max(maxElem, arr[i]);
    }

    for (size_t i = 1; i <= m; ++i) {
        size_t left = 0;
        size_t right = 0;
        if (scanf("%zu %zu", &left, &right) != 2) {
            perror("Can't scanf query");
            return EXIT_FAILURE;
        }

        
        std::unordered_map<size_t, size_t> mp = {};
        
        for (size_t j = left; j <= right; ++j) {
            ++mp[arr[j]];
        }
        
        size_t ans = 0;

        for (auto [key, val] : mp) {
            ans += key * val * val;
        }

        printf("%zu\n", ans);
    }
    
    return 0;
}