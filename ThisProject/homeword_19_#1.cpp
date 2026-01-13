#include <iostream>
#include <map>

int main() {
    int N;
    std::cout << "Type count (N): ";
    std::cin >> N;

    std::map<int, int> army;

    std::cout << "Enter pairs of numbers (Type and Increase):\n";
    for (int i = 0; i < N; ++i) {
        int type, count;
        std::cin >> type >> count;
        army[type] += count;
    }

    if (army.empty()) {
        std::cout << "No data was entered." << std::endl;
        return 0;
    }

    int minType = 0;
    int maxType = 0;
    int minVal = 0;
    int maxVal = 0;

    bool isFirst = true;

    for (auto pair : army) {
        
        if (isFirst) {
            minType = pair.first;
            minVal = pair.second;
            maxType = pair.first;
            maxVal = pair.second;
            isFirst = false;
        } else {
            if (pair.second > maxVal) {
                maxVal = pair.second;
                maxType = pair.first;
            }
            if (pair.second < minVal) {
                minVal = pair.second;
                minType = pair.first;
            }
        }
    }

    std::cout << "Type with maximum count (" << maxVal << "): " << maxType << std::endl;
    std::cout << "Type with minimum count (" << minVal << "): " << minType << std::endl;

    return 0;
}