using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <fstream>


const string filename = "file.txt";
const int MAX_SIZE_OF_GRAPH = 32768;
const int BAN_VALUE = 4;
const int MAX_SIZE_OF_RELATION_TO_RECOMMEND = 3;



bool isEveryThingANumber(const string& line)
{
	int size = line.length();
	//int spaceCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (line[i] == ' ')
		{
			//++spaceCount;
			continue;
		}



		if (line[i] < '0' || line[i] > '9')
		{
			return false;
		}
	}

	return true;

}


string ReturnName(const string& line)
{
	string name;
	int size = line.length();
	for (int i = 0; i < size; i++)
	{
		if (line[i] >= 'A' && line[i] <= 'z')
		{
			while (line[i] >= 'A' && line[i] <= 'z')
			{
				name += line[i];
				i++;
			}
			return name;
		}
	}
	return name;
}

int ReturnAge(string& line)
{
	string age;
	string::reverse_iterator ptr = line.rbegin();
	for (ptr; ptr != line.rend(); ptr++)
	{
		while (*ptr >= '0' && *ptr <= '9')
		{
			age += *ptr;
			++ptr;
		}
		break;
	
	}
	string officialAge;
	string::reverse_iterator forNUm = age.rbegin();
	for (forNUm; forNUm != age.rend(); forNUm++)
	{
		officialAge += *forNUm;
	}
	return stoi(officialAge);
}

string ReturnID(string& line)
{
	int index = 0;
	string id;
	while (line[index] != ' ')
	{
		id += line[index];
		index++;
	}
	return id;
}

class User
{
private:
	string name;
	int age;
	static int numberOfOfObjectsCreated;
	int id;

public:
	User(string name, int age);
	string GetName() const;
	int getAge() const;
	int GetId() const;
	void MinusStatic();
	void UpdateStatic();
	static int ReturnStaticVariable()
	{
		return numberOfOfObjectsCreated;
	}
	friend ostream& operator<<(ostream& os, const User& other);

};


void User::UpdateStatic()
{
	this->id = numberOfOfObjectsCreated;
	++numberOfOfObjectsCreated;
}

ostream& operator<<(ostream& os, const User& other)
{
	os << other.id << " " << other.name << " " << other.age << endl;
	return os;
}

int User::numberOfOfObjectsCreated = 0;

void User::MinusStatic()
{
	this->numberOfOfObjectsCreated--;
	this->id--;
	return;
}


User::User(string name,int age)
{
	this->name = name;
	this->age = age;
	this->id = numberOfOfObjectsCreated;
	numberOfOfObjectsCreated++;
}

string User::GetName() const
{
	return name;
}

int User::GetId() const
{
	return id;
}

int User::getAge() const
{
	return age;
}

class SocialMedia
{
private:

	vector<User> allUsers;


	vector<int> indexOfReomvedUser;

	vector<vector<pair<User, int> > > graph;

	bool CheckIfUsersAreLinked(const User& user1, const User& user2);

	int ReturnCommand(const string& command);

	int  ReturnIndexOfUser(const string& command);

	void RemoveFromGraph(const string& name);

	User ReturnUser(const string& name);

	bool searchForUser(string name);

	//void RestoreGraph(istream& readFile);


	//helper function not needed
	void PRINTALLFRIENDSHIPS()
	{
		for (int i = 0; i < (signed)graph.size(); i++)
		{
			if (graph[i].empty())
			{
				continue;
			}

			for (int j = 0; j <(signed)graph[i].size(); j++)
			{
				cout << graph[i][j].first.GetName() << " " << graph[i][j].first.getAge() << " " << graph[i][j].first.GetId() << " " << graph[i][j].second << endl;
			}
		}
	}

	//this is a tester Function not needed
	void PrintFriendShip(const string& name1, const string& name2)
	{
		if (!searchForUser(name1) || !searchForUser(name2))
		{
			cout << "User not found " << endl;
			return;
		}

		User u1 = ReturnUser(name1);
		User u2 = ReturnUser(name2);

		int id1 = u1.GetId();
		int id2 = u2.GetId();

		int sizeofU1 = graph[id1].size();
		int sizeOfU2 = graph[id2].size();

		cout << "Friends of: " << u1.GetName() << endl;

		for (int i = 0; i < sizeofU1; i++)
		{
			if (graph[id1][i].second == BAN_VALUE)
			{
				cout << "OOps it looks like " << u1.GetName() << " has banned  " << graph[id1][i].first.GetName() << " " << endl;
				continue;
			}

			cout << graph[id1][i].first.GetName() << endl;
		}
		cout << "End of 1st user friendship" << endl;

		cout << "Friends of: " << u2.GetName() << endl;

		for (int i = 0; i < sizeOfU2; i++)
		{

			if (graph[id2][i].second == BAN_VALUE)
			{
				cout << "OOps it looks like " << graph[id2][i].first.GetName()  << " has banned  " << u2.GetName() << " " << endl;
				continue;
			}

			cout << graph[id2][i].first.GetName() << endl;
		}
		cout << "End OF 2nd user friendship" << endl;
	}


