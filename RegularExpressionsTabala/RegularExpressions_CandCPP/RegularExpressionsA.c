/* 
������ ����� 12, ����� "����'������ ���������� 2", ������ �����.
�) �������� ��� ������ �� �++ �� ��������� ������� �������� string.h 
(��� ���������� ������, ����� �������� <string.h>) 
1) � ������ ���������� ���� ������ �� ������������� �� ������� �� 
����� � ������ (����� �������������� �������� �� ������� ����������) 
�� ����� ����� ���. 
2) ������ � ������ ���������� ���� �� ���� � �������� __.__.__ �� 
__/__/__ (� ���� ������ ���� 2 ��� 4 �����, � ����� ____(��).__.__) �� 
��������� �� �� �� ������� ������� __(��) ����� ����� __(�����). 
3) ������ �� ��� �� ���� ����� (� ��������� �� ���������� ������ � 
�������/�����) �� �������� �� �� ������� ������� (����� ����� � 
���������� �������, ������� 4 �������) �� ������� �������� �������. 
4) ������ �� ���� �� ������ ���� � ���� �� ������ ���� 
�� ���. */

#ifdef _MSC_VER // ��� ���������� Microsoft Visual Studio
#define _CRT_SECURE_NO_WARNINGS // ³��������� ����������� ��� ������������ ����������� �������
#endif

// ϳ�������� ������ �������� � �����
#include "RegularExpressionsA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// ������� ��� �������� �� � ������ �����������
bool isSeparator(char c) {
    char punctuations[] = ".,:;!?()[]{}\"\'";
    // ��������� true ���� ������ �� � ������, ������, ������������ ��� ������ ����������
    return !(isalnum(c) || c == '_' || strchr(punctuations, c) != NULL);
}

// ������� ��� ������ ������������
void findHyperlinks(const char* filename) {
    /* ��� �� ��������� 2 �����, ���� ��� ����������,
    ����� ��� ������ � ����� ����� ��� ���������� ��������� */
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "w");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256], prevWord[256] = "";

        // ��������� ����� �� ������
        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            // ������� ����� � ����� word
            strcpy(word, token);

            // ���� ����� ������ http, �� �������� �������� ����� �� ���� �������������
            if (strstr(word, "http") != NULL) {
                if (strlen(prevWord) > 0) {
                    printf("%s %s\n", prevWord, word);
                    fprintf(file2, "%s %s\n", prevWord, word);
                }
            }

            // ������� ����� � ����� prevWord
            strcpy(prevWord, "");
            for (int i = 0; word[i] != '\0'; i++) {
                if (!isSeparator(word[i])) {
                    strncat(prevWord, &word[i], 1);
                }
            }

            // ���������� �� ���������� ������
            token = strtok(NULL, " \t\n");
        }
    }

    // ��������� �����
    printf("\n");
    fprintf(file2, "\n");
    fclose(file);
    fclose(file2);
}

// ������� ��� �������� �� � ���� ����������
bool isValidDate(const char* date) {
    int day, month, year;

    // ���������� �� ���� � ������ ��.�����.����
    if (sscanf_s(date, "%d.%d.%d", &year, &month, &day) == 3) {
        if (year < 100) {
            if (year >= 0 && year <= 69) {
                year += 2000;
            }
            else {
                year += 1900;
            }
        }
        if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            return true;
        }
    }

    // ���������� �� ���� � ������ ����/�����/�� ��� ����.�����.��
    if (sscanf_s(date, "%d.%d.%d", &day, &month, &year) == 3 ||
        		sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3) {
		if (year < 100) {
			if (year >= 0 && year <= 69) {
				year += 2000;
			}
			else {
				year += 1900;
			}
		}
		if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
			return true;
		}
	}
    return false;
}

// ��������� ����� � ������� ������
const char* monthMap[] = {
    NULL, "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// ������� ��� ����������� ���� �� ������� �������
void convertDates(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256];

        // ��������� ����� �� ������
        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            strcpy(word, token);

            // ���� ����� ������ ������ ��� ����, �� �������� �� ������� ��� ����, ������ �� �����
            if (strlen(word) >= 8 && (strstr(word, ".") != NULL || strstr(word, "/") != NULL)) {
                char cleanedDate[256] = "";
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == '.' || word[i] == '/') {
                        strncat(cleanedDate, &word[i], 1);
                    }
                }

                // ���� ���� � ����������, �� �������� �� � ������� ������
                if (isValidDate(cleanedDate)) {
                    int day, month, year;
                    sscanf_s(cleanedDate, "%d.%d.%d", &day, &month, &year);
                    sscanf_s(cleanedDate, "%d/%d/%d", &day, &month, &year);

                    if (year < 100) {
                        if (year >= 0 && year <= 69) {
                            year += 2000;
                        }
                        else {
                            year += 1900;
                        }
                    }

                    // ���� �� ������� ����� ��
                    if (day >= 1000) {
                        sscanf_s(cleanedDate, "%d.%d.%d", &year, &month, &day);
						printf("Original date: %s -> ", word);
                        fprintf(file2, "Original date: %s -> ", word);

                        printf ("Uniform date: %d %s %d\n ", year, monthMap[month], day);
                        fprintf(file2, "Uniform date: %d %s %d\n", year, monthMap[month], day);
					}
					else {
                        printf("Original date: %s -> ", word);
						fprintf(file2, "Original date: %s -> ", word);

						printf("Uniform date: %d %s %d\n", year, monthMap[month], day);
						fprintf(file2, "Uniform date: %d %s %d\n", year, monthMap[month], day);
					}
                }
            }

            // ���������� �� ���������� ������
            token = strtok(NULL, " \t\n");
        }
    }

    // ��������� �����
    printf("\n");
    fprintf(file2, "\n");
    fclose(file);
    fclose(file2);
}

