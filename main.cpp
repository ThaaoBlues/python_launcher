#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <windows.h>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}



std::string read_file(std::string filename){
    std::string line;
    std::string content;
    std::ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline(myfile,line) )
        {
            content.append(line);
        }
        myfile.close();

        return content.c_str();
    }else{
        return "error";
    }
}




int main() {

    if(read_file("launcher.conf") == "error"){
        std::cout<<"launcher.conf file not found"<<std::endl;
        return 1;
    }

    if(!(exec("python -V").rfind("python 3.",0) != 0)){
        if(!(exec("python3 -V").rfind("python 3.",0) != 0)){
            system("curl \"https://www.python.org/ftp/python/3.9.4/python-3.9.4-amd64.exe\" -o python_installer.exe & python_installer.exe /quiet InstallAllUsers=0 Include_launcher=0 Include_test=0 SimpleInstall=1");
        }
    }

    
    std::string cmd =  "start cmd.exe /c " + read_file("launcher.conf");
    std::cout<<cmd<<std::endl;
    system(cmd.c_str());

    return 0;
}
