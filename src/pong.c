#include <stdio.h>
#include <math.h>

/*We greet you!! Before you opened the game Pong. The game developers are: sunflowa. 
On the screen you see a Pong field, a net, a ball, a counter and 2 rackets. Our program is played by 2 players. 
The essence of the game: each player must hit the ball from his side and hit it on the far opposite border. 
The goal of the game is to hit the ball on the opposite border 21 times. Rackets can be controlled by pressing the keys. 
The first player's control buttons are the A/Z buttons (regardless of case). 
Button A raises the racket 1 step, button Z releases it 1 step. 
The second player's control buttons are the K\M buttons (regardless of case). 
The K button moves the racket 1 step up, and the M button 1 step down. Both buttons are written together without a space. 
The spacebar button does not change the location of the racket. Other buttons are not allowed. 
The starting point of the program is pressing the Enter button. Good game!!
*/

int change_coor_y_racketA(int y_start_racket_A, char letter_A, int height);
int change_coor_y_racketB(int y_start_racket_B, char letter_B, int height);
void func_table(int height, int width, int x_ball, int y_ball, int x_racket_A, int x_racket_B,
                int y_start_racket_A, int y_start_racket_B, int count_A, int count_B);
void check_win(int count_A);

int main() {
    // data from task
    // A - first user (left)- count is number of win points, B - right
    int count_A = 0;
    int count_B = 0;
    int width = 80;
    int height = 25;
    char letter_A;   // letters for A user: A - up, Z - down, space - skip an action
    char letter_B;   // letters for B user: K - up, M - down, space - skip an action
    char skipping_letter;

    // initialization by start data: ball and racket positions
    int x_ball = 10;    // we set the coordinates outswelves
    int y_ball = 5;
    int x_racket_A = 4;
    int y_start_racket_A = height / 2;
    int x_racket_B = width - 5;
    int y_start_racket_B = height / 2;
    int vector_x = -1;
    int vector_y = -1;

    func_table(height, width, x_ball, y_ball, x_racket_A, x_racket_B, y_start_racket_A,
               y_start_racket_B, count_A, count_B);     // start picture

    while (count_A < 21 && count_B < 21) {
        printf("Player 1, you can move: A/Z. Player 2, you can move: K/M\n");
        scanf("%c%c%c", &letter_A, &letter_B, &skipping_letter);
        while ((letter_A != 'A' && letter_A != 'Z' && letter_A != 'a' &&
        letter_A != 'z' && letter_A != ' ') || (letter_B != 'K' && letter_B != 'M' &&
        letter_B != 'k' && letter_B != 'm' && letter_B != ' ')) {
            printf("One miss turn. Again, Player 1, you can move: A/Z. Player 2, you can move: K/M\n");
            scanf("%c%c%c", &letter_A, &letter_B, &skipping_letter);
        }
        // change rackets coordinates
        y_start_racket_A = change_coor_y_racketA(y_start_racket_A, letter_A, height);
        y_start_racket_B = change_coor_y_racketB(y_start_racket_B, letter_B, height);
        if (y_ball == 1 || y_ball == height - 2) {    // change ball coordinates
            vector_y = vector_y * (-1);
        }
        if (x_ball == width - 1) {
            vector_x = vector_x * (-1);
            count_B = count_B + 1;
        }
        if (x_ball == 0) {
            vector_x = vector_x * (-1);
            count_A =  count_A + 1;
        }
        if (x_ball == x_racket_A + 1 && (y_ball == y_start_racket_A ||
        y_ball == y_start_racket_A + 1 || y_ball == y_start_racket_A + 2)) {
            vector_x = -vector_x;
        }
        if (x_ball == x_racket_B - 1 && (y_ball == y_start_racket_B ||
        y_ball == y_start_racket_B + 1 || y_ball == y_start_racket_B + 2)) {
            vector_x = -vector_x;
        }
        x_ball = x_ball + vector_x;
        y_ball = y_ball + vector_y;
        func_table(height, width, x_ball, y_ball, x_racket_A, x_racket_B,
                   y_start_racket_A, y_start_racket_B, count_A, count_B);    // print updated picture
    }
    check_win(count_A);
}

int change_coor_y_racketA(int y_start_racket_A, char letter_A, int height) {
    if (letter_A == 'A' || letter_A == 'a') {    // move from OY is opposite, because OY starts from top!!!!
        y_start_racket_A = y_start_racket_A - 1;
    } else if (letter_A == 'Z' || letter_A == 'z') {
        y_start_racket_A = y_start_racket_A + 1;
    }
    if (y_start_racket_A < 2) {
        y_start_racket_A = 1;
    }
    if (y_start_racket_A >= height - 4) {
        y_start_racket_A = height - 4;
    }
    return y_start_racket_A;
}

int change_coor_y_racketB(int y_start_racket_B, char letter_B, int height) {
    // change y to B
    if (letter_B == 'K' || letter_B == 'k') {
        y_start_racket_B = y_start_racket_B - 1;
    } else if (letter_B == 'M' || letter_B == 'm') {
        y_start_racket_B = y_start_racket_B + 1;
    }
    if (y_start_racket_B < 2) {
        y_start_racket_B = 1;
    }
    if (y_start_racket_B >= height - 4) {
        y_start_racket_B = height - 4;
    }
    return y_start_racket_B;
}

void func_table(int height, int width, int x_ball, int y_ball, int x_racket_A,
                int x_racket_B, int y_start_racket_A, int y_start_racket_B, int count_A, int count_B) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == x_ball && y == y_ball) {    // print ball
                printf("*");
            } else if (x == x_racket_A && (y == y_start_racket_A || (y == y_start_racket_A + 1) ||
            (y == y_start_racket_A + 2))) {    // print left racket
                printf("|");
            } else if (x == x_racket_B && (y == y_start_racket_B || (y == y_start_racket_B + 1) ||
            (y == y_start_racket_B + 2))) {    // print right racket
                printf("|");
            } else if (y == 4 && x == width / 2 - 4) {     // print counter for user A
                printf("%d", count_A);
            } else if (y == 4 && x == width / 2 + 4) {    // print counter for user B
                printf("%d", count_B);
            } else if (y == 0 || y == height - 1) {       // print table
                printf("-");
            } else if (x == 0 || x == width / 2 || x == width - 1) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void check_win(int count_A) {
    // check for win
    if (count_A == 21) {
        printf("Player 2, congratulations, you win!");
    } else {
        printf("Player 1, congratulations, you win!");
    }
}
