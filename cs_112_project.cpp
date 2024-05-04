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
class Movies{
	private:
		string m_name,genre;
        vector<int> ratings;
        double sum=0.0;
	public:
		Movies(string m,int r,string g)
		{
			m_name=m;
            genre=g;
		}
		string getname(){return m_name;}
        string getgenre(){return genre;}
		void setname(string m2){m_name=m2;}
        void setgenre(string g2){genre=g2;}
        void addrating(int rating)
        {
            if(rating >=1 && rating <=4)
            {
                ratings.push_back(rating);
                cout<<"Thanks for your precious remarks\n";
            }
            else
            {
                cout<<"Invalid rating, rate between 1-4\n";
            }
        }
         double getAverageRating() const {
        if (ratings.empty()) return 0.0;
        double sum = 0.0;
        for (int rating : ratings) {
            sum += rating;
        }
        return sum / ratings.size();
    }
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