	User ReturnUserByID(int id);

	bool CheckIfTwoUsersAreBanned(const string& name1,const string& name2);

 public:
	 
	SocialMedia();

	bool AddUser( User& temp);
	
	bool MakeFriendShip(const string& user1, const string& user2,string typeOfFriendShip="normal");

	bool RemoveUser(const string& name);

	void InfoForSearchedUser(const string& name);

	void Ban(const string& name1, const string& name2);

	void RemoveFriendShip(const string& name1, const string& name2);

	void Recommend(const string& name);

	void WriteToFileUsers(const string& filename);

	void RestoreGraph(const string& filename);

	void printUsers();

	

};

void SocialMedia::printUsers()
{
	for (unsigned int i = 0; i < allUsers.size(); i++)
	{
		cout << allUsers[i].GetName() << " and age " << allUsers[i].getAge() << " and id " << allUsers[i].GetId() << endl;
	}
}

User SocialMedia::ReturnUserByID(int id)
{
	for (int i = 0; i < (signed)allUsers.size(); i++)
	{
		if (allUsers[i].GetId() == id)
		{
			return allUsers[i];
		}
	}
}

void SocialMedia::WriteToFileUsers(const string& filename)
{
	ofstream ofile(filename);

	int size = allUsers.size();
	for (int i = 0; i < size; i++)
	{
		ofile << allUsers[i];
	}
	bool shouldBreak = false;
	int graphsize = graph.size();
	for (int i = 0; i < graphsize; i++)
	{


		if (graph[i].empty())
		{
			continue;
		}

		for (int k = 0; k < (signed)indexOfReomvedUser.size(); k++)
		{

			if (i == indexOfReomvedUser[k])
			{
				cout << "i= " << i << " == "<<indexOfReomvedUser[k] << endl;
				shouldBreak = true;
				break;
			}
		}

		if (shouldBreak)
		{
			shouldBreak = false;
			continue;
		}
		for (int j = 0; j < (signed)graph[i].size(); j++)
		{
			ofile << i <<" "<<graph[i][j].first.GetId()<< " "<< graph[i][j].second<<endl;
		}
	}

	//first write allUsers
}


void SocialMedia::RestoreGraph(const string& filename)
{
	ifstream ifile(filename);
	string testLine;
	//if file is emptu
	while (getline(ifile, testLine))
	{
		if (!isEveryThingANumber(testLine))
		{
			string name = ReturnName(testLine);

			int age = ReturnAge(testLine);

			string id = ReturnID(testLine);

			int valueID = stoi(id);

			User temp(name, age);

			while(valueID != temp.GetId())
			{

				temp.UpdateStatic();
			}
			allUsers.push_back(temp);
		}
		else
		{
			if (testLine == "")
			{
				break;
			}
			int index = 0;
			string firstNum, secondNum,typeOfRelation;
			while (testLine[index]>='0' && testLine[index]<='9')
			{
				firstNum += testLine[index++];
			}
			index++;
			while (testLine[index] >= '0' && testLine[index] <= '9')
			{
				secondNum += testLine[index++];
			}
			index++;

			while (testLine[index] >= '0' && testLine[index] <= '9')
			{
				typeOfRelation += testLine[index++];
			}


			int idFirstUser = stoi(firstNum);
			int idSecondUser = stoi(secondNum);
			int id = stoi(typeOfRelation);
		//	int command = ReturnCommand(typeOfRelation);
			User u2 = ReturnUserByID(idSecondUser);
			graph[idFirstUser].push_back(make_pair(u2, id));

		}
	}
	this->printUsers();
	//this->PRINTALLFRIENDSHIPS();
	//

}

