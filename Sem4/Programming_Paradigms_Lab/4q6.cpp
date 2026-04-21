#include <iostream>
#include <string>

using namespace std;

class Cricketer {
protected:
    string name;
    int age;
public:
    void setBasicInfo(string n, int a) {
        name = n;
        age = a;
    }
};

class Batsman : virtual public Cricketer {
protected:
    int runs[100];
    string batOpponent[100];
    int matchCount;
public:
    Batsman() : matchCount(0) {}
};

class Bowler : virtual public Cricketer {
protected:
    int wickets[100];
    string bowlOpponent[100];
    int bowlMatchCount;
public:
    Bowler() : bowlMatchCount(0) {}
};

class AllRounder : public Batsman, public Bowler {
public:
    void insertBattingRecord(int r, string opp) {
        if (matchCount < 100) {
            runs[matchCount] = r;
            batOpponent[matchCount] = opp;
            matchCount++;
        }
    }

    void insertBowlingRecord(int w, string opp) {
        if (bowlMatchCount < 100) {
            wickets[bowlMatchCount] = w;
            bowlOpponent[bowlMatchCount] = opp;
            bowlMatchCount++;
        }
    }

    double countBattingAverage() {
        if (matchCount == 0) return 0;
        int total = 0;
        for (int i = 0; i < matchCount; i++) {
            total += runs[i];
        }
        return (double)total / matchCount;
    }

    int countTotalWickets() {
        int total = 0;
        for (int i = 0; i < bowlMatchCount; i++) {
            total += wickets[i];
        }
        return total;
    }

    void findHighestWickets() {
        if (bowlMatchCount == 0) return;
        int maxW = wickets[0];
        string opp = bowlOpponent[0];
        for (int i = 1; i < bowlMatchCount; i++) {
            if (wickets[i] > maxW) {
                maxW = wickets[i];
                opp = bowlOpponent[i];
            }
        }
        cout << "Highest Wickets: " << maxW << " against " << opp << endl;
    }

    void findHighestRuns() {
        if (matchCount == 0) return;
        int maxR = runs[0];
        string opp = batOpponent[0];
        for (int i = 1; i < matchCount; i++) {
            if (runs[i] > maxR) {
                maxR = runs[i];
                opp = batOpponent[i];
            }
        }
        cout << "Highest Runs: " << maxR << " against " << opp << endl;
    }

    void displayProfile() {
        cout << "\nPlayer: " << name << endl;
        cout << "Batting Average: " << countBattingAverage() << endl;
        cout << "Total Wickets: " << countTotalWickets() << endl;
        findHighestRuns();
        findHighestWickets();
    }
};

int main() {
    AllRounder player;
    player.setBasicInfo("Hardik Pandya", 30);

    player.insertBattingRecord(50, "Australia");
    player.insertBattingRecord(85, "Pakistan");
    player.insertBattingRecord(30, "England");

    player.insertBowlingRecord(3, "Australia");
    player.insertBowlingRecord(5, "South Africa");

    player.displayProfile();

    return 0;
}