#include <iostream>
using namespace std;

enum COMMAND {
	CMD_MOVE_UP = 0,
	CMD_MOVE_DOWN = 1,
	CMD_MOVE_LEFT = 2,
	CMD_MOVE_RIGHT = 3,
	CMD_INPUT_CHAR = 4,
	CMD_INPUT_NEWLINE = 5,
	CMD_GET_CHAR = 6,
	CMD_END_TC = 9
};

extern void init(int n);
extern void input_char(char in_char);
extern void input_newline();
extern void move_cursor(int direction); // 0: Up, 1: Down, 2: Left, 3: Right
extern char get_char(int row, int column);

static const int FACTOR = 14;
static const int CNT_CANDI = 53;
static char char_candidate[CNT_CANDI];

static int mSeed;
static int mrand(int num)
{
	mSeed = mSeed * 1103515245 + 37209;
	if (mSeed < 0) mSeed *= -1;
	return ((mSeed >> 8) % num);
}

static void make_candidate(){
	int idx = 0;
	for(int i = 'a'; i <= 'z'; ++i) char_candidate[idx++] = i;
	for(int i = 'A'; i <= 'Z'; ++i) char_candidate[idx++] = i;
	char_candidate[idx] = '.';
}

static void make_dummy(int n){
	int dummySize = n * 8 / 10;
	for(int i = 0; i < dummySize; ++i){
		for(int j = 0; j < dummySize; ++j){
			char ch = char_candidate[mrand(CNT_CANDI)];
			input_char(ch);
			move_cursor(CMD_MOVE_LEFT);
		}
		input_newline();
		move_cursor(CMD_MOVE_UP);
	}
}

static int run(){
	int cmd = 0;
	int get_total = 0;
	int get_correct = 0;
    char ch, user_ch;
    
	while(1){
		cin >> cmd;
		if(cmd == CMD_END_TC) break;
		else if(cmd == CMD_INPUT_CHAR){	
			cin >> ch;
			input_char(ch);
		}
		else if(cmd == CMD_INPUT_NEWLINE){
			input_newline();
		}
		else if(cmd == CMD_GET_CHAR){
			int row, col;
			cin >> row >> col >> ch;
			user_ch = get_char(row, col);
			++get_total;
			if(user_ch >= '.' && user_ch <= 'z' && ch == user_ch) ++get_correct;			
		}
		else{
			move_cursor(cmd); 
		}
		cmd = 0;
	}
	return get_correct * 1000 / get_total;
}

int main(){	
	std::ios::sync_with_stdio(false);

	//freopen("sample_input.txt", "r", stdin);
	
	make_candidate();
	int total_score = 0;
	int T;
	cin >> T;
	
	for(int tc = 1; tc <= T; ++tc){
		int N;
		cin >> N;
		init(N);
		if(tc > 4){
			cin >> mSeed;
			make_dummy(N);
		}
		int score = run();		
		cout << "#" << tc << " " << score << endl;
		total_score += score;
	}
	cout << "Total Score: " << total_score << endl;
	
	return 0;
}