//Not Finished
void SocialMedia::Recommend(const string& name)
{
	if (!searchForUser(name))
	{
		cout << "User does not exist" << endl;
		return;
	}


	User temp = ReturnUser(name);

	if (graph[temp.GetId()].empty())
	{
		//vector<vector<pair<User, int> > > copyGraph(graph);

		
	}

	vector<pair<User, int>> friends = graph[temp.GetId()];
	int size = friends.size();
	vector<bool> visited(MAX_SIZE_OF_GRAPH, false);
	queue<pair<User,int> > q;
	visited[temp.GetId()] = true;
	for (int i = 0; i < size; i++)
	{
		int sumRelation = friends[i].second;
		int index = friends[i].first.GetId();
		int size1 = graph[index].size();

		vector<pair<User, int> > friendOfFriends = graph[index];
		visited[index] = true;
		

			for (int j = 0; j < friendOfFriends.size(); j++)
			{
				if (!visited[friendOfFriends[j].first.GetId()] &&  friendOfFriends[j].second!=4)
				{
					cout << friendOfFriends[j].first.GetName() << ' ';
					//sumRelation += graph[index][j].second;
				//	cout << friendOfFriends[j].first.GetName() << " goes in queueu ";
					q.push(make_pair(friendOfFriends[j].first, sumRelation+graph[index][j].second));
				}
				
			
			}
	  
	}
	cout << endl;

	int numberOfPrints = 0;
	queue<pair<User, int> > copyQueue(q);
	while (!q.empty())
	{
		if (numberOfPrints == 30)
		{
			break;
		}
		pair<User, int> v = q.front();
		q.pop();

		if (visited[v.first.GetId()])
		{
			continue;
		}
		visited[v.first.GetId()] = true;
		if (v.second >= MAX_SIZE_OF_RELATION_TO_RECOMMEND)
		{
			cout << v.first.GetName() << ' ';
			numberOfPrints++;
		}

		if (!graph[v.first.GetId()].empty())
		{
			int size2 = graph[v.first.GetId()].size();

			for (int i = 0; i < size2; i++)
			{
				if (!visited[graph[v.first.GetId()][i].first.GetId()])
				{
					q.push(make_pair(graph[v.first.GetId()][i].first, v.second + graph[v.first.GetId()][i].second));
					visited[graph[v.first.GetId()][i].first.GetId()] = true;
				}
			}
		}
	}

}


int SocialMedia::ReturnCommand(const string& command)
{
	if (command == "normal")
	{
		return 1;
	}
	else if (command == "bestie")
	{
		return 2;
	}
	else if (command == "family")
	{
		return 3;
	}
	else
	{
		return 4;
	}
}



SocialMedia::SocialMedia()
{
	graph.resize(MAX_SIZE_OF_GRAPH);

}


bool SocialMedia::searchForUser(string name)
{
	int size = allUsers.size();
	for (int i = 0; i < size; i++)
	{
		

		if (allUsers[i].GetName() == name)
		{
			return true;
		}
	}
	return false;
}


bool SocialMedia::AddUser(User& temp)
{
	if (!searchForUser(temp.GetName()))
	{
		//working code here
		allUsers.push_back(temp);
		cout << "User added Succesfully" << endl;
		return true;
	}
	else
	{

		temp.MinusStatic();
		cout << "User Already Exists" << endl;
		return false;
	}
}



bool SocialMedia::CheckIfUsersAreLinked(const User& user1, const User& user2)
{
	int id1 = user1.GetId();
	int id2 = user2.GetId();

	bool found = false;

	if (graph[id1].empty())
	{
		return false;
	}

	int size = graph[id1].size();
	for (int i = 0; i < size; i++)
	{
		if (graph[id1][i].first.GetName() == user2.GetName())
		{
			found = true;
			break;
		}
	}
	return found;
}





bool SocialMedia::MakeFriendShip(const string& user1, const string& user2,string typeOfFriendShip)
{
	if (!searchForUser(user1) || !searchForUser(user2))
	{
		cout << "Users not found" << endl;
		return false;
	}


	

	User u1 = ReturnUser(user1);
	User u2 = ReturnUser(user2);

	string name1 = u1.GetName();
	string name2 = u2.GetName();

	if(CheckIfTwoUsersAreBanned(name1, name2) == true)
	{
		cout << "Users are banned from eachOther and can not be linked to be friends" << endl;
		return false;
	}

	if (CheckIfUsersAreLinked(u1, u2) == true)
	{
		cout << "They are already friends" << endl;
		cout << "Relinking  " << endl;
		int relation = ReturnCommand(typeOfFriendShip);
		int size1 = graph[u1.GetId()].size();
		for (int i = 0; i < size1; i++)
		{
			if (graph[u1.GetId()][i].first.GetName() == name2)
			{

				
				graph[u1.GetId()][i].second = relation;
				break;
			}
		}

		int size2 = graph[u2.GetId()].size();
		for (int i = 0; i < size2; i++)
		{
			if (graph[u2.GetId()][i].first.GetName() == name1)
			{
				graph[u2.GetId()][i].second = relation;
				break;
			}
		}

		//PrintFriendShip(user1, user2);
		return true;
	}
	else
	{
		int relation = ReturnCommand(typeOfFriendShip);
		graph[u1.GetId()].push_back(make_pair(u2, relation));
		graph[u2.GetId()].push_back(make_pair(u1, relation));

		//PrintFriendShip(user1, user2);


		cout << "FriendShip Made :) " << endl;
		return true;
	}
}



