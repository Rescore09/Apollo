#include <curl/curl.h>
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    std::string url = "http://127.0.0.1:8080";
    int choice;
    std::cout << "1.Login  2.Register\nEnter choice (1 or 2): ";
    std::cin >> choice;
    std::cin.ignore();

    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::string endpoint = (choice == 1) ? "/login" : "/register";
    std::string json = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_URL, (url + endpoint).c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json.size());

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) std::cerr << curl_easy_strerror(res) << std::endl;
        else std::cout << response_string << std::endl;

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
