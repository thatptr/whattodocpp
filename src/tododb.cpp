#include "tododb.hpp"

int main(){
  todofile file;
  std::cout << file.get_todo(2) << std::endl;
  return EXIT_SUCCESS;
}