bool SocialMedia::RemoveUser(const string& name)
{
	if (!searchForUser(name))
	{
		cout << "User does not exist" << endl;
		return false;
	}
	//Here we know that user exists so we do not jave to check in functions ReturnIndexOfUser AND RemoveFromGraph if he exists again!!!
	else
	{
		int index = ReturnIndexOfUser(name);
		RemoveFromGraph(name);
		allUsers.erase(allUsers.begin() + index);
	//	this->PRINTALLFRIENDSHIPS();
		return true;
	}
	return true;
}



//THIS IS a private function and it is calles in RemoveUser
void SocialMedia::RemoveFromGraph(const string& name)
{
	
	vector<pair<User, int> > saveFriendsOfDeletedUser;
	User toRemove = ReturnUser(name);
	int IndexToRemove = toRemove.GetId();
	int size = graph[IndexToRemove].size();
	for (int i = 0; i < size; i++)
	{
		saveFriendsOfDeletedUser.push_back(make_pair(graph[IndexToRemove][i].first, graph[IndexToRemove][i].second));
	}

	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < (signed)graph[saveFriendsOfDeletedUser[i].first.GetId()].size(); j++)
		{

			if (graph[saveFriendsOfDeletedUser[i].first.GetId()][j].first.GetName() == name)
			{
				graph[saveFriendsOfDeletedUser[i].first.GetId()].erase(graph[saveFriendsOfDeletedUser[i].first.GetId()].begin() + j);
				break;
			}		
		}
	}

	indexOfReomvedUser.push_back(IndexToRemove);
}



int SocialMedia::ReturnIndexOfUser(const string& name)
{
	int size = allUsers.size();
	for (int i = 0; i < size; i++)
	{
		if (allUsers[i].GetName() == name)
		{
			return i;
		}
	}
	return -1;
}



void SocialMedia::InfoForSearchedUser(const string& name)
{
	if (!searchForUser(name))
	{
		cout << "User does not exist!" << endl;
		return;
	}
	//Here we know that user exists
	User client = ReturnUser(name);
	cout << "User name is : " << client.GetName() << "  and is " << client.getAge() << " years old" << endl;
	cout << "Friend list is  :  ";
	int indexOfClient = client.GetId();
	int size = graph[indexOfClient].size();
	for (int i = 0; i < size; i++)
	{
		if (graph[indexOfClient][i].second == BAN_VALUE)
		{
			//cout << "It looks like users are bannned  :"<< graph[indexOfClient][i].first.GetName() <<endl;
			continue;
		}
		cout << graph[indexOfClient][i].first.GetName() <<" ";
	}
	cout << endl;
}



User SocialMedia::ReturnUser(const string& name)
{
	int size = allUsers.size();
	for (int i = 0; i < size; i++)
	{
		if (allUsers[i].GetName() == name)
		{
			return allUsers[i];
		}
	}
	return User("Error", 9999);
}



void SocialMedia::Ban(const string& name1, const string& name2)
{
	//check if they exist


	if (CheckIfTwoUsersAreBanned(name1, name2))
	{
		cout << "FAIL USERS ARE  ALREADY BANNED " << endl;

		PrintFriendShip(name1, name2);

		return;
	}

	//Here we know that they exist
	User client1 = ReturnUser(name1);
	User client2 = ReturnUser(name2);





	int idClient1 = client1.GetId();
	int idClient2 = client2.GetId();

	int sizeFriendShipClient1 = graph[idClient1].size();
	int sizeFreindShipClient2 = graph[idClient2].size();

	User u1 = ReturnUser(name1);
	User u2 = ReturnUser(name2);

	bool found = false;

	for (int i = 0; i < sizeFriendShipClient1; i++)
	{
		if (graph[idClient1][i].first.GetName() == name2)
		{
			graph[idClient1][i].second = BAN_VALUE;
			found = true;
			break;

		}
	}

	if (!found)
	{
		this->MakeFriendShip(name1, name2);
		for (int i = 0; i < graph[idClient1].size(); i++)
		{
			if (graph[idClient1][i].first.GetName() == name2)
			{
				graph[idClient1][i].second = BAN_VALUE;
				found = true;
				break;

			}
		}

		for (int i = 0; i < graph[idClient2].size(); i++)
		{
			if (graph[idClient2][i].first.GetName() == name1)
			{
				graph[idClient2][i].second = BAN_VALUE;
				break;
			}
		}
		return;

	}


	for (int i = 0; i < sizeFreindShipClient2; i++)
	{
		if (graph[idClient2][i].first.GetName() == name1)
		{
			graph[idClient2][i].second = BAN_VALUE;
			break;
		}
	}

	cout << " Users " << name1 << " has banned " << name2 << " :( " << endl;
//	PrintFriendShip(name1, name2);


}



