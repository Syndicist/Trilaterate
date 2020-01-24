#include <math.h>
#include <iostream>
#include <fstream>
#include<iostream>
#include <string>
#include <iomanip>
using namespace std;

bool debug = false;

pair<float, float> calcTri(pair<float, float> A, float AZDist, pair<float, float> B, float BZDist, pair<float, float> C, float CZDist)
{
	pair<float, float> Z;
	pair<float, float> AZ;
	pair<float, float> BZ;
	float ABDist = sqrt(powf(A.first - B.first,2.0) + powf(A.second - B.second,2.0));
	Z.first = (powf(BZDist, 2.0) - powf(AZDist, 2.0) - powf(ABDist, 2.0)) / (2 * ABDist);
	Z.second = sqrt(powf(AZDist, 2.0) - powf(Z.first, 2.0));

	float O = atan2(A.second - B.second,A.first - B.first);
	float tempx = Z.first;
	float tempy = Z.second;
	Z.first = tempx * cos(O) - tempy * sin(O);
	Z.second = tempy * cos(O) + tempx * sin(O);
	
	Z.first += A.first;
	Z.second += A.second;
	
	float CZtest = sqrt(powf(C.first - Z.first, 2.0) + powf(C.second - Z.second, 2.0));
	if (abs(CZtest - CZDist) > 0.01)
	{
		Z.first = (powf(BZDist, 2.0) - powf(AZDist, 2.0) - powf(ABDist, 2.0)) / (2 * ABDist);
		Z.second = -sqrt(powf(AZDist, 2.0) - powf(Z.first, 2.0));

		float O = atan2(A.second - B.second, A.first - B.first);
		float tempx = Z.first;
		float tempy = Z.second;
		Z.first = tempx * cos(O) - tempy * sin(O);
		Z.second = tempy * cos(O) + tempx * sin(O);

		Z.first += A.first;
		Z.second += A.second;
	}
	return Z;
}

int main()
{
	ifstream in;
	in.open("data.txt");
	int sets; 
	pair<float, float> A;
	pair<float, float> B;
	pair<float, float> C;
	float AZDist, BZDist, CZDist;

	if(debug)
		cout << "Checking input file..." << endl;
	if (in.peek() != std::ifstream::traits_type::eof())
	{
		if (debug)
			cout << "File found!" << endl;
		in >> sets;

		for (float i = 0; i < sets; i++)
		{
			in >> A.first >> A.second >> AZDist >> B.first >> B.second >> BZDist >> C.first >> C.second >> CZDist;
			if (debug)
			{
				cout << "Data set " << i << ":" << endl;
				cout << A.first << " " << A.second << " " << AZDist << endl;
				cout << B.first << " " << B.second << " " << BZDist << endl;
				cout << C.first << " " << C.second << " " << CZDist << endl;
				cout << "Unknown Point:" << endl;
			}
			pair<float, float> Z = calcTri(A, AZDist, B, BZDist, C, CZDist);
			
			printf("%.2f %.2f\n", Z.first, Z.second);
		}
	}
	else if(debug)
		cout << "File not found!" << endl;
	in.close();
	if (debug)
		cout << "Input custom data. Enter 0 to exit." << endl;
	cin >> sets;
	if (sets == 0)
		return 0;
	for (float i = 0; i < sets; i++)
	{
		cin >> A.first >> A.second >> AZDist >> B.first >> B.second >> BZDist >> C.first >> C.second >> CZDist;
		pair<float, float> Z = calcTri(A, AZDist, B, BZDist, C, CZDist);
		cout << Z.first << " " << Z.second << endl;
	}
	return 0;
}