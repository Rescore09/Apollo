const axios = require("axios");
const readline = require("readline");

const url = "http://127.0.0.1:8080";

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function register(username, password) {
    axios.post(`${url}/register`, { username, password })
        .then(response => {
            const data = response.data;
            console.log(`Register: ${data.status} - ${data.message}`);
            rl.close();
        })
        .catch(error => {
            if (error.response) {
                console.log(`Register failed with status code ${error.response.status}: ${error.response.data}`);
            } else {
                console.log(`Register failed: ${error.message}`);
            }
            rl.close();
        });
}

function login(username, password) {
    axios.post(`${url}/login`, { username, password })
        .then(response => {
            const data = response.data;
            console.log(`Login: ${data.status} - ${data.message}`);
            rl.close();
        })
        .catch(error => {
            if (error.response) {
                console.log(`Login failed with status code ${error.response.status}: ${error.response.data}`);
            } else {
                console.log(`Login failed: ${error.message}`);
            }
            rl.close();
        });
}

function main() {
    rl.question("1.Login  2.Register\nEnter choice (1 or 2): ", choice => {
        if (choice === '1') {
            rl.question("Enter username: ", username => {
                rl.question("Enter password: ", password => {
                    login(username, password);
                });
            });
        } else if (choice === '2') {
            rl.question("Enter username: ", username => {
                rl.question("Enter password: ", password => {
                    register(username, password);
                });
            });
        } else {
            console.log("Invalid choice. Please enter 1 or 2.");
            rl.close();
        }
    });
}

main();
