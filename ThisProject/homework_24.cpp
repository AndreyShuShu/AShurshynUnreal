#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Observer Interface (The Subscriber)
// Anyone who wants to be notified must implement this.
class ISubscriber {
public:
    virtual void onVideoUploaded(string title) = 0;
};

// 2. Concrete Observer (A real User)
class User : public ISubscriber {
private:
    string name;
public:
    User(string n) : name(n) {}

    // This runs when the channel notifies us
    void onVideoUploaded(string title) override {
        cout << "Hello " << name << "! New video uploaded: " << title << endl;
    }
};

// 3. Subject (The YouTube Channel)
class YouTubeChannel {
private:
    vector<ISubscriber*> subscribers; // List of people to notify

public:
    // Add someone to the list
    void subscribe(ISubscriber* s) {
        subscribers.push_back(s);
    }

    // Remove someone from the list
    void unsubscribe(ISubscriber* s) {
        // Standard C++ way to remove an item from a vector
        subscribers.erase(
            std::remove(subscribers.begin(), subscribers.end(), s),
            subscribers.end()
        );
    }

    // The main logic: Notify everyone
    void uploadVideo(string title) {
        cout << "\n[Channel] Uploading video: " << title << "..." << endl;
        
        // Loop through all subscribers and notify them
        for (ISubscriber* sub : subscribers) {
            sub->onVideoUploaded(title);
        }
    }
};

int main() {
    // Create the Publisher (Channel)
    YouTubeChannel myChannel;

    // Create Subscribers
    User user1("John");
    User user2("Alice");
    User user3("Bob");

    // Users subscribe to the channel
    myChannel.subscribe(&user1);
    myChannel.subscribe(&user2);
    myChannel.subscribe(&user3);

    // Channel uploads a video -> All 3 get notified
    myChannel.uploadVideo("Learn C++ in 5 minutes");

    // Alice decides to unsubscribe
    cout << "\n(Alice unsubscribed)" << endl;
    myChannel.unsubscribe(&user2);

    // Channel uploads another video -> Only John and Bob get notified
    myChannel.uploadVideo("Observer Pattern Tutorial");

    return 0;
}