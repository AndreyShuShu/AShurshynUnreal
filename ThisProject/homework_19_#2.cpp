#include <iostream>
#include <vector>
#include <string>

int main() {
    int N;
    std::cout << "Type count of commands (N): ";
    std::cin >> N;

    std::vector<std::string> commands;

    std::cout << "Type commands (right, left, forward, backward):\n";
    for (int i = 0; i < N; ++i) {
        std::string cmd;
        std::cin >> cmd;
        commands.push_back(cmd);
    }

    int x, y;
    std::cout << "Type initial coordinates (X Y): ";
    std::cin >> x >> y;

    for (const auto& cmd : commands) {
        if (cmd == "right") {
            x++;
        } else if (cmd == "left") {
            x--;
        } else if (cmd == "forward") {
            y++;
        } else if (cmd == "backward") {
            y--;
        } else {
            std::cout << "Ignoring unknown command: " << cmd << std::endl;
        }
    }

    std::cout << "Final coordinates: " << x << " " << y << std::endl;
    return 0;
}