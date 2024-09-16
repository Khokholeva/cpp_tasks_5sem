#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct OffTheField{
	int x, y;
	string dir;
	OffTheField(int xx, int yy, int dd): x(xx), y(yy) {
		if (dd == 1) {
			dir = "right";
		}
		if (dd == 2) {
			dir = "up";
		}
		if (dd == 3) {
			dir = "left";
		}
		if (dd == 4) {
			dir = "down";
		}
	}
	
};
struct IllegalCommand {
	int x, y, dir;
	IllegalCommand(int xx, int yy, int dd): x(xx), y(yy),  dir(dd){}
};

struct Robot {
	int x, y;
	Robot(int xx = 1, int yy = 1): x(xx), y(yy){}
	void move(int dir) {
		if (dir == 1) {
			if (x > 9) throw(OffTheField(x, y, dir));
			x++;
		}
		else if (dir == 2) {
			if (y > 9) throw(OffTheField(x, y, dir));
			y++;
		}
		else if (dir == 3) {
			if (x < 2) throw(OffTheField(x, y, dir));
			x--;
		}
		else if (dir == 4) {
			if (y < 2) throw(OffTheField(x, y, dir));
			y--;
		}
		else throw IllegalCommand(x, y, dir);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Robot r;
	int dir;
	while (true) {
		cin >> dir;
		try {
			r.move(dir);
		}
		catch (OffTheField e) {
			cerr << "Error: Destination out of bounds: Position (" << e.x << ", " << e.y << "), trying to go " << e.dir << endl;
		}
		catch (IllegalCommand e) {
			cerr << "Error: Not a valid command: Position (" << e.x << ", " << e.y << "), used command " << e.dir << endl;
		}
	}

	return EXIT_SUCCESS;
}
