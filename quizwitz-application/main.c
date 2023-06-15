#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//-----Function prototypes----//
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

#define clrscr() system("clear")
#define getchar() system("read -n 1 -s -r");

//global variables
int full = 0;
int q[10];

struct data
{
    int score, age;
    char name[20], username[20], pass[20];
};

struct data d;

//indicates the start of the program
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
    printf("Enter the option for which you want to enter the data in.\n");
    printf("1. Username* : %s\n2. Name* : %s\n", d.username, d.name);
    printf("3. Password* : %s\n4. Submit\n5. Back\n", d.pass);
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            printf("Enter your username: ");
            scanf("%s", d.username);
            if (!check(d.username))
            {
                printf("Username already exists.\n");
                strcpy(d.username, "");
            }
            getchar();
            signup();
            break;

        case 2:
            printf("Enter your name:");
            scanf("%s", d.name);
            signup();
            break;

        case 3:
            printf("Enter password:");
            scanf("%s", p1);
            printf("Enter the password once again for confirmation\n");
            scanf("%s", p2);
            if (strcmp(p1, p2)!=0)
            {
                printf("Unsuccessful. Passwords do not match\n");
                strcpy(p1, "");
                strcpy(p2, "");
            }
            else 
            {
                printf("Password creation successful.\n");
                strcpy(d.pass, p1);
            }
            getchar();
            signup();
            break;

        case 4:
            printf("Are you sure? Press 'y' for yes and 'n' for no.\n");
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
                    printf("Account successfully created.\n");
                    printf("Press any button to continue.\n");
                    getchar();
                    menu();
                }
                else
                {
                    printf("Please fill all the mandatory fields.\nPress any key to try again.\n");
                    getchar();
                    signup();
                }
            }
            else
            {
                printf("Press any key to continue.\n");
                getchar();
                signup();
            }
            start();
            break;
        case 5: 
            start();
        default:
            printf("Wrong input! Press any key to try again!\n");
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

