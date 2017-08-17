/*

	Greedy best-first-search
	subject : artificial intelligence 
	EXPERIMENT NUMBER 4

	graph contains 20 locations

	description: program reads and processes a flat file which contains the graph data. After successful creation of graph, it sets destinaition
	as bucharest and prompts user to enter the origin. The program will print the best possible path to bucharest.

*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>
//user defined datatype
#define VERTEX struct vertex
VERTEX
{
	std::string vertex_name;
	int str8_line_dist;
	std::vector <std::string> connected_vertices;
	std::vector <struct vertex*> connected_places;
	std::vector <int> connect_edge_weights;
};
//global variables
std::vector<VERTEX> places;
std::vector<VERTEX*> openList, closeList;
std::vector<int> heuristicList;
VERTEX *origin, *destination;
void input_places()			//reading the flat file and formation of vertices
{
	std::string line;
	std::ifstream graphData("aiEXP.csv");
	
	if (graphData.is_open())
	{
		while (getline(graphData, line))
		{
			VERTEX p;
			std::string separatedValues, name, str8_linedist, connectedPlaces, theirWeights, eachPlace, eachWeight;
			std::istringstream commaSeparation(line);
			getline(commaSeparation, name,',');
			getline(commaSeparation, str8_linedist,',');
			getline(commaSeparation, connectedPlaces,',');
			getline(commaSeparation, theirWeights,',');
			commaSeparation.clear();
			std::cout << name << "\t" << str8_linedist << "\t" << connectedPlaces << "\t" << theirWeights << "\n";
			p.vertex_name = name;
			p.str8_line_dist = atoi(str8_linedist.c_str());
			std::istringstream connectedPlaces1(connectedPlaces);
			std::istringstream theirWeights1(theirWeights);
			while (getline(connectedPlaces1, eachPlace,' ') && getline(theirWeights1, eachWeight,' '))
			{
				p.connected_vertices.push_back(eachPlace);
				p.connect_edge_weights.push_back(atoi(eachWeight.c_str()));
			}
			connectedPlaces1.clear();
			theirWeights1.clear();
			places.push_back(p);
		}
	}
	graphData.clear();
	graphData.close();
}
void printVName(VERTEX *placeName)		//prints the name of the vertex
{
	std::cout << placeName->vertex_name;
}
void sort_it()		//selection sorts the heuristic weight list and openList simultaneously
{
	int l = heuristicList.size();
	for (int i = 0; i < l; i++)
	{
		int minpos = i;
		for (int j = i; j < l; j++)
		{
			if (heuristicList[j] < heuristicList[minpos])
			{
				minpos = j;
			}
		}
		if (minpos != i)
		{
			VERTEX *temp;
			temp = openList[i];
			int temp1;
			temp1 = heuristicList[i];
			openList[i] = openList[minpos];
			heuristicList[i] = heuristicList[minpos];
			heuristicList[minpos] = temp1;
			openList[minpos] = temp;
		}
	}
}
void create_graphs()		//connects the vertices to form a graph
{
	std::cout << "Creating Graphs";
	for (int i = 0; i < 20; i++)
	{
		VERTEX *p;
		p = &places[i];
		if (!p->vertex_name.compare("bucharest"))
		{
			destination = p;
		}
		int length = p->connected_vertices.size();
		for (int j = 0; j < length; j++)
		{
			std::string place_name = p->connected_vertices[j];
			for (unsigned int k = 0; k < places.size(); k++)	//find city in the stored list
			{
				if (!place_name.compare(places[k].vertex_name))
				{
					p->connected_places.push_back(&places[k]);
					break;	//if found then store address into the connected list and exit inner loop
				}
			}
		}
	}
}
void print_vertices()		//print all the vertices of the graph
{
	for (unsigned int i = 0; i < places.size(); i++)
	{
		int lengthV = places[i].connected_places.size();
		for (int j = 0; j < lengthV; j++)
			std::cout << places[i].connected_places[j]->vertex_name;
	}
}
void printlist()		//prints openList. 
{
	std::cout << "\n";
	int len = openList.size();
	for (int i = 0; i < len; i++)
		std::cout << openList[i]->vertex_name << "\t"<<i<<"\n";
}
bool isNotPresent(VERTEX *place)		//To check if the vertex is present in closeList
{
	int length = closeList.size();
	bool flag = true;
	for (int i = 0; i<length;i++)
	{
		if (place->vertex_name.compare(closeList[i]->vertex_name)==0)
		{
			flag=false;
		}
	}
	return flag;
}
void find_path()		//greedy? best first search 
{
		VERTEX *newPlace;
		newPlace = openList[0];
		printVName(newPlace);
		if (newPlace->vertex_name.compare("bucharest") == 0)
		{
			return;
		}
		closeList.push_back(newPlace);
		int weight = heuristicList[0];		//incase if someone wants to print weights
		openList.pop_back();
		openList.clear();
			heuristicList.pop_back();
			heuristicList.clear();
			int lengthV = newPlace->connected_places.size();
			for (int i = 0; i < lengthV; i++)
			{
				int heuristicWeight1 = newPlace->connected_places[i]->str8_line_dist + newPlace->connect_edge_weights[i];
				if (isNotPresent(newPlace->connected_places[i]))
				{
					heuristicList.push_back(heuristicWeight1);
					openList.push_back(newPlace->connected_places[i]);
				}
			}
			sort_it();
			std::cout << "--->";
			find_path();	
}
void find_path_greedy(VERTEX *currentPlace)		//greedy search
{
	printVName(currentPlace);
	if (currentPlace->vertex_name.compare("bucharest") == 0)
	{	
		return;
	}
	int lengthV = currentPlace->connected_places.size();
	int low = currentPlace->str8_line_dist;
	VERTEX *newPlace;
	for (int i = 0; i < lengthV; i++)
	{
		if (low > currentPlace->connected_places[i]->str8_line_dist)
		{
			low = currentPlace->connected_places[i]->str8_line_dist;
			newPlace = currentPlace->connected_places[i];
		}
	}
	std::cout << "--->";
	find_path_greedy(newPlace);
}
int main()
{
	bool location_flag = false;
	input_places();
	create_graphs();
	std::cout << "Destination set to " << destination->vertex_name;
	while (true)
	{
		std::cout << "\n Please enter origin or quit to exit:";
		std::string origin_name;
		std::cin >> origin_name;
		if (origin_name.compare("quit") == 0)
		{
			break;
		}
		VERTEX *p;
		for (unsigned int i = 0; i < places.size(); i++)
		{
			p = &places[i];
			if (origin_name.compare(p->vertex_name) == 0)	//check if the location exists in the graph
			{
				location_flag = true;
				origin = p;
				break;
			}
		}
		if (location_flag)
		{
			if (origin_name.compare("bucharest") != 0)
			{
				//std::cout << origin->vertex_name;
				heuristicList.push_back(999999);
				openList.push_back(origin);
				find_path();
				heuristicList.clear();
				openList.clear();
				closeList.clear();
			}
			else
			{
				std::cout << "You are at bucharest.";
			}
		}
		else {
			std::cout << "Sorry, location not found.\nPlease try again.";
		}
	}
}