#include <iostream>
#include "topology.h"
#include <set>
#include <limits>
#include "myZmq.h"
#include <sys/time.h>
#include <string>
#include <unistd.h>
#include "tree.h"

std::vector<int> treee;

int main(){
    std::string command;
    TNode node(-1, -1, -1);
    Tree tree;
    std::string answer;
    while(std::cin >> command){
        if(command == "create"){
            int child;
            std::cin >> child;
            if(tree.exist(child)){
                std::cout << "Error: child already existed!\n";
            }
            else{
                treee.push_back(child);
                while(true){
                    int idParent = tree.findId();
                    if(idParent == node.id){
                        answer = node.createChild(child);
                        tree.addElem(child, idParent);
                        break;
                    }
                    else{
                        std::string message = "create " + std::to_string(child);
                        answer = node.sendStr(message, idParent);
                        if(answer == "Error: id is not found"){
                            tree.notAvailable(idParent);
                        }
                        else{
                            tree.addElem(child, idParent);
                            treee.push_back(child);
                            break;
                        }
                    }
                }
                std::cout << answer << std::endl;
            }
        } else if (command == "heartbit"){
            int time;
            std::cin >> time;
            for (int i = 0; i <= 10; ++i) {
                for (int child = 0; child < treee.size(); ++child) {
                    if(!tree.exist(treee[child])){
                        std::cout << "";
                        // std::cout << "(" << treee[child] << ") => Heartbit: node id is unavailable now\n";
                    }
                    else if(node.leftId == treee[child] || node.rightId == treee[child]){
                        answer = node.Ping(treee[child]);
                        std::cout << "(" << treee[child] << ") => " << answer << std::endl;
                    }
                    else{
                        struct timeval stop, start;
                        gettimeofday(&start, NULL);
                        answer = "Heartbit: node id is unavailable now\n";
                        std::string message = "ping " + std::to_string(treee[child]);
                        while ((answer == "Heartbit: node id is unavailable now\n") && ((stop.tv_sec - start.tv_sec) * 1000 <= 4*time)) {
                            gettimeofday(&stop, NULL);
                            answer = node.sendStr(message, treee[child]);
                            if(answer == "Error: id is not found"){
                                answer = "OK: 0";
                            }
                        }
                        std::cout << "(" << treee[child] << ") => " << answer << std::endl;
                    }
                }
                usleep(time);
            }
        } else if(command == "ping"){
            int child;
            std::cin >> child;
            if(!tree.exist(child)){
                std::cout << "Error: child is not existed!\n";
            }
            else if(node.leftId == child || node.rightId == child){
                answer = node.Ping(child);
                std::cout << answer << std::endl;
            }
            else{
                std::string message = "ping " + std::to_string(child);
                answer = node.sendStr(message, child);
                if(answer == "Error: id is not found"){
                    answer = "OK: 0";
                }
                std::cout << answer << std::endl;
            }
        } else if(command == "exec"){
            std::string str;
            int child;
            std::cin >> child;
            getline(std::cin, str);
            if(!tree.exist(child)){
                std::cout << "Error: child is not existed!\n";
            }else{
                std::string message = "exec " + str;
                answer = node.sendStr(message, child);
                std::cout << answer << std::endl;
            }
        }
        else if(command == "remove"){
            int child;
            std::cin >> child;
            std::string message = "remove";
            if(!tree.exist(child)){
                std::cout << "Error: child is not existed!\n";
            }else{
                answer = node.sendStr(message, child);
                if(answer != "Error: id is not found"){
                    treee.erase(std::remove(treee.begin(), treee.end(), child), treee.end());
                    tree.Remove(child);
                    if(child == node.leftId){
                        unbind(node.left, node.leftPort);
                        node.leftId = -2;
                        answer = "OK";
                    }
                    else if(child == node.rightId){
                        node.rightId = -2;
                        unbind(node.right, node.rightPort);
                        answer = "OK";
                    }
                    else{
                        message = "clear " + std::to_string(child);
                        answer = node.sendStr(message, std::stoi(answer));
                    }
                    std::cout << answer << std::endl;
                }
            }
        } else if (command == "kill") {
            node.removeElem();
            tree.Remove(tree.findId());
            treee.clear();
            break;
        }
    }
    return 0;
}