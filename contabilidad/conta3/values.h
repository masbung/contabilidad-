//Counter to identify the number of journals made
int jou_count = 0;

//add_acc
int lastid;
int *plastid = &lastid;

//load_all_acc
int num_accounts2;

//Journal, print_current_jou, save_jou 
int fa = 0;
//print_current_jou
int fb = 0;

//load_all_led
// k = getc, nl = new line, nc = new character, elt = espace/line/tab, ast = number of asterisks, num_accounts = total of accounts
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
int k,nl, nw, nc, elt, ast, num_accounts, state;
int aa, ab, ac, ad, ae, af, ag;
int arr1[30][30],csum[30];
int stop, stop2;
int countArray[1][50];
int countArray2[1][50];

//print_led
int ba, bb, bc, bd;

//save_current_jou
int da = 0;
char response2[3] = "no";

//journal
int ea=0, ed=0, ee=0, ef;
char comment[30];
int sourceArray[1][40]; //Account number 
int amountArray[40][2]; //Amount of move in journal