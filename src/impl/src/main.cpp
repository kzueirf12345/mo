#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>

// https://codeforces.com/problemset/problem/86/D

struct Query {
    size_t left;
    size_t right;
    size_t index;
};

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

    std::vector<Query> queries(m + 1);

    for (size_t i = 1; i <= m; ++i) {
        if (scanf("%zu %zu", &queries[i].left, &queries[i].right) != 2) {
            perror("Can't scanf queries[i]");
            return EXIT_FAILURE;
        }
        queries[i].index = i;
    }

    size_t blockSize = static_cast<size_t>(std::sqrt(n));

    std::sort(
        queries.begin() + 1, 
        queries.end(), 
        [&blockSize](const Query& first, const Query& second) {
            const size_t blockFirst  = (first.left  - 1) / blockSize;
            const size_t blockSecond = (second.left - 1) / blockSize;
            if (blockFirst != blockSecond) {
                return blockFirst < blockSecond;
            }
            return (blockFirst % 2 == 0) 
                ? (first.right < second.right)
                : (first.right > second.right);
        }
    );

    std::vector<long long> ans(m + 1, 0);
    std::vector<size_t> freq(maxElem + 1, 0);

    size_t curLeft = 1;
    size_t curRight = 0;
    long long curCnt = 0;

    for (size_t i = 1; i <= m; ++i) {
        const Query q = queries[i];
        
        // Уменьшаем левую границу
        while (curLeft > q.left) {
            --curLeft;
            size_t val = arr[curLeft];
            size_t curFreq = freq[val];
            curCnt += static_cast<long long>(val * (2 * curFreq + 1));
            ++freq[val];
        }
        
        // Увеличиваем правую границу
        while (curRight < q.right) {
            ++curRight;
            size_t val = arr[curRight];
            size_t curFreq = freq[val];
            curCnt += static_cast<long long>(val * (2 * curFreq + 1));
            ++freq[val];
        }
        
        // Увеличиваем левую границу
        while (curLeft < q.left) {
            size_t val = arr[curLeft];
            size_t curFreq = freq[val];
            curCnt -= static_cast<long long>(val * (2 * curFreq - 1));
            --freq[val];
            ++curLeft;
        }
        
        // Уменьшаем правую границу
        while (curRight > q.right) {
            size_t val = arr[curRight];
            size_t curFreq = freq[val];
            curCnt -= static_cast<long long>(val * (2 * curFreq - 1));
            --freq[val];
            --curRight;
        }
        
        ans[q.index] = curCnt;
    }

    for (size_t i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
    }
    
    return 0;
}