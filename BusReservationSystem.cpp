/*

Bus Reservation System Implementation that allows several options:
1. Install
2. Reservation
3. Show
4. Buses Available
5. Exit App


Install: 
- read from stdin such details as bus number, driver's name, arrival time, 
departure time, location to depart from, destination

Reservation:
- function to make a reservation in a bus/ buy a ticket by given bus number
- if someone requests to reserve a seat with seat number bigger then 32, error
message - There are only 32 seats available in this bus; if the requested seat is
empty, reserve it by entering passenger's name; if the requested seat is already booked, 
error message - The seat no. is already reserved

Show:
- function to read bus number from stdin to get details about the ride
- as long if bus number is correct (it's smaller then max bus numbers) print details 
as bus number, bus driver, arrival time, departure time, from/to and print who reserved each
seat in the bus

Buses Available:
- function to go through the list of buses to print details about a bus: 
number, driver, arrival/departure time, from/to

Exit:
- command to exit bus reservation system

*/


#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

static int p = 0;
bus[10];

class a
{
	// keep data in arrays
	char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];

public:
	// functions to be implemented
	void install();
	void allotment();
	void empty();
	void show();
	void avail();
	void position(int i);
}


// function to draw a vertical (top to bottom) line using ch starting 
// at the current cursor position in the window
void vline(char ch)
{
	for (int i = 80; i >0; i--)
  		cout<<ch;
}

void a::install()
{	
	// read from stdin bus number
	cout<<"Enter bus no: ";
	cin>>bus[p].busn;

	// read from stdin driver's name
	cout<<"\nEnter Driver's name: ";
	cin>>bus[p].driver;
	
	// read from stdin arrival time
	cout<<"\nArrival time: ";
	cin>>bus[p].arrival;

	// read from stdin departure
	cout<<"\nDeparture: ";
	cin>>bus[p].depart;

	// read from stdin location to depart from
	cout<<"\nFrom: \t\t\t";
	cin>>bus[p].from;

	// read from stdin location to depart to
	cout<<"\nTo: \t\t\t";
	cin>>bus[p].to;

	// empty bus
	bus[p].empty();
	
	// increment bus number
	p++;
}


// function to make a reservation in the bus
void a::allotment()
{
	int seat;
	char number[5];

	top:
	// read from stdin bus number
	cout<<"Bus no: ";
	cin>>number;

	int n;
	for(n=0; n<=p; n++) {
		if(strcmp(bus[n].busn, number)== 0)
			break;
	}

	// as long if bus number is smaller then nr of buses
	while(n<=p) {

		// read seat number
		cout<<"\nSeat Number: ";
		cin>>seat;

		if(seat>32) {
			// there are only 32 seats in the bus
			cout<<"\nThere are only 32 seats available in this bus.";
		} else if (strcmp(bus[n].seat[seat/4][(seat%4)-1], "Empty")==0) {
			
			// give passanger's name
			cout<<"Enter passanger's name: ";
			cin>>bus[n].seat[seat/4][(seat%4)-1];

			break;
		} else
			// if the seat is already booked by someone
			cout<<"The seat no. is already reserved.\n";
		}

	}
	if(n>p) {
		// if bus number doesn't exist, error message
		cout<<"Enter correct bus no.\n";
		goto top;
	}

}

// function for empty seats
void a::empty()
{
	
	// go through the list of seats and initialize them as Empty
	for(int i=0; i<8; i++) {
		for(int j=0; j<4; j++) {
			strcpy(bus[p].seat[i][j], "Empty");
		}
	}
}

// function to show details of a bus ride
void a::show()
{

	int n;
	char number[5];

	// read bus number from stdin to get details about the ride
	cout<<"Enter bus no: ";
	cin>>number;

	for(n=0; n<=p; n++){
		if(strcmp(bus[n].busn, number)==0)
		break;
	}

	// as long if bus number is correct (it's smaller then max bus numbers)
	while(n<=p) {
		vline('*');

		// print details as bus number, bus driver, arrival time, departure time, from/to
		cout<<"Bus no: \t"<<bus[n].busn
		<<"\nDriver: \t"<<bus[n].driver<<"\t\tArrival time: \t"
		<<bus[n].arrival<<"\tDeparture time:"<<bus[n].depart
		<<"\nFrom: \t\t"<<bus[n].from<<"\t\tTo: \t\t"<<
		bus[n].to<<"\n";

		vline('*');

		bus[0].position(n);
		
		int a=1; // contor through the list of seats
		for (int i=0; i<8; i++) {
			for(int j=0; j<4; j++) {
				a++;
						
				// if seat is not empty, show who reserved it
				if(strcmp(bus[n].seat[i][j],"Empty")!=0)
					cout<<"\nThe seat no "<<(a-1)<<" is reserved for "<<bus[n].seat[i][j]<<".";
			}
		}
		break;
	}

	// if bus number is incorrect, error message
	if(n>p)
		cout<<"Enter correct bus no: ";
}

// function to return empty seats in each bus
void a::position(int l)
{
	int s=0; 
	int p=0;
	for (int i=0; i<8; i++) {
		cout<<"\n";
		for (int j=0; j<4; j++) {
			s++;
			// if empty seats
			if(strcmp(bus[l].seat[i][j], "Empty")==0) {
          			cout.width(5);
				cout.fill(' ');
				cout<<s<<".";
				cout.width(10);
				cout.fill(' ');
				cout<<bus[l].seat[i][j];
				p++;
			} else {
				cout.width(5);
				cout.fill(' ');
				cout<<s<<".";
				cout.width(10);
				cout.fill(' ');
				cout<<bus[l].seat[i][j];
			}
		}
	}
	cout<<"\n\nThere are "<<p<<" seats empty in Bus No: "<<bus[l].busn;

}

// function to return available buses
void a::avail()
{
	// go through the list of buses
	for(int n=0; n<p; n++) {
		vline('*');

		// print details about a bus: number, driver, arrival/departure time, from/to

		cout<<"Bus no: \t"<<bus[n].busn<<"\nDriver: \t"<<bus[n].driver
		<<"\t\tArrival time: \t"<<bus[n].arrival<<"\tDeparture Time: \t"
		<<bus[n].depart<<"\nFrom: \t\t"<<bus[n].from<<"\t\tTo: \t\t\t"
		<<bus[n].to<<"\n";

		vline('*');
		vline('_');
	}

}

int main()
{
	system("cls");
	int w;

	// loop to choose option and switch between system's options
	while(1) {
		cout<<"\n\n\n\n\n";
		cout<<"\t\t\t1.Install\n\t\t\t"
		<<"2.Reservation\n\t\t\t"
		<<"3.Show\n\t\t\t"
		<<"4.Buses Available. \n\t\t\t"
		<<"5.Exit";

		// choose your option
		cout<<"\n\t\t\tEnter your choice:-> ";
		cin>>w;

		// switch case instruction to choose an option: Install, Reservation, Show, Available, Exit App
		switch(w) {
			case 1:  bus[p].install();
				break;
			case 2:  bus[p].allotment();
				break;
			case 3:  bus[0].show();
				break;
			case 4:  bus[0].avail();
				break;
			case 5:  exit(0);
		}
	}

	return 0;
}