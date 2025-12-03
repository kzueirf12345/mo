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
    size_t order;
};

size_t HilbertOrder(size_t x, size_t y, size_t pow, size_t rotate);
void AddPosition(size_t pos, const std::vector<size_t>& arr, std::vector<size_t>& freq, long long &curCnt);
void RemovePosition(size_t pos, const std::vector<size_t>& arr, std::vector<size_t>& freq, long long &curCnt);

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

    static constexpr const int HILBERT_POW = 21;
    std::vector<Query> queries(m + 1);

    for (size_t i = 1; i <= m; ++i) {
        if (scanf("%zu %zu", &queries[i].left, &queries[i].right) != 2) {
            perror("Can't scanf queries[i]");
            return EXIT_FAILURE;
        }
        queries[i].index = i;
        queries[i].order = HilbertOrder(queries[i].left - 1, queries[i].right - 1, HILBERT_POW, 0);
    }

    std::sort(queries.begin(), queries.end(), [](const Query &a, const Query &b){
        return a.order < b.order;
    });

    std::vector<long long> ans(m + 1, 0);
    std::vector<size_t> freq(maxElem + 1, 0);

    size_t curLeft = 1;
    size_t curRight = 0;
    long long curCnt = 0;

    for (const Query &q : queries) {
        while (curLeft > q.left) {
            --curLeft;
            AddPosition(curLeft, arr, freq, curCnt);
        }
        while (curRight < q.right) {
            ++curRight;
            AddPosition(curRight, arr, freq, curCnt);
        }
        while (curLeft < q.left) {
            RemovePosition(curLeft, arr, freq, curCnt);
            ++curLeft;
        }
        while (curRight > q.right) {
            RemovePosition(curRight, arr, freq, curCnt);
            --curRight;
        }
        ans[q.index] = curCnt;
    }

    for (size_t i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
    }
    
    return 0;
}

size_t HilbertOrder(size_t x, size_t y, size_t pow, size_t rotate) {
    if (pow == 0) {
        return 0;
    }

    const size_t height = 1 << (pow - 1);

    size_t seg = (x < height ? 0ull : 1ull) * 2 + (y < height ? 0ull : 1ull);
    seg = (seg + rotate) & 3;

    static constexpr const size_t rotateDelta[4] = {3, 0, 0, 1};

    size_t newX = x & (height - 1);
    size_t newY = y & (height - 1);
    size_t newRotate = (rotate + rotateDelta[seg]) & 3;

    size_t lowBits = HilbertOrder(newX, newY, pow - 1, newRotate);

    size_t highBits = seg << (2 * (pow - 1));

    return highBits | lowBits;
}

void AddPosition(size_t pos, const std::vector<size_t>& arr, std::vector<size_t>& freq, long long &curCnt) {
    size_t val = arr[pos];
    size_t curFreq = freq[val];
    curCnt += 1LL * val * (2LL * curFreq + 1LL);
    ++freq[val];
}

void RemovePosition(size_t pos, const std::vector<size_t>& arr, std::vector<size_t>& freq, long long &curCnt) {
    size_t val = arr[pos];
    size_t curFreq = freq[val];
    curCnt -= 1LL * val * (2LL * curFreq - 1LL);
    --freq[val];
}
