//
// Created by rjx on 16-11-17.
//
#include <iostream>
#include "MatrixG.cpp"
#include "ListG.cpp"


bool MatrixTest(MatrixG & mg) {
	cout << "Detect your operation: 1.insert a point 2.Build an edge 3.travel the graph 4.exit:";
	int op;
	cin >> op;
	switch(op) {
		case 1:
		{
			Point p;
			cout << "Input the point data:"; string data; cin >> data; p.setData(data); mg.addPoint(p);
		}
		return true;
		case 2:
		{
			cout << "Input the two points data:\n";
			cout << "Point1 data :"; string data1; cin >> data1;
			cout << "POint2 data :"; string data2; cin >> data2;
			mg.createrAnEdge(data1, data2);
		}
		return true;
		case 3:
		{
			cout << "Select the method of travel: (B) => BFS , (D) => DFS :";
			string m; cin >> m;
			if (m == "B") {
				mg.travel("B");
				cout << endl;
			} else if (m == "D") {
				mg.travel("D");
				cout << endl;
			} else {
				cout << "Invaild input\n";
			}
		}
		return true;
		case 4:
		return false;
		default:
		cout << "Invaild input\n";
		return true;
	}
}
bool ListGTest(ListG & lg) {
	cout << "Detect your operation: 1.insert a point 2.Build an edge 3.travel the graph 4.exit:";
	int op;
	cin >> op;
	switch(op) {
		case 1:
		{
			Point p;
			cout << "Input the point data:"; string data; cin >> data; p.setData(data); lg.addPoint(p);
		}
		return true;
		case 2:
		{
			cout << "Input the two points data:\n";
			cout << "Point1 data :"; string data1; cin >> data1;
			cout << "POint2 data :"; string data2; cin >> data2;
			lg.createrAnEdge(data1, data2);
		}
		return true;
		case 3:
		{
			cout << "Select the method of travel: (B) => BFS , (D) => DFS :";
			string m; cin >> m;
			if (m == "B") {
				lg.travel("B");
				cout << endl;
			} else if (m == "D") {
				lg.travel("D");
				cout << endl;
			} else {
				cout << "Invaild input\n";
			}
		}
		return true;
		case 4:
		return false;
		default:
		cout << "Invaild input\n";
		return true;
	}
}
void testStart() {
	int op = 2;
	cout << "Select the buiid form : 1.Matrix 2.List 3.exit";
	cin >> op;
	switch (op) {
		case 1:
		{		MatrixG mg;
			cout << "Start test Matrixed Graph\n";
			while (MatrixTest(mg));
			cout << "MatrixG test end\n";
		}
		testStart();
		break;
		case 2:
		{		ListG lg;
			cout << "Start test Listed Graph\n";
			while (ListGTest(lg));
			cout << "Listed graph end\n";
		}
		testStart();
		break;
		case 3:
		cout << "All test end!!!\n\n";
		return;
		default:
		cout << "Invaild input\n";
		testStart();
	}
}
int main(int argc, char const *argv[])
{
	testStart();
	return 0;
}