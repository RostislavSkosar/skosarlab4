#include "Cs.h"
#include "utils.h"
using namespace std;

int Cs::GetNextId() {
	return NextId;
}
void Cs::SetNextId(int newNextId) {
	NextId = newNextId;
}
int Cs::GetId()const { return id; }
int Cs::NextId = 0;
Cs::Cs() {
	id = ++NextId;
}



istream& operator>>(istream& in, Cs& station)
{
	cout << "Enter the name of the compressor station : ";
	INPUT_LINE(in, station.name);
	cout << "Enter the number of workshops at the station : ";
	station.workshops = GetCorrectNumber(0, 100000);
	cout << "Enter the number of workshops in operation: ";
	station.workshops_work = GetCorrectNumber(0, station.workshops);
	cout << "Enter effect:";
	station.effect = GetCorrectNumber(0.00, 100.00);
	return in;
};

ostream& operator <<(ostream& out, const  Cs& station) {
	PRINT_PARAM(cout, station.id);
	PRINT_PARAM(cout, station.name);
	PRINT_PARAM(cout, station.workshops);
	PRINT_PARAM(cout, station.workshops_work);
	PRINT_PARAM(cout, station.effect);
	return out;
}
ofstream& operator << (ofstream& file, const Cs& station) {
	file << station.id << endl;
	file << station.name << endl;
	file << station.workshops << endl;
	file << station.workshops_work << endl;
	file << station.effect << endl;
	return file;
}
ifstream& operator >> (ifstream& file, Cs& station) {
	file >> station.id;
	file >> ws;
	getline(file, station.name);
	file >> station.workshops;
	file >> station.workshops_work;
	file >> station.effect;
	Cs::NextId = (Cs::NextId < station.id) ? station.id : Cs::NextId;
	return file;
}



void Cs::ChangeStatusCS(Cs& station) {
	cout << "Number of workshops in operation:" << endl;
	workshops_work = GetCorrectNumber(0, workshops);
}


std::string Cs::GetThePipeNameCs() const
{
	return name;
}

double Cs::GetPercentUnused() const
{
	return 100.0 - double((+workshops_work / workshops) * 100);
}