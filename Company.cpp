#include "Company.h"
#include<iostream>
#include<fstream>
using std::ofstream;
using std::ifstream;
#include<string>
#include <thread>
#include <chrono>
#include"UI.h"
#include"Event.h"
#include"ReadyEvent.h"
#include"CancelEvent.h"
#include"PromotionEvent.h"





PriorityQueue<Cargo*> Company::getWaitingVipCargolist() {
	return Waiting_VIP_cargo;

}
LinkedQueue<Cargo*> Company::getWaitingSpecialCargolist() {
	return Waiting_Special_cargo;     
}
LinkedList<Cargo*> Company::getWaitingNormalCargolist() {
	return Waiting_Normal_cargo;
}
PriorityQueue<Cargo*> Company::getDeliveringCargolist() {
	return Delivering_Cargo;
}
LinkedQueue<Truck*> Company::getWaitingSpecialTrucklist() {
	return Waiting_Special_Truck;
}
LinkedQueue<Truck*> Company::getWaitingVipTrucklist() {
	return Waiting_VIP_Truck;

}

LinkedQueue<Truck*> Company::getWaitingNormalTrucklist() {
	return Waiting_Normal_Truck;
}
PriorityQueue<Truck*> Company::getInCheckuplist() {
	return Checkup_Truck;
}
LinkedQueue<Cargo*> Company::getdeliverdCargo() {
	return Deliverd_Cargo;
}


void Company::FileLoad() {
	ifstream inputfile(Uiptr->getfilename(), ios::in);
	while (!end)
	{
		//Reading Trucks and their properties to add them to the Trucks list:

		inputfile >> numof_Normal_Trucks;
		inputfile >> numof_Special_Trucks;
		inputfile >> numof_VIP_Trucks;


		if (numof_Normal_Trucks > 0)
			inputfile >> speed_Normal_Trucks;
		if (numof_Special_Trucks > 0)
			inputfile >> speed_Special_Trucks;
		if (numof_VIP_Trucks > 0)
			inputfile >> speed_VIP_Trucks;


		if (numof_Normal_Trucks > 0)
			inputfile >> Normal_Truck_Capacity;
		if (numof_Special_Trucks > 0)
			inputfile >> Special_Truck_Capacity;
		if (numof_VIP_Trucks > 0)
			inputfile >> Normal_Truck_Capacity;


		inputfile >> numof_journeys_before_checkup;
		if (numof_Normal_Trucks > 0)
			inputfile >> Normal_Trucks_checkup_duration;
		if (numof_Special_Trucks > 0)
			inputfile >> Special_Trucks_checkup_duration;
		if (numof_VIP_Trucks > 0)
			inputfile >> VIP_Trucks_checkup_duration;

		inputfile >> Normal_Cargo_autoP;
		inputfile >> Max_Waiting_Time;


		//Adding Trucks to truck lists:
		for (int i = 1; i <= numof_Normal_Trucks; i++)
		{
			
			Truck* Add_Truck = new Truck(normal_T, Normal_Trucks_checkup_duration, speed_Normal_Trucks, numof_journeys_before_checkup, Waiting,i);
			Waiting_Normal_Truck.enqueue(Add_Truck);
			
		}

		for (int i = numof_Normal_Trucks + 1; i <= numof_Normal_Trucks + numof_Special_Trucks; i++) {

			Truck* Add_Truck = new Truck(Special_T, Special_Trucks_checkup_duration, speed_Special_Trucks, numof_journeys_before_checkup, Waiting,i);
			Waiting_Special_Truck.enqueue(Add_Truck);
		}

		for (int i = numof_Normal_Trucks + numof_Special_Trucks +1; i <= numof_Normal_Trucks + numof_Special_Trucks+ numof_VIP_Trucks; i++) {
			Truck* Add_Truck = new Truck(VIP_T, VIP_Trucks_checkup_duration, speed_VIP_Trucks, numof_journeys_before_checkup, Waiting,i);
			Waiting_VIP_Truck.enqueue(Add_Truck);

		}

		//Adding Events:

		inputfile >> num_events;
		for (int i = 0; i < num_events; i++) {
			inputfile >> event_type;

			Event* E = NULL;
			if (event_type == 'R') {
				//This is Ready event
				inputfile >> Cargo_type;
				if (Cargo_type == 'N') {
					numof_Normal_Cargo++;
				}

				inputfile >> event_day;
				inputfile >> event_hour;
				inputfile >> Cargo_id;
				inputfile >> Dist;
				inputfile >> LT;
				inputfile >> cost;

				E = new ReadyEvent('R', event_day, event_hour, Cargo_id, 'N', Dist, LT, cost);
				//class event should contain this function to add new cargo to lists
			}

			else if (event_type == 'X') {
				//This is cancelltion event
				inputfile >> event_day;
				inputfile >> event_hour;
				inputfile >> Cargo_id;
				E = new CancelEvent('X', event_day, event_hour, Cargo_id);
				// class event contain cancelevent to remove cargo from lists
			}

			else if (event_type == 'P') {
				//This is promotion event
				inputfile >> event_day;
				inputfile >> event_hour;
				inputfile >> Cargo_id;
				inputfile >> Extra_money;
				E = new PromotionEvent('P', event_day, event_hour, Cargo_id, Extra_money);
				//class event contain this function to promote normal cargo to vip
			}

			if (E) {
				events.enqueue(E);

			}


			

			
		}


		end = true;
		
	}

	
}

void Company::simplesimulate()
{
	Cargo* Y;
	Cargo* W;
	Cargo* Z;
	Event* x;
	//Global = Time(0, 0);
	//Uiptr->Readfilename();
	//FileLoad();
	//UiPtr->ModeType();


	while (!events.isEmpty() && Waiting_Normal_cargo.Isempty() && Waiting_Special_cargo.isEmpty() && Waiting_VIP_cargo.isEmpty())
	{
		Global.updatehour();

		events.peek(x);

		if (x->getEventtime() == Global)
		{
			if (x->getEvent_type() == 'R')
			{
				x->Execute(Waiting_Special_cargo, Waiting_VIP_cargo, Waiting_Normal_cargo);
				events.dequeue(x);


			}

			else if (x->getEvent_type() == 'P')

			{
				x->Execute(Waiting_Special_cargo, Waiting_VIP_cargo, Waiting_Normal_cargo);
				events.dequeue(x);


			}

			else
			{
				x->Execute(Waiting_Special_cargo, Waiting_VIP_cargo, Waiting_Normal_cargo);
				events.dequeue(x);



			}
		}

		else
			break;


		if (Global.gethour() % 5 == 0)
		{
			if (!Waiting_Special_cargo.isEmpty())
			{
				Waiting_Special_cargo.dequeue(Y);
				Deliverd_Cargo.enqueue(Y);
			}

			if (!Waiting_VIP_cargo.isEmpty())
			{
				Waiting_VIP_cargo.dequeue(W);
				Deliverd_Cargo.enqueue(W);
			}

			if (!Waiting_Normal_cargo.Isempty())
			{

				Waiting_Normal_cargo.deletefirst(Z);
				Deliverd_Cargo.enqueue(Z);

			}

		}

		Uiptr->PrintData();
		Uiptr->getinput();

	}
}

Company::Company()
{
	Uiptr = new UI();
	Uiptr->getfilename();
	FileLoad();
	Global.setday(0);
	Global.sethour(0);

}
