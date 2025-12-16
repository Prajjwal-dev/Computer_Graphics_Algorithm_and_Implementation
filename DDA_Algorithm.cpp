#include <iostream>
#include <cmath>
#include <vector>

#ifdef _WIN32
#include <windows.h>
void delay(int ms) { Sleep(ms); }
#else
#include <unistd.h>
void delay(int ms) { usleep(ms * 1000); }
#endif

using namespace std;

// Move cursor (ANSI)
void moveCursor(int r, int c) {
    cout << "\033[" << r << ";" << c << "H";
}

int main() {
    int x1, y1, x2, y2;

    cout << "Enter start point (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter end point (x2 y2): ";
    cin >> x2 >> y2;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1, y = y1;
    vector<int> px, py;

    // -------- RESULT TABLE --------
    cout << "\nDDA RESULT TABLE\n";
    cout << "Step\tX\tY\tPlotted Pixel\n";
    cout << "---------------------------------\n";

    for (int i = 0; i <= steps; i++) {
        px.push_back(round(x));
        py.push_back(round(y));

        cout << i << "\t"
             << x << "\t"
             << y << "\t("
             << round(x) << ", "
             << round(y) << ")\n";

        x += xInc;
        y += yInc;
    }

    // -------- GRAPH SETTINGS --------
    int maxX = max(x1, x2) + 2;
    int maxY = max(y1, y2) + 2;

    int graphTopRow;
    cout << "\nDIGITIZED GRAPH (Animated)\n\n";

    // Save graph top position
    graphTopRow = 10 + steps;

    // Draw empty graph
    for (int j = maxY; j >= 0; j--) {
        for (int i = 0; i <= maxX; i++)
            cout << ". ";
        cout << endl;
    }

    // -------- ANIMATION --------
    for (int k = 0; k < px.size(); k++) {
        int row = graphTopRow + (maxY - py[k]) + 1;
        int col = 1 + px[k] * 2;

        moveCursor(row, col);
        cout << "*";
        cout.flush();

        delay(400);
    }

    moveCursor(graphTopRow + maxY + 2, 1);
    cout << "\n* = DDA plotted points\n";

    return 0;
}

