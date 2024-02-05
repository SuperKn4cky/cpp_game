#include <iostream>
#include <string>
#include "../include/client.hpp"
#include "../include/host.hpp"

using namespace std::literals;

int main(int ac, char **av)
{
    try {
        if (ac < 3)
            throw std::runtime_error("Wrong arguments number");
        if ("host"sv != av[1] && "client"sv != av[1]) {
            throw std::runtime_error("Mode argument is not valid");
        }
        if (std::string(av[2]).find_first_not_of("0123456789") !=
            std::string::npos)
            throw std::runtime_error("Port argument is  not valid");
        if ("host"sv == av[1]) {
            host(atoi(av[2]));
        } else {
            if (ac != 4) {
                throw std::runtime_error("Wrong arguments number");
            } else if ("client"sv == av[1]) {
                client(atoi(av[2]), av[3]);
            }
        }
    } catch (std::exception &e) {
        std::cout << "Error : " << e.what() << std::endl;
        exit(-1);
    }
}
