#include <iostream>
#include "topology.h"
#include <set>
#include <limits>
#include "myZmq.h"
#include <sys/time.h>
#include <string>
#include <unistd.h>
#include "tree.h"

void split(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::vector<int> treee;
// std::vector<zmq::context_t> ctx(100);
// zmq::socket_t sock3(ctx, zmq::socket_type::push);
// zmq::socket_t sock4(ctx, zmq::socket_type::pull);
// std::vector<std::string> play;
std::vector<int> playC;
std::vector<std::vector<std::string>> playT;

int main(){
    std::ofstream ofs;
    ofs.open("data_types.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    std::ofstream fout("data_types.txt", std::ios_base::app);
    if (!fout.is_open()) {
        std::cout << "(((";
        return 8;
    }
    for (int i = 0; i < 100; ++i) {
        std::string str = std::to_string(i) + "\n";
        fout << str;
    }
    fout.close();
    zmq::context_t ctx2, ctx3;
    zmq::socket_t sock3(ctx2, zmq::socket_type::pull);
    sock3.bind("tcp://127.0.0.1:6999");
    zmq::socket_t sock4(ctx3, zmq::socket_type::push);
    sock4.bind("tcp://127.0.0.1:6998");
    // for (int i = 0; i < 1; ++i) {
    //     sock4.send(zmq::buffer(std::to_string(i*2) + " "), zmq::send_flags::none);
    // }
    std::string command, name;
    TNode node(-1, -1, -1);
    Tree tree;
    std::string answer;
    while(true){
        int child, COunt=1000;
        std::string mes, mes2;
        // mes2 = receive_message(sock3);
        int fl=1;
        std::vector<std::string> msg2;
        // split(mes2, " ", msg2);
        // std::cout << mes2 << "\n";
        // if (mes2 != "" && find(play.begin(), play.end(), mes2) == play.end()) {
            // play.push_back(mes2);
            // sock4.send(zmq::buffer(std::to_string((play.size()-1)*2)), zmq::send_flags::none);
        // }
        std::ifstream fin("data_types.txt"); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
        if (!fin.is_open()) {
            std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
            return 8;
        }
        std::string nom;
        fin >> nom;
        fin.close();
        int noom;
        if (nom == "") {
            continue;
        } else{
            noom = stoi(nom);
        }
        for (int j = 0; j < noom; ++j) {
            zmq::context_t ctx;
            zmq::message_t message;
            zmq::socket_t sock1(ctx, zmq::socket_type::push);
            zmq::socket_t sock2(ctx, zmq::socket_type::pull);
            sock2.bind("tcp://127.0.0.1:" + std::to_string(8000+2*j));
            sock1.bind("tcp://127.0.0.1:" + std::to_string(8000+2*j+1));
            mes = receive_message(sock2);
            std::vector<std::string> msg;
            split(mes, " ", msg);
            command = msg[0];
            name = msg[1];
            if(command == "create"){
                child = stoi(msg[2]);
                int player_count = stoi(msg[3]);
                if(tree.exist(child)){
                    sock1.send(zmq::buffer("-1"), zmq::send_flags::none);
                }
                else{
                    std::vector<std::string> nam;
                    nam.push_back(name);
                    treee.push_back(child);
                    playC.push_back(player_count);
                    playT.push_back(nam);
                    while(true){
                        int idParent = tree.findId();
                        if(idParent == node.id){
                            answer = node.createChild(child, player_count);
                            tree.addElem(child, idParent);
                            break;
                        }
                        else{
                            std::string message = "create " + std::to_string(child) + " " + std::to_string(player_count);
                            answer = node.sendStr(message, idParent);
                            if(answer == "Error: id is not found"){
                                tree.notAvailable(idParent);
                            }
                            else{
                                tree.addElem(child, idParent);
                                break;
                            }
                        }
                    }
                    sock1.send(zmq::buffer(answer), zmq::send_flags::none);
                }
            } else if (command == "find") {
                for (int k = 0; k < treee.size(); ++k) {
                    if (playC[k] > playT[k].size()) {
                        sock1.send(zmq::buffer(std::to_string(treee[k])), zmq::send_flags::none);
                        playT[k].push_back(name);
                        break;
                    }
                }
            } else if (command == "heartbit"){
                int time;
                std::cin >> time;
                for (int i = 0; i <= 2; ++i) {
                    for (int childC = 0; childC < treee.size(); ++childC) {
                        if(!tree.exist(treee[childC])){
                            std::cout << "Error: child is not existed!\n";
                        }
                        else if(node.leftId == treee[childC] || node.rightId == treee[childC]){
                            answer = node.Ping(treee[childC]);
                            std::cout << answer << std::endl;
                        }
                        else{
                            std::string message = "ping " + std::to_string(treee[childC]);
                            answer = node.sendStr(message, treee[childC]);
                            if(answer == "Error: id is not found"){
                                answer = "OK: 0";
                            }
                            std::cout << "(" << treee[childC] << ") => " << answer << std::endl;
                        }
                    }
                    usleep(time);
                }
            } else if(command == "ping"){
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
            } else if(command == "join"){
                std::string req = msg[3], str;
                child = stoi(msg[2]);
                str = req + " " + name;
                int flug = 1;
                if(!tree.exist(child)){
                    sock1.send(zmq::buffer("Error: game is not existed!"), zmq::send_flags::none);
                }else{
                    for (int k = 0; k < treee.size(); ++k) {
                        if (treee[k] == child) {
                            if (find(playT[k].begin(), playT[k].end(), name) == playT[k].end()) {
                                if (playC[k] < playT[k].size()) {
                                    playT[k].push_back(name);
                                } else {
                                    flug = 0;
                                    sock1.send(zmq::buffer("-1"), zmq::send_flags::none);
                                }
                            }
                            break;
                        }
                    }
                    if (flug) {
                        std::string message = "join " + str;
                        answer = node.sendStr(message, child);
                        sock1.send(zmq::buffer(answer), zmq::send_flags::none);
                    }
                }
                if (answer == "4 быка и 0 коровы!" && flug) {
                    command = "remove";
                    sock1.send(zmq::buffer(name + ", Вы победитель!)"), zmq::send_flags::none);
                }
            } else if (command == "kill") {
                node.removeElem();
                tree.Remove(tree.findId());
                treee.clear();
                return 2;
            }
            if(command == "remove"){
                std::cin >> child;
                std::string message = "remove";
                if(!tree.exist(child)){
                    std::cout << "Error: child is not existed!\n";
                }else{
                    answer = node.sendStr(message, child);
                    int p;
                    for (p = 0; p < treee.size(); ++p) {
                        if (treee[p] == child) {
                            break;
                        }
                    }
                    playT.erase(std::remove(playT.begin(), playT.end(), playT[p]), playT.end());
                    playC.erase(std::remove(playC.begin(), playC.end(), playC[p]), playC.end());
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
            }
            sock2.unbind("tcp://127.0.0.1:" + std::to_string(8000+2*j));
            sock1.unbind("tcp://127.0.0.1:" + std::to_string(8000+2*j+1));
        }
    }
    // sock2.unbind("tcp://127.0.0.1:8000");
    // sock1.unbind("tcp://127.0.0.1:8001");
    // sock1.unbind("tcp://127.0.0.1:" + std::to_string(8000));
    // sock2.unbind("tcp://127.0.0.1:" + std::to_string(8001));
    sock3.unbind("tcp://127.0.0.1:6999");
    sock4.unbind("tcp://127.0.0.1:6998");
    return 0;
}