#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>

// https://codeforces.com/problemset/problem/86/D

int main() {
    size_t n = 0, m = 0;

    if (scanf("%zu %zu", &n, &m) != 2) {
        perror("scanf n t");
        return EXIT_FAILURE;
    }

    std::vector<size_t> arr(n + 1, 0);
    size_t maxElem = 0;
        
    for (size_t i = 1; i <= n; ++i) {
        if (scanf("%zu", &arr[i]) != 1) {
            perror("scanf a[i]");
            return EXIT_FAILURE;
        }
        maxElem = std::max(maxElem, arr[i] + 1);
    }

    std::vector<size_t> totalCount(maxElem, 0);
    for (size_t i = 1; i <= n; ++i) {
        ++totalCount[arr[i]];
    }

    size_t blockSize = static_cast<size_t>(std::sqrt(n)) + 1;

    std::vector<size_t> frequent;
    std::vector<size_t> rare;
    std::vector<bool> isFrequent(maxElem, false);

    for (size_t v = 1; v < maxElem; ++v) {
        if (totalCount[v] >= blockSize) {
            frequent.push_back(v);
            isFrequent[v] = true;
        } else if (totalCount[v] > 0) {
            rare.push_back(v);
        }
    }

    std::vector<std::vector<size_t>> prefFreq;
    prefFreq.resize(frequent.size());
    for (size_t i = 0; i < frequent.size(); ++i) {
        prefFreq[i].assign(n + 1, 0);
    }

    for (size_t i = 1; i <= n; ++i) {
        for (size_t k = 0; k < frequent.size(); ++k) {
            prefFreq[k][i] = prefFreq[k][i - 1];
        }

        if (isFrequent[arr[i]]) {
            size_t id = static_cast<size_t>(
                std::lower_bound(frequent.begin(), frequent.end(), arr[i]) - frequent.begin()
            );
            ++prefFreq[id][i];
        }
    }

    std::vector<std::vector<size_t>> rarePositions(maxElem);
    for (size_t i = 1; i <= n; ++i) {
        if (!isFrequent[arr[i]]) {
            rarePositions[arr[i]].push_back(i);
        }
    }

    while (m--) {
        size_t l = 0, r = 0;

        if (scanf("%zu %zu", &l, &r) != 2) {
            perror("scanf query");
            return EXIT_FAILURE;
        }

        long long ans = 0;

        for (size_t k = 0; k < frequent.size(); ++k) {
            size_t v = frequent[k];
            size_t cnt = prefFreq[k][r] - prefFreq[k][l - 1];
            ans += static_cast<long long>(cnt * cnt * v);
        }

        for (size_t v : rare) {
            const std::vector<size_t>& pos = rarePositions[v];
            auto itL = std::lower_bound(pos.begin(), pos.end(), l);
            auto itR = std::upper_bound(pos.begin(), pos.end(), r);
            size_t cnt = static_cast<size_t>(itR - itL);
            if (cnt > 0) {
                ans += static_cast<long long>(cnt * cnt * v);
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
