#include <iostream>
#include <vector>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
void delay(int ms) { Sleep(ms); }
#else
#include <unistd.h>
void delay(int ms) { usleep(ms*1000); }
#endif

using namespace std;

void moveCursor(int r, int c) {
    cout << "\033[" << r << ";" << c << "H";
}

int main() {
    int xc, yc, rx, ry;
    cout << "Enter ellipse center (xc yc): ";
    cin >> xc >> yc;
    cout << "Enter radius along x-axis (rx): ";
    cin >> rx;
    cout << "Enter radius along y-axis (ry): ";
    cin >> ry;

    vector<pair<int,int>> plottedPoints;
    int step = 0;

    cout << "\nMIDPOINT ELLIPSE RESULT TABLE\n";
    cout << "Step\tDecisionParam\tPlotted Points\n";
    cout << "------------------------------------------\n";

    int x = 0;
    int y = ry;
    double rx2 = rx*rx;
    double ry2 = ry*ry;

    // Decision param for region 1
    double p1 = ry2 - (rx2*ry) + 0.25*rx2;

    // Region 1
    while (2*ry2*x < 2*rx2*y) {
        vector<pair<int,int>> sym = {
            {xc+x, yc+y}, {xc-x, yc+y}, {xc+x, yc-y}, {xc-x, yc-y}
        };
        plottedPoints.insert(plottedPoints.end(), sym.begin(), sym.end());

        cout << step << "\t" << p1 << "\t";
        for (auto &pt : sym) cout << "(" << pt.first << "," << pt.second << ") ";
        cout << endl;

        if (p1 < 0)
            p1 += 2*ry2*x + 3*ry2;
        else {
            y--;
            p1 += 2*ry2*x - 2*rx2*y + 3*ry2;
        }
        x++;
        step++;
    }

    // Decision param for region 2
    double p2 = ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2;

    // Region 2
    while (y >= 0) {
        vector<pair<int,int>> sym = {
            {xc+x, yc+y}, {xc-x, yc+y}, {xc+x, yc-y}, {xc-x, yc-y}
        };
        plottedPoints.insert(plottedPoints.end(), sym.begin(), sym.end());

        cout << step << "\t" << p2 << "\t";
        for (auto &pt : sym) cout << "(" << pt.first << "," << pt.second << ") ";
        cout << endl;

        if (p2 > 0)
            p2 -= 2*rx2*y + rx2;
        else {
            x++;
            y--;
            p2 += 2*ry2*x - 2*rx2*y + rx2;
        }
        step++;
    }

    // -------- GRAPH --------
    int maxX = xc + rx + 2;
    int maxY = yc + ry + 2;
    cout << "\nDIGITIZED ELLIPSE GRAPH (Animated)\n\n";

    int graphTopRow = 15 + step;

    // Draw empty graph
    for (int j=maxY; j>=0; j--) {
        for (int i=0; i<=maxX; i++) cout << ". ";
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
    cout << "\n* = Plotted ellipse points\n";

    return 0;
}

