#include "Bank.h"
#include <pthread.h>
pthread_mutex_t lock;
TransferThreadParameters *TransferThreadParameters_new(Bank *b, int fromAccount, int maxAmount) {
    TransferThreadParameters *param = (TransferThreadParameters *)malloc(sizeof(TransferThreadParameters));
    param->b = b;
    param->fromAccount = fromAccount;
    param->maxAmount = maxAmount;

    return param;
}

void *transfer_thread(void *vargp) {
    TransferThreadParameters *param = (TransferThreadParameters *)vargp;
    Bank *b = param->b;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int fromAccount = param->fromAccount;
    int maxAmount = param->maxAmount;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }
    free(param);
    //For 1000 iterations
    int i = 0;
   
    for(i = 0; i < 10000; ++i) {
        
        //Put money to random account in the bank
        int toAccount = (int)(rand() % b->numAccounts);
        //Put random amount into the random account
        int amount = (int)(rand() % maxAmount);
        //Transfer the funds
        pthread_mutex_lock(&lock);
        Bank_transfer(b, fromAccount, toAccount, amount);
        pthread_mutex_unlock(&lock);
    }
    
    printf("Account[%d] is done.\n", fromAccount);
}
