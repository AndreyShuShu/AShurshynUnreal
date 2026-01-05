#include <iostream>
#include <string>

using namespace std;

// Function 1: read the variables
void inputPlayers(string names[], int health[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "Player " << i + 1 << " (Name and health): ";
        cin >> names[i] >> health[i];
    }
}

// Function 2: take a damage (change the health massive)
void applyDamage(int health[], int count) {
    int damage;
    cout << "Input the damage: ";
    cin >> damage;

    for (int i = 0; i < count; i++) {
        health[i] = health[i] - damage;
    }
}

// Function 3: find max health value
void findMaxHealth(string names[], int health[], int count) {
    int maxIndex = 0;
    for (int i = 1; i < count; i++) {
        if (health[i] > health[maxIndex]) {
            maxIndex = i;
        }
    }
    cout << "max health: " << names[maxIndex] << endl;
}

// Function 4: find min health value
void findMinHealth(string names[], int health[], int count) {
    int minIndex = 0;
    for (int i = 1; i < count; i++) {
        if (health[i] < health[minIndex]) {
            minIndex = i;
        }
    }
    cout << "min health: " << names[minIndex] << endl;
}

// Function 5: output the deads
void findDeadPlayers(string names[], int health[], int count) {
    cout << "Dead players: ";
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (health[i] <= 0) {
            cout << names[i] << " ";
            found = true;
        }
    }
    if (!found) cout << "nobody";
    cout << endl;
}

int main() {
    // create two massives
    string names[64];
    int health[64];
    int count;

    cout << "Input the amount of players: ";
    cin >> count;

    // call the functions
    inputPlayers(names, health, count);
    
    applyDamage(health, count);

    int choice;
    cout << "Input request (1-max, 2-min, 3-dead): ";
    cin >> choice;

    if (choice == 1) {
        findMaxHealth(names, health, count);
    } 
    else if (choice == 2) {
        findMinHealth(names, health, count);
    } 
    else if (choice == 3) {
        findDeadPlayers(names, health, count);
    } 
    else {
        cout << "Choice error" << endl;
    }

    return 0;
}