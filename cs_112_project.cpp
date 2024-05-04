#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
class User
{
    private:
        string name;
        int pin;
    public: 
        User(string name, int pin)
        {
            this->name = name;
            this->pin = pin;
        }
        string getName(){return name;}
        int getPin(){return pin;}
        void setName(string name){this->name = name;}
        void setPin(int pin){this->pin = pin;}
};
void signup(vector<User> &users)
{
    fstream file ("users.txt");
    stringstream ss;
    string name;
    int pin;
    cin.ignore();
    cout<<"Enter your name: ";
    getline(cin,name);
    cout<<"Enter your pin: (4 digits)";
    cin>>pin;
    if(pin<9999||pin>1000)
    {
        cout<<"Invalid pin, try again";
        goto end;
    }
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            cout<<"User already in use,choose another username";
            goto end;
        }
//        else
//        {
//            users.emplace_back(name,pin);
//        }
    }
    end:;
}
void login(vector<User>&users)
{

}

// Creating Read from file function
vector<User> ReadUsersFromFile()
{
    vector<User> users;
    stringstream ss;
    fstream file("user.txt",ios::app);
    string line;
    string t_name;
    int t_pin;
    while(getline(file, line))
    {
        ss<<line;
        if(ss>>t_name>>t_pin)
        {
            users.emplace_back(t_name,t_pin);
            ss.clear();
        }
    }
    file.close();
    return users;
}
class Movies{
	private:
		int rating;
		string m_name;
	public:
		Movies(string m,int r)
		{
			m_name=m;
			rating=r;
		}
		string getname(){return m_name;}
		int getrating(){return rating;}
		void setname(string m2){m_name=m2;}
		void setname(int r2){rating=r2;}	
};

vector<User> ReadmovieFromFile()
{
    vector<User> users;
    stringstream ss;
    fstream file("Movies.txt",ios::app);
    string line;
    string t_name;
    int t_pin;
    while(getline(file, line))
    {
        ss<<line;
        if(ss>>t_name>>t_pin)
        {
            users.emplace_back(t_name, t_pin);
            ss.clear();
        }
    }
    file.close();
    return users;
}
int main()
{

}
