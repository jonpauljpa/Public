#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getFrequency(int dice_array[], int frequency_array[]);
void printScoreCard(int scorecard[]);
int roll(void);
void reRoll(int dice_array[], int keepArray[]);
void printDice(int dice_array[]);
int getChanceScore(int dice_array[]);
int sumOfNum(int dice_array[], int num);
int getThreeOfKindScore(int dice_array[]);
int getFourOfKindScore(int dice_array[]);
int getSmallStraightScore(int dice_array[]);
int getLargeStraightScore(int dice_array[]);
int getFullHouseScore(int dice_array[]);
int getYahtzeeScore(int dice_array[]);
int highScore(int scorecard[]);

int main(void)
{ // Rand seed & Array Block
    srand(time(0));
    int diceArray[5] = {0};
    int freqArray[6] = {0};
    int keepArray[5] = {0};
    int scorecard[16] = {0};

    // Menu Block
    puts("Let's Play Yahtzee!");
    printf("%s", "Your Hand is: ");
    reRoll(diceArray, keepArray); // Random initial value
    printDice(diceArray);
    puts("Place a 1 to Keep a Dice Value, Place a 0 to Reroll it");

    for (int i = 0; i < 5; i++)
    {
        scanf("%i", &keepArray[i]);
    }

    reRoll(diceArray, keepArray);
    printDice(diceArray);
    puts("Place a 1 to Keep a Dice Value, Place a 0 to Reroll it");

    for (int i = 0; i < 5; i++)
    {
        scanf("%i", &keepArray[i]);
    }

    reRoll(diceArray, keepArray);
    puts("Your Final Hand is:");
    printDice(diceArray);

    // Scorecard Block
    scorecard[0] = sumOfNum(diceArray, 1);
    scorecard[1] = sumOfNum(diceArray, 2);
    scorecard[2] = sumOfNum(diceArray, 3);
    scorecard[3] = sumOfNum(diceArray, 4);
    scorecard[4] = sumOfNum(diceArray, 5);
    scorecard[5] = sumOfNum(diceArray, 6);
    scorecard[6] = getThreeOfKindScore(diceArray);
    scorecard[7] = getFourOfKindScore(diceArray);
    scorecard[8] = getFullHouseScore(diceArray);
    scorecard[9] = getSmallStraightScore(diceArray);
    scorecard[10] = getLargeStraightScore(diceArray);
    scorecard[11] = getChanceScore(diceArray);
    scorecard[12] = getYahtzeeScore(diceArray);
    printScoreCard(scorecard);

    // High Score Block
    printf("%s%i\n", "Your Highest Score is: ", highScore(scorecard));
}

int highScore(int scorecard[]) // Iterates thru scorecard array and returns highest value
{
    int highScore = 0;
    for (int i = 0; i < 12; i++)
    {
        if (scorecard[i] > highScore)
        {
            highScore = scorecard[i];
        }
    }
    return highScore;
}

void getFrequency(int dice_array[], int frequency_array[])
{
    for (int i = 0; i < 5; i++)
    {
        int diceRoll = dice_array[i];
        frequency_array[diceRoll - 1]++; // Minus 1 to account for index 0, larger array
    }
}

void printScoreCard(int scorecard[])
{ // Pre-mapped values in this array as notated in main
    puts("-----SCOREBOARD-----");
    printf("%s%i\n", "Ones: ", scorecard[0]);
    printf("%s%i\n", "Twos: ", scorecard[1]);
    printf("%s%i\n", "Threes: ", scorecard[2]);
    printf("%s%i\n", "Fours: ", scorecard[3]);
    printf("%s%i\n", "Fives: ", scorecard[4]);
    printf("%s%i\n", "Sixes: ", scorecard[5]);
    printf("%s%i\n", "Three of a kind: ", scorecard[6]);
    printf("%s%i\n", "Four of a kind: ", scorecard[7]);
    printf("%s%i\n", "Full House: ", scorecard[8]);
    printf("%s%i\n", "Small Straight: ", scorecard[9]);
    printf("%s%i\n", "Large Straight: ", scorecard[10]);
    printf("%s%i\n", "Chance: ", scorecard[11]);
    printf("%s%i\n", "YAHTZEE: ", scorecard[12]);
}
int roll(void) // Copied from previous prob set
{
    int range = 6;
    int start = 1;
    int dieRand = rand();
    int dieNum = dieRand % range + start;
    return dieNum;
}

