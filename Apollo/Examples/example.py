import requests

url = "http://127.0.0.1:8080"  

def register(username, password):
    payload = {"username": username, "password": password}
    response = requests.post(f"{url}/register", json=payload)
    if response.status_code == 200:
        data = response.json()
        print(f"Register: {data['status']} - {data['message']}")
    else:
        print(f"Register failed with status code {response.status_code}: {response.text}")

def login(username, password):
    payload = {"username": username, "password": password}
    response = requests.post(f"{url}/login", json=payload)
    if response.status_code == 200:
        data = response.json()
        print(f"Login: {data['status']} - {data['message']}")
    else:
        print(f"Login failed with status code {response.status_code}: {response.text}")

def main():
    print("1.Login  2.Register")
    choice = input("Enter choice (1 or 2): ")
    if choice == '1':
        username = input("Enter username: ")
        password = input("Enter password: ")
        login(username, password)
    elif choice == '2':
        username = input("Enter username: ")
        password = input("Enter password: ")
        register(username, password)
    else:
        print("Invalid choice. Please enter 1 or 2.")    


if __name__ == "__main__":
    main()