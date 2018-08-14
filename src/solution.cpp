#define NULL 0

const int DIR_UP     = 0;
const int DIR_DOWN   = 1;
const int DIR_LEFT   = 2;
const int DIR_RIGHT  = 3;

const int MAX_N = 700;


class Char {
public:
    Char* prev;
    Char* next;
    char element;

    Char() {
        prev = NULL;
        next = NULL;
        element = '\0';
    }

    Char(char c) {
        prev = NULL;
        next = NULL;
        element = c;
    }
};

class Line {
public:
    Line* prev;
    Line* next;
    Char* firstChar;
    Char* lastChar;
    int length;

    Line() {
        prev = NULL;
        next = NULL;
        firstChar = new Char();
        lastChar = firstChar;
        length = 1;
    }

    Line(Char* firstChar_, Char* lastChar_, int length_) {
        prev = NULL;
        next = NULL;
        firstChar = firstChar_;
        lastChar = lastChar_;
        length = length_;
    }

    ~Line() {
        Char* c = firstChar;
        while (c != NULL) {
            Char* nextC = c->next;
            delete c;
            c = nextC;
        }
    }

    Char* getChar(int col) {
        Char* c = firstChar;
        for (int i = 1; i < col; i++) {
            c = c->next;
        }
        return c;
    }
};


Line* firstLine = NULL;

Line* getLine(int row) {
    Line* line = firstLine;
    for (int i = 1; i < row; i++) {
        line = line->next;
    }
    return line;
}


class Cursor {
public:
    Line* currLine;
    Char* currChar;
    int currRow;
    int currCol;


    void init(Line* firstLine_) {
        currLine = firstLine_;
        currChar = currLine->firstChar;
        currRow = 1;
        currCol = 1;
    }

    void inputChar(char inChar) {
        Char* prevChar = currChar->prev;
        Char* nextChar = currChar;

        // 새 문자 생성
        Char* newChar = new Char(inChar);

        // 문자 간 연결
        if (prevChar == NULL) {
            currLine->firstChar = newChar;
        }
        else {
            prevChar->next = newChar;
            newChar->prev = prevChar;
        }
        newChar->next = nextChar;
        nextChar->prev = newChar;

        // 라인 정보 갱신
        currLine->length += 1;

        // 커서 갱신
        currCol += 1;
        currChar = nextChar;
    }

    void inputNewLine() {
        inputChar('\n');

        Char* newLine_firstChar = currChar;
        Char* newLine_lastChar = currLine->lastChar;
        int newLine_length = currLine->length - currCol + 1;

        // 현재 라인 자르기
        currLine->lastChar = currChar->prev;
        currLine->lastChar->next = NULL;
        currLine->length = currCol - 1;

        // 새 라인 생성
        Line* newLine = new Line(newLine_firstChar, newLine_lastChar, newLine_length);
        newLine->firstChar->prev = NULL;

        // 라인 간 연결
        Line* prevLine = currLine;
        Line* nextLine = currLine->next;
        newLine->prev = prevLine;
        prevLine->next = newLine;
        if (nextLine != NULL) {
            newLine->next = nextLine;
            nextLine->prev = newLine;
        }

        // 커서 갱신
        currLine = newLine;
        currChar = newLine->firstChar;
        currRow += 1;
        currCol = 1;
    }

    void move(int direction) {
        switch (direction) {
        case DIR_UP:
            if (currLine->prev == NULL) {
                return;
            }
            currLine = currLine->prev;
            currRow -= 1;

            if (currCol > currLine->length) {
                currCol = currLine->length;
                currChar = currLine->lastChar;
            }
            else {
                currChar = currLine->getChar(currCol);
            }
            break;

        case DIR_DOWN:
            if (currLine->next == NULL) {
                return;
            }
            currLine = currLine->next;
            currRow += 1;

            if (currCol > currLine->length) {
                currCol = currLine->length;
                currChar = currLine->lastChar;
            }
            else {
                currChar = currLine->getChar(currCol);
            }
            break;

        case DIR_LEFT:
            if (currCol > 1) {
                currCol -= 1;
                currChar = currChar->prev;
                return;
            }

            if (currLine->prev == NULL) {
                return;
            }

            currLine = currLine->prev;
            currRow -= 1;
            currCol = currLine->length;
            currChar = currLine->lastChar;
            break;

        case DIR_RIGHT:
            if (currCol < currLine->length) {
                currCol += 1;
                currChar = currChar->next;
                return;
            }

            if (currLine->next == NULL) {
                return;
            }

            currLine = currLine->next;
            currRow += 1;
            currCol = 1;
            currChar = currLine->firstChar;
            break;
        }
    }
};


Cursor cursor;


void clear() {
    Line* line = firstLine;
    while (line != NULL) {
        Line* nextLine = line->next;
        delete line;
        line = nextLine;
    }

    firstLine = new Line();
}


void init(int n) {
    clear();
    cursor.init(firstLine);
}

void input_char(char in_char) {
    cursor.inputChar(in_char);
}

void input_newline() {
    cursor.inputNewLine();
}

void move_cursor(int direction) {
    cursor.move(direction);
}

char get_char(int row, int column) {
    Line* line = getLine(row);
    Char* c = line->getChar(column);
    return c->element;
}
