/*
===========================================
Tiana's Track Training App
Author: Jani

Description:
A console-based workout tracking system
that allows athletes to log performance,
track progress over time, and receive
motivational feedback based on improvement.

Inspired by The Princess and the Frog.
===========================================
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

// Function prototypes
void loadFromFile(vector<double>& times, vector<string>& types);
void saveToFile(const vector<double>& times, const vector<string>& types);
void showMenu();
void addWorkout(vector<double>& times, vector<string>& types, const string& userName);
void viewProgress(const vector<double>& times, const vector<string>& types);
void showMotivation(double time, double previousTime, const string& userName);

// ================= MAIN =================
int main() {
    vector<double> times;
    vector<string> types;

    string userName;
    int choice;

    cout << "=====================================\n";
    cout << "   Tiana's Track Training App\n";
    cout << "   Discipline. Growth. Consistency.\n";
    cout << "=====================================\n\n";

    cout << "Enter your name: ";
    cin >> userName;

    loadFromFile(times, types);

    do {
        showMenu();

        // Input validation (professional touch)
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addWorkout(times, types, userName);
                break;

            case 2:
                viewProgress(times, types);
                break;

            case 3:
                saveToFile(times, types);
                break;

            case 4:
                cout << "\nKeep pushing forward, " << userName << "!\n";
                cout << "Success comes from consistency.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

// ================= FILE HANDLING =================
void loadFromFile(vector<double>& times, vector<string>& types) {
    ifstream file("workouts.txt");

    if (!file.is_open()) return;

    double time;
    string type;

    while (file >> type >> time) {
        types.push_back(type);
        times.push_back(time);
    }

    file.close();
}

void saveToFile(const vector<double>& times, const vector<string>& types) {
    ofstream file("workouts.txt");

    if (!file.is_open()) {
        cout << "Error: Unable to save file.\n";
        return;
    }

    for (size_t i = 0; i < times.size(); i++) {
        file << types[i] << " " << times[i] << endl;
    }

    file.close();
    cout << "Progress successfully saved.\n";
}

// ================= UI =================
void showMenu() {
    cout << "\n===== Training Menu =====\n";
    cout << "1. Add Workout\n";
    cout << "2. View Progress\n";
    cout << "3. Save Progress\n";
    cout << "4. Exit\n";
    cout << "Choice: ";
}

// ================= CORE FEATURES =================
void addWorkout(vector<double>& times, vector<string>& types, const string& userName) {
    string type;
    double time;

    cout << "Enter event (100m, 200m, etc.): ";
    cin >> type;

    cout << "Enter time (seconds): ";
    cin >> time;

    double previousTime = times.empty() ? -1 : times.back();

    types.push_back(type);
    times.push_back(time);

    cout << "\nWorkout recorded successfully.\n";

    showMotivation(time, previousTime, userName);
}

void viewProgress(const vector<double>& times, const vector<string>& types) {
    if (times.empty()) {
        cout << "No workouts recorded yet.\n";
        return;
    }

    cout << "\n--- Performance History ---\n";

    double best = times[0];
    double total = 0;

    for (size_t i = 0; i < times.size(); i++) {
        cout << i + 1 << ". " << types[i]
             << " | Time: " << times[i] << "s\n";

        if (times[i] < best)
            best = times[i];

        total += times[i];
    }

    cout << "\nAverage Time: " << total / times.size() << " seconds\n";
    cout << "Best Time: " << best << " seconds\n";
}

// ================= MOTIVATION SYSTEM =================
void showMotivation(double time, double previousTime, const string& userName) {
    cout << "\nMotivation: ";

    if (previousTime != -1) {
        if (time < previousTime) {
            cout << userName << ", you're improving. Keep going!\n";
            return;
        } else if (time > previousTime) {
            cout << userName << ", setbacks build comebacks. Stay consistent!\n";
            return;
        }
    }

    if (time < 60) {
        cout << userName << ", elite performance!\n";
    } else if (time < 120) {
        cout << userName << ", strong effort. Keep pushing!\n";
    } else {
        cout << userName << ", progress takes time. Stay committed!\n";
    }
}