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
class Movie{
	private:
		int rating;
		string m_name;
	public:
		Movie(string m,int r)
		{
			m_name=m;
			rating=r;
		}
		string getname(){return m_name;}
		int getrating(){return rating;}
		void setname(string m2){m_name=m2;}
		void setname(int r2){rating=r2;}	
};

void signup(vector<User>&users)
{
    fstream file ("users.txt",ios::app);
    stringstream ss;
    string name;
    int pin;
    cout<<"Enter your name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter your pin: (4 digits)";
    cin>>pin;
    if(pin>9999||pin<1000)
    {
        cout<<"Invalid pin, try again";
        return;
    }
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            cout<<"User already in use,choose another username";
            return;
        }
        else
        {
            users.emplace_back(name,pin);
        }
    }
}
void login(vector<User>&users)
{
    fstream file ("users.txt",ios::in);
    stringstream ss;
    string name;
    int pin;
    bool userfound=false;
    cout<<"Enter your name: ";
    cin.ignore();
    getline(cin,name);  
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            cout<<"Enter your pin: ";
            cin>>pin;
            if(users[i].getPin()==pin)
            {
                cout<<"Welcome "<<name<<endl;
                userfound=true;
            }
            else
            {
                cout<<"Wrong pin"<<endl;
            }
        }
    }  
    if(!userfound)
    {
        cout<<"User not found"<<endl;
    }
}
vector<User>ReadUsersFromFile()
{
    vector<User> users;
    stringstream ss;
    fstream file("user.txt",ios::in);
    string line;
    string t_name;
    int t_pin;
    while(getline(file, line))
    {
        ss<<line;
        ss>>t_name>>t_pin;
        users.emplace_back(t_name, t_pin);
        ss.clear();
    }
    file.close();
    return users;
}
vector<Movie> ReadmovieFromFile()
{
    vector<Movie> movies;
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
            movies.emplace_back(t_name, t_pin);
            ss.clear();
        }
    }
    file.close();
    return movies;
}
void WriteMoviesToFile(vector<Movie>&movies)
{
    fstream file("Movies.txt",ios::in);
    string name;
    int rating;
    string genre;
    cout<<"Enter movie name and release date: /n";
    cin.ignore();
    getline(cin,name);
    cout<<"Movie Genre: ";
    getline(cin,genre);
    cout<<"Movie Rating: ";
    cin>>rating;
    file<<name<<genre<<rating;
    file.close();
}
int main()
{

}
