// File EnvVar_CPP.сpp
// Realization of EnvVar
// Done by Tanya Voitsehivska (comp math 1)
// Date 10.12.2022
// Implementations for EnvVAr


#include <iostream>
#include <algorithm>
#include <fenv.h>
#include <cstdio>
#include <string>
#include <locale>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cstring>
#include <filesystem>


// task 1: Write the function that determines the type of operating system of the data computer
int task1_v0()
{
    // first version of the task 1 by functions getenv()
    if(getenv("OS")) // if the environment variable exists, then it is executed
    {
        // This environment variable is specific to Windows
        std::cout<<"You are Windows OS user\n";
    }
    else if(getenv("WSL_DISTRO_NAME"))
    {
        // This environment variable is specific to Ubuntu Linux
        std::cout<<"You are "<<getenv("WSL_DISTRO_NAME")<<" Linux user\n";
    }
    else if(getenv("XDG_CURRENT_DESKTOP"))
    {
        // This environment variable is specific to gnome linux
        std::cout<<"You are "<<getenv("XDG_CURRENT_DESKTOP")<<" Linux user\n";
    }
    else if(getenv("XPC_SERVICE_NAME"))
    {
        // This environmental variable is characteristic of apple products
        std::cout<<"You are Mac OS user\n";
    }
    else
    {
        std::cout<<"You are Linux OS  user or Unknown OS user\n";
        return -1;
    }
    return 0;
}


int task1_v1()
{
    // second version of the task 1 by #ifdef
    // this algorithm checks for the existence of appropriate macros in the system
    #ifdef _WIN32
	    std::cout<<"You are Windows OS user\n";
    #elif __APPLE__
	    std::cout<<"You are Mac OS user\n";
    #elif __linux__
	    std::cout<<"You are Linux OS  user\n";
    #else
	    std::cout<<"Unknown OS\n";
        return -1;
    #endif
    return 0;
}


// task 2: Write a function that writes the contents of our file to a new file located in the system directory.
int task2()
{
    // we look for the SystemRoot environment variable and, if successful, perform further manipulations with the files
    std::string my_env = getenv("SystemRoot");
    if(getenv("SystemRoot"))
    {
        std::cout << "SD: " << my_env;

        // enter the name of our file
        std::string filename1("task2.txt");
        // combine the file name with the path to the system directory
        std::string filename2 = my_env.append("/task2_result.txt");
        std::cout << "\nfilename2 => " << filename2;

        // overwrite the contents of the files
        char cc[256];
        FILE *f1, *f2;

        if((f1 = fopen(filename1.c_str(), "r")) == NULL)
        {
            perror("Error occured while opening file");
        }
        if((f2 = fopen(filename2.c_str(), "w")) == NULL)
        {
            perror("Error occured while opening file");
        }

        // until we reach the end, we read 256 bytes
        while((fgets(cc, 256, f1)) != NULL)
        {
            // write string
            fputs(cc, f2);
            //printf("%s", cc);
        }
        fclose(f1);
        fclose(f2);
        return 0;
    }
    else
    {
        std::cout << "\nNot found SystemRoot\n";
        return -1;
    }

}


// task 3: Write a function that determines whether a PYTHON variable exists on the system,
//         and if not, sets this variable to the correct path.
int task3()
{
    if(getenv("PYTHON"))
    {
        // if the environment variable PYTHON exists, then it is executed
        std::cout << "PYTHON variable in system" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "PYTHON variable NOT in system" << std::endl;

        // sets PYTHON variable
        std::cout << "Result of setenv => " << setenv("PYTHON", "Something", 50) << std::endl;

        // check if it set in the correct way
        if(setenv("PYTHON", "Something", 50) == 0)
        {
            std::cout << "variable PYTHON set in correct way" << std::endl;
        }
        else
        {
            std::cout << "variable PYTHON set in NOT correct way" << std::endl;
        }

    }

    // Checking whether the variable appeared in the environment
    std::cout << "Let's check again:" << std::endl;
    if(getenv("PYTHON"))
    {
        std::cout << "PYTHON variable in system" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "PYTHON variable NOT in system" << std::endl;
        return -1;
    }
}


// task 4: Write a function that determines whether a variable exists in the system
//         PYTHON3, and in the current directory the file file1.py (file name is entered
//         from the console) and if there is, it runs the command 'PYTHON3 file1.py' in the console
int task4(std::string option)
{
    // Checking whether the PYTHON3 variable exists in the system
    if (std::getenv("PYTHON3"))
    {
        std::cout << "PYTHON3 variable in system" << std::endl;
    }
    else
    {
        std::cout << "PYTHON3 variable NOT in system" << std::endl;
    }

    char str[50] = "";

    if (option[0] == '1')
    {
        // Enter the name of the file
        std::cout << "Please, enter a file name: ";
        std::cin.getline(str, 50);
        std::cout << "Your file name => " << str << std::endl;
    }
    else
    {
        std::ifstream file;
        file.open("task4_input.txt");
        if (!file.is_open())
        {
            std::cout << "Error occured while opening file" << std::endl;
            return -1;
        }
        file >> str;
        file.close();
    }

    // We combine "PYTHON3 " + filename for the next command
    char pyt[50] = "PYTHON3 ";
    // If it doesn't work for you and it gives: 'PYTHON3' is not recognized as an internal or external command, operable program or batch file,
    // then replace "PYTHON3 " with "python "
    char* com = std::strcat(pyt, str);

    // Check if the file file1.py exists in the current directory
    if (!std::filesystem::exists(str))
    {
        std::cout << "Error occured while opening file" << std::endl;
        return -1;
    }
    else
    {
        std::cout << str << " exists in the current directory" << std::endl;
        // Run the ‘PYTHON3 file1.py’ command in the console
        std::system(com);
    }
    return 0;
}


// task 5: With the <fenv> library, make it possible to enter real numbers in floating point format,
//         but instead of a dot a comma is used.
int task5(std::string option)
{
  // Set the rounding mode to round-to-nearest, which is the default for most systems
  fesetround(FE_TONEAREST);

  // Set the locale to use a comma as the decimal separator
  std::setlocale(LC_ALL, "en_US.UTF-8");

  double x;
  std::string input;


  if (option[0] == '1')
  {
    std::cout << "Enter a real number in floating point format using a comma: ";
    std::getline(std::cin, input);
  }
  else
  {
    // Open the file for reading
    std::string dateFile;
	std::ifstream file("task5_input.txt");
    file >> dateFile; //read first row
    input = dateFile.c_str();
    file.close();
  }


  // Replace the comma with a dot
  std::replace(input.begin(), input.end(), ',', '.');

  // Parse the input string using the strtod() function
  x = std::strtod(input.c_str(), nullptr);

  std::cout << "You entered: " << x << std::endl;
  return 0;
}


// The END.
