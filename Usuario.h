#include <string>

using namespace std;

struct Usuario {

    string university;
    unsigned long long UsuarioID;
    string UsuarioName;
    int numberTweets;
    int friendsCount;
    int followersCount;
    string createdAt;

    Usuario(string university, unsigned long long UsuarioID, string UsuarioName, int numberTweets, int friendsCount, int followersCount, string createdAt): 
        
        university(university), 
        UsuarioID(UsuarioID), 
        UsuarioName(UsuarioName), 
        numberTweets(numberTweets), 
        friendsCount(friendsCount), 
        followersCount(followersCount), 
        createdAt(createdAt){}
    
    Usuario() {
        university = ""; 
        UsuarioID = 0; 
        UsuarioName = ""; 
        numberTweets = 0; 
        friendsCount = 0; 
        followersCount = 0; 
        createdAt = "";
    }
};