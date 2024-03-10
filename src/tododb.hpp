#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

/* Purpose of this file: make a file class for the retreival, storage and deletion of a specific peice of information */

// Get the config path from XDG_DATA_HOME if set, if not, use ~/.local/share/
static std::string get_config_path(){
  if (getenv("XDG_DATA_HOME")){
    std::string data_home = getenv("XDG_DATA_HOME");
    return (data_home + "/tododb");
  }

  return ((std::string)(getenv("HOME")) + "/.local/share/tododb");
}

class todofile {
private:
  std::string todo_file;

public:
  todofile() {
    if (!std::filesystem::is_directory(get_config_path()))
      std::filesystem::create_directory(get_config_path());

      std::ofstream file(get_config_path() + "/todo.txt");
      file << "";
      file.close();

      todo_file = (get_config_path() + "/todo.txt");
  }

  void add_todo(std::string todo){
    std::ofstream temp(todo_file, std::ios::app);
    temp << todo << std::endl;
    temp.close();
  }
  
  std::string get_todo(int todo_number) {
  // Open the file for reading
  std::ifstream file(todo_file);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << todo_file << "'\n";
    return "";  // Return an empty string if file opening fails
  }

  // Read the specified todo line
  std::string line;
  for (int currentLine = 1; currentLine <= todo_number; ++currentLine) {
    if (!std::getline(file, line)) {
      std::cerr << "Error: To-do number " << todo_number << " not found in the file\n";
      return "";  // Return an empty string if the todo number is out of range
    }
  }

  return line;  // Return the extracted todo item
}


};
