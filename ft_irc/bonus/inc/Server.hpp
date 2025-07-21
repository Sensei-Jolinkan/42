#pragma once

#include "libs.hpp"
#include "Admin.hpp"
#include "User.hpp"
#include "Bot.hpp"

enum InputState { WAIT_NICK = 0, WAIT_USER = 1, REGISTERED = 2, WAIT_PASSWORD = 3, JOINED = 4 };

class Server
{
    private:

        int _port;
        int _serverFd;
        int _epollFD;
        int _opt;
        int _userLimit;
        int _currentUsers;
        std::string _topic;
        std::string _passWord;

        bool _running;
        bool _invite;

        Admin _admin;
        std::map<int, Admin *> _staffs;
        std::map<int, int> _staffStates;
        std::map<int, User *> _users;
        std::map<int, int> _userStates;
        std::map<int, std::string> _tempNick;
        std::map<int, std::string> _tempUser;

        struct sockaddr_in _serverAddr;
        struct epoll_event _events[MAX_EVENTS];
        char _buffer[IRC_MESSAGE_MAX];

        Bot bot;
        bool _OnOff;

        Server( const Server & );
        Server& operator=( const Server & );

    public:

        Server( int port, std::string passWord );
        ~Server();

        const std::string& getPassWord() const;
        const std::string& getTopic() const;
        int getPort() const;

        const std::string& getAdminNickName() const;
        const std::string& getAdminUserName() const;
        const std::string& getStaffNickName() const;
        const std::string& getStaffUserName() const;

        void makeNonBlocking(int fd);
        void setUpServer();

        void run();
        void freeData();
        int createNewUser();
        int commandAdmin();
        int commandUserStaff( int event_fd );
        int userToStaff( int fd );
        int staffToUser( int fd );

        std::string readInput(int fd);

        void printMsgAdmin( int fd, const std::string& msg ) const;
        void printMsgServer( int fd, const std::string& msg ) const;
        void printMsgUser( int fd, const std::string& msg, const std::string& nickName ) const;
        void printMsgStaff( int fd, const std::string& msg, const std::string& nickName ) const;
};

std::string getCurrentTime();