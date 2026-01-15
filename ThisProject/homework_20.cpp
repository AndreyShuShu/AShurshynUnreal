#include <iostream>
#include <vector>
#include <string>
#include <cmath> // For sqrt and pow

using namespace std;

// 1. Define the Character structure
struct Character {
    string name;
    int health;
    int x;
    int y;
};

int main() {
    int count;
    cout << "Input the number of characters: ";
    cin >> count;

    vector<Character> characters;

    // 2. Read multiple characters from console
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
        
        characters.push_back(p);
    }

    // 3. Read data about the meteorite
    int metX, metY, metDamage, metPower;
    cout << "\n--- METEORITE IMPACT ---" << endl;
    cout << "Enter impact coordinates (X Y): ";
    cin >> metX >> metY;
    cout << "Enter damage from meteorite: ";
    cin >> metDamage;
    cout << "Enter meteorite power: ";
    cin >> metPower;

    // Calculate impact radius
    double impactRadius = 3.0 * metPower;
    
    bool anyDead = false;
    vector<string> damagedNames;

    cout << "\n--- RESULTS ---" << endl;
    // 4. Logic for applying damage
    for (auto &p : characters) {
        // Calculate distance between character and meteorite
        // Formula: sqrt((x2 - x1)^2 + (y2 - y1)^2)
        double distance = sqrt(pow(p.x - metX, 2) + pow(p.y - metY, 2));

        // Check if the character is within the impact zone
        if (distance <= impactRadius) {
            p.health -= metDamage;
            damagedNames.push_back(p.name);

            // Check if the character is dead (if health <= 0, they are dead)
            if (p.health <= 0) {
                p.health = 0; // To avoid showing negative health
                anyDead = true;
            }
        }
    }

    // 5. Output the names of damaged characters
    if (damagedNames.empty()) {
        cout << "No one was hit." << endl;
    } else {
        cout << "Characters who received damage:" << endl;
        for (const string& name : damagedNames) {
            cout << "- " << name << endl;
        }
    }

    // 6. Output whether there are dead characters
    if (anyDead) {
        cout << "\nThere are dead characters!" << endl;
        cout << "List of the dead:" << endl;
        for (const auto &p : characters) {
            if (p.health == 0) {
                cout << "- " << p.name << " (R.I.P.)" << endl;
            }
        }
    } else {
        cout << "\nThere are no dead characters." << endl;
    }

    return 0;
}