# define p1 0
# define p2 1

int turn = 0;
int flag[2] = {0, 0};


void peterson(int p) {
    while (1) {
        flag[p] = 1;
        turn = p;
        int other = 1 - p;
        //Entry Section
        while (flag[other] == 0 && turn == p){
            //Critical Section
        printf("Process %d is in the critical section.\n", p);
           //exit Section
        turn = other;
        flag[p] = 0;
        }
        break;
    }
}

int main() {
    peterson(p1);
    peterson(p2);
    return 0;
}