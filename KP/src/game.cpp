#include <bits/stdc++.h>
#include "topology.h"
#include <sys/time.h>
#include <set>
#include "myZmq.h"
#include <string>
#include<time.h>
#include "tree.h"
#include <sstream>

std::string randNumber()
{
    std::string num;
    for (int i = 0; i < 4; i++)
        num += std::to_string(rand() % 10); 
    return num;
}

int main(int argc, char *argv[]){
    if (argc < 4){
        printf("Usage: ./main childID parentPort parentID\n");
        exit(-1);
    }
    srand(time(NULL));
    std::string number = randNumber();
    std::vector<std::string> players;
    // std::cout << atoi(argv[1]) << " " << atoi(argv[2]) << " " << atoi(argv[3]) << " " << atoi(argv[4]) << "\n";
    TNode node(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    int playerC = atoi(argv[4]), que = 0;
    while(true){
        std::string message;
        std::string command;
        message = receive_message(node.parent);
        std::istringstream request(message);
        request >> command;
        if(command == "pid"){
            std::string answer = std::to_string(getpid());
            send_message(node.parent, answer);
        }
        else if(command == "ping"){
            int child;
            request >> child;
            std::string answer = node.Ping(child);
            send_message(node.parent, answer);
        }
        else if(command == "create"){
            int child, player_count;
            request >> child;
            request >> player_count;
            std::string answer = node.createChild(child, player_count);
            send_message(node.parent, answer);
        }
        else if(command == "send"){
            int child;
            std::string str;
            request >> child;
            getline(request, str);
            str.erase(0, 1);
            std::string answer = node.sendStr(str, child);
            send_message(node.parent, answer);
        } else if(command == "join"){
            std::string name, ans, rabbit;
            request >> ans;
            request >> name;
            if (find(players.begin(), players.end(), name) == players.end()) {
                players.push_back(name);
            }
            if (players.size() != playerC) {
                std::string answer = name + ", В игру присоединилось " + std::to_string(players.size()) + " из " + std::to_string(playerC);
                // for (int i = 0; i < players.size(); ++i) {
                send_message(node.parent, answer);
                // }
            } else if (name != players[que]) {
                std::string answer = name + ", Сейчас ходит " + players[que];
                // for (int i = 0; i < players.size(); ++i) {
                send_message(node.parent, answer);
                // }
            } else {
                std::string req = node.game(ans, number);
                std::string answer = name + ", " + req;
                // for (int i = 0; i < players.size(); ++i) {
                send_message(node.parent, answer);
                // }
                ++que;
            }
            if (que >= players.size()) {
                que = 0;
            }
        } else if(command == "remove"){
            std::string answer = node.removeElem();
            send_message(node.parent, answer);
            disconnect(node.parent, node.parentPort);
            node.parent.close();
            break;
        } else if(command == "clear"){
            int child;
            request >> child;
            std::string answer = node.clearChild(child);
            send_message(node.parent, answer);
        }
    }
    sleep(1);
    return 0;
}