// ������� ��� �������� �� � ����� ������
bool isNumber(const char* word) {
    char* endptr;
    // ���������� �� � ����� ������
    strtod(word, &endptr);
    return *endptr == '\0';
}

// ���������� ����� �� ������� �������
void convertNumbers(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char word[256];

        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            strcpy(word, token);

            // ���� ����� � ������, �� �������� ���� � ������� ������
            if (isNumber(word)) {
                double num = strtod(word, NULL);
                printf("%.4f, ", num);
                fprintf(file2, "%.4f, ", num);
            }

            // ���������� �� ���������� ������
            token = strtok(NULL, " \t\n");
        }
    }
    
    // ��������� �����
    printf("\n\n");
    fprintf(file2, "\n\n");
    fclose(file);
    fclose(file2);
}

// ������� ��� �������� �� � ��� ����������
bool isValidTime(const char* time) {
	int hour, minute, second;

	// ���������� �� ��� � � ������ hh:mm:ss
    if (sscanf_s(time, "%2d:%2d:%2d", &hour, &minute, &second) == 4) {
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
			return true;
		}
	}

	// ���������� �� ��� � � ������ hh:mm
    if (sscanf_s(time, "%2d:%2d", &hour, &minute) == 2) {
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
			return true;
		}
	}
	return false;
}

// Function to replace dates and times with current date and time
void replaceDatesAndTimes(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("RegExpA.txt", "a");

    if (file == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \t\n");
        bool containsDateOrTime = false;

        while (token != NULL) {
            char word[256]; // �����, ��� ���� �����������
            strcpy(word, token); // ������� ����� � ����� word
            time_t now = time(NULL); // �������� ���
            struct tm* ltm = localtime(&now); // ��������� ���

            // ���� ����� ������ ������ ��� ����, �� �������� �� ������� ��� ����, ������ �� �����
            if (strstr(word, ".") != NULL || strstr(word, "/") != NULL) {
                char cleanedDate[256] = ""; // ����, ��� ���� �����������
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == '.' || word[i] == '/') {
                        strncat(cleanedDate, &word[i], 1);
                    }
                }
                
                // ���� ���� � ����������, �� �������� ������� ����
                if (isValidDate(cleanedDate)) {
                    printf("%d %s %d; ", 1900 + ltm->tm_year, monthMap[1+ltm->tm_mon], ltm->tm_mday);

                    fprintf(file2, "%d %s %d; ", 1900 + ltm->tm_year, monthMap[1+ltm->tm_mon], ltm->tm_mday);
                    containsDateOrTime = true;
                }
            }
            // ���� ����� ������ ���������, �� �������� �� ������� ��� ���� �� ���������
            if (strstr(word, ":") != NULL) {
                char cleanedTime[256] = "";
                for (int i = 0; word[i] != '\0'; i++) {
                    if (isdigit(word[i]) || word[i] == ':') {
                        strncat(cleanedTime, &word[i], 1);
                    }
                }

                // ���� ��� � ����������, �� �������� �������� ���
                if (strlen(cleanedTime) == 8 && isValidTime(cleanedTime)) {
                    // ���������� ���� �����, ��� ������ ������ ��� ����������
                    if (ltm->tm_hour < 10) {
                        if (ltm->tm_min < 10) {
                            if (ltm->tm_sec < 10) {
                                printf("0%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("0%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                        else {
                            if (ltm->tm_sec < 10) {
                                printf("0%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("0%d:%d:%d;", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "0%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                    }
                    else {
                        if (ltm->tm_min < 10) {
                            if (ltm->tm_sec < 10) {
                                printf("%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:0%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:0%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                        else {
                            if (ltm->tm_sec < 10) {
                                printf("%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:%d:0%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                            else {
                                printf("%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                fprintf(file2, "%d:%d:%d; ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                            }
                        }
                    }
                    containsDateOrTime = true;
                }
                else if (strlen(cleanedTime) == 5 && isValidTime(cleanedTime)) {
                    if (ltm->tm_hour < 10) {
                        if (ltm->tm_min < 10) {
							printf("0%d:0%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "0%d:0%d; ", ltm->tm_hour, ltm->tm_min);
						}
						else {
							printf("0%d:%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "0%d:%d; ", ltm->tm_hour, ltm->tm_min);
						}
					}
					else {
						if (ltm->tm_min < 10) {
							printf("%d:0%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "%d:0%d; ", ltm->tm_hour, ltm->tm_min);
						}
						else {
							printf("%d:%d; ", ltm->tm_hour, ltm->tm_min);
							fprintf(file2, "%d:%d; ", ltm->tm_hour, ltm->tm_min);
						}
					}
                    containsDateOrTime = true;
                }
            }

            token = strtok(NULL, " \t\n");
        }

        // ���� ����� ������ ���� ��� ���, �� ���������� �� ����� �����
        if (containsDateOrTime) {
            printf("\n");
            fprintf(file2, "\n");
        }
    }
    // ��������� �����
    fclose(file);
    fclose(file2);
}

