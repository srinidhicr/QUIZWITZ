#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//-----Function prototypes----//
void start();
void close();
void leaderboard();
void rules();
void opta(char ch);
void qset();
void optb(char ch);
void optc(char ch);
void optd(char ch);
void set1();
void set2();
void set3();
void clean1();
void clean2();
void clean3();
void clean();
void sc();
void admin();
void login();
void signup();
void erase();
void stor();
void list();
void tech();
void humanBody();
void currentAff();
int search(char u[], char p[]);
void menu();
void review();
void techr();
void humanr();
void currentr();
void randques();

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

int check();
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
                    fprintf(fp, "%s\t\t", d.username);
                    fprintf(fp, "%s\t\t", d.name);
                    fprintf(fp, "%s\n", d.pass);
                    fclose(fp);
                    printf("Account successfully created.\n");
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
      getchar()
      login();
    }
    else
    {
        printf("You have succesfully logged in!\nPress any key to go to player menu.\n");
        getchar();
        menu();
    }
}

int search(char u[], char p[])
{
    char user[20], pwd[20];
    FILE *fp;
    fp = fopen("userdata.txt", "r");
    while(fscanf(fp, "%s %*s %*s", user) ==1 )
    {
        if (strcmp(u, user)==0)
        {
            while(fscanf(fp, "%*s %*s %s", pwd) == 1) 
            {
                if (strcmp(p, pwd)==0)
                    return 1;
            }
        }
    }
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
                        case 1:
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
//review the attempted questions
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
void techr()
{
    int i=0;
    char uname[20], score1, score2, s;
    FILE *fp, *f;
    fp = fopen("tech.txt", "r");
    while(fscanf(fp, "%s %*s %*c %*c", uname)==1)
    {
        while (strcmp(uname, d.username)!=0){
            break;
        }
    }
    while(fscanf(fp, "%*s %*s %c %c", score1, score2))
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
        f = fopen("techr.txt", "r");
        while((s=fgetc(f))!=EOF) 
            printf("%c", s);
    }
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
                tech();
                break;
        case 2:
                humanBody();
                break;
        case 3:
                currentAff();
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
//leaderboard for tech: listing name, username, score1 and score2
void tech()
{
    FILE *fp;
    char s;
    fp = fopen("tech.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}
//leaderboard
void humanBody()
{
    FILE *fp;
    char s;
    fp = fopen("humanbody.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}
//leaderboard
void currentAff()
{
    FILE *fp;
    char s;
    fp = fopen("currentaffairs.txt", "r");
    while((s=fgetc(fp))!=EOF) 
        printf("%c",s);
    fclose(fp);
    getchar();
}
//option a is correct
void opta(char ch)
{
    if (ch == 'a')
        d.score++;
}
//option b is correct
void optb(char ch)
{
    if (ch =='b')
        d.score++;
}
//option c is correct
void optc(char ch)
{
    if (ch =='c')
        d.score++;
}
//option d is correct
void optd(char ch)
{
    if (ch =='d')
        d.score++;
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
//clear the previous contents on the screen and display the necessary data
void clean()
{
    getchar();
    clrscr();
}
void clean1()
{
    getchar();
    clrscr();
    printf("\t\t\t\tQUIZ\n");
    printf("\t\t\t     TECHNOLOGY\n");
}
void clean2()
{
    getchar();
    clrscr();
    printf("\t\t\t\tQUIZ\n");
    printf("\t\t\t    HUMAN ANATOMY\n");
}

void clean3()
{
    getchar();
    clrscr();
    printf("\t\t\t\tQUIZ\n");
    printf("\t\t\t  CURRENT AFFAIRS\n");
}

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
    stor();
}

void stor()
{

    FILE * p;
    p=fopen("packagefile.txt","a");
    fprintf(p, "%s\t", d.name);
    fprintf(p, "  %d\n", d.score);
    fclose(p);
    printf("\n\t\t   Press any key to go to the menu!");
    getchar();
    clrscr();
    menu();
}

void close()
{
    clrscr();
    printf("\t\t\tQuizWitz waves you a goodbye!\n");
}

int main()
{
    start();
}

void randques()
{
    int lower = 1, upper = 20, count = 10, j, num;
    srand(time(0));
    for (j = 0; j < 10; j++) {
        num = (rand() % (upper - lower + 1)) + lower;
        q[j] = num;
    }
}

void set1()
{
   randques();
   char ch;
   for (int i=0; i<10; i++)
   {
      switch(q[i])
      {
         case 1: printf("Q.The creation of cryptocurrency 'Dogecoin' was inspired by which of these creatures?\n");
                 printf("a) Dog\nb) Monkey\nc) Parrot\nd) Squirrel\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 opta(ch);
                 clean1();
                 break;

         case 2: printf("Q.The first-ever 3D printed house of India has recently been inaugurated by Union Finance Minister Nirmala Sitharaman at which place?\n");
                 printf("a) IIT Delhi\nb) IIT Bengaluru\nc) IIT Madras\nd) IIT Kanpur\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optc(ch);
                 clean1();
                 break;

         case 3: printf("Q.Microsoft has opened its new IDC facility in which city?\n");
                 printf("a) Faridabad\nb) Mumbai\nc) Surat\nd) Noida\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

         case 4: printf("Q.Which company has completed the acquisition of smart wearable company Fitbit?\n");
                 printf("a) Hike\nb) Flipkart\nc) Facebook\nd) Google\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

         case 5: printf("Q.Number of bit used by the IPv6 addressdesktop __\n");
                 printf("a) 32 bit\nb) 64 bit\nc) 128 bit\nd) 256 bit\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optc(ch);
                 clean1();
                 break;

         case 6: printf("Q. Which of the following programming language is used to create programs like applets?\n");
                 printf("a) COBOL\nb) C Language\nc) Java\nd) BASIC\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optc(ch);
                 clean1();
                 break;

        case 7: printf("Q.A network designed to allow communication within an organization is called:\n");
                printf("a) World Wide Web\nb) Yahoo\nc) Intranet\nd) Internet\n");
                printf("\nEnter option:\n");
                scanf(" %c", &ch);
                optc(ch);
                clean1();
                break;

        case 8: printf("Q.What is the name of China's first Mars Rover?\n");
                printf("a) Zhurong\nb) Zhing\nc) Shiang\nd) Huo Xing\n");
                printf("\nEnter option:\n");
                scanf(" %c", &ch);
                opta(ch);
                clean1();
                break;

        case 9: printf("Q.Which of these products is not made by the Apple Corporation?\n");
                printf("a) IMAX\nb) iPhone\nc) iPad\nd) iPod\n");
                printf("\nEnter option:\n");
                scanf(" %c", &ch);
                opta(ch);
                clean1();
                break;

        case 10: printf("Q.What is the name of India's first social media app named launched by Vice President Venkiah Naidu?\n");
                 printf("a) Milap\nb) Chatmat\nc) Connect\nd) Elyments\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

        case 11: printf("Q.How many computer languages are in use?\n");
                 printf("a) 2000\nb) 5000\nc) 50\nd) 20\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 opta(ch);
                 clean1();
                 break;

        case 12: printf("Q. Which of these is not an early computer?\n");
                 printf("a) ENIAC\nb) UNIVAC\nc) NASA\nd) SAGE\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean1();
                 break;

        case 13: printf("Q.Who founded Apple Computer?\n");
                 printf("a) Stephen Fry\nb) Bill Gates\nc) Steve Jobs\nd) Stephen Hawking\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optc(ch);
                 clean1();
                 break;

        case 14: printf("Q. Which of these is not a peripheral, in computer terms?\n");
                 printf("a) Keyboard\nb) Monitor\nc) Mouse\nd)  Motherboard\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

        case 15: printf("Q.Which of the following is not one of the early “protocols,” or ways to use the Internet?\n");
                 printf("a) Blogging\nb) Telnet\nc) Gopher\nd) FTP\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 opta(ch);
                 clean1();
                 break;

        case 16: printf("Q.What does the Internet prefix WWW stand for?\n");
                 printf("a) Wide Width Wickets\nb) World Wide Web\nc) Worldwide Weather\nd) Western Washington World\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optb(ch);
                 clean1();
                 break;

        case 17: printf("Q. Which of these is not a kind of computer?\n");
                 printf("a) Apple\nb) Lenovo\nc) Toshiba\nd) Lada\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

        case 18: printf("Q.Who invented flexible photographic film?\n");
                 printf("a)Leonardo da Vinci\nb) Linda Eastman\nc) Louis Daguerre\nd) George Eastman\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

        case 19: printf("Q. When was the DVD introduced?\n");
                 printf("a) 1970\nb) 1990\nc) 2000\nd) 1995\n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optd(ch);
                 clean1();
                 break;

        case 20: printf("Q. What fighter plane of World War II came out of a design for a racing seaplane?\n");
                 printf("a) F6F Hellcat\nb) SBD Dauntless\nc) Spitfire\nd) Zero \n");
                 printf("\nEnter option:\n");
                 scanf(" %c", &ch);
                 optc(ch);
                 clean1();
                 break;
      }
   }
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
}

void set2()
{
   randques();
   int i;
   char ch;
   for (i=0; i<10; i++)
   {
      switch(q[i])
      {
         case 1: printf("Q. What is the longest bone in the human body?\n");
                 printf("a) Fibula\nb) Tibia\nc) Femur\nd) None of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

         case 2: printf("Q. What is the name of the substance that gives skin and hair its pigment?\n");
                 printf("a) Carotene\nb) Hemoglobin\nc) Melanin\nd) Keratin\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

         case 3: printf("Q. It has been estimated that the human body consists of ______ cells?\n");
                 printf("a) 15 trillion\nb) 500 million\nc) 37.2 trillion\nd) 27 billion\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

         case 4: printf("Q. Microglia cells, a type of glial cell, account for what percentage of cells in the brain?\n");
                 printf("a) 0–4%%\nb) 5–10%%\nc) 10–15%%\nd)25–30%%\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

         case 5: printf("Q. ______ maintains homeostasis in the internal environment by regulating vital organs such as digestion, respiration, blood circulation, excretion, and the secretion of hormones.\n");
                 printf("a) The autonomic nervous system\nb) Feedback looping\nc) The somatic nervous system\nd) None of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 opta(ch);
                 clean2();
                 break;

         case 6: printf("Q. Hormones have an influence on ______.\n");
                 printf("a) the capacity for new learning\nb) vividness of imagery\nc) growth\nd) all of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean2();
                 break;

        case 7: printf("Q. Organisms within the gut play a role in early programming and later responsivity of the stress system. The gut is inhabited ______ times the number of cells in the human body (Dinan and Cryan, 2012).\n");
                printf("a) 5\nb) 10\nc) 15\nd) 20\n");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                optb(ch);
                clean2();
                break;

        case 8: printf("Q. Our ______ is made up of barriers and cells that keep harmful germs from entering the body.");
                printf("a) innate immune system\nb) endocrine system\nc) adaptive immune system\nd) nervous system");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                opta(ch);
                clean2();
                break;

        case 9: printf("Q.  Which cells are a type of white blood cell (called lymphocytes) which attack infected or damaged cells directly or produce powerful chemicals that mobilize an army of other IS substances and cells?\n");
                printf("a) glial cells\nb) B cells\nc) dendritic cell\nd) T Cells\n");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                optd(ch);
                clean2();
                break;

        case 10: printf("Q.  Inflammation is a ______ process that is only intended to last a few days but, if it is continued indefinitely, there is a poor prognosis in many conditions. Inflammatory responses take precedence over normal body.\n");
                 printf("a) homogenous\nb) heterogeneous\nc) homeostatic\nd) none of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

        case 11: printf("Q. Who in The Wisdom of the Body coined the term ‘homeostasis’?\n");
                 printf("a) Walter Cannon (1932)\nb) Curt Richter (1942)\nc) Claude Bernard (1865)\nd) Mellanby (1920)\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 opta(ch);
                 clean2();
                 break;

        case 12: printf("Q. The ______ uses neurotransmitters and the ______ uses neuromodulators and hormones.\n");
                 printf("a) endocrine system, nervous system\nb) nervous system, immune system\nc) nervous system, endocrine system\nd) immune system, nervous system\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean2();
                 break;

        case 13: printf("Q. Which structure of the eye is the most sensitive but contains no blood vessels?\n");
                 printf("a) Pupil\nb) Cornea\nc) Iris\nd) None of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean2();
                 break;

        case 14: printf("Q. What is the human body's largest external organ?\n");
                 printf("a) Stomach\nb) Skin\nc) Liver\nd) None of these\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean2();
                 break;

        case 15: printf("Q. How many layers of skin are in the epidermis?\n");
                 printf("a) 3\nb) 2\nc) 4\nd) 5\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean2();
                 break;

        case 16: printf("Q. How much exercise each week is recommended to help prevent heart disease?\n");
                 printf("a) 60 minutes on average\nb) 90 minutes on average\nc) 120 minutes on average\nd) 150 minutes on average\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean2();
                 break;

        case 17: printf("Q. How can you tell if food has enough bacteria to cause food poisoning?\n");
                 printf("a) It will smell\nb) It can't, it will appear normal\nc) It will have a different colour\nd) It will taste different\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean2();
                 break;

        case 18: printf("Q. Drinking a moderate amount of alcohol is considered safe for your heart. What can happen if you drink more?\n");
                 printf("a) Too much alcohol can raise blood pressure\nb) Too much alcohol can raise triglyceride levels\nc) Too much alcohol lowers LDL ('bad') cholesterol\nd) Both a and b\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean2();
                 break;

        case 19: printf("Q. What does the 19 in COVID-19 refer to?\n");
                 printf("a) There are 19 variants of the coronavirus\nb) There are 19 symptoms of coronavirus disease\nc) This is the 19th coronavirus pandemic\nd) The coronavirus and the disease it causes were identified in 2019\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean2();
                 break;

        case 20: printf("Q. Which pharmaceuticals company has decided to expand its vaccine business in the United Kingdom with an investment of 240 million?\n");
                 printf("a) Franco India Pharmaceuticals\nb) Serum Institute of India\nc) Astra Zeneca Pharma India\nd) None of the above\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean2();
                 break;
      }
   }
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
}

void set3()
{
   int i;
   char ch;
   for (i=0; i<10; i++)
   {
      switch(q[i])
      {
         case 1: printf("Q.Leena Nair is appointed as the secretary in the ministry of _.\n");
                 printf("a) Home Affairs\nb) Tribal Affairs\nc) External Affairs\nd) Parliamentary Affairs\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

         case 2: printf("Q.Mamata Banerjee has been sworn in how many times as the Chief Minister of West Bengal?\n");
                 printf("a) Second\nb) Third\nc) Fourth\nd) Fifth\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

         case 3: printf("Q.Which party has won majority seats in the Puducherry Assembly Election 2021?\n");
                 printf("a) BJP\nb) INC\nc) AINRC\nd) DMK\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean3();
                 break;

         case 4: printf("Q. Who is the present speaker of Lok Sabha?\n");
                 printf("a) Meera Kumar\nb) Ramnath Kovind\nc) Om birla\nd) Ramvilas Paswa\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean3();
                 break;

         case 5: printf("Q.ADB has projected India's economic growth for 2021-2022 at which percent?\n");
                 printf("a) 10.0 %%\nb) 9.7 %%\nc) 5.9 %%\nd) 8.9%%\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

         case 6: printf("Q.Bharat Dynamics Limited (BDL) and the Indian Army have signed a deal refurbishment of IGLA-1M missiles worth of?\n");
                 printf("a) Rs 371.41 crore\nb) Rs 571.41 crore\nc) Rs 271.41 crore\nd) Rs 471.41 crore\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean3();
                 break;

        case 7: printf("Q.What is the interest rate on employees' provident fund (EPF) deposits for 2020-21?\n");
                printf("a) 7.4 %%\nb) 8.5 %%\nc) 8.1 %%\nd) 6.1 %%\n");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                optb(ch);
                clean3();
                break;

        case 8: printf("Q.Which company launched 'Savdhan Rahein, Safe Rahein' a public awareness campaign on financial fraud risks?\n");
                printf("a) DCB Bank\nb) Bajaj Finserv\nc) SBI Capital\nd) ICICI Bank\n");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                optb(ch);
                clean3();
                break;

        case 9: printf("Q.Which pharmaceuticals company has decided to expand its vaccine business in the United Kingdom with an investment of 240 million?\n");
                printf("a) Franco India Pharmaceuticals\nb) Serum Institute of India\nc) Astra Zeneca Pharma India\nd) None of the above\n");
                printf("\nEnter option:\n");
                scanf("%c", &ch);
                optb(ch);
                clean3();
                break;

        case 10: printf("Q.The State Bank of India allocated how much amount towards the fight against Covid 19?\n");
                 printf("a) Rs. 70 cr\nb) Rs. 92 cr\nc) Rs. 71 cr\nd) Rs. 70 cr\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 11: printf("Q. U.S has recently named which country as the State Sponsor of Terrorism?\n");
                 printf("a) Argentina\nb) Cuba\nc) Chile\nd) Brazil\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 12: printf("Q. Which personality announced to give away USD 100 million for the best carbon capture technology?\n");
                 printf("a) Bill Gates\nb) Elon Musk\nc) Mark Zuckerberg\nd) Jack Ma\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 13: printf("Q.Neptune Declaration’, which was seen in the news recently, is associated with which sector?\n");
                 printf("a) Aviation\nb) Migrant Labourers\nc) Maritime\nd) Sports\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optc(ch);
                 clean3();
                 break;

        case 14: printf("Q.Which organization has issued Purple Notice to member countries against investment frauds via dating applications?\n");
                 printf("a) UNFCCC\nb) International Court of Justice\nc) World Trade Organization\nd) Interpol\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean3();
                 break;

        case 15: printf("Q.The UN Security Council has expressed concern over the military coup in which country?\n");
                 printf("a) Chile\nb) Myanmar\nc) Nepal\nd) Syria\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 16: printf("Q.Which country proposed the observance of the World Pulses Day?\n");
                 printf("a) Chile\nb) Burkina Faso\nc) Niger\nd) Benin\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 17: printf("Q.Which country is to host a virtual SAARC meet to discuss on management and response of Covid-19?\n");
                 printf("a)Nepal\nb) India\nc) Sri Lanka\nd) Afghanistan ");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 18: printf("Q.Which country has suspended its Defence cooperation with Myanmar, over its recent military takeover?\n");
                 printf("a)New Zealand\nb) Australia\nc) United Kingdom\nd) India\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optb(ch);
                 clean3();
                 break;

        case 19: printf("Q.What is the name given to thr group of nations consisting of the United States, India, Australia and Japan?\n");
                 printf("a)G4\nb) BRICS\nc) SAARC\nd) QUAD\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean3();
                 break;

        case 20: printf("Q.What is “La Perouse”, that was seen in the news recently?\n");
                 printf("a)French Labour Law\nb) Japanese Satellite\nc) Chinese Mobile App\nd) Defence Exercise\n");
                 printf("\nEnter option:\n");
                 scanf("%c", &ch);
                 optd(ch);
                 clean3();
                 break;
      }
   }
    printf("\t\t\t\tQUIZWITZ\n");
    printf("\t\t--------------------------------------\n");
    printf("\t\t    You scored a total of %d points! ", d.score);
    sc();
}