bool SocialMedia::CheckIfTwoUsersAreBanned(const string& name1, const string& name2)
{
	if (!searchForUser(name1) || !searchForUser(name2))
	{
		cout << "User does not exist! Try again " << endl;
		return false;
	}


	User client1 = ReturnUser(name1);
	User client2 = ReturnUser(name2);

	int idClient1 = client1.GetId();
	int idClient2 = client2.GetId();

	int sizeFriendShipClient1 = graph[idClient1].size();
	int sizeFreindShipClient2 = graph[idClient2].size();

	for (int i = 0; i < sizeFriendShipClient1; i++)
	{
		if (graph[idClient1][i].first.GetName() == name2)
		{
			if (graph[idClient1][i].second == BAN_VALUE)
			{
				return true;
			}
			
		}
	}

	for (int i = 0; i < sizeFreindShipClient2; i++)
	{
		if (graph[idClient2][i].first.GetName() == name1)
		{
			if (graph[idClient2][i].second == BAN_VALUE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}


	return false;

}

void SocialMedia::RemoveFriendShip(const string& name1, const string& name2)
{
	if (!searchForUser(name1) || !searchForUser(name2))
	{
		cout << "User does not exist! " << endl;
		return;
	}

	User client1 = ReturnUser(name1);
	User client2 = ReturnUser(name2);

	if(CheckIfUsersAreLinked(client1,client2) == false)
	{
		cout << "Users are not friends" << endl;
		return;
	}
	int idClient1 = client1.GetId();
	int idClient2 = client2.GetId();


	int sizeOFClient1Friends = graph[idClient1].size();
	int sizeOFClient2Friends = graph[idClient2].size();


	for (int i = 0; i < sizeOFClient1Friends; i++)
	{
		if (graph[idClient1][i].first.GetName() == name2)
		{
			graph[idClient1].erase(graph[idClient1].begin() + i);
			break;
		}
	}


	for (int i = 0; i < sizeOFClient2Friends; i++)
	{
		if (graph[idClient2][i].first.GetName() == name1)
		{
			graph[idClient2].erase(graph[idClient2].begin() + i);
			break;
		}
	}
	cout << " FriendShip Removed :(" << endl;
	//  PrintFriendShip(name1, name2);
} 


int main()
{
	SocialMedia facebook;
	facebook.RestoreGraph(filename);

	while (true)
	{
		string command;
		cin >> command;
		if (command == "create")
		{
			string name;
			int age;
			cout << "Enter name: ";
			cin >> name;
			//cout << endl;
			cout << "Enter age: ";
			cin >> age;

			User client(name, age);
			facebook.AddUser(client);
		//	{
				//ifile << client;
		//	}
			facebook.printUsers();
		}

		else if (command == "link")
		{
			string name1, name2;
			string typeOfFriendship;
			cin >> name1 >> name2>>typeOfFriendship;
			facebook.MakeFriendShip(name1, name2,typeOfFriendship);
		}
		else if (command == "ban")
		{
			string name1, name2;
			cin >> name1 >> name2;
			facebook.Ban(name1, name2);
		}
		else if (command == "delink")
		{
			string name1, name2;
			cin >> name1 >> name2;
			facebook.RemoveFriendShip(name1,name2);
		}
		else if (command == "find")
		{
			string userToFind;
			cin >> userToFind;
			facebook.InfoForSearchedUser(userToFind);
		}
		else if (command == "delete")
		{
			string name;
			cin >> name;
			facebook.RemoveUser(name);
		}
		else if (command == "reccomend")
		{
			string name;
			cin >> name;
			facebook.Recommend(name);
		}
		else
		{
			facebook.WriteToFileUsers(filename);
			break;
		}
	}
}



