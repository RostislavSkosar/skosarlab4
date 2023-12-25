#include "GasTransportationSystem.h"

using namespace std;
void GasTransportationSystem::Show()
{
	Show(GetPipes());
	Show(GetCS());
	ShowConnections();
}

bool CheckByDiameters(const Pipe& p, int param)
{
	return p.GetDiameter() == param;
}
Pipe GasTransportationSystem::AddPipe(int diameter)
{
	Pipe p;
	p.SetDiameter(diameter);
	cin >> p;
	pipe_map.insert({ p.GetId(), p });
	return p;
}


void GasTransportationSystem::ShowConnections()
{
	if (ObjectsExist(connections)) {
		for (auto& [id_pipe, edge] : connections) {
			cout << "id pipe " << id_pipe << " | " << "id station(out) "
				<< cs_map.at(edge.id_out).GetId() << "   ->  id station (in)  "
				<< cs_map.at(edge.id_in).GetId() << "\n";
		}
		cout << "\n";
	}
	else
		cout << "Not connections!\n\n";
}
void GasTransportationSystem::ConnectStations(int id_out, int id_in, int id_pipe)
{
	if (cs_map.contains(id_out) && cs_map.contains(id_in))
	{
		Edge edge(id_out, id_in);
		connections.insert({ id_pipe, edge });
		cout << "Stations are connected!\n";
	}
	else
		cout << "Stations with this IDs not found\n";
}





vector<int> GasTransportationSystem::TopologicalSorting()
{
	Graph graph = InitGraph();
	vector<int> result;
	result.reserve(cs_map.size());
	if (graph.isDAG())
		result = graph.TopologicalSorting();
	return result;

}
unordered_map<int, double> GasTransportationSystem::ShortestDistance(int id_cs)
{
	Graph graph(cs_map, pipe_map, connections);
	return graph.Dijkstra(id_cs);
}


Graph GasTransportationSystem::InitGraph()
{
	Graph graph(cs_map, pipe_map, connections);
	return graph;
}


bool GasTransportationSystem::IsPipeObjectsEmpty()
{
	if (pipe_map.size() == 0) {
		cout << "System has no pipes!\n";
		return true;
	}
	return false;
}

bool GasTransportationSystem::IsCSObjectsEmpty()
{
	if (cs_map.size() == 0) {
		cout << "System has no stations!\n";
		return true;
	}
	return false;
}
bool GasTransportationSystem::PipeExist(int id_pipe)
{
	if (pipe_map.contains(id_pipe))
		return true;
	return false;
}

bool GasTransportationSystem::CSExist(int id_cs)
{
	if (cs_map.contains(id_cs)) 
		return true;
	cout << "Station not found!\n";
	return false;
}

bool GasTransportationSystem::IsPipeConnected(int id_pipe)
{
	if (connections.contains(id_pipe))
		return true;
	return false;
}

bool GasTransportationSystem::IsCSConnected(int id_cs)
{
	for (auto& [id, edge] : connections) {
		if (edge.id_in == id_cs || edge.id_out == id_cs)
			return true;
	}
	return false;
}


void GasTransportationSystem::Writing_to_file() {
	ofstream file;
	cout << "Enter the file name: ";
	string line;
	INPUT_LINE(cin, line);
	file.open(line);
	if (!file)
		cout << "file is not found" << endl;
	else {
		file << pipe_map.size() << " " << cs_map.size() << " " << connections.size() << endl;
		for (const auto& [key, pipe] : pipe_map) {
			file << pipe;
		}
		for (const auto& [key, station] : cs_map) {
			file << station;
		}
		for (const auto& [key, edge] : connections) {
			file << key << "\n";
			file << edge.id_out << "\n";
			file << edge.id_in << "\n";
		}
	}

	file.close();
}

void GasTransportationSystem::Read_from_file() {
	cout << "Enter the file name: ";
	string line;
	INPUT_LINE(cin, line);
	ifstream file;
	file.open(line);
	pipe_map.clear();
	cs_map.clear();
	int num_pipe;
	int num_cs;
	int num_edges;
	int id_pipe;
	Edge edge(0, 0);
	Pipe p;
	Cs cs;

	if (file) {
		file >> num_pipe >> num_cs >> num_edges;
		for (int i = 0; i < num_pipe; i++) {
			file >> p;
			pipe_map.insert({ p.GetId(), p });
		}
		for (int i = 0; i < num_cs; i++) {
			file >> cs;
			cs_map.insert({ cs.GetId(), cs });
		}
		for (int i = 0; i < num_edges; i++) {
			file >> id_pipe;
			file >> edge.id_out;
			file >> edge.id_in;
			connections.insert({ id_pipe, edge });
		}
	}
	else {
		cout << "File is not found\n";
	}
}


