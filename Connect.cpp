// Standard includes
#include <stddef.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Connector Includes

#include "cppconnection/driver.h"
#include "cppconnection/exception.h"
#include "cppconnection/resultset.h"
#include "cppconnection/statement.h"


// Link to the Connector/C++ library

#pragma comment(lib, "mysqlcppconn.lib")

// Connection details
string server = "localhost";
string username = "root";
string password = "root"; // 
int connection(string input[1][3]);
void read_table();
void operations();
ofstream out;
ifstream in;
vector<vector<double> > fields;

int main()
{
	int choice=1;
	while (choice != 4)
	{
		cout << "Enter 1 to write CSV file data into table\n";
		cout << "Enter 2 for Read Table Entries\n";
		cout << "Enter 3 for Table Operations\n";
		cout << "Enter 4 for Exit..!!!\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			try
			{

				in.open("C:\\first.csv");
				if (in)
				{
					string line;
					int j=0;
					string arr[1][3];
					while (getline(in, line))
					{
						stringstream str(line);
						string input;
						fields.push_back(vector<double>());
						while (getline(str, input, ','))
						{
							//cout << string(input) << endl;
							//fields.back().push_back(stod(input));
							//fields.back().push(stod(input));
							//cout << input;
							arr[0][j] = input;
							j++;
						}
						connection(arr);
						j = 0;
					}
				}

				break;
			}
			catch (const std::exception& e)
			{
				cout << " Error !!!! Not able to read..\n" << e.what();
			}
			break;

		case 2:
			read_table();
			break;


		case 3:
			operations();
			break;
		}
	}
}

	int connection(string input[1][3])
	{
		out.open("C:\\first.csv");
		sql::Driver     *driver; // MySQL Driver Object
		sql::Connection *connection; // MySQL connection Object
		sql::Statement  *statement;   // Statement which holds SQL commands
		sql::ResultSet  *resultSet;    // ResultSet to hold the results
									   //Here is the connection

		try {

			driver = get_driver_instance();
			connection = driver->connect(server, username, password);
			statement = connection->createStatement();
			statement->execute("use db");
			statement->execute("insert into csv values('" + input[0][0] + "','" + input[0][1] + "','" + input[0][2] + "');");
		}
		catch (sql::SQLException& e)
		{
			cout << "Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}
	system("pause");
	return 0;

}
	void read_table()
	{
		sql::Driver     *driver; // MySQL Driver Object
		sql::Connection *connection; // MySQL connection Object
		sql::Statement  *statement;   // Statement which holds SQL commands
		sql::ResultSet  *resultSet;    // ResultSet to hold the results
									   //Here is the connection

		try {

			driver = get_driver_instance();
			connection = driver->connect(server, username, password);
			statement = connection->createStatement();
			statement->execute("use db");
			resultSet = statement->executeQuery("select * from csv;");
			while (resultSet->next())
			{
			// Iterating the result set

			cout << resultSet->getString(1) << "\t";
			cout << resultSet->getString(2) << "\t";
			cout << resultSet->getString(3) << endl;
			}
		}
		catch (sql::SQLException& e) 
		{
			cout << "Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		//Clear resources
		//delete res;
		//delete statement;
		//delete connection;
		system("pause");
		
	}


	void operations()
	{
		sql::Driver     *driver; // MySQL Driver Object
		sql::Connection *connection; // MySQL connection Object
		sql::Statement  *statement;   // Statement which holds SQL commands
		sql::ResultSet  *resultSet;    // ResultSet to hold the results
									   //Here is the connection

		try
		{

			driver = get_driver_instance();
			connection = driver->connect(server, username, password);
			statement = connection->createStatement();
			connection->setSchema("db");
			//statement->execute("use db");
			statement->executeUpdate("update csv set roll='215' where id = '130';");
		}
		catch (sql::SQLException& e) 
		{
			cout << "Error message: " << e.getErrorCode() << endl;
			system("pause");
			exit(1);
		}

		//Clear resources
		//delete res;
		//delete statement;
		//delete connection;
		system("pause");

	}