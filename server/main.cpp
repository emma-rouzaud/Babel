/*
** EPITECH PROJECT, 2019
** BABEL
** File description:
** main
*/

#include "server.hpp"

int main()
{
  try {
    std::unique_ptr<Server> server = Server::create();
    printf("Ok Sever is ready !!!\n\n");
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
