#include "Pipe.h"
#include "utils.h"
using namespace std;

int Pipe::pipe_diameters[] = { 500, 700, 1000, 1400 };
int Pipe::NextId = 0;
int Pipe::EnterCorrectDiameter()
{
	cout << "Diameter (500, 700, 1000, 1400 mm): ";
	int diameter = GetCorrectNumber(1, INT_MAX);
	while (!count(begin(pipe_diameters), end(pipe_diameters), diameter)) {
		cout << "Enter the correct diameter (500, 700, 1000, 1400 mm): ";
		diameter = GetCorrectNumber(1, INT_MAX);
	}
	return diameter;
}
void Pipe::ChangeStatus(Pipe& pipe) {
	pipe.repair = !pipe.repair;

}
int Pipe::GetNextId() {
	return NextId;
}
std::string Pipe::GetThePipeName() const
{
	return name;
}
int Pipe::GetDiameter() const
{
	return diametr;
}
double Pipe::GetLength() const
{
	return status ? lenght : DBL_MAX;
}
int Pipe::GetId()const { return id; }
void Pipe::SetDiameter(int d)
{
	diametr = d;
}
string Pipe::PrintStatus() const
{
	return status ? "In repair" : "In Working condition";

}
double Pipe::GetCapacity() const
{
	return status ? lenght : 0;
}
Pipe::Pipe() {
	id =++ NextId;
}


bool Pipe::ReturningThePipeRepair() const
{
	return repair;
}

istream& operator>>(istream& in, Pipe& p)
{
	cout << "Enter the name of the pipe: ";
	INPUT_LINE(in, p.name);
	cout << "Enter the length of the pipe (in kilometers):";
	p.lenght = GetCorrectNumber(1.00, 500.00);
	if (p.diametr == 0) {
		cout << "Enter the diameter of the pipe: ";
		p.diametr = GetCorrectNumber(1, 1000);
	}

	/*p.diametr = p.EnterCorrectDiameter();*/

	cout << "Enter the value for pipe repair (0 - not under repair, 1 - under repair): ";
	p.repair = GetCorrectNumber(0, 1);
	return in;
}
ostream& operator <<(ostream& out, const Pipe& pipe) {
	PRINT_PARAM(cout, pipe.id);
	PRINT_PARAM(cout, pipe.name);
	PRINT_PARAM(cout, pipe.lenght);
	PRINT_PARAM(cout, pipe.diametr);
	PRINT_PARAM(cout, (pipe.repair ? "in repair" : " not in repair"));
	return out;
}
ofstream& operator << (ofstream& file, const Pipe& pipe) {
	file << pipe.id << endl;
	file << pipe.name << endl;
	file << pipe.lenght << endl;
	file << pipe.diametr << endl;
	file << pipe.repair << endl;
	return file;
}
ifstream& operator >> (ifstream& file, Pipe& pipe) {
	Pipe::NextId = 1;
	file >> pipe.id;
	file >> ws;
	getline(file, pipe.name);
	file >> pipe.lenght;
	file >> pipe.diametr;
	file >> pipe.repair;
	Pipe::NextId = (Pipe::NextId < pipe.id) ? pipe.id : Pipe::NextId;
	return file;
}