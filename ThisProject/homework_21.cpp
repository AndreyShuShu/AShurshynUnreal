#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. Definition of the Character class
class Character {
public:
    string name;
    int health;
    int x;
    int y;
    int speed;

    // 2. Movement method
    // Changes position based on direction and speed
    void Move(int dirX, int dirY) {
        x += dirX * speed;
        y += dirY * speed;
    }
};

int main() {
    int count;
    cout << "Input the number of characters: ";
    cin >> count;

    vector<Character> characters;

    // 3. Reading character data
    for (int i = 0; i < count; ++i) {
        Character p;
        cout << "\nCharacter #" << i + 1 << ":" << endl;
        cout << "  Name: ";
        cin >> p.name;
        cout << "  Health: ";
        cin >> p.health;
        cout << "  Position X: ";
        cin >> p.x;
        cout << "  Position Y: ";
        cin >> p.y;
        cout << "  Speed: ";
        cin >> p.speed;
        
        characters.push_back(p);
    }

    // 4. Reading and executing movement commands
    int commandCount;
    cout << "\nInput number of move commands: ";
    cin >> commandCount;

    cout << "Enter commands (Format: CharacterIndex DirX DirY):" << endl;
    for (int i = 0; i < commandCount; ++i) {
        int charIndex, dirX, dirY;
        
        cout << "Command #" << i + 1 << ": ";
        cin >> charIndex >> dirX >> dirY;

        if (charIndex >= 1 && charIndex <= characters.size()) {
            // Call the Move method
            characters[charIndex - 1].Move(dirX, dirY);
        } else {
            cout << "Invalid character index!" << endl;
        }
    }

    // 5. Displaying final positions
    cout << "\n--- FINAL POSITIONS ---" << endl;
    for (const auto &p : characters) {
        cout << "Character: " << p.name 
             << " | Health: " << p.health
             << " | New Position: (" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}