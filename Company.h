#pragma once
#include"LinkedQueue.h"
#include"PriQueue.h"
#include"QueueADT.h"
#include"Event.h"
#include"Cargo.h"
#include"Enums.h"
#include"Time.h"
#include"Truck.h"
#include"LinkedList.h"
#include "UI.h"
class UI;

class Company

{    private:

	UI* Uiptr;
	Time Global;


	//waiting lists:

	LinkedQueue<Event*> events;

	LinkedQueue <Cargo*>Waiting_Special_cargo;
	PriorityQueue<Cargo*>Waiting_VIP_cargo;
	LinkedList<Cargo*>Waiting_Normal_cargo;

	LinkedQueue<Truck*>Waiting_Special_Truck;
	LinkedQueue<Truck*>Waiting_VIP_Truck;
	LinkedQueue<Truck*>Waiting_Normal_Truck;

	//Delivering lists:

	PriorityQueue<Cargo*> Delivering_Cargo;

	//completed lists:

	LinkedQueue<Cargo*> Deliverd_Cargo;

	//incheckup lists:
	 
	PriorityQueue<Truck*> Checkup_Truck;
	PriorityQueue<Truck*> Maintainanc_Truck;

	
	//data members to read file input datas:

	int numof_VIP_Trucks = 0, numof_Special_Trucks = 0, numof_Normal_Trucks = 0;
	int speed_VIP_Trucks = 0, speed_Special_Trucks = 0, speed_Normal_Trucks = 0;
	int VIP_Truck_Capacity;
	int Special_Truck_Capacity;
	int Normal_Truck_Capacity;
	int  numof_journeys_before_checkup = 0;
	int  VIP_Trucks_checkup_duration = 0, Special_Trucks_checkup_duration = 0, Normal_Trucks_checkup_duration = 0;
	int numof_Normal_Cargo;
	int Normal_Cargo_autoP = 0;
	int Max_Waiting_Time = 0;

	int num_events = 0;

	char event_type = 0, Cargo_type = 0; int event_time;
	int Cargo_id = 0, Dist = 0, LT = 0, cost = 0;
	int Extra_money;

	int event_day;
	int event_hour;
	char eventtype;
	
	bool workinghours;

	bool end = 0;

	//datamemebrs for output file:

	int WT; //waiting time
	int CDT; //cargo delivery time

	int TVC, TNC, TSP; //total number of cargo of each type
	int TST, TNT, TVT; //total number of truck of each type
	int AWT; //average waiting time for all cargos
	int APC; //percentage of automatically promoted cargos
	int AAT, AU; // average utlizition and active time of all trucks



public:

	//functions to get the lists 
	PriorityQueue<Cargo*> getWaitingVipCargolist();
	LinkedQueue<Cargo*> getWaitingSpecialCargolist();
	LinkedList<Cargo*> getWaitingNormalCargolist();
	PriorityQueue<Cargo*> getDeliveringCargolist();
	LinkedQueue<Truck*> getWaitingSpecialTrucklist();
	LinkedQueue<Truck*> getWaitingVipTrucklist();
	LinkedQueue<Truck*> getWaitingNormalTrucklist();
	PriorityQueue<Truck*> getInCheckuplist();
	LinkedQueue<Cargo*> getdeliverdCargo();

	/*bool workinghours()
	{
		Time x = GetGlobalTime();

		if (x.gethour() > 5 && x.gethour() < 23)
		{
			return true;
             }

		else 
		
		{  
		
		return false;
               }

	}*/

	Company();
	//~Company();

	void FileLoad(); //read file
	void save(); //create output file
	void UpdateTime(Time &Global); //incremnt hours and days

	void Assign(); //assign waiting cargo to avaliable trucks
	void execute(); //call event excute function each timestep to excute the events at that time
	void move(); //move cargos to differnet lists
	void Simulate(); //full simulation function
	void printoutput(); //call ui to print the output
	Time GetGlobalTime()//Return the current global time
	{

		return Global;
	}

	void simplesimulate();



	}; // to test loadfile function, ui output functionsand lists operations

