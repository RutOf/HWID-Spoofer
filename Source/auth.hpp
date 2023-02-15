#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>

namespace KeyAuth {

    struct ApiData {
        std::string numUsers;
        std::string numOnlineUsers;
        std::string numKeys;
        std::string version;
        std::string customerPanelLink;
        std::string username;
        std::string ipAddress;
        std::string hardwareId;
        std::string createdDate;
        std::string lastLoginDate;
        std::vector<std::string> subscriptions;
        std::string expiryDate;
        bool success;
        std::string message;
    };

    class Api {
    public:
        Api(const std::string& name, const std::string& ownerId, const std::string& secret, const std::string& version, const std::string& url);

        void ban(const std::string& reason = "");
        void init();
        void check();
        void log(const std::string& message);
        void license(const std::string& key);
        std::string getVar(const std::string& varId);
        std::string webhook(const std::string& id, const std::string& params);
        void setVar(const std::string& varId, const std::string& varData);
        bool checkBlacklist();
        void upgrade(const std::string& username, const std::string& key);
        void login(const std::string& username, const std::string& password);
        void webLogin();
        void submitButton(const std::string& buttonValue);
        std::vector<unsigned char> downloadFile(const std::string& fileId);
        void registerUser(const std::string& username, const std::string& password, const std::string& key);

        ApiData getData() const;
    private:
        std::string sessionId_;
        std::string encryptionKey_;
        ApiData data_;
    };
}
