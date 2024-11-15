#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//for anagram
    char ana1[] = "listen";
    char ana2[] = "earth";
    char ana3[] = "binary";

//for caesar-cipher
    char ciph1[] = "There is a secret code";
    char ciph2[] = "Attack at dawn";
    char ciph3[] = "Meet me at the park";

//for word-guessing
    char word1[] = "program";
    char word2[] = "network";
    char word3[] = "science";

int stlen(char str[]);
void stcpy(char str[],char str1[]);
int stcompare(char str1[],char str2[]);

int show_menu();

void shuffle(char result[], char str[]);

void encrypt(char str[],int shift);
void decrypt(char str[],int shift);

int is_substring(char str[],char sub[]);


int main()
{
    srand(time(NULL));

    int score=0;

    char chosen[50];
    char chosen_phrase[200];
    char chosen_word[50];

    int r = rand() % 3;

    if (r == 0)
    {
        stcpy(chosen_word, word1);
        stcpy(chosen,ana1);
        stcpy(chosen_phrase,ciph1);
    }
    else if (r == 1)
    {
        stcpy(chosen_word, word2);
        stcpy(chosen,ana2);
        stcpy(chosen_phrase,ciph2);
    }
    else
    {
        stcpy(chosen_word, word3);
        stcpy(chosen,ana3);
        stcpy(chosen_phrase,ciph3);
    }


    int x= show_menu();

    if(x == 2)
    {
        return 0;
    }

    //anagram challenge
        printf("Starting Anagram Challenge...\n");

        char shuffled_word[50];
        shuffle(shuffled_word,chosen);
        printf("Scrambled word: %s\n",shuffled_word);
        
        int anagram_attempt = 1;
        int anagram_success = 0;
        while(anagram_attempt <= 3)
        {
            char guess[50];
            printf("Your guess: ");
            scanf("%s",guess);

            if(stcompare(guess,chosen) == 1)
            {
                printf("Correct! You solved it in %d attempt(s)\n",anagram_attempt);
                anagram_success=1;
                break;
            }
            else
            {
                printf("Incorrect! ");
                if(anagram_attempt < 3)
                {
                    printf("Try again.\n");
                }
                else
                {
                    printf("Correct word: %s\n",chosen);
                    break;
                }
                anagram_attempt++;
            }
        }
        if( anagram_attempt > 3 ) anagram_attempt--;

        score = score + (10*anagram_success) + ((3 - anagram_attempt)*10);

    //caesar-cipher challenge
        int shift=0;
        while(shift == 0)
        {
            shift = rand() % 10;
        }
        printf("Starting Caesar Cipher Challenge...\n");

        char encrypted[200];
        stcpy(encrypted,chosen_phrase);

        encrypt(encrypted,shift);
        printf("Encrypted phrase: %s\n",encrypted);

        int cipher_attempt=1;
        int cipher_success=0;

        while(cipher_attempt<=3)
        {
            char guess_phrase[200];
            getchar();
            printf("Your guess: ");
            scanf("%[^\n]",guess_phrase);

            if(stcompare(guess_phrase,chosen_phrase) == 1)
            {
                printf("Correct! You decrypted it in %d attempt(s)\n",cipher_attempt);
                cipher_success=1;
                break;
            }
            else
            {
                printf("Incorrect! ");
                if(cipher_attempt < 3)
                {
                    printf("Try again.\n");
                }
                else
                {
                    printf("Correct phrase: %s\n",chosen_phrase);
                    break;
                }
                cipher_attempt++;
            }
        }

        if(cipher_attempt>3) cipher_attempt--;

        score = score + (cipher_success*10) + ((3-cipher_attempt)*10);
    
    
    //word guessing challenge
        printf("Starting Word Guessing Challenge....\n");

        int word_attempt = 1;
        int word_guess_success=0;

        printf("Hint: %c%c%c___\n", chosen_word[0], chosen_word[1], chosen_word[2]);

        printf("Select an option: 1. Write Answer 2.Check Substring 3.Check Length: \n");
        
        int used_check_substring = 0,used_check_len = 0;
        int utilty_count = 0;

        while(word_attempt <= 3)
        {
            int option;
            printf("Enter option: ");

            scanf("%d", &option );
            

            //user wants to check substring
            if(option == 2)
            {
                if(!used_check_substring)
                {
                    char sub[50];
                    printf("Enter substring: ");
                    scanf("%s",sub);
                    if (is_substring(chosen_word, sub) == 1)
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }

                    used_check_substring = 1;
                    utilty_count++;
                    score = score - 2;
                }
                else
                {
                    printf("Error: Utility already used.\n");
                }
            }

            //user wants to check length
            else if(option == 3)
            {
                if(!used_check_len)
                {
                    printf("Enter length: ");
                    int n;
                    scanf("%d",&n);
                    if(stlen(chosen_word) == n)
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }

                    utilty_count++;
                    used_check_len = 1;
                    score = score - 2;
                }
                else
                {
                    printf("Error: Utility already used.\n");
                }
            } 

            //user wants to enter the answer
            else if(option == 1)
            {   
                char guess_word[200];

                printf("Enter your guess: ");
                scanf("%s",guess_word);

                if(stcompare(chosen_word,guess_word) == 1)
                {
                    printf("Correct! You guessed it in %d attempt(s) using %d utility functions.\n",word_attempt,utilty_count);
                    word_guess_success=1;
                    break;
                }
                else
                {
                    printf("Incorrect! ");
                    if(word_attempt == 3)
                    {
                        printf("Correct word: %s\n",chosen_word);
                        break;
                        
                    }
                    else
                    {
                        printf("Try again.\n");
                    }
                }

                word_attempt++;
            }

            //if user enters option other than the three mentioned
            else
            {
                printf("Invalid option. Please enter a number between 1 & 3 again.\n");
            }
        }

        if(word_guess_success > 3) word_guess_success--;

        score = score + word_guess_success*10 + (3 - word_attempt)*10;

    if(anagram_success == 1 && cipher_success == 1 && word_guess_success == 1)
    {
        score = score +5;
    }

    printf("Game Over!\n");
    printf("Your total score: %d points\n",score);

    return 0;
}


