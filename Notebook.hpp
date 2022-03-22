#include <iostream>
#include <climits>
#include "Direction.hpp"


namespace ariel
{
    class Notebook{
        private:
        int pages;
        int rows;
        int col;

        public:
        Notebook(){
            pages = INT_MAX;
            rows = INT_MAX;
            col = 100;
        }

        void write(int page, int row, int column, Direction,std::string txt);
        std::string read(int page, int row, int column,Direction,int length);
        void erase(int page, int row, int column,Direction,int length);
        void show(int page);

    };
}

