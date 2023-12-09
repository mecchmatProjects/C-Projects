// File EnvVar_C.h
// Realization of EnvVar
// Done by Tanya Voitsehivska (comp math 1)
// Date 06.12.2022
// Headers for EnvVAr

// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task1_v0()
{
    // first version of the task 1 by functions getenv()
    if(getenv("OS")) // if the environment variable exists, then it is executed
    {
        // This environment variable is specific to Windows
        printf("You are Windows OS user\n", getenv("OS"));
    }
    else if(getenv("WSL_DISTRO_NAME"))
    {
        // This environment variable is specific to Ubuntu Linux
        printf("You are %s Linux user\n", getenv("WSL_DISTRO_NAME"));
    }
    else if(getenv("XDG_CURRENT_DESKTOP"))
    {
        // This environment variable is specific to gnome linux
        printf("You are %s Linux user\n", getenv("XDG_CURRENT_DESKTOP"));
    }
    else if(getenv("XPC_SERVICE_NAME"))
    {
        // This environmental variable is characteristic of apple products
        printf("You are Mac OS user\n");
    }
    else
    {
        printf("You are Linux OS  user or Unknown OS user\n");
        return -1;
    }
    return 0;
}

// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task1_v1()
{
    // second version of the task 1 by #ifdef
    // this algorithm checks for the existence of appropriate macros in the system
    #ifdef _WIN32
	    printf("You are Windows OS user\n");
    #elif __APPLE__
	    printf("You are Mac OS user\n");
    #elif __linux__
	    printf("You are Linux OS  user\n");
    #else
	    printf("Unknown OS\n");
        return -1;
    #endif
    return 0;
}

// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task2()
{
    // we look for the SystemRoot environment variable and, if successful, perform further manipulations with the files
	char * my_env = getenv("SystemRoot");
    if(my_env)
    {
        printf("SD:  %s \n", my_env);

        // enter the name of our file
        char * filename1 = "task2.txt";
        // combine the file name with the path to the system directory
        char * filename2 = strcat(my_env, "/task2_result.txt"); ;
        printf("filename2 => %s\n", filename2);

        // overwrite the contents of the files
        char cc[256];
        FILE *f1, *f2;

        if((f1= fopen(filename1, "r"))==NULL)
        {
            perror("Error occured while opening file");
        }
        if((f2= fopen(filename2, "w"))==NULL)
        {
            perror("Error occured while opening file");
        }

        // until we reach the end, we read 256 bytes
        while((fgets(cc, 256, f1))!=NULL)
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
        printf("Not found SystemRoot\n");
        return -1;
    }

}

// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task3()
{
    if(getenv("PYTHON"))
    {
        // if the environment variable PYTHON exists, then it is executed
        printf("PYTHON variable in system \n");
        return 0;
    }
    else
    {
        printf("PYTHON variable NOT in system \n");

        // sets PYTHON variable
        printf("Result of setenv => %d \n", setenv ("PYTHON", "Something", 50));

        // check if it set in the correct way
        if(setenv ("PYTHON", "Something", 50)==0)
        {
            printf("variable PYTHON set in correct way \n");
        }
        else
        {
            printf("variable PYTHON set in NOT correct way \n");
        }

    }

    // Checking whether the variable appeared in the environment
    printf("Let's check again:\n");
    if(getenv("PYTHON"))
    {
        printf("PYTHON variable in system \n");
        return 0;
    }
    else
    {
        printf("PYTHON variable NOT in system \n");
        return -1;
    }
}

// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task4(char option[])
{
    // Checking whether the PYTHON3 variable exists in the system
    if(getenv("PYTHON3"))
    {
        printf("PYTHON3 variable in system \n");
    }
    else
    {
        printf("PYTHON3 variable NOT in system \n");
    }

    char str[50] = "";

    if (option[0] == '1')
    {
        // Enter the name of the file
        printf("Please, enter a file name: ");
        fgets(str, 50, stdin);
        str[strlen(str) - 1] = '\0';            //Replace \n with \0 at the end of the line
        printf("Your file name => %s\n", str);
    }
    else
    {
        FILE * file;
        if((file= fopen("task4_input.txt", "r"))==NULL)
        {
        perror("Error occured while opening file");
        }
        fgets(str, 50, file);
        fclose(file);
    }



    // We combine "PYTHON3 " + filename for the next command
    char pyt[50] = "PYTHON3 ";
    // If it doesn't work for you and it gives: 'PYTHON3' is not recognized as an internal or external command, operable program or batch file,
    // then replace "PYTHON3 " with "python "
    char * com = strcat(pyt, str);


    // Check if the file file1.py exists in the current directory
    FILE *f;
    if((f = fopen(str, "r"))==NULL)
    {
        perror("Error occured while opening file");
        return -1;
    }
    else
    {
        printf("%s exists in the current directory \n", str);
        fclose(f);
        // Run the ‘PYTHON3 file1.py’ command in the console
        system(com);
    }
    return 0;
}


// @result - int: 0 - in the case of success;
//               -1 - in the case of failure
int task5(char option[])
{
    // Set the rounding mode to round-to-nearest, which is the default for most systems
    fesetround(FE_TONEAREST);

    // Set the locale to use a comma as the decimal separator
    setlocale(LC_ALL, "en_US.UTF-8");

    double x;
    char input[100];
    if (option[0] == '1')
    {


        printf("Enter a real number in floating point format using a comma: ");
        fgets(input, sizeof(input), stdin);

        // Replace the comma with a dot
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] == ',') {
            input[i] = '.';
        }
        }
    }
    else
    {
        FILE * file;
        if((file= fopen("task5_input.txt", "r"))==NULL)
        {
            perror("Error occured while opening file");
        return -1;
        }
        fgets(input, sizeof(input), file);
        // Replace the comma with a dot
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] == ',') {
            input[i] = '.';
        }
        }
        fclose(file);
    }


    // Parse the input string using the strtod() function
    x = strtod(input, NULL);

    printf("You entered: %f\n", x);
    return 0;
}

// The END.
