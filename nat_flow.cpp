#include<iostream>
#include<fstream>
#include<map>

using namespace std;

class NAT
{
	public:
	//member variable of map data structure
	map< pair<string, string>, pair<string, string> > nat;
		
	/* member function for scanning the nat file
	   to file the map data structure (nat here) */
	void scan_nat();

	/* member function to contents of flow and
	   find the corresponding nat match in 
	   map data structure (nat here) */
	void search_flow();
};

void NAT::scan_nat()
{
	pair<string, string> left_tuple, right_tuple;
	bool ip_read = false;
	bool port_read = false;
	bool left_tuple_read = false;
	bool right_tuple_read = false;
	string word;
	string ip;
	string port;
	int i = 0;
	
	std::ifstream input("NAT.txt");

	for(std::string line; getline(input, line);) {
		
		/* all the lines in the NAT file are read one by one
		   are parsed and then added to the nat member variable */
		i = 0;
		while (1) {

			/* parsing is done character by character
			   characters are accumulated to form string till
			   a ":", "," or "\0" is encountered. */
			if (line[i] == ':' || line[i] == ',' || line[i] == '\0') {
				
				/* if ip_read is not set the word 
				   read if an ip, after reading mark
				   ip_flag as true
				   else word read is port, after
				   reading mark port_flag as true */
				if (!ip_read) {
					ip = word;
					ip_read = true;
				}
				else {
					port = word;
					port_read = true;
				}

				/* if both ip and port are read
				   assigning it to either left or 
				   right tuple */
				if (ip_read && port_read) {

					/* if left_tuple_read is not true
					   it is a left tuple in the line read
					   correspondingly set left_tuple_read
					   else it is a right tuple in the line read
					   correspondingly set right_tuple_read */
					if (!left_tuple_read) {
						left_tuple = make_pair(ip, port);
						left_tuple_read = true;
						ip_read = false;
						port_read = false;
					}
					else if (left_tuple_read) {
						right_tuple = make_pair(ip, port);
						right_tuple_read = true;
					}
				}

				/* if both the left_tuple and right_tuple are read
				   add it to the nat member variable and reset flags */
				if (left_tuple_read && right_tuple_read) {
					nat[left_tuple] = right_tuple;
					left_tuple_read = false;
					right_tuple_read = false;
					ip_read = false;
					port_read = false;
				}

				//once done, make temporary scanner variable empty
				word = "";

				//break the loop once the end is reached
				if (line[i] == '\0') {
					break;
				}
			}
			else {
				word = word + line[i];
			}
			i++;
		}
	}
}

void NAT::search_flow()
{
	map< pair<string, string>, pair<string, string> >:: iterator itr;
	pair<string, string> tuple;
	bool ip_read = false;
	bool port_read = false;
	bool left_tuple_read = false;
	bool right_tuple_read = false;
	string word;
	string ip;
	string port;
	int i = 0;

	std::ifstream output("flow.txt");

	for(std::string line; getline(output, line);) {
		
		/* all the lines in the NAT file are read one by one
		   are parsed and then added to the nat member variable */
		i = 0;
		ip_read = false;
		port_read = false;
		while (1) {

			/* parsing is done character by character
			   characters are accumulated to form string till
			   a ":", "," or "\0" is encountered. */
			if (line[i] == ':' || line[i] == ',' || line[i] == '\0') {

				/* if ip_read is not set the word 
				   read if an ip, after reading mark
				   ip_flag as true
				   else word read is port, after
				   reading mark port_flag as true */
				if (!ip_read) {
					ip = word;
					ip_read = true;
				}
				else {
					port = word;
					port_read = true;
				}

				/* if both ip and port are read
				   search for corresponding flow in
				   nat member variable */
				if (ip_read && port_read) {
					tuple = make_pair(ip, port);

					if ((itr = nat.find(tuple)) != nat.end()) {
						cout << tuple.first << ":" << tuple.second << " -> " << (itr -> second).first << ":" << (itr -> second).second << endl;
					}
					else if ((itr = nat.find(make_pair("*", port))) != nat.end()) {
						cout << tuple.first << ":" << tuple.second << " -> " << (itr -> second).first << ":" << (itr -> second).second << endl;
					}
					else if ((itr = nat.find(make_pair(ip, "*"))) != nat.end()) {
						cout << tuple.first << ":" << tuple.second << " -> " << (itr -> second).first << ":" << (itr -> second).second << endl;
					}
					else {
						cout << "No nat match for " << tuple.first << ":" << tuple.second << endl;
					}
				}

				//once done, make temporary scanner variable empty
				word = "";
				
				//break the loop once the end is reached
				if (line[i] == '\0') {
					break;
				}
			}
			else {
				word = word + line[i];
			}
			i++;
		}
	}
}

int main() {
	/* creating the object of the class
	   created above */
	NAT obj;

	/* scanning NAT.txt to store
	   the data in nat member variable
	   by parsing the file */
	obj.scan_nat();


	/* scanning Flow.txt to search
	   the data in nat member variable
	   by parsing the file */
	obj.search_flow();

	return 0;
}
