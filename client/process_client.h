#ifndef _PROCESS_H
#define _PROCESS_H


#include<iostream>
#include<sstream>
#include<ctime>
using namespace std;


class Order_client						//a class which records every order
{
public:
	Order_client(string t35, string t11, string t150, string t38, string t39, string t44) :
		tag_35(t35), tag_11(t11), tag_150(t150), tag_38(t38), tag_39(t39), tag_44(t44) {};
	string tag_35;
	string tag_11;
	string tag_150;
	string tag_38;
	string tag_39;
	string tag_44;
	string order_msg();
	string cancel_msg();
};

vector<Order_client> Order_records;		//the book which owns all orders 



int stringToInteger(string str)			//a basic function which turns string type to int type
{
	istringstream stream(str);
	int value;
	stream >> value >> ws;
	return value;
}

string integerToString(int n)			//a basic function which turns int type to string type
{
	ostringstream stream;
	stream << n;
	return stream.str();
}



string realToString(double d)			//a basic function which turns double type to string type
{
	ostringstream stream;
	stream << uppercase << d;
	return stream.str();
}

double stringToReal(string str)			//a basic function which turns string type to double type
{
	istringstream stream(str);
	double value;
	stream >> value >> ws;
	return value;
}


string Order_client::order_msg()
{
	tag_35 = "35=D";
	return tag_35;
}

string Order_client::cancel_msg()
{
	tag_35 = "35=F";
	return tag_35;
}


void show_all_orders(vector<Order_client> book)									//print all the records by the client;
{
	vector<Order_client>::iterator it;
	for (it = book.begin();it != book.end();++it)
	{
		cout << it->tag_35 << ";" << it->tag_11 << ";" << it->tag_150 << ";" << it->tag_38 << ";" << it->tag_39 << ";" << it->tag_44 << ";" << endl;
	}

}


#endif 


