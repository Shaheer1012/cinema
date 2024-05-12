#include <iostream>
#include <iomanip>
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
        User(string name, int pin,string prefferedgenre = "")
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
        friend ostream &operator <<(ostream &out,User &obj)
        {
            out<<"Username: "<<obj.name<<endl<<"Pin: "<<obj.pin<<endl<<"Preffered Genre: "<<obj.prefferedgenre<<endl;
        }
};
class Movie
{
	private:
		string m_name,genre;
        double ratings;
        vector<string> comments;
	public:
        int counter=1;
		Movie(string m = "",double r = 0,string g = "")
		{
			m_name=m;
            ratings=r;
            genre=g;

		}
        double getRating(){return ratings;}
		string getName(){return m_name;}
        string getGenre(){return genre;}
        void setRating(double r){ratings=r;}
		void setName(string m2){m_name=m2;}
        void setGenre(string g2){genre=g2;}	
        int moviecounter(){counter++;return counter;}
        friend istream &operator>>(istream &in, Movie &obj)
        {
            in>>obj.m_name>>obj.ratings>>obj.genre;
            return in;
        }
        friend ostream &operator <<(ostream &out,Movie&obj)
        {
            out<<"Name: "<<obj.m_name<<endl<<"Genre: "<<obj.genre<<endl<<"Ratings: "<<setprecision(3)<<obj.ratings<<endl;
            return out;
        }
};
string Spaceremover(string str)
{
    for(int i=0;i<str.size();i++)
    {
        if (str[i]==' ')
        {
            str[i]='_';
        }
    }
    return str;
}
string Spacer(string str)
{
    for(int i=0;i<str.size();i++)
    {
        if(str[i] == '_')
        {
            str[i]=' ';
        }
    }
    return str;
}
void WriteCommentsToFile(vector<vector<string>>& comments) 
{
    ofstream file("comments.txt");
    for (size_t i = 0; i < comments.size(); ++i) 
    {
        for (size_t j = 0; j < comments[i].size(); j++) 
        {
            file << Spaceremover(comments[i][j]) << " "; 
        }
        file<<endl;
    }
    file.close();
}
vector<vector<string>> ReadCommentsFromFile() 
{
    vector<vector<string>> comments;
    ifstream file("comments.txt");
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        vector<string> movieComments;
        string comment;
        while (getline(ss, comment,' ')) 
        {
            movieComments.push_back(comment); 
        }
        comments.push_back(movieComments);
    }
    file.close();
    return comments;
}
void addComment(vector<vector<string>>& comments, int movieno) 
{
    string comment;
    cout << "Enter your comment: ";
    getline(cin >>ws,comment);
    comment = Spaceremover(comment);
    comments[movieno-1].push_back(comment);
    WriteCommentsToFile(comments); 
}
void displayComments(vector<vector<string>>& comments, vector<Movie>& movies, vector<User>& users, int movieno) 
{
    cout << movies[movieno-1] << endl;
    for (int i = 1; i < comments[movieno-1].size(); i++) 
    { 
        cout << "- " << Spacer(comments[movieno-1][i]) << endl; 
    }
}
void DisplayMovies(int movieno,vector<Movie>&movies)
{
    cout<<"======================================="<<endl;
    cout<<movies[movieno-1];
}
void DisplayUsers(int userno,vector<User>&users)
{
    cout<<"======================================="<<endl;
    cout<<users[userno-1];
}
void WriteMoviesToFile(vector<Movie>& movies) 
{
    ofstream file("Movies.txt");
    for (int i = 0; i < movies.size(); i++) 
    {
        file << movies[i].getName() << " " << movies[i].getGenre() << " " << movies[i].getRating() << endl;
    }
    file.close();
}
void WriteUsersToFile(vector<User>& users) 
{
    ofstream file("user.txt");
    for (int i = 0; i < users.size(); i++) 
    {
        file << users[i].getName() << " " << users[i].getPin() << " " << users[i].getPrefferedgenre() << endl;
    }
    file.close();
}
void AddRating(int i,vector<Movie>&movies,double rat)
{
    if(rat>4)
    {
        cout<<"Invalid rating, enter number b/w (1-4)"<<endl;
        return;
    }
    else
    {
    double currate=(movies[i-1].getRating()+rat)/movies[i-1].moviecounter(); 
    movies[i-1].setRating(currate);
    WriteMoviesToFile(movies);
    }
}
void signup(vector<User>&users)
{
    fstream file ("users.txt",ios::app);
    stringstream ss;
    string name;
    int pin;
    string genre;
    bool userfound=false;
    cout<<"Enter your name: ";
    getline(cin,name);
    name=Spaceremover(name);
    cout<<"Enter your pin: (4 digits): ";
    cin>>pin;
    cout<<"Enter your preffered genre: ";
    cin.ignore();
    getline(cin,genre);
    genre=Spaceremover(genre); 
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
            userfound=true;
            return;
        }
    }
    if(!userfound)
    {
        users.emplace_back(name,pin,genre);
        WriteUsersToFile(users);
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
    bool userfound=false;
    bool pinmatches=false;
    cout<<"Enter your name: ";
    getline(cin,name);  
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            userfound=true;
            userno=i;
            cout<<"Enter your pin: ";
            cin>>pin;
            if(users[i].getPin()==pin)
            {
                pinmatches=true;
            }
        }
    }  
    if(userfound && pinmatches)
    {
        cout<<"Welcome "<<name<<endl;
        return userno;
    }
    else if(userfound && !pinmatches)
    {
        cout<<"Wrong pin"<<endl;
        return 0;
    }
    else
    {
        cout<<"User not found"<<endl;
        return 0;
    }
}
vector<User>ReadUsersFromFile()
{
    vector<User> users;
    stringstream ss;
    string prefferedgenre;
    fstream file("user.txt",ios::in);
    string line;
    string t_name;
    int t_pin;
    while(getline(file, line))
    {
        ss<<line;
        ss>>t_name>>t_pin>>prefferedgenre;
        t_name=Spacer(t_name);
        prefferedgenre=Spacer(prefferedgenre);
        users.emplace_back(t_name, t_pin,prefferedgenre);
        ss.clear();
    }
    file.close();
    return users;
}
vector<Movie> ReadMoviesFromFile()
{
    vector<Movie> movies;
    stringstream ss;
    fstream file("Movies.txt");
    string line;
    string t_name;
    string t_genre;
    double t_rating;
    while(getline(file, line))
    {
        ss<<line;
        ss>>t_name>>t_genre>>t_rating;
        t_name=Spacer(t_name);
        t_genre=Spacer(t_genre);
        movies.emplace_back(t_name, t_rating,t_genre);
        ss.clear();
    }
    file.close();
    return movies;
}
void MovieRecommend(vector<Movie>& movies,vector<User>&users,int userno) 
{
    string genre;
    bool foundRecommendations = false;
    genre=users[userno].getPrefferedgenre();
    for (int i=0;i<movies.size();i++) 
    {
        if (movies[i].getGenre() == genre) 
        {
            cout << "Name: " << movies[i].getName() << ", Rating: " << movies[i].getRating() << endl;
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
    vector<User> users = ReadUsersFromFile();
    vector<Movie> movies = ReadMoviesFromFile();
    vector<vector<string>>comments=ReadCommentsFromFile();
    displayComments(comments,movies,users,9); 
}
