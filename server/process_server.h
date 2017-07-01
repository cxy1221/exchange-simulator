#ifndef _PROCESS_H
#define _PROCESS_H


#include<iostream>
#include<sstream>
#include<ctime>
#include<vector>
using namespace std;


class Order_server						//a class which records every order
{
public:
	Order_server(string t35, string t11, string t150, string t38, string t39, string t44) :
		tag_35(t35), tag_11(t11), tag_150(t150),tag_38(t38), tag_39(t39), tag_44(t44) {};
	string tag_35;
	string tag_11;
	string tag_150;
	string tag_38;
	string tag_39;
	string tag_44;

};

vector<Order_server> Order_book;		//the book which owns all orders 



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

vector<string> split_tag(string s)						//a function which splits each tag acording to ";"
{
	vector<string> ret;
	size_t last = 0;
	size_t index = s.find_first_of(';', last);
	while (index != std::string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(',', last);
	}
	if (index - last>0)
	{
		ret.push_back(s.substr(last, index - last));
	}
	return ret;
}

string id_creation()								//create an unique id for tag 11 according to time
{
	time_t now_time = time(NULL);
	return integerToString(now_time);
}


string do_with_35D(string price, string num, vector<Order_server>& book)		//process the message "35=D"
{
	
	if (stringToReal(price)* stringToInteger(num)> 1000000)
	{
		Order_server new_order("35=8", "11=" + id_creation(), "150=1", "38=" + integerToString(1000000/stringToReal(price)), "39=1", "44=" + price);
		book.push_back(new_order);
		return "35=8;150=0;39=0;   35=8;150=1;39=1;";
	}
	else
	{
		Order_server new_order("35=8", "11=" + id_creation(), "150=2", "38=" + num, "39=2", "44=" + price);
		book.push_back(new_order);
		return "35=8;150=0;39=0;   35=8;150=2;39=2;";
	}
}


string do_with_35F(string id, vector<Order_server>& book)						//process the message "35=F"
{
	vector<Order_server>::iterator it;
	for (it = book.begin();it != book.end();++it)
		if (it->tag_11 == id)
		{
			book.erase(it);
			return "35=8;150=4;39=4;";
		}

	return "35=9;39=8;";
}


void show_order_book(vector<Order_server> book)									//print the order book;
{
	vector<Order_server>::iterator it;
	for (it = book.begin();it != book.end();++it)
	{
		cout << it->tag_35 << ";" << it->tag_11 << ";" << it->tag_150 << ";" << it->tag_38 << ";" << it->tag_39 << ";" << it->tag_44 << ";" << endl;
	}
		
}



string process_client_msg(string client_msg)						//a function which determines order or cancel message the server receives
{
	vector<string> tags = split_tag(client_msg);
	vector<string> ::iterator it;
	string num="", price="",id="";
	for (it = tags.begin();it != tags.end();++it)
	{
		if ((*it) == "35=D")
		{
			vector<string> ::iterator iter;
			for (iter = tags.begin();iter != tags.end();++iter)
			{
				if (it->find("44=") !=it->npos)
				{
					price = it->substr(3, it->length() - 3);
				}
				if (it->find("38=") != it->npos)
				{
					num = it->substr(3, it->length() - 3);
				}
			}

		}
		if ((*it) == "35=F")
		{
			vector<string> ::iterator iter;
			for (iter = tags.begin();iter != tags.end();++iter)
			{
				if (it->find("11=") != it->npos)
				{
					id = it->substr(3, it->length() - 3);
				}
				
			}

		}

	}
	if (num != ""&&price != "")								//check the behaviour
	{
		return do_with_35D(price, num, Order_book);
	}
	if (id != "")
	{
		return do_with_35F(id, Order_book);
	}
}
#endif 