unordered_set<int> GetEditNumbers(unordered_set<int>& result)
{
	unordered_set<int> IDs;
	int id;
	int Max_ID = Pipe::GetNextId();
	do {
		id = GetCorrectNumber(0, Max_ID);
		if (result.contains(id)) {
			IDs.insert(id);
		}
	} while (id != 0);

	return IDs;
}

unordered_set<int> GetEditNumberss(unordered_set<int>& result)
{
	unordered_set<int> IDs;
	int id;
	int Max_ID = Cs::GetNextId();
	do {
		id = GetCorrectNumber(0, Max_ID);
		if (result.contains(id)) {
			IDs.insert(id);
		}
	} while (id != 0);

	return IDs;
}
///
unordered_set<int> GasTransportationSystem::SearchFreePipesByDiameters(int diameter)
{
	unordered_set<int> found_pipes;
	for (auto& id_pipe : FindByFilter(pipe_map, CheckByDiameters, diameter)) {
		if (!connections.contains(id_pipe))
			found_pipes.insert(id_pipe);
	}

	return found_pipes;
}
/// 
void EditOnePipe(unordered_map<int, Pipe>& pipe_map) {
	cout << "Enter ID of pipe (1 - " << Pipe::GetNextId() << "): ";
	int id = GetCorrectNumber(0, Pipe::GetNextId());
	if (pipe_map.count(id) != 0) {
		pipe_map[id].ChangeStatus(pipe_map[id]);
		cout << "Status was changed!\n";
	}
	else
		cout << "Pipe with this ID has not found\n";
}
bool CheckName(const Pipe& p, std::string param)
{
	return (p.GetThePipeName().find(param) != std::string::npos);
}
bool ChekByStatus(const Pipe& p, bool param) {
	return (p.ReturningThePipeRepair() == param);
}

