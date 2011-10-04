#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;

void printMaze(vector<string>& maze) {
    REP(i, maze.size()) {
        REP(j, maze[i].size()) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

struct State {
    int r;
    int c;
    int turn;
    State() {}
    State(int r, int c, int turn)
        : r(r), c(c), turn(turn) {}
};

bool check(vector<string>& maze, queue<State>& q, int r, int c, int turn) {
    bool isGoal = false;
    if (r >= 0 && r < maze.size() && c >= 0 && c < maze[r].size()) {
        if (maze[r][c] == 'G') {
            isGoal = true;
        } else if (maze[r][c] == '.') {
            if (turn < 10) {
                maze[r][c] = '0' + turn;
            } else {
                maze[r][c] = 'x';
            }
            State s(r, c, turn);
            q.push(s);
        }
    }
    return isGoal;
}

int solve(vector<string>& maze) {
    State state;
    state.turn = 0;
    REP(i, maze.size()) REP(j, maze[i].size())
        if (maze[i][j] == 'S') {
            state.r = i;
            state.c = j;
        }
    
    queue<State> q;
    q.push(state);

    while (!q.empty()) {
        State s = q.front();
        q.pop();

        bool isGoal = false;
        isGoal |= check(maze, q, s.r-1, s.c, s.turn+1);
        isGoal |= check(maze, q, s.r+1, s.c, s.turn+1);
        isGoal |= check(maze, q, s.r, s.c-1, s.turn+1);
        isGoal |= check(maze, q, s.r, s.c+1, s.turn+1);

        if (isGoal) return s.turn+1;
    }
    return -1;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> maze;
    string tmp;
    REP(i, N) {
        cin >> tmp;
        maze.push_back(tmp);
    }

    cout << "=== before ===" << endl;
    printMaze(maze);
    int answer = solve(maze);
    cout << "=== after ===" << endl;
    printMaze(maze);
    cout << "Answer: " << answer << endl;
}
