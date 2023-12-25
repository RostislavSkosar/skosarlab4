#pragma once
#include<string>
#include <iostream>
#include <fstream>
class Cs
{

private:
	int id = 1;
	std::string name = "None";
	int workshops = 0;
	double effect = 0;
	static int NextId;



public:


	std::string GetThePipeNameCs() const;
	static int GetNextId();
	static void SetNextId(int newNextId);


	void ChangeStatusCS(Cs& station);
	double GetPercentUnused() const;

	Cs();
	int GetId() const;
	int workshops_work = 0;
	friend std::istream& operator>>(std::istream& in, Cs& station);
	friend std::ostream& operator<< (std::ostream& out, const Cs& station);
	friend std::ofstream& operator << (std::ofstream& file, const Cs& station);
	friend std::ifstream& operator >> (std::ifstream& file, Cs& station);

}; 