int show_menu()
{
    printf("Welcome to the Game World!\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d",&choice);

    return choice;
}

int stlen(char str[]) 
{
    int size = 0;
    while (str[size])
    {
        size++;
    }
    return size;
}


void stcpy(char str[],char str1[])
{
    int i;
    for(i=0 ; str1[i] ; i++)
    {
        str[i] = str1[i];
    }

    str[stlen(str1)] = '\0';
}

//pass two strings so the first is a shuffled version of the second
void shuffle(char result[], char str[])
{
    int n=stlen(str);
    
    stcpy(result,str);

    int i,j;
    for(i=n-1 ; i>= 0 ; i--)
    {
        j= rand() % (i+1);

        char temp=result[i];
        result[i]=result[j];
        result[j]=temp;
    }
}

//returns 0 if the strings dont exactly match
int stcompare(char str1[],char str2[])
{
    if(stlen(str1) != stlen(str2))
    {
        return 0;
    }

    int i;
    for(i=0 ; str1[i] ; i++)
    {
        if(str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

//shifts each character in str by "shift" forward and wraps around
void encrypt(char str[],int shift)
{
    int i,temp;
    for(i=0 ; str[i] ; i++)
    {
        if(str[i]!=' ')
        {
            if(str[i]>='a'&&str[i]<='z')
            {
                str[i] = ((str[i] - 'a' + shift) % 26) + 'a';
            }
            else if(str[i]>='A' && str[i]<='Z')
            {
                str[i] = ((str[i] - 'A' + shift) % 26) + 'A';
            }
        }
    }
}

void decrypt(char str[],int shift)
{
    int i,temp;
    for(i=0;str[i];i++)
    {
        if(str[i]!=' ')
        {
            if(str[i]>='a'&&str[i]<='z')
            {
                str[i] = ((str[i] - 'a' - shift) % 26) + 'a';
            }
            else if(str[i]>='A' && str[i]<='Z')
            {
                str[i] = ((str[i] - 'A' - shift) % 26) + 'A';
            }
        }
    }
}


int is_substring(char str[],char sub[])
{
    int i,j;
    int sub_size = stlen(sub);
    int str_size = stlen(str);

    if (sub_size == 0)
    {
        return 1;
    }
    if (sub_size > str_size)
    {
        return 0;
    }


    for(i=0 ;i <= str_size - sub_size ; i++)
    {
        for(j=0;j<sub_size;j++)
        {
            if(str[i+j] != sub[j])
            {
                break;
            }
        }

        if(j == sub_size)
        {
            return 1;
        }
    }
    
    return 0;
}
