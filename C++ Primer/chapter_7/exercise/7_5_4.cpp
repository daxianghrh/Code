#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    Point(int x=0, int y=0 )
        : x(x), y(y) {}
};

void displayPoint(const Point& p) 
{
    cout << "(" << p.x << "," 
         << p.y << ")" << endl;
}

int main()
{
    displayPoint(1);
    //Point p = 1;
}