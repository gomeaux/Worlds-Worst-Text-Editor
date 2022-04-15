#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>
#include <cstring>
int main() {

    // file vector
    std::vector<std::string> textfile;

    // variables
    int line = 0;
    int line2 =0;
    bool close_editor = false;
    bool file_ready = false;

    // file stream IO
    std::fstream filestream;

    // strings
    std::string str;
    std::string filename;
    std::string clipboard;
    
    // print title
	printf("%c", 214);
	for (int i = 0; i < 24; i++) {printf("%c", 196);}
	printf("%c\n%cWORLDS WORST TEXT EDITOR%c\n%c", 183, 186, 186, 211);
	for (int i = 0; i < 24; i++) {printf("%c", 196);}
	printf("%c\n", 189);

    // get file ready
    while (file_ready == false) {

        // create or open?
        printf("CREATE or OPEN file?: ");
        std::cin >> str;
        std::transform(str.begin(), str.end(), str.begin(), std::ptr_fun<int, int>(std::toupper));
        if (str[0] == 'C') {str.resize(6);}
        else {str.resize(4);}

        // Create new file
        if (str == "CREATE") {
            printf("File name: ");
            std::cin.ignore(); // ignores last '\n';
            std::getline(std::cin, filename);
            filestream.open(filename, std::ios::out); // make new file
            if (!filestream) {
				printf("Error creating file. Closing program.\n\n");
                goto END_EARLY;
			} else {
				file_ready = true;
				std::cout << "Ready.\n\n";
                textfile.resize(1);
			}
        }

        // Open existing file
        else if (str == "OPEN") {
            printf("File name: ");
            std::cin.ignore();
            std::getline(std::cin, filename);
            filestream.open(filename);
            if (!filestream) {
                printf("Error opening file. Closing program.\n\n");
                goto END_EARLY;
            } else {
                file_ready = true;
                printf("Ready.\n\n");
            }
        }

        // error
        else {
            printf("Invalid Command. Closing program.\n\n");
            goto END_EARLY;
        }

        // COMMAND LOOP
        while (std::getline(filestream, str)) {textfile.push_back(str);}
        while (!close_editor) {

            // prompt
            printf(":");
            std::getline(std::cin, str);
            std::transform(str.begin(), str.end(), str.begin(), std::ptr_fun<int, int>(std::toupper));
            str.resize(4);
             
            // EXIT commmand
            if (str == "EXIT") {close_editor = true;}

            // LINE command
            else if (str == "LINE") {
                printf(":");
                std::cin >> line;
                while ( (std::cin.fail() == true) || (textfile.size() < line) ) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                printf(":");
                str.clear(); std::cin.ignore();
                std::getline(std::cin, str);
                textfile.at(line - 1) = str;
                str.clear();
                printf("\n");
            }

            // SHOW command
            else if (str == "SHOW") {
                for (int i = 0; i < textfile.size(); i++) {
                    str = textfile[i];
                    std::cout << str << "\n";
                }
                printf("\n");
            }

            // LDLT command
            else if (str == "LDLT") {
                printf(":");
                std::cin >> line;
                while (textfile.size() < line) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                textfile.erase(textfile.begin() + line);
                if (textfile.empty() == true) {textfile.push_back("");}
                printf("\n");
				std::cin.ignore();
            }

            // NWLN command
            else if (str == "NWLN") {
                textfile.push_back("");
                printf("\n");
            }

            // SAVE command
            else if (str == "SAVE") {
                close_editor = true;
                filestream.close();
                std::ofstream out;
                out.open(filename);
                for (int i = 0; i < textfile.size(); i++) {
                    str = textfile[i];
                    out << str;
                    out << std::endl;
                }
                out.close();
            }

            // FDLT command
            else if (str == "FDLT") {
                filestream.close();
                char arr[filename.size() + 1];
                strcpy(arr, filename.c_str());
                if (remove(arr) == 0) {
                    std::cout << filename << " Deleted." << std::endl;
                    close_editor = true;
                } else { std::cout << "An error occurred deleting " << arr << std::endl;}
            }

            // INFO command
            else if (str == "INFO") {
                std::cout << "Taped and thrown together by Austin Comeaux in C++." << std:: endl;
                std::cout << "Don't contact me. Probably wont fix bugs." << std::endl;
                std::cout << "Email: austinccomeaux@gmail.com" << std:: endl;
                std::cout << "Version: 1.0 Build Date: April 14 2022.\n" << std::endl;
            }

            // BLNK command
            else if (str == "BLNK") {
                printf(":");
                std::cin >> line;
                while (textfile.size() < line) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                textfile.at(line - 1) = "";
                printf("\n");
				std::cin.ignore();
            }

            // COPY command
            else if (str == "COPY") {
                printf(":");
                std::cin >> line;
                while (textfile.size() < line) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                clipboard = textfile[line - 1];
                printf("\n");
				std::cin.ignore();
            }

            // PSTE command
            else if (str == "PSTE") {
                printf(":");
                std::cin >> line;
                while (textfile.size() < line) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                textfile.at(line - 1) = clipboard;
				std::cin.ignore();
				printf("\n");
            }

            // FCLR command
            else if (str == "FCLR") {
                textfile.clear();
                textfile.push_back("");
                printf("\n");
				if (textfile.empty() == true) {
					textfile.push_back("");
				}
            }

            // SWAP command
            else if (str == "SWAP") {
                printf(":");
                std::cin >> line;
                while (textfile.size() < line) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line;
                }
                printf(":");
                std::cin >> line2;
                while (textfile.size() < line2) {
                    printf("Retry\n:");
                    std::cin.clear();
                    rewind(stdin);
                    std::cin >> line2;
                }
                str = textfile[line - 1];
                textfile.at(line - 1) = textfile[line2 - 1];
                textfile.at(line2 - 1) = str;
                printf("\n"); 
				std::cin.ignore();
            }

            // HELP command
            else if (str == "HELP") {
                std::cout << "EXIT: Closes without saving." << std::endl;
                std::cout << "LINE: Edit specified line of file." << std::endl;
                std::cout << "SHOW: Display the file contents." << std::endl;
                std::cout << "LDLT: Delete specified line, move lower lines up." << std::endl;
                std::cout << "NWLN: Add new blank line at the end of file." << std::endl;
                std::cout << "SAVE: Save file and close." << std::endl;
                std::cout << "FDLT: Delete currently opened file." << std::endl;
                std::cout << "INFO: Display information about the program." << std::endl;
                std::cout << "BLNK: Make specified line blank." << std::endl;
                std::cout << "COPY: Copy specified line to clipboard." << std::endl;
                std::cout << "PSTE: Paste clipboard contents to specified line." << std::endl;
                std::cout << "FCLR: Entire file is wiped blank. Not deleted." << std::endl;
                std::cout << "SWAP: Exchange contents of two specified lines." << std::endl;
                std::cout << "HELP: Display command list.\n" << std::endl;
            }

            // No valid command given
            else {printf("No valid command given.\n\n");}
        }
    }

    // end
END_EARLY:
    filestream.close();
    return 0;
}