void reRoll(int dice_array[],
            int keep_array[]) // Utilizes parallel array to re-roll on boolean input
{
    for (int i = 0; i < 5; ++i)
    {
        if (keep_array[i] == 0)
        {
            dice_array[i] = roll();
        }
    }
}

void printDice(int dice_array[]) // Copied from printIntArray in previous prob set
{
    printf(" %c", '[');
    for (int i = 0; i < 5; i++)
    {
        printf(" %i", dice_array[i]);
    }
    printf(" %c\n", ']');
}

int getChanceScore(int dice_array[]) // Sums all values in diceArray
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += dice_array[i];
    }
    return sum;
}

int sumOfNum(int dice_array[], int num) // Sums values in diceArray that match target num argument
{
    int sumNum = 0;
    for (int i = 0; i < 5; i++)
    {
        if (dice_array[i] == num)
        {
            sumNum += dice_array[i];
        }
    }
    return sumNum;
}

int getThreeOfKindScore(int dice_array[])
{
    int freq_array[6] = {0};
    getFrequency(dice_array, freq_array); // Creating freq array from passed dice_array
    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        if (freq_array[i] == 3)
        {
            sum = (i + 1) * 3; // Index of freq array + 1 = dice value
            return sum;
        }
    }
    return 0;
}

int getFourOfKindScore(int dice_array[])
{
    int freq_array[6] = {0};
    getFrequency(dice_array, freq_array);
    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        if (freq_array[i] == 4)
        {
            sum = (i + 1) * 4;
            return sum;
        }
    }
    return 0;
}

int getSmallStraightScore(int dice_array[])
{
    int freq_array[6] = {0};
    int numCount = 0;
    getFrequency(dice_array, freq_array);
    int smStraightPt = 30;
    for (int i = 0; i < 6; i++)
    { // Increments a non zero value & resets in freq array to account for num sequence
        if (freq_array[i] != 0)
        {
            numCount++;
        }
        else
        {
            numCount = 0;
        }
        if (numCount == 4) // If no reset and increment reaches 4, sm straight in hand
        {
            return smStraightPt;
        }
    }
    return 0;
}

int getLargeStraightScore(int dice_array[])
{
    int freq_array[6] = {0};
    int numCount = 0;
    getFrequency(dice_array, freq_array);
    int lgStraightPt = 40;
    for (int i = 0; i < 6; i++)
    {
        if (freq_array[i] != 0)
        {
            numCount++;
        }
        else
        {
            numCount = 0;
        }
    }
    if (numCount == 5) // If no reset and increment reaches 5, lg straight in hand
    {
        return lgStraightPt;
    }
    return 0;
}

int getFullHouseScore(int dice_array[])
{
    int freq_array[6] = {0};
    int pair = 0;
    int threeOfKind = 0;
    int fullHousePt = 25;
    getFrequency(dice_array, freq_array);
    for (int i = 0; i < 6; i++)
    {
        if (freq_array[i] == 2) // Checks freq array for a pair
        {
            pair++;
        }
        if (freq_array[i] == 3) // Checks freq array for 3 of a kind
        {
            threeOfKind++;
        }
    }
    if (pair > 0 && threeOfKind > 0) // If both conditions true, full house in hand
    {
        return fullHousePt;
    }
    return 0;
}

int getYahtzeeScore(int dice_array[])
{
    int freq_array[6] = {0};
    int yahtzeePt = 50;
    getFrequency(dice_array, freq_array);
    for (int i = 0; i < 6; i++)
    {
        if (freq_array[i] == 5) // If value in any freq array index equals 5, yahtzee in hand
        {
            return yahtzeePt;
        }
    }
    return 0;
}
