#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. Basic Structures
struct Stats {
    int str, intel, agi; // Power, Intelligence, Agility
    Stats operator+(const Stats& b) { return {str + b.str, intel + b.intel, agi + b.agi}; }
};

struct Item { string name, icon; };

struct Passive : Item {
    Stats buff; // Bonuses to characteristics
};

struct Weapon : Item {
    int damage;
    int cooldown; // Number of turns for reloading
    int lastAttackTurn = -100; // Turn of last attack (ready immediately)
};

// 2. Character Class
class Character {
    string name;
    int health;
    Stats baseStats;
    Weapon* weapon = nullptr;       // Active weapon
    vector<Passive*> passives;      // Passive items

public:
    Character(string n, int hp, Stats s) : name(n), health(hp), baseStats(s) {}

    // Calculate characteristics (Base + Items)
    Stats getStats() {
        Stats total = baseStats;
        for (auto p : passives) total = total + p->buff;
        return total;
    }

    // LOGIC: Equipping weapon
    void setWeapon(Weapon* w) {
        cout << "[" << name << "] Equipping weapon '" << w->name << "': ";
        if (weapon) cout << "Dropped '" << weapon->name << "'. "; // Scenario: Already has a weapon
        else        cout << "Slot was empty. ";                // Scenario: No weapon
        weapon = w;
        cout << "Took new one.\n";
    }

    // LOGIC: Adding passive
    void addPassive(Passive* p) {
        if (passives.size() < 3) passives.push_back(p);
        else cout << "Inventory is full!\n";
    }

    // LOGIC: Attack (accepts current game turn)
    void attack(int currentTurn) {
        if (!weapon) { cout << "No weapon!\n"; return; }

        // Cooldown check
        if (currentTurn - weapon->lastAttackTurn >= weapon->cooldown) {
            // Scenario: Weapon is ready
            Stats s = getStats();
            int dmg = weapon->damage + s.str; // Damage = weapon + strength
            weapon->lastAttackTurn = currentTurn;
            cout << ">>> ATTACK (" << weapon->icon << ")! Damage: " << dmg << endl;
        } else {
            // Scenario: Weapon is reloading
            int wait = weapon->cooldown - (currentTurn - weapon->lastAttackTurn);
            cout << ">>> Not ready yet! Wait turns: " << wait << endl;
        }
    }

    void printInfo() {
        Stats s = getStats();
        cout << name << " | P:" << s.str << " I:" << s.intel << " A:" << s.agi;
        if (weapon) cout << " | Weapon: " << weapon->name;
        cout << endl;
    }
};

int main() {
    // Creation of items
    Passive p1 = {{"Ring", "[o]"}, {5, 0, 0}};
    Passive p2 = {{"Boots", "[L]"}, {0, 0, 5}};
    Weapon sword = {{"Sword", "[|]"}, 20, 2};
    Weapon axe   = {{"Axe", "[P]"}, 40, 5};

    Character hero("Hero", 100, {10, 10, 10});
    hero.addPassive(&p1);
    hero.addPassive(&p2);
    hero.printInfo();

    // 1. Equipping weapon (when none is equipped)
    hero.setWeapon(&sword);

    // 2. Simulation of battle by turns
    cout << "\n--- Turn 1 ---\n";
    hero.attack(1); // Attack will proceed

    cout << "--- Turn 2 ---\n";
    hero.attack(2); // Too early (cooldown 2, 1 passed)

    cout << "--- Turn 3 ---\n";
    hero.attack(3); // Attack will proceed (1 + 2 = 3)

    // 3. Changing weapon (when one is already equipped)
    cout << "\n--- Changing weapon ---\n";
    hero.setWeapon(&axe);
    hero.attack(4); // New weapon is ready

    return 0;
}