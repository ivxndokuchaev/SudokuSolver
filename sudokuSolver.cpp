#include <iostream>

struct Array {
    int array[9][9] = {
        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
        { 0, 0, 0, 0, 8, 0, 0, 7, 9 },
    };
};

class Board {
    private:
        int m_board[9][9];
        int m_length;
        Array m_sfield;

        bool containsInASquare(int array[9][9], int a, int y, int x) {
            if (x < 3 && y < 3) {
                for (int i=0; i<3; ++i) {
                    for (int k=0; k<3; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 2 && x < 6 && y < 3) {
                for (int i=3; i<6; ++i) {
                    for (int k=0; k<3; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 5 && y < 3) {
                for (int i=6; i<9; ++i) {
                    for (int k=0; k<3; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x < 3 && y > 2 && y < 6) {
                for (int i=0; i<3; ++i) {
                    for (int k=3; k<6; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 2 && x < 6 && y > 2 && y < 6) {
                for (int i=3; i<6; ++i) {
                    for (int k=3; k<6; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 5 && y > 2 && y < 6) {
                for (int i=6; i<9; ++i) {
                    for (int k=3; k<6; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x < 3 && y > 5) {
                for (int i=0; i<3; ++i) {
                    for (int k=6; k<9; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 2 && x < 6 && y > 5) {
                for (int i=3; i<6; ++i) {
                    for (int k=6; k<9; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            } else if (x > 5 && y > 5) {
                for (int i=6; i<9; ++i) {
                    for (int k=6; k<9; ++k) {
                        if (array[k][i] == a) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

    bool containsInRow(int array[9][9], int a, int row) {
        for (int i=0; i<9; ++i) {
            if (array[row][i] == a) {
                return true;
            }
        }
        return false;
    }

    bool containsInColumn(int array[9][9], int a, int col) {
        for (int i=0; i<9; ++i) {
            if (array[i][col] == a) {
                return true;
            }
        }
        return false;
    }

    bool canPutElement(int array[9][9], int a, int x, int y) {
        if (array[x][y] != 0) {
            return false;
        } else if (containsInRow(array, a, x) || containsInColumn(array, a, y)) {
            return false;
        } else if (containsInASquare(array, a, x, y)) {
            return false;
        }
        return true;
    }

    void initialize() {
        for (int x=0; x<m_length; ++x) {
            for (int y=0; y<m_length; ++y) {
                m_board[x][y] = m_sfield.array[x][y];
            }
        }
    }

    bool unassignedLocation(int board[9][9], int& row, int& col) {
        for (int x=0; x<9; ++x) {
            for (int y=0; y<9; ++y) {
                if (board[x][y] == 0) {
                    row = x;
                    col = y;
                    return true;
                }
            }
        }
        return false;
    }

    public:
        Board() { 
            m_length = 9; 
            initialize();
        }

        bool solve() {
            int row, col;

            if (!unassignedLocation(m_board, row, col)) {
                return true;
            }
            

            for (int num=1; num<=9; ++num) {
                if (canPutElement(m_board, num, row, col)) {
                    m_board[row][col] = num;

                    if (solve()) {
                        return true;
                    }

                    m_board[row][col] = 0;
                }

            }

            return false;
        }

        void print() {
            for (int x=0; x<m_length; ++x) {
                for (int y=0; y<m_length; ++y) {
                    std::cout << m_board[x][y] << " ";
                }
                std::cout << '\n';
            }
        }

};

int main() {
    using namespace std;

    Board board;

    cout << "---INITIAL BOARD:\n";
    board.print();
    cout << "\n\n";

    cout << "----SOLVED BOARD:\n";
    board.solve();
    board.print();

    return 0;
}