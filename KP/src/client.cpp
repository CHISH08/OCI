#include <bits/stdc++.h>
#include "topology.h"
#include <set>
#include <limits>
#include "myZmq.h"
#include <zmq_addon.hpp>
#include <sys/time.h>
#include <zmq.hpp>
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

int main() {

    std::string name, command;
    int id, playersC;
    std::cout << "Enter your name\n";
    std::cin >> name;
    zmq::context_t ctx, ctx2, ctx3;
    zmq::socket_t sock3(ctx2, zmq::socket_type::push);
    sock3.connect("tcp://127.0.0.1:6999");
    int flag = 1;
    // sock3.send(zmq::buffer(name), zmq::send_flags::none);
    flag = 0;
    zmq::socket_t sock4(ctx3, zmq::socket_type::pull);
    sock4.connect("tcp://127.0.0.1:6998");
    // std::string port = "";
    // while (port == "") {
    //     port = receive_message(sock4);
    //     std::cout << port << "\n";
    // }
    // std::cout << "good";
    std::ifstream fin("data_types.txt"); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
 
    if (!fin.is_open()) {
        std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
        return 8;
    }
    std::string port;
    fin >> port;
    fin.close();
    std::ofstream fout("data_types.txt");
    if (!fout.is_open()) {
        std::cout << "(((";
        return 8;
    }
    for (int i = stoi(port) + 1; i < 100; ++i) {
        std::string str = std::to_string(i) + "\n";
        fout << str;
    }
    fout.close();
    int count = (stoi(port))*2 + 8000;
    zmq::socket_t sock1(ctx, zmq::socket_type::push);
    zmq::socket_t sock2(ctx, zmq::socket_type::pull);
    sock1.connect("tcp://127.0.0.1:" + std::to_string(count));
    sock2.connect("tcp://127.0.0.1:" + std::to_string(count+1));
    // std::cout << "good\n";
    std::cout << "Enter command\n";
    while(std::cin >> command) {
        if (command == "create") {
            std::cin >> id;
            std::cin >> playersC;
            std::string answer = "create " + name + " " + std::to_string(id) + " " + std::to_string(playersC); 
            sock1.send(zmq::buffer(answer), zmq::send_flags::none);
            std::string mes = receive_message(sock2);
            std::cout << mes << "\n";
            if (mes[0] == '-' && mes[1] == '1') {
                std::cout << "Error: game already existed!\n";
                std::cout << "Enter command\n";
                continue;
            }
            // std::cout << "good\n";
            command = "join";
        } else if (command == "join") {
            std::cin >> id;
        } else if (command == "find") {
            sock1.send(zmq::buffer(command + " " + name), zmq::send_flags::none);
            std::string mes = receive_message(sock2);
            id = stoi(mes);
            command = "join";
        } else if (command == "kill") {
                std::string answer = "kill " + name;
                sock1.send(zmq::buffer(answer), zmq::send_flags::none);
                sock1.disconnect("tcp://127.0.0.1:" + std::to_string(count));
                sock2.disconnect("tcp://127.0.0.1:" + std::to_string(count+1));
                return 1;
            }
        while (command == "join") {
            std::string ans;
            std::cout << "Enter your answer\n";
            std::cin >> ans;
            std::string answer;
            if (ans == "kill") {
                answer = "kill " + name;
                sock1.send(zmq::buffer(answer), zmq::send_flags::none);
                sock1.disconnect("tcp://127.0.0.1:" + std::to_string(count));
                sock2.disconnect("tcp://127.0.0.1:" + std::to_string(count+1));
                return 1;
            }
            std::vector<std::string> mesV;
            // while(mesV[0] != name) {
            answer = "join " + name + " " + std::to_string(id) + " " + ans;
            sock1.send(zmq::buffer(answer), zmq::send_flags::none);
            std::string mes = receive_message(sock2);
            if (mes[0] == '-' && mes[1] == '1') {
                std::cout << "The maximum number of players has been reached!..\n";
                break;
            }
            split(mes, ",", mesV);
            mesV[1].erase(0, 1);
            if (mesV[0] == name) {
                std::cout << mesV[1] << "\n";
            } else {
                break;
            }
            // }
            if (mesV[1] == "Игра окончилась!" || mesV[1] == "4 быка и 0 коровы!") {
                answer = "remove " + name + " " + std::to_string(id);
                sock1.send(zmq::buffer(answer), zmq::send_flags::none);
                break;
            }
        }
        std::cout << "Enter command\n";
    }
    sock1.disconnect("tcp://127.0.0.1:" + std::to_string(count));
    sock2.disconnect("tcp://127.0.0.1:" + std::to_string(count+1));
    sock3.disconnect("tcp://127.0.0.1:6999");
    sock4.disconnect("tcp://127.0.0.1:6998");
}