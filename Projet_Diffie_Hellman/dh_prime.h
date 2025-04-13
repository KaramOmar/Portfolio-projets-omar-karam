#define MAX_PRIME 4294967296/1000 // 2^32 = sqrt(2^64)
#define MIN_PRIME 100

long random_long(long min,long max);
int rabin (long a, long n) ;
long puissance_mod_n (long a, long e, long n);
void xor(char *msg, char* key,int msg_length,char *crypted);
long generePremierRabin(long min,long max,int *cpt);
long seek_generator(long start,long p);
int nb_digit_base10(long n);
void generate_shared_key(long min,long max);
long genPrimeSophieGermain(long min,long max,int *cpt);
//long xchange_shared_key(long generateur, long premier);
long int_pow(long a, long e);
