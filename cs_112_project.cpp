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
        string prefferedgenre;
    public: 
        User(string name, int pin,string prefferedgenre)
        {
            this->name = name;
            this->pin = pin;
            this->prefferedgenre=prefferedgenre;
        }
        string getPrefferedgenre(){return prefferedgenre;}
        string getName(){return name;}
        int getPin(){return pin;}
        void setPrefferedgenre(string prefferedgenre){this->prefferedgenre = prefferedgenre;}
        void setName(string name){this->name = name;}
        void setPin(int pin){this->pin = pin;}
};
class Movie{
	private:
		string m_name,genre;
        vector<int>ratings;
        
	public:
		Movie(string m,int r,string g)
		{
			m_name=m;
            genre=g;
		}
        int getRating(int i){return ratings[i];}
		string getName(){return m_name;}
        string getGenre(){return genre;}
        void setRating(int r,int i){ratings[i]=r;}
		void setName(string m2){m_name=m2;}
        void setGenre(string g2){genre=g2;}	
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
        double getAverageRating()
        {
            if (ratings.empty()) return 0.0;
            double sum = 0.0;
            for (int rating : ratings)
            {
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
    string genre;
    cout<<"Enter your genre: ";
    cin>>genre;
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
            users.emplace_back(name,pin,genre);
        }
    }
}
void changePrefferedgenre(vector<User>&users,int &userno)
{
    string genre;
    cout<<"Enter the genre you prefer to watch"<<endl;
    getline(cin,genre);
    users[userno].setPrefferedgenre(genre);
}
int login(vector<User>&users)
{
    fstream file ("users.txt",ios::in);
    stringstream ss;
    string name;
    int userno;
    int pin;
    int userno;
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
                userno=i;
                return userno;
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
    return ;
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
vector<Movie> ReadmMoviesFromFile()
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
    file<<name<<" "<<genre<<" "<<rating;
    file.close();
}
void MovieRecommend(vector<Movie>& movies,vector<User>&users,int &userno) 
{
    string genre;
    bool foundRecommendations = false;
    genre=users[userno].getPrefferedgenre();
    for (int i=0;i,movies.size();i++) 
    {
        if (movies[i].getGenre() == genre) 
        {
            cout << "Name: " << movies[i].getName() << ", Rating: " << movies[i].getRating(i) << endl;
            foundRecommendations = true;
        }
    }
    if (!foundRecommendations) 
    {
        cout << "No movies found in the genre \"" << genre << "\"" << endl;
    }
}
int main()
{
    vector<Movie> movies = ReadmMoviesFromFile();
}
