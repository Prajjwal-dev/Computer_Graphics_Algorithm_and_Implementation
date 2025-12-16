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

int main() {
    int x1, y1, x2, y2;

    cout << "Enter start point (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter end point (x2 y2): ";
    cin >> x2 >> y2;

    // Ensure left-to-right drawing
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    int p = 2 * dy - dx;

    vector<int> px, py, pval;

    int x = x1;
    int y = y1;

    // -------- RESULT TABLE --------
    cout << "\nBRESENHAM RESULT TABLE\n";
    cout << "Step\tP\tPlotted Pixel\n";
    cout << "-----------------------------\n";

    for (int i = 0; i <= dx; i++) {
        px.push_back(x);
        py.push_back(y);
        pval.push_back(p);

        cout << i << "\t" << p << "\t(" << x << ", " << y << ")\n";

        x++;
        if (p < 0) {
            p += 2 * dy;
        } else {
            y += yi;
            p += 2 * (dy - dx);
        }
    }

    // -------- GRAPH SETTINGS --------
    int maxX = max(x1, x2) + 2;
    int maxY = max(y1, y2) + 2;

    cout << "\nDIGITIZED GRAPH (Animated)\n\n";

    int graphTopRow = 10 + dx;

    // Draw empty graph
    for (int j = maxY; j >= 0; j--) {
        for (int i = 0; i <= maxX; i++)
            cout << ". ";
        cout << endl;
    }

    // -------- GRAPH ANIMATION --------
    for (int k = 0; k < px.size(); k++) {
        int row = graphTopRow + (maxY - py[k]) + 1; // FIXED mapping
        int col = 1 + px[k] * 2;

        moveCursor(row, col);
        cout << "*";
        cout.flush();

        delay(400);
    }

    moveCursor(graphTopRow + maxY + 3, 1);
    cout << "\n* = Bresenham plotted points\n";

    return 0;
}

