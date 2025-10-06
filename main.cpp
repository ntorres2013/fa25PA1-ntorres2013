#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "linkedlist.h"

using namespace std;

// Robot type lives here, not in the container
struct Robot {
    int id;
    string name;
    int battery;
    int drain;
    bool paused;
    Robot(int pid, string n, int b, int d)
        : id(pid), name(n), battery(b), drain(d), paused(false) {}

};

ostream& operator<<(ostream &out, const Robot &ring)
{
    out << "ID: " << ring.id << endl;
    out << "Name: " << ring.name << endl;
    out << "Battery: " << ring.battery << endl;
    out << "Drain: " << ring.drain << endl;
    out << "Paused: ";
    if (ring.paused) {
        out << "Yes";
    }
    else
    {
        out << "No";
    }
    out << endl;
    return out;
}


static int nextId = 1;
static int score  = 0;
static int quantum = 1;

// ---------------- Menu Actions ----------------
void addRobot(LinkedList<Robot>& ring) {
    string name;
    int battery;

    cout << "Robot Name: ";
    cin >> name;
    cout << "Battery: ";
    cin >> battery;

    Robot robotCreation = Robot(nextId++, name, battery, quantum);
    ring.append(robotCreation);
    score += 2;     // +2 add robot
}

void runOneTurn(LinkedList<Robot>& ring) {
    Robot& curr = ring.front();

    if(curr.paused)
//    If paused, skip and move to the next (rotate)
    {
        ring.rotate();
        return;
    }

//    Reduce its battery, the robot at the head uses up drain units of battery
    curr.battery -= curr.drain;

    score += 1;     // +1 per valid turn

//    If battery hits 0, robot is removed from the ring
    if(curr.battery <= 0)
    {
        ring.pop_front();
        score += 3;     // +3 per correct removal
    }
//    If it still has battery, update battery then rotate
    else
    {
        ring.set_front(curr);
        ring.rotate();
    }
}

void runNTurns(LinkedList<Robot>& ring) {
    int n;

    cout << "Enter the number of turns you want to run: ";
    cin >> n;

    for(int i = 0; i < n; i++) {
        if(ring.empty())    // No turns left
        {
            break;
        }

        Robot& curr = ring.front();

        if(curr.paused) {
            ring.rotate();       // Skip paused robot
            continue;
        }

        curr.battery -= curr.drain;

        score += 1;     // +1 per valid turn

        if(curr.battery <= 0)
        {
            ring.pop_front();    // Remove robot if battery hits 0
            score += 3;         // +3 per correct removal
        }
        else
        {
            ring.rotate();       // Advance to next robot
        }
    }
}


void pauseResume(LinkedList<Robot>& ring) {
//    Case 1: Checks if list is empty
    if(ring.empty())
    {
        cout << "Empty ring" << endl;
        return;
    }

//    Case 2: Asks user for ID for pausing or resuming
    int id;
    cout << "Enter ID to pause/resume robot:";
    cin >> id;

    bool found = false;

    for(int i = 0; i < ring.size(); i++)
    {
        Robot& curr = ring.front();

        if(curr.id == id)   // If ID matches correctly
        {
            curr.paused = !curr.paused;     // Toggle. If paused, resume. If resumed, pause.
            found = true;       // Update status to true
            break;
        }
        ring.rotate();
    }

}

void showRing(LinkedList<Robot>& ring) {
    // Example: ring.display();
    if(ring.empty())
    {
        return;
    }
    ring.display();
}

void splitRing(LinkedList<Robot>& ring) {
//    Case 1: Ring is empty
    if(ring.empty())
    {
        return;
    }
    LinkedList<Robot> a;    // Create first ring
    LinkedList<Robot> b;   // Create second ring
    ring.splitIntoTwo(a, b);   // Call splitIntoTwo function, first and second as parameters
    score += 5;         // +5 successful split
    a.display();    // Display first ring
    cout << endl;
    b.display();    // Display second ring
}

void mergeRings(LinkedList<Robot>& ring) {
    if(ring.empty())
    {
        return;
    }

    LinkedList<Robot> other;
    ring.mergeWith(other);
}

void statsReport(LinkedList<Robot>& ring) {
    if(ring.empty())
    {
        return;
    }
    int totalBattery = 0;                 // Sum of all robot batteries
    int pausedCount = 0;                  // Count of paused robots
    int n = ring.size();                  // Number of robots

    for (int i = 0; i < n; i++) {        // Loop through the ring
        Robot& r = ring.front();          // Get the current robot
        totalBattery += r.battery;        // Add battery to total
        if (r.paused) pausedCount++;      // Increment paused count if paused
        ring.rotate();                    // Move to next robot
    }

    cout << "Total robots: " << n << endl;
    cout << "Average battery: " << totalBattery / (double)n << endl;
    cout << "Paused robots: " << pausedCount << endl;
}

void exit(){
    cout << "Ending Robot Relay Ring..." << endl;
}

// ---------------- Main ----------------
int main() {
    LinkedList<Robot> ring;

    unordered_map<int, function<void()>> cmd;
    cmd[0] = [&]{ exit(); };
    cmd[1] = [&]{ addRobot(ring); };
    cmd[2] = [&]{ runOneTurn(ring); };
    cmd[3] = [&]{ runNTurns(ring); };
    cmd[4] = [&]{ pauseResume(ring); };
    cmd[5] = [&]{ showRing(ring); };
    cmd[6] = [&]{ splitRing(ring); };
    cmd[7] = [&]{ mergeRings(ring); };
    cmd[8] = [&]{ statsReport(ring); };

    while (true) {
        cout << "\n=== Robot Relay Ring ===\n";
        cout << "Robots: " << ring.size() << "   Score: " << score << "   Quantum: " << quantum << "\n";
        cout << "1) Add robot\n";
        cout << "2) Run 1 turn\n";
        cout << "3) Run N turns\n";
        cout << "4) Pause/Resume robot\n";
        cout << "5) Display ring\n";
        cout << "6) Split ring into two\n";
        cout << "7) Merge rings\n";
        cout << "8) Stats report\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        int choice;
        if (!(cin >> choice)) break;
        if (choice == 0) { cout << "Goodbye!\n"; break; }

        auto it = cmd.find(choice);
        if (it != cmd.end()) it->second();
        else cout << "Invalid choice. Try again.\n";
    }
}
