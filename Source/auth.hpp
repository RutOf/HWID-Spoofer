#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>

namespace KeyAuth {
    class API {
    public:
        API(const std::string& name, const std::string& ownerId, const std::string& secret, const std::string& version, const std::string& url);

        void Ban(const std::string& reason = "");
        void Init();
        void Check();
        void Log(const std::string& message);
        void License(const std::string& key);
        std::string Var(const std::string& varId);
        std::string Webhook(const std::string& id, const std::string& params);
        void SetVar(const std::string& var, const std::string& varData);
        std::string GetVar(const std::string& var);
        bool CheckBlack();
        void Upgrade(const std::string& username, const std::string& key);
        void Login(const std::string& username, const std::string& password);
        void WebLogin();
        void Button(const std::string& value);
        std::vector<unsigned char> Download(const std::string& fileId);
        void Register(const std::string& username, const std::string& password, const std::string& key);

        struct Data {
            std::string numUsers;
            std::string numOnlineUsers;
            std::string numKeys;
            std::string version;
            std::string customerPanelLink;
            std::string username;
            std::string ip;
            std::string hwid;
            std::string createdDate;
            std::string lastLogin;
            std::vector<std::string> subscriptions;
            std::string expiry;
            bool success;
            std::string message;
        };
        Data data;
    private:
        std::string m_sessionId;
        std::string m_encryptionKey;
    };
}
