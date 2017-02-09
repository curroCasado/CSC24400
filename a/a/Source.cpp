//****************************************   PROGRAM IDENTIFICATION   ************************************
//*                                                                                                      *
//*   PROGRAM FILE NAME:  program1.cpp               ASSIGMENT  #:   1           Grade: ___________      *
//*                                                                                                      *
//*   PROGRAM AUTHOR:        ____________________________________________________                        *
//*                                             Curro Casado                                             *
//*                                                                                                      *
//*   COURSE #;  CSC 24400 11                                      DUE DATE:  JANUARY 31, 2017           *
//*                                                                                                      *
//********************************************************************************************************

//*****************************************   PROGRAM DESCRIPTION   **************************************
//*                                                                                                      *
//*   PROCESS:  This program calculates the fare vehicles have to pay in a parking lot. It also prints   *
//*             said ticket with all the information: type of vehicle, time of entry and exit and the    *
//*             total amount to pay.                                                                     *
//*   USER DEFINED                                                                                       *
//*     MODULES    : readTimes - reads the time of entry and exit from the file                          *
//*                  printBill - print the parking fee with all information                              *
//*                  calculateBill - calculate the price of the parking fee                              *
//*                  header - print the output preamble                                                  *
//*                  footer - print the output salutation                                                *
//*                                                                                                      *
//********************************************************************************************************

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void readTimes(ifstream &, int &, int &);
void printBill(ofstream &, char, int, double, int, int);
double calculateBill(char, int);
void header(ofstream &);
void footer(ofstream &);
void SkipToTop(ofstream &, int &);

int main()
{

	char typeVehicle;
	int inTime, outTime, time;
	int Count = 0;
	double price;

	ifstream in("DATA1.txt", ios::in);  // data file
	ofstream out("results.txt", ios::out);  // output file

	header(out); // call header

	in >> typeVehicle; // read type vehicle

	while (typeVehicle != 'X') // check if type of vehicle is not X
	{
		readTimes(in, inTime, outTime); // call readTime to get the times of entry and exit


		time = outTime - inTime; // calculate the amaunt of minute
		if (time % 60 == 0) // see if time is divisible by 60
		{
			time /= 60; // get the time in hours
		}
		else if (time % 60 != 0) // if minutes pass just one minute the hour sum an hours
		{
			time /= 60;
			time += 1;  // sum an hours
		}

		price = calculateBill(typeVehicle, time); // call the function calculateBill to get the price
												  // return price
		printBill(out, typeVehicle, time, price, inTime, outTime); // call the fuction print

		Count += 1; // counter for the tikects

		if (Count >= 3)
			SkipToTop(out, Count);

		in >> typeVehicle; // read the next type vehicle
	}

	footer(out);
	return 0;
}
//************************************************  END OF FUCTION MAIN   ****************************************

//************************************************   FUNCTION SKIPTOTOP   ****************************************
void SkipToTop(ofstream &out, int &count)
{
	for (int i = 0; i < 10; i++)
	{
		out << endl;
	}
	count = 0;
	return;
}
//***********************************************  END OF FUNCTION   *********************************************

//***********************************************   FUNCTION PRINTBILL  ***************************************
void printBill(ofstream &out, char type, int time, double price, int timeIn, int timeOut)
{
	// Receives - type of vehicle , time, and price.
	// Task - Print the ticket.
	// Returns - nothing.


	out << endl << endl;
	out << "       The input data was:" << endl;
	out << "         " << type << " " << timeIn << " " << timeOut << endl;
	out << "		$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	out << "		$                      $" << endl;
	out << "		$   MISSOURI WESTERN   $" << endl;
	out << "		$   UNIVERSITY         $" << endl;
	out << "		$                      $" << endl;
	out << "		$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	out << "		$     PARKING FEE      $" << endl;
	out << "		$                      $" << endl;
	out << "		$  Customer            $" << endl;
	out << "		$  Category:  ";// the vehicle type is reflected on the bill
	if (type == 'C')
		out << "Car      $" << endl;
	else if (type == 'T')
		out << "Truck    $" << endl;
	else if (type == 'S')
		out << "SC       $" << endl;
	out << "		$                      $" << endl;
	if (time > 9)
		out << "		$  Time:      " << time << " hours $" << endl; // print the time for less than 10 hours
	else
		out << "		$  Time:      " << time << " hours  $" << endl; // print the time for less than 10 hours
	out << "		$                      $" << endl;
	out << "		$  Amount              $" << endl;
	out << "		$  Paid:      $" << setprecision(2) << fixed << price << "    $" << endl; // print the value to pay 
	out << "		$                      $" << endl;
	out << "		$$$$$$$$$$$$$$$$$$$$$$$$" << endl;


	return;
}
//***********************************************   END OF FUNCTION PRINTBILL  **********************************

//**********************************************  FUNCTION CALCULATEBILL  ****************************************
double calculateBill(char type, int time)
{
	// Receives - type of vehicle and times.
	// Task - Calculate the price of the ticket.
	// Returns - price.
	double price;



	if (type == 'C') // if type is a Car
	{
		if (time <= 2)
			price = 0.2 * time;
		else if (time <= 5)
			price = 0.4 + (0.15 * (time - 2));
		else if (time <= 15)
			price = 0.85 + (0.05 * (time - 5));
		else if (time > 15)
			price = 1.35;
		// calculate price for a Car depending of each hours
	}
	else if (type == 'T') // if type is a Truck
	{
		if (time <= 1)
			price = 0.4;
		else if (time <= 4)
			price = 0.4 + (0.25 * (time - 1));
		else if (time <= 16)
			price = 1.15 + (0.10 * (time - 4));
		else if (time > 15)
			price = 2.35;
		// calculate price for a Truck depending of each hours
	}
	else if (type == 'S') // if is a SC
	{
		price = 0.12 * time;
		// calculate price for a SC depending of each hours
	}

	return price;
}
//**********************************************  END OF FUNCTION CALCULATEBILL  ************************************

//**********************************************   FUNCTION READ  **************************************************
void readTimes(ifstream &in, int &inTime, int &outTime)
{
	// Receives - input and times.
	// Task - Read the times of entry and exit.
	// Returns - nothing.

	in >> inTime;  // read time in from file
	in >> outTime;  // read time out from file

	return;
}
//**********************************************   END OF FUNCTION READ  ***********************************************

//**********************************************   FUNCTION HEADER   *************************************************
void header(ofstream &Outfile)
{
	// Receives - the output file
	// Task - print the output preamble
	// Returns - Nothing
	Outfile << setw(30) << "Curro Casado";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2017";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------" << endl << endl;
	return;
}
//********************************************** END OF PROGRAM HEADER ***************************************************

//**********************************************   FUNCTION HEADER   *************************************************
void footer(ofstream &Outfile)
{
	// Receives - the output file
	// Task - print the output salutation
	// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------------" << endl;
	Outfile << setw(35) << "|        END OF PROGRAM  OUTPUT      |" << endl;
	Outfile << setw(35) << "--------------------------------------" << endl;
	return;
}
//********************************************** END OF PROGRAM HEADER ***************************************************
