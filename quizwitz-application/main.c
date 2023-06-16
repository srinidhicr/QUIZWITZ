#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/*  ----- FUNCTION PROTOTYPES ----  */
void start();
void close();
void leaderboard();
void rules();
void qset();
void set1();
void set2();
void set3();
void sc();
void admin();
void login();
void signup();
void erase();
void techStore();
void haStore();
void caScore();
void list();
void leadTech();
void leadHumanBody();
void leadCurrentAff();
int search(char u[], char p[]);
void menu();
void review();
void techr();
void humanr();
void currentr();
int randques();
int check(char *u);

/*  ----- PREPROCESSOR DIRECTIVES ----  */
#define clrscr() system("clear")
#define getchar() system("read -n 1 -s -r");
#define upper 2

/*  ----- GLOBAL VARIABLES ----  */
int full = 0;
int q[10];

struct data
{
    int score, age;
    char name[20], username[20], pass[20];
};

struct data d;

/*  ----- MAIN MENU OF THE QUIZ ----  */
void start()
{
        clrscr();
        int ch,x=1;
        do{
                printf("\t\t\t\tWelcome to QUIZWITZ!\n");
                printf("\t\t\t------------------------------------\n");
                printf("\t\t\t  Press any of the options below!\n");
                printf("\t\t\t\t 1. Login\n\t\t\t\t 2. Sign Up\n\t\t\t\t 3. Exit \n");
                printf("\t\t\t------------------------------------\n");
                scanf("%d",&ch);
                switch(ch)
                {
                        case 1:
                                login();
                                break;
                        case 2:
                                signup();
                                break;
                        case 3:
                                close();
                                break;
                        case 9:
                                admin();
                                break;
                        default:
                                printf("\t\tWrong Input! Try again!\n");
                                x=0;
                }
        }
        while(!x);
}

/*  ----- SIGNUP ----  */

//initialising the structure variables
void erase()
{
    d.age = d.score =0;
    strcpy(d.name, "null");
    strcpy(d.username, "null");
    strcpy(d.pass, "null");
}

//entering the details to signup
void signup()
{
    clrscr();
    char p1[20], p2[20];
    int op, user;
    char ch;
    printf("\t\t\t\tQUIZWITZ - SIGNUP\n\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\tEnter the option for which you want to enter the data in.\n");
    printf("\t\t\t\t1. Username* : %s\n\t\t\t\t2. Name* : %s\n", d.username, d.name);
    printf("\t\t\t\t3. Password* : %s\n\t\t\t\t4. Submit\n\t\t\t\t5. Back\n", d.pass);
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            printf("\t\t\tEnter your username: ");
            scanf("%s", d.username);
            if (!check(d.username))
            {
                printf("\t\t\tUsername already exists.\n");
                strcpy(d.username, "");
            }
            getchar();
            signup();
            break;

        case 2:
            printf("\t\t\tEnter your name:");
            scanf("%s", d.name);
            signup();
            break;

        case 3:
            printf("\t\t\t\tEnter password:");
            scanf("%s", p1);
            printf("\t\tEnter the password once again for confirmation - ");
            scanf("%s", p2);
            if (strcmp(p1, p2)!=0)
            {
                printf("\t\t\tUnsuccessful. Passwords do not match\n\t\t\t\t");
                strcpy(p1, "");
                strcpy(p2, "");
            }
            else 
            {
                printf("\t\t\tPassword creation successful.\n");
                strcpy(d.pass, p1);
            }
            getchar();
            signup();
            break;

        case 4:
            printf("\t\tAre you sure? Press 'y' for yes and 'n' for no.\n");
            scanf("%s", &ch);
            if (ch == 'y')
            {
                if (strcmp(d.name, "null") != 0 && strcmp(d.username, "null") != 0 && strcmp(d.pass, "null") != 0)
                {
                    FILE *fp;
                    fp = fopen("userdata.txt", "a");
                    fprintf(fp, "%s ", d.username);
                    fprintf(fp, "%s ", d.name);
                    fprintf(fp, "%s\n", d.pass);
                    fclose(fp);
                    printf("\t\t\tAccount successfully created.\n");
                    printf("\t\t\tPress any button to continue.\n");
                    getchar();
                    menu();
                }
                else
                {
                    printf("\t\tPlease fill all the mandatory fields.\nPress any key to try again.\n");
                    getchar();
                    signup();
                }
            }
            else
            {
                printf("\t\t\tPress any key to continue.\n");
                getchar();
                signup();
            }
            start();
            break;
        case 5: 
            start();
        default:
            printf("\t\tWrong input! Press any key to try again!\n");
            getchar();
            signup();        
    } 
}

