
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

volatile long long result = 0;

double measureSequential(const vector<int>& data) {
    long long sum = 0;

    auto start = steady_clock::now();

    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i];
    }

    auto end = steady_clock::now();
    result = sum;

    return duration<double, milli>(end - start).count();
}


double measureStrided(const vector<int>& data, size_t stride) {
    long long sum = 0;
    size_t index = 0;

    auto start = steady_clock::now();

    for (size_t i = 0; i < data.size(); i++) {
        sum += data[index];

        index += stride;

        if (index >= data.size()) {
            index -= data.size();
        }
    }

    auto end = steady_clock::now();
    result = sum;

    return duration<double, milli>(end - start).count();
}


double measureRandom(const vector<int>& data,
                    const vector<size_t>& indexes) {
    long long sum = 0;

    auto start = steady_clock::now();

    for (size_t i = 0; i < indexes.size(); i++) {
        sum += data[indexes[i]];
    }

    auto end = steady_clock::now();
    result = sum;

    return duration<double, milli>(end - start).count();
}

double median(vector<double> values) {
    sort(values.begin(), values.end());

    size_t middle = values.size() / 2;

    if (values.size() % 2 == 0) {
        return (values[middle - 1] + values[middle]) / 2.0;
    }

    return values[middle];
}

int main() {
    vector<size_t> sizes = {
        8 * 1024,
        64 * 1024,
        1024 * 1024,
        8 * 1024 * 1024
    };

    mt19937 generator(42);

    cout << fixed << setprecision(3);

    cout << "CPU Cache Research - Improved Experiment\n";

    for (size_t size : sizes) {
        vector<int> data(size);

        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i % 100);
        }

        vector<size_t> indexes(size);

        for (size_t i = 0; i < size; i++) {
            indexes[i] = i;
        }

        shuffle(indexes.begin(), indexes.end(), generator);

        vector<double> sequentialTimes;
        vector<double> stridedTimes;
        vector<double> randomTimes;

        // Warm-up
        measureSequential(data);
        measureStrided(data, 17);
        measureRandom(data, indexes);

        // 15 repetitions
        for (int repeat = 0; repeat < 15; repeat++) {
            sequentialTimes.push_back(measureSequential(data));
            stridedTimes.push_back(measureStrided(data, 17));
            randomTimes.push_back(measureRandom(data, indexes));
        }

        cout << "\nArray size: "
             << size * sizeof(int) / 1024
             << " KB\n";

        cout << "Sequential median: "
             << median(sequentialTimes) << " ms\n";

        cout << "Strided median:    "
             << median(stridedTimes) << " ms\n";

        cout << "Random median:     "
             << median(randomTimes) << " ms\n";
    }

    return 0;
}
