#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include<Windows.h>
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
            return out;
        }
};
class Movie
{
	private:
		string m_name,genre;
        double ratings;
        int numrates;
        vector<string> comments;
	public:
        int counter=1;
		Movie(string m = "",double r = 0,string g = "",int numrates=0)
		{
			m_name=m;
            ratings=r;
            genre=g;
            this->numrates=numrates;
		}
        int getnumrates(){return numrates;}
        double getRating(){return ratings;}
		string getName(){return m_name;}
        string getGenre(){return genre;}
        void setnumrates(int r){numrates=r;}
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
            out<<"Name: "<<obj.m_name<<endl<<"Genre: "<<obj.genre<<endl<<"Ratings: "<<setprecision(3)<<obj.ratings<<"Veiws: "<<obj.numrates<<endl;
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
void addComment(vector<vector<string>>& comments, int movieno, vector<User>& users,int userno) 
{
    string comment;
    cout << "Enter your comment: ";
    getline(cin >>ws,comment);
    Beep(700,200);
    comment=users[userno].getName() + ": " + comment;
    comment = Spaceremover(comment);
    comments[movieno-1].push_back(comment);
    WriteCommentsToFile(comments); 
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
        file << Spaceremover(movies[i].getName()) << " " << Spaceremover(movies[i].getGenre()) << " " << movies[i].getRating()<<" "<<movies[i].getnumrates() << endl;
    }
    file.close();
}
void WriteUsersToFile(vector<User>& users) 
{
    ofstream file("user.txt");
    for (int i = 0; i < users.size(); i++) 
    {
        file << Spaceremover(users[i].getName()) << " " << users[i].getPin() << " " << Spaceremover(users[i].getPrefferedgenre()) << endl;
    }
    file.close();
}
void AddRating(int movieno, vector<Movie>& movies, double rat)
{
    if (rat > 4 || rat < 1)
    {
        cout << "Invalid rating, enter number between 1 and 4" << endl;
        Sleep(1000);
        return;
    }
    else
    {
        int num = movies[movieno - 1].getnumrates();
        num++; // Increment the number of rates
        movies[movieno - 1].setnumrates(num);
        double currate = ((movies[movieno - 1].getRating() * movies[movieno - 1].getnumrates()) + rat) / (movies[movieno - 1].getnumrates() + 1);
        movies[movieno - 1].setRating(currate);
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
    Beep(700,200);
    cout<<"Enter your pin: (4 digits): ";
    cin>>pin;
    Beep(700,200);
    cout<<"Enter your preffered genre: ";
    cin.ignore();
    getline(cin,genre);
    Beep(700,200);
    if(pin>9999||pin<1000)
    {
        cout<<"Invalid pin, try again"<<endl;
        Sleep(1000);
        return;
    }
    cin.ignore();
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            cout<<"User already in use,choose another username"<<endl;
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
    Beep(700,200);
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
    Beep(700,200);
    for(int i=0;i<users.size();i++)
    {
        if(users[i].getName()==name)
        {
            userfound=true;
            userno=i;
            cout<<"Enter your pin(4-digit): ";
            cin>>pin;
            Beep(700,200);
            if(users[i].getPin()==pin)
            {
                pinmatches=true;
                break;
            }
            else
            {
                break;
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
        Sleep(1000);
        return -1;
    }
    else
    {
        cout<<"account doesnt exist"<<endl;
        Sleep(1000);
        return -1;
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
    int t_numrates;
    while(getline(file, line))
    {
        ss<<line;
        ss>>t_name>>t_genre>>t_rating>>t_numrates;
        t_name=Spacer(t_name);
        t_genre=Spacer(t_genre);
        movies.emplace_back(t_name, t_rating,t_genre,t_numrates);
        ss.clear();
    }
    file.close();
    return movies;
}
void MovieRecommend(vector<Movie>& movies,vector<User>&users,int userno) 
{
    Sleep(1);
    system("CLS");
    string genre;
    bool foundRecommendations = false;
    genre=users[userno].getPrefferedgenre();
for (int i = 0; i < movies.size(); i++) 
{
    if (movies[i].getGenre() == genre) 
    {
        if (i < 9) 
        {
            cout << " |  " << setw(22) << left << movies[i].getName().substr(0, 20) << "| "
                 << setw(7) << fixed << setprecision(2) << movies[i].getRating() << "| "
                 << setw(9) << movies[i].getGenre() << endl;
        }
        else if (i < 1000) 
        {
            cout << " | " << setw(22) << left << movies[i].getName().substr(0, 20) << " | "
                 << setw(7) << fixed << setprecision(2) << movies[i].getRating() << " | "
                 << setw(9) << movies[i].getGenre() << endl;
        }
        foundRecommendations = true;
    }
}

    if (!foundRecommendations) 
    {
        cout << "No movies found in the genre \"" << genre << "\"" << endl;
    }
}
void displayMainMenu() 
{
    Sleep(1);
    system("CLS");
    cout << "IMTB - Interactive Movie Recommendation System" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "1. Login" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
}
void displayMovieList(vector<Movie>& movies, const string& username) 
{
    Sleep(1);
    system("CLS");
    cout << "==============================================" << endl;
    cout << "Movie List" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "No. | Title                 | Rating | Genre" << endl;
    cout << "----------------------------------------------" << endl;
    for (size_t i = 0; i < 9; ++i) 
    {
        cout  << i+1 << "  | " << setw(22) << left << movies[i].getName().substr(0, 20) << " | "
             << setw(7) << fixed << setprecision(2) << movies[i].getRating() << " | "
             << setw(9) << movies[i].getGenre() << endl;
    }
    for (size_t i = 9; i < movies.size(); ++i) 
    {
        cout  << i+1 << " | " << setw(22) << left << movies[i].getName().substr(0, 20) << " | "
             << setw(7) << fixed << setprecision(2) << movies[i].getRating() << " | "
             << setw(9) << movies[i].getGenre() << endl;
    }
    cout << "----------------------------------------------" << endl;
    cout << right << setw(50) << "Logged in as: " << username << endl;
}

void displayMovieDetails( Movie& movie, vector<string>& comments) 
{
    Sleep(1);
    system("CLS");
    cout << "IMTB - Movie Details" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Title: " << movie.getName() << endl;
    cout << "Rating: " << fixed << setprecision(2) << movie.getRating() << endl;
    cout << "Genre: " << movie.getGenre() << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Comments:" << endl;
    for (const string& comment : comments) 
    {
        cout << "- " << Spacer(comment) << endl;
    }
    cout << "----------------------------------------------" << endl;
}
void addRating(vector<Movie>& movies, int index) 
{
    double rating;
    cout << "Enter your rating for this movie (1-4): ";
    cin >> rating;
    Beep(700,200);
    AddRating(index, movies, rating);
}
int main() 
{
    vector<User> users = ReadUsersFromFile();
    vector<Movie> movies = ReadMoviesFromFile();
    vector<vector<string>>comments=ReadCommentsFromFile();
    int currentUser;
    bool loggedIn = false;
    int choice;

    while (true) 
    {
        displayMainMenu();
        cout << "Enter your choice (1,2,3): ";
        cin >> choice;
        Beep(700,200);
        if (choice == 1) 
        {
            cin.ignore();
            currentUser = login(users);
            if (currentUser != -1) 
            {
                loggedIn = true;
                cout << "Logged in successfully!" << endl;
                Sleep(1000);
            } 
            else 
            {
                Sleep(1000);
            }
        } 
        else if (choice == 2) 
        {
            cin.ignore();
            signup(users);
        } 
        else if (choice == 3) 
        {
            cout << "Thank you for using our system. Goodbye!" << endl;
            return 0;
        } 
        else 
        {
            cout << "Invalid choice! Please try again." << endl;
            Sleep(1000);
        }
        if (loggedIn) 
        {
            while (true) 
            {
                string username=users[currentUser].getName();
                displayMovieList(movies,username);
                cout << "Enter the index of the movie you would like to watch (0 to return to main menu): ";
                cin >> choice;
                Beep(700,200);
                if (choice == 0) 
                {
                    break;
                } 
                else if (choice < 1 || choice > static_cast<int>(movies.size())) 
                {
                    cout << "Invalid movie index! Please try again." << endl;
                    Sleep(1000);
                } 
                else 
                {
                    displayMovieDetails(movies[choice - 1], ReadCommentsFromFile()[choice - 1]);
                    cout << "Would you like to rate this movie? (y/n): ";
                    char ratechoice;
                    cin>>ratechoice;
                    Beep(700,200);
                    if (ratechoice == 'y' || ratechoice == 'Y')
                    {
                        addRating(movies, choice);
                    }
                    cout << "Would you like to add a comment for this movie? (y/n): ";
                    char addCommentChoice;
                    cin >> addCommentChoice;
                    Beep(700,200);
                    if (addCommentChoice == 'y' || addCommentChoice == 'Y') 
                    {
                        addComment(comments, choice, users, currentUser);
                    }
                    cout << "Would you like movie recommendations based on your preferred genre? (y/n): ";
                    char recommendationChoice;
                    cin >> recommendationChoice;
                    Beep(700,200);
                    if (recommendationChoice == 'y' || recommendationChoice == 'Y') 
                    {
                        MovieRecommend(movies, users, currentUser);
                    }
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
            }
        }
    }
}