//to check whether the particular username exists or not
int check(char *up)
{
    FILE *fp;
    fp = fopen("userdata.txt", "r");
    char uname[20];
    while(fscanf(fp, "%s %*s %*s", uname) ==1)
    {
        if (strcmp(uname, d.username)==0)
            return 0;
    }
    return 1;
}

/*  ----- LOGIN ----  */

//for logging inside the acc
void login()
{
    char s1[20], p[20];
    int i, y;
    clrscr();
    printf("\t\t\t\tQUIZWITZ - LOGIN\n\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\t\tUsername: ");
    scanf("%s", s1);
    printf("\t\t\t\tPassword: ");
    scanf("%s", p);
    y = search(s1, p);
    if (!y)
    {
      printf("\n\t\t\t\tInvalid credentials\n");
      printf("\t\t\t\t   Try again!\n");
      strcpy(s1, "");
      strcpy(p, "");
      printf("\t\t\tPress any key to try again\n");
      getchar();
      login();
    }
    else
    {
        strcpy(d.username, s1);
        printf("\t\t\t    You have succesfully logged in!\n\t\t\tPress any key to go to the player menu.\n");
        getchar();
        menu();
    }
}

// searching for existing user when logging in
int search(char u[], char p[])
{
    char user[20], pwd[20];
    FILE *fp;
    fp = fopen("userdata.txt", "r");
    while (fscanf(fp, "%s", user) == 1)
    {
        if (strcmp(u, user) == 0)
        {
            fscanf(fp, "%*s %s", pwd); // Read the password directly after reading the username
            if (strcmp(p, pwd) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

/*  ----- PLAYER - MAIN MENU ----  */
void menu()
{
    clrscr();
    int ch;
    printf("\t\t\t\tQUIZWITZ - PLAYER LOGIN\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\tChoose any of the options to view:\n");
    printf("\t\t\t\t 1. Attempt Quiz\n\t\t\t   2. Review previous attempts\n\t\t\t\t 3.  Exit\n");
    scanf("%d", &ch);
    switch(ch)
    {
                        case 1:rules();
                                qset();
                                break;
                        case 2:
                                review();
                                break;
                        case 3:
                                close();
                                break;
                        default:
                                printf("\t\tWrong Input! Try again!\n");
                                printf("Press any key to return to menu.");
                                getchar();
                                clrscr();
                                menu();
    }
}

/*  ----- RULES & QUESTION MENU ----  */

//rules to be followed in the game
void rules()
{
        clrscr();
        printf("\t\t   QUIZWITZ - RULES AND REGULATIONS\n");
        printf("\t\t--------------------------------------\n");
        printf("\t\t 1. The overall quiz is of 10 points\n");
        printf("\t\t 2. The quiz comprises of three topics\n");
        printf("\t\t 3. Only one option is correct among the four\n");
        printf("\t\t 4. No time limit and no negative mark deductions!\n");
        printf("\t\t 5. Irrevelant inputs result in no points.\n");
        printf("\t 6. Scores are listed in the leaderboard based on total points.\n");
        printf("\n\t\t*******************************************\n");
        printf("\t\t\t\tGOOD LUCK!!!\n");
        printf("\n\t\t*******************************************\n");
        printf("\n\t\tPress any key when you're good to proceed!\n");
        getchar();
        qset();
}

//select the topic you want to attempt quiz on
void qset()
{
    clrscr();
    int select;
    printf("\n\t\t\t\tQUIZWITZ\n");
            printf("\t\t--------------------------------------\n");
    printf("\t\tSelect the topic you want to attempt quiz in!\n");
    printf("\t\t\t  1. Technology\n\t\t\t  2. Human anatomy\n\t\t\t  3. Current Affairs\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1: set1();
                break;
        case 2: set2();
                break;
        case 3: set3();
                break;
        default:printf("\t\t\t     Invalid input, try again!\n");
                 qset();
    }
}

/*  ----- QUESTION SETS ----  */

//technology set
void set1()
{
    int ques = randques();
    char ch[10], filename[100], content[1000];
    sprintf(filename, "%s%d", "techQ", ques);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
    }
    clrscr();

    printf("\t\t\tQUIZWITZ - TECHNOLOGY\n");
    printf("\t\t--------------------------------------\n");
    while (fgets(content, sizeof(content), file)) {
        printf("%s", content);
    }
    fclose(file);
    printf("\n\nEnter the appropriate answers.\n");
    for (int i=0; i<10; i++){
        printf("\nAns. %d - ", i+1);
        scanf("%s", &ch[i]);
    }
    char ansFile[100];
    sprintf(ansFile, "%s%d", "techA", ques);
    strcat(ansFile, ".txt");
    d.score = calcScore(ansFile, ch);

    clrscr();
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
    techStore();
    getchar();
    clrscr();
    menu();
}

//human body set
void set2()
{
    int ques = randques();
    char ch[10], filename[100], content[1000];
    sprintf(filename, "%s%d", "humanQ", ques);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
    }
    clrscr();

    printf("\t\t\tQUIZWITZ - HUMAN ANATOMY\n");
    printf("\t\t--------------------------------------\n");
    while (fgets(content, sizeof(content), file)) {
        printf("%s", content);
    }
    fclose(file);
    for (int i=0; i<10; i++){
        printf("\nAns. %d - ", i+1);
        scanf("%s", &ch[i]);
    }
    char ansFile[100];
    sprintf(ansFile, "%s%d", "humanA", ques);
    strcat(ansFile, ".txt");
    d.score = calcScore(ansFile, ch);

    clrscr();
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
    haStore();
    getchar();
    clrscr();
    menu();
}

//current affairs set
void set3()
{
    int ques = randques();
    char ch[10], filename[100], content[1000];
    sprintf(filename, "%s%d", "currentQ", ques);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
    }
    clrscr();

    printf("\t\t\tQUIZWITZ - CURRENT AFFAIRS\n");
    printf("\t\t--------------------------------------\n");
    while (fgets(content, sizeof(content), file)) {
        printf("%s", content);
    }
    fclose(file);
    for (int i=0; i<10; i++){
        printf("\nAns. %d - ", i+1);
        scanf("%s", &ch[i]);
    }
    char ansFile[100];
    sprintf(ansFile, "%s%d", "currentA", ques);
    strcat(ansFile, ".txt");
    d.score = calcScore(ansFile, ch);

    clrscr();
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
    caStore();
    getchar();
    clrscr();
    menu();
    
}

/*  ----- ADDITIONAL FUNCTIONS ----  */

//calculate score from the entered details
int calcScore(char* ansFile, char *ch){
    int score=0;
    FILE* file = fopen(ansFile, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read each line from the file and compare with array elements
    char line[50];
    int lineNumber = 1;
    while (fgets(line, 50, file) != NULL) {
        // Remove the newline character at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Check if the line matches the element in the array
        if (line[0] == ch[lineNumber - 1] || line[0] == tolower(ch[lineNumber - 1]) || line[0] == toupper(ch[lineNumber - 1])) {
            score++;
        } 
        lineNumber++;
    }
    // Close the file
    fclose(file);
    return score;
}

// generate a random question paper
int randques()
{
    int lower = 1, num;
    srand(time(0));
    num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

//test score feedback
void sc()
{
    if(d.score == 10)
        printf("\n\t Congratulations! You just scored a perfect 10 out of 10!\n");
    else if (d.score>=7 && d.score<=9)
        printf("\n\t\t     Not bad...You did pretty well!\n");
    else if (d.score<=6 && d.score>=4)
        printf("\n\t\t     Okayy..Better luck next time!\n");
    else
        printf("\n  Hmmm....You could definitely do better than this, try thinking harder!\n");
}

//store the test scores of technology quiz
void techStore()
{
    FILE* file = fopen("techLeaderboard.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read existing contents into memory
    char** lines = NULL;
    char line[100];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        lines = realloc(lines, (lineCount + 1) * sizeof(char*));
        lines[lineCount] = strdup(line);
        lineCount++;
    }

    fclose(file);

    file = fopen("techLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.username, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
}

//store the test scores of human anatomy quiz
void haStore()
{
    FILE* file = fopen("humanLeaderboard.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read existing contents into memory
    char** lines = NULL;
    char line[100];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        lines = realloc(lines, (lineCount + 1) * sizeof(char*));
        lines[lineCount] = strdup(line);
        lineCount++;
    }

    fclose(file);

    file = fopen("humanLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.username, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    getchar();
    clrscr();
    menu();
}

//store the test scores of current affairs quiz
void caStore()
{
    FILE* file = fopen("caLeaderboard.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read existing contents into memory
    char** lines = NULL;
    char line[100];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline character
        lines = realloc(lines, (lineCount + 1) * sizeof(char*));
        lines[lineCount] = strdup(line);
        lineCount++;
    }

    fclose(file);

    file = fopen("caLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.username, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    getchar();
    clrscr();
    menu();
}

/*  ----- TEST MARK REVIEWS ----  */

//review the previous test scores
void review()
{
    clrscr();
    int ch, score1, score2;
    char uname[20];
    printf("\t\t\t\tREVIEW\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\tSelect the topic you want to review.\n");
    printf("\t\t\t\t 1. Technology\n\t\t\t\t 2. Human Anatomy\n\t\t\t\t 3. Current Affairs\n\t\t\t\t 4. Return to Menu\n");
    printf("\t\t\t\tEnter your choice:");
    scanf("%d", &ch);
    switch(ch)
    {
        case 1: techr();
                break;
        case 2: humanr();
                break;
        case 3: currentr();
                break;
        case 4: menu();
                break;
        default: printf("Invalid option, Try again!\n");
                review();
    }
}

//previous scores of technology quiz
void techr()
{
    clrscr();
    printf("\t\t\t\tREVIEW - TECHNOLOGY\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\tThe marks are printed in the order of NEW -> OLD.\n\n");
    char word[100], word2[100];
    int flag = 0;
    strcpy(word, d.username);
    FILE* fp = fopen("techLeaderboard.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", word2);
        //printf("%s", Iline);
        if (strcmp(word2, word) == 0) {
            printf("%s", line);
            flag = 1;
        }
    }
    if (flag == 0){
            printf("\t\t\t\tNo data to be displayed.\n");
        }

    fclose(fp);
    getchar();
    clrscr();
    menu();
}

//previous scores of human anatomy quiz
void humanr()
{
    clrscr();
    printf("\t\t\t\tREVIEW - HUMAN ANATOMY\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\tThe marks are printed in the order of NEW -> OLD.\n");
    char word[100], word2[100];
    int flag = 0;
    strcpy(word, d.username);
    FILE* fp = fopen("humanLeaderboard.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", word2);
        //printf("%s", Iline);
        if (strcmp(word2, word) == 0) {
            printf("%s", line);
            flag = 1;
        }
    }
    if (flag == 0){
            printf("\t\t\t\tNo data to be displayed.\n");
        }

    fclose(fp);
    getchar();
    clrscr();
    menu();
}

//previous scores of current affairs quiz
void currentr()
{
    clrscr();
    printf("\t\t\t\tREVIEW - CURRENT AFFAIRS\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\tThe marks are printed in the order of NEW -> OLD.\n");
    char word[100], word2[100];
    int flag = 0;
    strcpy(word, d.username);
    FILE* fp = fopen("caLeaderboard.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", word2);
        //printf("%s", Iline);
        if (strcmp(word2, word) == 0) {
            printf("%s", line);
            flag = 1;
        }
    }
    if (flag == 0){
            printf("\t\t\t\tNo data to be displayed.\n");
        }

    fclose(fp);
    getchar();
    clrscr();
    menu();
}

/*  ----- ADMIN - MAIN MENU ----  */

void admin()
{
    clrscr();
    int ch;
    printf("\t\t\t\tQUIZWITZ - ADMIN LOGIN\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\tChoose any of the options to view:\n");
    printf("\t\t\t\t 1. List of students\n\t\t\t\t 2. Leaderboard\n\t\t\t\t 3. Exit\n");
    scanf("%d", &ch);
    switch(ch)
    {
                        case 1:
                                list();
                                break;
                        case 2:
                                leaderboard();
                                break;
                        case 3:
                                close();
                                break;
                        default:
                                printf("\t\tWrong Input! Try again!\n");
                                printf("Press any key to return to admin menu.");
                                getchar();
                                clrscr();
                                admin();
    }
}

/*  ----- PLAYER LIST ----  */

void list()
{
    clrscr();
    printf("\t\t\t\tQUIZWITZ - ADMIN LOGIN\n");
    printf("\t\t\t\tList of Users\n");
    printf("\t\t\t------------------------------------\n");
    FILE *fp;
    char username[20];

    fp = fopen("userdata.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    while (fscanf(fp, "%s", username) == 1) {
        printf("%s\n", username);
        // Skip remaining columns in the file
        fscanf(fp, "%*[^\n]");
    }
    fclose(fp);
    getchar();
    admin();
}

/*  ----- ADMIN LEADERBOARD ----  */

void leaderboard()
{
    clrscr();
    int ch;
    printf("\t\t\t\tQUIZWITZ - ADMIN LOGIN\n");
    printf("\t\t\t\tLEADERBOARD SETTINGS\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\t  Press any of the options below!\n");
    printf("\t\t\t\t 1. Technology\n\t\t\t\t 2. Human Anatomy\n\t\t\t\t 3. Current Affairs\n\t\t\t\t 4. Return To Admin Menu\n");
    printf("\t\t\t------------------------------------\n");
    scanf("%d", &ch);
    switch(ch)
    {
        case 1:
                leadTech();
                break;
        case 2:
                leadHumanBody();
                break;
        case 3:
                leadCurrentAff();
                break;
        case 4:
                admin();
                break;
        default:
                printf("\t\tWrong Input! Try again!\n");
                printf("Press any key to try again!\n");
                getchar();
                clrscr();
                leaderboard();
    }
}

//leaderboard for tech
void leadTech()
{
    clrscr();
    printf("\t\t\t\tQUIZWITZ - ADMIN\n");
    printf("\t\t\t\tLEADERBOARD - Technology\n");
    printf("\t\t\t------------------------------------\n");
    FILE *fp;
    char s;
    fp = fopen("techLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
    admin();
}

//leaderboard of human anatomy
void leadHumanBody()
{
    clrscr();
    printf("\t\t\t\tQUIZWITZ - ADMIN\n");
    printf("\t\t\t\tLEADERBOARD - Human Anatomy\n");
    printf("\t\t\t------------------------------------\n");
    FILE *fp;
    char s;
    fp = fopen("humanLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
    admin();
}

//leaderboard of current affairs
void leadCurrentAff()
{
    clrscr();
    printf("\t\t\t\tQUIZWITZ - ADMIN\n");
    printf("\t\t\t\tLEADERBOARD - Current Affairs\n");
    printf("\t\t\t------------------------------------\n");
    FILE *fp;
    char s;
    fp = fopen("caLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
    admin();
}

/*  ----- STARTING POINT ----  */
int main()
{
    start();
}

/*  ----- ENDING POINT ----  */
void close()
{
    clrscr();
    printf("\t\t\tQuizWitz waves you a goodbye!\n");
}
