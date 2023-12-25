#pragma once
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pipe.h"
#include "Cs.h"
#include "utils.h"
#include "Graph.h"
class Graph;
struct Edge
{
	int id_out;
	int id_in;
	Edge(int out, int in) {
		id_out = out;
		id_in = in;
	}
};

class GasTransportationSystem
{
public:

	template <typename T>
	void Add(std::unordered_map<int, T>& map);
	template <typename T>
	void Show(const std::unordered_map<int, T>& map);
	void Show();
	Pipe AddPipe(int diameter);
	void Writing_to_file();
	void Read_from_file();
	void ConnectingStations();
	void ViewShortestDistance();
	void MaxFlow();
	void EditPipe();
	void EditCS();
	void ShowConnections();

	std::unordered_map<int, Pipe>& GetPipes();
	std::unordered_map<int, Cs>& GetCS();
	std::unordered_set<int> SearchFreePipesByDiameters(int diameter);
	void ConnectStations(int id_out, int id_in, int id_pipe);
	void DeleteConnection(int id_pipe);
	bool IsPipeConnected(int id_object);
	bool IsCSConnected(int id_cs);
	std::vector<int> TopologicalSorting();
	std::unordered_map<int, double> ShortestDistance(int id_cs);

	Graph InitGraph();
	bool PipeExist(int id_pipe);
	bool CSExist(int id_cs);
	bool IsPipeObjectsEmpty();
	bool IsCSObjectsEmpty();
private:
	std::unordered_map<int, Pipe> pipe_map;
	std::unordered_map<int, Cs> cs_map;
	std::unordered_map<int, Edge> connections;

};
template<typename T>
inline void GasTransportationSystem::Add(std::unordered_map<int, T>& map)
{
	T object;
	std::cin >> object;
	map.insert({ object.GetId(), object });
}

template<typename T>
inline void GasTransportationSystem::Show(const std::unordered_map<int, T>& map)
{
	for (const auto& [key, object] : map)
	{
		operator << (std::cout, object);
	}
}
