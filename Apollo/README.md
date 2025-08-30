# Apollo

A lightweight HTTP server in C++ using [Crow](https://github.com/CrowCpp/Crow) with a simple file-based user database.

<div style="background-color: #5f4e14ff; padding: 10px; border-left: 5px solid #ffeeba;">
  ⚠️ <strong>Warning:</strong> This version is very trash, and this project is simply for fun. In the future I will update this using actual databases and Hardware ID locks (Just recreating CerberAuth.)
</div>

## Features

* Register new users
* Login existing users
* JSON request/response
* File-based database
* Multithreaded server
* Comes with Python, Javascript, and C++ example usages.

## Requirements

* C++17 compiler (Visual Studio works perfectly)
* [Crow 1.2.1](https://github.com/CrowCpp/Crow)
* Optional: [vcpkg](https://github.com/microsoft/vcpkg) for dependency management

## Installation

1. Clone this repository:

```bash
git clone https://github.com/rescore/Apollo.git
cd Apollo
```

2. Install Crow (if using vcpkg):

```bash
vcpkg install crow
```

3. Setup the enviroment:

```bash
vcpkg integrate install
```

## Usage

Build the executable:


Server listens on `http://localhost:8080`.

### API Endpoints

* **POST /register**

Request JSON:

```json
{
  "username": "rescore",
  "password": "pass123"
}
```

Response JSON:

```json
{
  "status": "success",
  "message": "User registered!"
}
```

* **POST /login**

Request JSON:

```json
{
  "username": "rescore",
  "password": "pass123"
}
```

Response JSON:

```json
{
  "status": "success",
  "message": "Logged in!"
}
```

## Notes

* User database is stored in `users.sexy`
* Passwords are stored in plain text (for simplicity) — **not recommended for production**