bool CheckBySetSize(const std::unordered_set<int>& id_set) {
	if (id_set.size() == 0) {
		std::cout << "Not obects\n";
		return false;
	}
	return true;
}
void ShowObjects(std::unordered_map<int, Pipe>& pipe_map, std::unordered_set<int>& id_set) {
	for (auto& id : id_set) {
		std::cout << pipe_map[id];
	}
}
void EditPipes(std::unordered_map<int, Pipe>& pipe_map, std::unordered_set<int>& id_set)
{
	ShowObjects(pipe_map, id_set);
	cout << "enter 0 if you want to change all pipes or enter the necessary ids in order, enter 0 to finish" << endl;
	unordered_set<int> numbers = GetEditNumbers(id_set);
	MenuEditByFilter();
	switch (GetCorrectNumber(0, 3))
	{
	case 1:
	{
		for (auto& id : numbers) {
			pipe_map[id].ChangeStatus(pipe_map[id]);
		}
		std::cout << "Status was changed!\n";
		break;
	}
	case 2:
	{
		for (auto& id : numbers) {
			if ((pipe_map[id]).repair == false)
				pipe_map[id].ChangeStatus(pipe_map[id]);
		}
		std::cout << "Status was changed!\n";
		break;
	}
	case 3:
	{
		for (auto& id : numbers) {
			if ((pipe_map[id]).repair == true)
				pipe_map[id].ChangeStatus(pipe_map[id]);
		}
		std::cout << "Status was changed!\n";
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void EditPackagePipe(unordered_map<int, Pipe>& pipe_map) {
	MenuEditPackageP();
	switch (GetCorrectNumber(0, 2))
	{
	case 1:
	{
		cout << "Enter name of pipe: ";
		unordered_set id_set = FindByFilter(pipe_map, CheckName, EnterLine());
		if (CheckBySetSize(id_set))

			EditPipes(pipe_map, id_set);
		break;
	}
	case 2:
	{
		cout << "Enter the value for pipe repair (0 - not under repair, 1 - under repair): ";
		unordered_set<int> id_set = FindByFilter(pipe_map, ChekByStatus, bool(GetCorrectNumber(0, 1)));
		if (CheckBySetSize(id_set))
			EditPipes(pipe_map, id_set);
		break;
	}
	case 0:
	{
		break;
	}
	default:
		cout << "Wrong action" << "\n";
		break;
	}
}

void EditAllPipes(std::unordered_map<int, Pipe>& pipe_map)
{
	std::unordered_set<int> id_set;
	for (auto& [key, value] : pipe_map) {
		id_set.insert(key);
	}
	EditPipes(pipe_map, id_set);
}


void DeletePipe(std::unordered_map<int, Pipe>& pipe_map, std::unordered_map<int, Edge>& connections) {
	std::cout << "Enter ID of pipe (1 - " << Pipe::GetNextId() << "): ";
	int id = GetCorrectNumber(0, Pipe::GetNextId());
	if (pipe_map.count(id) != 0) {
		pipe_map.erase(id);
		connections.erase(id);
		std::cout << "Pipe was deleted!\n";
	}
	else
		std::cout << "Pipe with this ID has not found\n";
}
void GasTransportationSystem::EditPipe()
{
	if (pipe_map.size() != 0) {
		Show(pipe_map);
		MenuEditPipe();
		switch (GetCorrectNumber(0, 4))
		{
		case 1:
		{
			EditOnePipe(pipe_map);
			break;
		}
		case 2:
		{
			EditPackagePipe(pipe_map);
			break;
		}
		case 3:
		{
			EditAllPipes(pipe_map);
			break;
		}
		case 4:
		{
			DeletePipe(pipe_map, connections);
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}
	}
	else
		cout << "Currently, the system has not pipes!\n";
}



bool CheckCSName(const Cs& cs, std::string name)
{
	return (cs.GetThePipeNameCs().find(name) != std::string::npos);
}

bool CheckUnworking(const Cs& cs, double p) {
	return (cs.GetPercentUnused() >= p);
}

void ShowObjectsCS(std::unordered_map<int, Cs>& cs_map, std::unordered_set<int>& id_set) {
	for (auto& id : id_set) {
		std::cout << cs_map[id];
	}
}


void EditOneCS(unordered_map<int, Cs>& cs_map) {
	cout << "Enter ID of cs (1 - " << Cs::GetNextId() << "): ";
	int id = GetCorrectNumber(0, Cs::GetNextId());
	if (cs_map.count(id) != 0) {
		cs_map[id].ChangeStatusCS(cs_map[id]);
		cout << "Status was changed!\n";
	}
	else
		cout << "Cs with this ID has not found\n";
}

void EditCss(std::unordered_map<int, Cs>& cs_map, std::unordered_set<int>& id_set)
{
	ShowObjectsCS(cs_map, id_set);
	cout << "enter the necessary ids in order, enter 0 to finish" << endl;
	unordered_set<int> numberss = GetEditNumberss(id_set);
	for (auto& id : numberss)
		if (cs_map.find(id) != cs_map.end()) {
			cs_map[id].ChangeStatusCS(cs_map[id]);
			std::cout << "The number of working shops of the compressor station has been changed\n";
		}
}



void EditPackageCS(unordered_map<int, Cs>& cs_map) {
	MenuEditPackageP();
	switch (GetCorrectNumber(0, 2))
	{
	case 1:
	{
		cout << "Enter name of cs: ";
		unordered_set id_set = FindByFilter(cs_map, CheckCSName, EnterLine());
		if (CheckBySetSize(id_set))
			EditCss(cs_map, id_set);
		break;
	}
	case 2:
	{
		cout << "Enter procent ";
		unordered_set<int> id_set = FindByFilter(cs_map, CheckUnworking, double(GetCorrectNumber(0.0, 100.0)));
		if (CheckBySetSize(id_set))
			EditCss(cs_map, id_set);
		break;
	}
	case 0:
	{
		break;
	}
	default:
		cout << "Wrong action" << "\n";
		break;
	}
}

void EditAllCS(std::unordered_map<int, Cs>& cs_map)
{
	std::unordered_set<int> id_set;
	for (auto& [key, value] : cs_map) {
		id_set.insert(key);
	}
	EditCss(cs_map, id_set);
}


void DeleteCS(std::unordered_map<int, Cs>& cs_map, std::unordered_map<int, Edge>& connections) {
	std::cout << "Enter ID of CS (1 - " << Cs::GetNextId() << "): ";
	int id = GetCorrectNumber(0, Cs::GetNextId());
	if (cs_map.count(id) != 0) {
		//cs_map.erase(id);
		vector<int> id_pipes;
		for (auto& [id_pipe, edge] : connections) {
			if (edge.id_in == id || edge.id_out == id)
				id_pipes.push_back(id_pipe);
		}

		for (int i = 0; i < id_pipes.size(); ++i)
			connections.erase(id_pipes[i]);
		std::cout << "CS was deleted!\n";
		cs_map.erase(id);
	}
	else
		std::cout << "CS with this ID has not found\n";
}



void GasTransportationSystem::EditCS()
{
	if (cs_map.size() != 0) {
		MenuEditStation();
		switch (GetCorrectNumber(0, 4)) {
		case 1:
		{
			EditOneCS(cs_map);
			break;
		}
		case 2:
		{
			EditPackageCS(cs_map);
			break;
		}
		case 3:
		{
			EditAllCS(cs_map);
			break;
		}
		case 4:
		{
			DeleteCS(cs_map, connections);
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}

	}
	else
		std::cout << "Currently, the system has not CS!\n";
}
void EnteringIDs(int& id_out, int& id_in)
{
	cout << "Enter id first station: ";
	id_out = GetCorrectNumber(1, INT_MAX);
	cout << "Enter id second station: ";
	id_in = GetCorrectNumber(1, INT_MAX);

	while (id_out == id_in) {
		cout << "IDs match! Enter IDs again\n";
		cout << "Enter id first station: ";
		id_out = GetCorrectNumber(1, INT_MAX);
		cout << "Enter id second station: ";
		id_in = GetCorrectNumber(1, INT_MAX);
	}
}
int EnterPipesID()
{
	cout << "Enter ID of pipe: ";
	return GetCorrectNumber(1, INT_MAX);
}
int EnterStationsID()
{
	cout << "Enter ID of cs: ";
	return GetCorrectNumber(1, INT_MAX);
}
void GasTransportationSystem::DeleteConnection(int id_pipe) {

	if (connections.contains(id_pipe)) {
		connections.erase(id_pipe);
		cout << "Connection was deleted\n";

	}
	else
		cout << "Connection not found!\n";

}
void OutputDistance(unordered_map<int, double>& distances, int id_second_cs)
{
	if (distances.at(id_second_cs) == DBL_MAX)
		cout << "no way\n";
	else
		cout << distances.at(id_second_cs) << "\n";
}
void GasTransportationSystem::ViewShortestDistance()
{
	Graph graph = InitGraph();
	cout << "Enter the id station you want to search from: ";
	int id_first_cs = GetCorrectNumber(1, INT_MAX);
	if (IsCSConnected(id_first_cs)) {
		unordered_map<int, double> found_distances = graph.Dijkstra(id_first_cs);
		cout << "Distance to one station or for all? (\"1\" - one, \"0\" - all): ";
		if (GetCorrectNumber(0, 1)) {
			int id_second_cs = EnterStationsID();
			if (IsCSConnected(id_second_cs)) {
				cout << "Distance to the station " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);



			}

		}
		else {
			for (auto& [id_second_cs, dist] : found_distances) {
				cout << "Distance to the station " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);

			}
		}

	}
	else
		cout << "Station not in graph!\n";
}

void GasTransportationSystem::MaxFlow()
{
	Graph graph = InitGraph();
	int id_out, id_in;
	EnteringIDs(id_out, id_in);
	if (IsCSConnected(id_out) && IsPipeConnected(id_in))
	{
		cout << "Maximum flow from station " << id_out << " to "
			<< "station " << id_in << ": " << graph.FordFulkerson(id_out, id_in) << "\n";
	}

}
void GasTransportationSystem::ConnectingStations()
{
	MenuConnectingStations();
	switch (GetCorrectNumber(0, 4))
	{
	case 1:
	{
		Show(pipe_map);
		Show(cs_map);
		ShowConnections();
		int id_out;
		int id_in;
		EnteringIDs(id_out, id_in);
		int diameter = Pipe::EnterCorrectDiameter();
		unordered_set<int> found_pipes = SearchFreePipesByDiameters(diameter);

		if (ObjectsExist(found_pipes)) {
			int id_pipe = EnterPipesID();
			if (found_pipes.contains(id_pipe))
				ConnectStations(id_out, id_in, id_pipe);
			else
				cout << "Pipe with this id is not in the found pipes!\n";
		}
		else {
			cout << "There are no free pipes with this id!\n" <<
				"Want to create (\"1\" - yes, \"0\" - no)?: ";
			if (GetCorrectNumber(0, 1)) {
				Pipe p = AddPipe(diameter);
				ConnectStations(id_out, id_in, p.GetId());
			}

		}
		break;
	}
	case 2:
	{
		TopologicalSorting();
		break;
	}
	case 3:
	{
		DeleteConnection(EnterPipesID());

	}
	case 4:
	{
		vector<int> result = TopologicalSorting();
		if (ObjectsExist(result))
		{
			cout << "Topological Sorting: ";
			for (auto& id_cs : result)
				cout << id_cs << ", ";
			cout << "\n";
		}
		else
		{
			cout << "Topological sorting is not possible. There are cycles!\n";
		}
		break;

	}
	case 0:
	{

		break;
	}
	default:
		break;
	}


}


std::unordered_map<int, Pipe>& GasTransportationSystem::GetPipes()
{
	return pipe_map;
}


std::unordered_map<int, Cs>& GasTransportationSystem::GetCS()
{
	return cs_map;
}