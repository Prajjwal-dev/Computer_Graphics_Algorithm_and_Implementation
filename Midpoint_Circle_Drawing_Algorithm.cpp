#include <iostream>
#include <vector>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
void delay(int ms) { Sleep(ms); }
#else
#include <unistd.h>
void delay(int ms) { usleep(ms * 1000); }
#endif

using namespace std;

// ANSI cursor movement
void moveCursor(int r, int c) {
    cout << "\033[" << r << ";" << c << "H";
}

// Filter points by selected octant
vector<pair<int,int>> filterOctant(const vector<pair<int,int>> &pts, int oct) {
    vector<pair<int,int>> res;
    for (auto &p : pts) {
        int x = p.first;
        int y = p.second;
        switch(oct) {
            case 1: if (x >= 0 && y >= 0) res.push_back(p); break;
            case 2: if (x <= 0 && y >= 0) res.push_back(p); break;
            case 3: if (x <= 0 && y <= 0) res.push_back(p); break;
            case 4: if (x >= 0 && y <= 0) res.push_back(p); break;
            case 5: if (y <= 0 && x <= 0) res.push_back(p); break;
            case 6: if (y >= 0 && x <= 0) res.push_back(p); break;
            case 7: if (y <= 0 && x >= 0) res.push_back(p); break;
            case 8: if (y >= 0 && x >= 0) res.push_back(p); break;
        }
    }
    return res;
}

int main() {
    int xc, yc, r, oct;
    cout << "Enter circle center (xc yc): ";
    cin >> xc >> yc;
    cout << "Enter radius: ";
    cin >> r;
    cout << "Enter octant (1-8) to plot: ";
    cin >> oct;

    int x = 0;
    int y = r;
    int p = 1 - r;
    int step = 0;

    vector<pair<int,int>> plottedPoints; // store all plotted points

    cout << "\nMIDPOINT CIRCLE RESULT TABLE (Octant " << oct << ")\n";
    cout << "Step\tP\tPlotted Points\n";
    cout << "------------------------------------------\n";

    while (x <= y) {
        vector<pair<int,int>> symPoints = {
            {xc + x, yc + y}, {xc - x, yc + y},
            {xc + x, yc - y}, {xc - x, yc - y},
            {xc + y, yc + x}, {xc - y, yc + x},
            {xc + y, yc - x}, {xc - y, yc - x}
        };

        vector<pair<int,int>> octPoints = filterOctant(symPoints, oct);

        plottedPoints.insert(plottedPoints.end(), octPoints.begin(), octPoints.end());

        // Print table
        cout << step << "\t" << p << "\t";
        for (auto &pt : octPoints) {
            cout << "(" << pt.first << "," << pt.second << ") ";
        }
        cout << endl;

        if (p < 0)
            p += 2 * x + 3;
        else {
            y--;
            p += 2 * (x - y) + 5;
        }
        x++;
        step++;
    }

    // -------- GRAPH SETTINGS --------
    int maxX = xc + r + 2;
    int maxY = yc + r + 2;

    cout << "\nDIGITIZED CIRCLE GRAPH (Animated, Octant " << oct << ")\n\n";

    int graphTopRow = 15 + step;

    // Draw empty graph
    for (int j = maxY; j >= 0; j--) {
        for (int i = 0; i <= maxX; i++)
            cout << ". ";
        cout << endl;
    }

    // Animate plotting
    for (auto &pt : plottedPoints) {
        int row = graphTopRow + (maxY - pt.second) + 1;
        int col = 1 + pt.first * 2;
        moveCursor(row, col);
        cout << "*";
        cout.flush();
        delay(300);
    }

    moveCursor(graphTopRow + maxY + 3, 1);
    cout << "\n* = Plotted points in selected octant\n";

    return 0;
}

