#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// 1. Basic Structures
struct Stats {
    int str, intel, agi;
    int speed; // adding speed attribute

    Stats operator+(const Stats& b) const { 
        return {str + b.str, intel + b.intel, agi + b.agi, speed + b.speed}; 
    }
};

struct Item { 
    string name, icon; 
    virtual ~Item() = default; // virtual destructor for proper cleanup
};

struct Passive : Item {
    Stats buff; 
};

// Item that boosts speed
struct SpeedBooster : public Passive {
    SpeedBooster(string n, string i, int speedBonus) {
        name = n;
        icon = i;
        buff = {0, 0, 0, speedBonus}; // speed bonus only
    }
};

struct Weapon : Item {
    int damage;
    int cooldown; 
    int lastAttackTurn = -100; 
};

// 2. Character Class
class Character {
    string name;
    int health;
    Stats baseStats;
    int currentSpeed; // variable to hold current speed

    // Using smart pointers (unique_ptr means the character owns the item)
    std::unique_ptr<Weapon> weapon; 
    vector<std::unique_ptr<Passive>> inventory; 

public:
    Character(string n, int hp, Stats s) : name(n), health(hp), baseStats(s) {
        // When creating, we calculate the initial speed
        updateSpeed();
    }

    // Speed recalculation method
    void updateSpeed() {
        Stats total = baseStats;
        for (const auto& item : inventory) {
            total = total + item->buff;
        }
        currentSpeed = total.speed;
        cout << "[System] Speed recalculated. Current Speed: " << currentSpeed << endl;
    }

    Stats getStats() {
        Stats total = baseStats;
        for (const auto& item : inventory) {
            total = total + item->buff;
        }
        return total;
    }

    void setWeapon(std::unique_ptr<Weapon> w) {
        cout << "[" << name << "] Equipping weapon '" << w->name << "': ";
        if (weapon) cout << "Dropped '" << weapon->name << "'. "; 
        else        cout << "Slot was empty. ";               
        
        weapon = std::move(w);
        cout << "Took new one.\n";
    }

    // method to add passive items
    void addPassive(std::unique_ptr<Passive> p) {
        if (inventory.size() < 3) {
            cout << "[" << name << "] Picked up item: " << p->name << endl;
            inventory.push_back(std::move(p)); // move the unique_ptr into inventory
            
            // recalculate speed after adding new passive item
            updateSpeed();
        }
        else {
            cout << "Inventory is full!\n";
        }
    }

    void attack(int currentTurn) {
        if (!weapon) { cout << "No weapon!\n"; return; }

        if (currentTurn - weapon->lastAttackTurn >= weapon->cooldown) {
            Stats s = getStats();
            int dmg = weapon->damage + s.str; 
            weapon->lastAttackTurn = currentTurn;
            cout << ">>> ATTACK (" << weapon->icon << ")! Damage: " << dmg << endl;
        } else {
            int wait = weapon->cooldown - (currentTurn - weapon->lastAttackTurn);
            cout << ">>> Not ready yet! Wait turns: " << wait << endl;
        }
    }

    void printInfo() {
        Stats s = getStats();
        cout << "========================================\n";
        cout << name << " Stats | STR:" << s.str << " INT:" << s.intel << " AGI:" << s.agi 
             << " | SPEED: " << currentSpeed;
        
        if (weapon) cout << "\nActive Weapon: " << weapon->name;
        
        cout << "\nInventory: ";
        if(inventory.empty()) cout << "Empty";
        for(const auto& item : inventory) {
            cout << item->name << " ";
        }
        cout << "\n========================================\n";
    }
};

int main() {
    // Creating objects via smart pointers
    // Using make_unique for safe memory allocation
    auto ring = std::make_unique<Passive>();
    ring->name = "Ring of Power";
    ring->icon = "[o]";
    ring->buff = {5, 0, 0, 0};

    // Creating a special item for speed boost
    auto boots = std::make_unique<SpeedBooster>("Boots of Haste", "[L]", 25);

    auto sword = std::make_unique<Weapon>();
    sword->name = "Sword";
    sword->icon = "[|]";
    sword->damage = 20;
    sword->cooldown = 2;

    // creating a hero (Base Stats: Str, Int, Agi, Speed)
    Character hero("Hero", 100, {10, 10, 10, 5}); // base speed 5
    
    hero.printInfo();

    // 1. Adding items
    cout << "\n--- Looting ---\n";
    hero.addPassive(std::move(ring));
    hero.addPassive(std::move(boots));

    hero.printInfo();

    // 2. Weapon equipment
    hero.setWeapon(std::move(sword));

    // 3. Fighting simulation
    cout << "\n--- Battle ---\n";
    hero.attack(1); 
    
    // Trying to add a third item to check inventory limit
    auto cape = std::make_unique<Passive>();
    cape->name = "Cape";
    cape->buff = {0, 0, 5, 10};
    hero.addPassive(std::move(cape));

    hero.printInfo(); // Speed should be even higher (30 + 10 = 40)

    return 0;
}