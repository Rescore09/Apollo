#include "crow.h"
#include <fstream>
#include <unordered_map>
#include <mutex>

// code isn't too good, will update it soon!

std::mutex db_mutex;
const std::string db_file = "users.sexy";

std::unordered_map<std::string, std::string> load_users() {
    std::lock_guard<std::mutex> lock(db_mutex);
    std::unordered_map<std::string, std::string> users;
    std::ifstream f(db_file);
    if (f.good()) {
        std::string u, p;
        while (f >> u >> p)
            users[u] = p;
    }
    return users;
}

void save_users(const std::unordered_map<std::string, std::string>& users) {
    std::lock_guard<std::mutex> lock(db_mutex);
    std::ofstream f(db_file);
    for (auto& [u, p] : users)
        f << u << " " << p << "\n";
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/register").methods(crow::HTTPMethod::Post)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username") || !body.has("password"))
            return crow::response(400, "Invalid JSON");

        std::string user = body["username"].s();
        std::string pass = body["password"].s();

        auto users = load_users();
        if (users.find(user) != users.end()) {
            crow::json::wvalue res;
            res["status"] = "error";
            res["message"] = "User already exists";
            return crow::response{ res };
        }

        users[user] = pass;
        save_users(users);

        crow::json::wvalue res;
        res["status"] = "success";
        res["message"] = "User registered!";
        return crow::response{ res };
        });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::Post)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username") || !body.has("password"))
            return crow::response(400, "Invalid JSON");

        std::string user = body["username"].s();
        std::string pass = body["password"].s();

        auto users = load_users();
        crow::json::wvalue res;

        if (users.find(user) != users.end() && users[user] == pass) {
            res["status"] = "success";
            res["message"] = "Logged in!";
        }
        else {
            res["status"] = "error";
            res["message"] = "Invalid credentials";
        }
        return crow::response{ res };
        });

    app.port(8080).multithreaded().run();
}