//for logging inside the acc
void login()
{
    char s1[20], p[20];
    int i, y;
    clrscr();
    printf("\t\t\t\tQUIZWITZ - LOGIN\n\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\tUsername: ");
    scanf("%s", s1);
    printf("\t\tPassword: ");
    scanf("%s", p);
    y = search(s1, p);
    if (!y)
    {
      printf("\nInvalid credentials\n");
      printf("Try again!\n");
      strcpy(s1, "");
      strcpy(p, "");
      printf("Press any key to try again\n");
      getchar();
      login();
    }
    else
    {
        strcpy(d.username, s1);
        printf("You have succesfully logged in!\nPress any key to go to player menu.\n");
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

//student menu
void menu()
{
    clrscr();
    int ch;
    printf("\t\t\t\tQUIZWITZ - PLAYER LOGIN\n");
    printf("\t\t\t------------------------------------\n");
    printf("Choose any of the options to view:\n");
    printf("\t\t\t\t 1. Attempt Quiz\n\t\t\t\t 2. Review previous attempts\n\t\t\t\t 3.  Exit\n");
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

//review the previous test scores
void review()
{
    clrscr();
    int ch, score1, score2;
    char uname[20];
    printf("\t\t\t\tREVIEW\n");
    printf("Select the topic you want to review.");
    printf("\t\t\t\t 1. Technology\n\t\t\t\t 2. Human Anatomy\n\t\t\t\t 3.  Current Affairs\n\t\t\t\t 4. Return to Menu\n");
    printf("Enter your choice:");
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
    char word[100];
    strcpy(word, d.username);
    FILE* fp = fopen("techLeaderboard.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strncmp(line, word, strlen(word)) == 0) {
            printf("%s", line);
        }
    }

    fclose(fp);
}

void humanr()
{
    int i=0;
    char uname[20], score1, score2, s;
    FILE *fp, *f;
    fp = fopen("humanbody.txt", "r");
    while(fscanf(fp, "%s %*s %*s %*s", uname)==1)
    {
        while (strcmp(uname, d.username)!=0){
            break;
        }
    }
    while(fscanf(fp, "%*s %*s %s %s", score1, score2))
    {
        if(strcmp(&score1, "null") != 0 && strcmp(&score2, "null") != 0)
        {
            printf("You are allowed to view the answers.\n");
            i=1;
        }
        else
            printf("You are allowed to view the answers only after you have attempted the quiz twice.\n");
    }
    fclose(fp);
    if (i==1)
    {
        f = fopen("humanr.txt", "r");
        while((s=fgetc(f))!=EOF) 
            printf("%c", s);
    }
}

void currentr()
{
    int i=0;
    char uname[20], score1, score2, s;
    FILE *fp, *f;
    fp = fopen("current.txt", "r");
    while(fscanf(fp, "%s %*s %*s %*s", uname)==1)
    {
        while (strcmp(uname, d.username)!=0){
            break;
        }
    }
    while(fscanf(fp, "%*s %*s %s %s", score1, score2))
    {
        if(strcmp(&score1, "null") != 0 && strcmp(&score2, "null") != 0)
        {
            printf("You are allowed to view the answers.\n");
            i=1;
        }
        else
            printf("You are allowed to view the answers only after you have attempted the quiz twice.\n");
    }
    fclose(fp);
    if (i==1)
    {
        f = fopen("currentr.txt", "r");
        while((s=fgetc(f))!=EOF) 
            printf("%c", s);
    }
}
//admin login
void admin()
{
    int ch;
    printf("\t\t\t\tQUIZWITZ - ADMIN LOGIN\n");
    printf("\t\t\t------------------------------------\n");
    printf("\t\t\t\tChoose any of the options to view:\n");
    printf("\t\t\t\t 1. List of students\n\t\t\t\t 2. Leaderboard\n\t\t\t\t 3.Exit\n");
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
//list the registered students with their username, name, password
void list()
{
    printf("\t\t\t\tQUIZWITZ - ADMIN LOGIN\n");
    printf("\t\t\t\tList of Users\n");
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
}

//leaderboard for tech: listing name, username, score1 and score2
void leadTech()
{
    FILE *fp;
    char s;
    fp = fopen("techLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}

//print leaderboard
void leadHumanBody()
{
    FILE *fp;
    char s;
    fp = fopen("humanbodyLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}

//print leaderboard
void leadCurrentAff()
{
    FILE *fp;
    char s;
    fp = fopen("currentaffairsLeaderboard.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}

//leaderboard menu
void leaderboard()
{
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
//rules to be followed in the game
void rules()
{
        printf("\t\t   QUIZWITZ - RULES AND REGULATIONS\n");
        printf("\t\t--------------------------------------\n");
        printf("\t 1. The overall quiz is of 10 points\n");
        printf("\t 2. The quiz comprises of three topics\n");
        printf("\t 3. Only one option is correct among the four\n");
        printf("\t 4. No time limit and no negative mark deductions!\n");
        printf("\t 5. Irrevelant inputs result in no points.\n");
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
    printf("\t\tSelect the topic you want to attempt quiz in!\n");
    printf("\t\t\t1. Technology\n\t\t\t2. Human anatomy\n\t\t\t3. Current Affairs\n");
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

    // Open the file for writing, truncating existing contents
    file = fopen("techLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.name, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    printf("\n\t\t   Press any key to go to the menu!");
    getchar();
    clrscr();
    menu();
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

    // Open the file for writing, truncating existing contents
    file = fopen("humanLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.name, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    printf("\n\t\t   Press any key to go to the menu!");
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

    // Open the file for writing, truncating existing contents
    file = fopen("caLeaderboard.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Write new data at the top
    fprintf(file, "%s\t  %d\n", d.name, d.score);

    // Write existing data
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    fclose(file);
    printf("\n\t\t   Press any key to go to the menu!");
    getchar();
    clrscr();
    menu();
}

// STARTING POINT
int main()
{
    start();
}

// EXIT POINT
void close()
{
    clrscr();
    printf("\t\t\tQuizWitz waves you a goodbye!\n");
}

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
    int lower = 1, upper = 2, num;
    srand(time(0));
    num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

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

    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
    techStore();
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

    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
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

    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
}