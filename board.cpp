#include<vector>
#include<map>
#include<algorithm>
using namespace std;
enum Piece{
    black=1,
    white=-1,
    empty=0    
};

map<Piece,char> symbols{make_pair(black,'X'),make_pair(white,'O'),make_pair(empty,'.')};


bool issub(vector<int> l,vector<int> subl){
    int l_size = l.size();
    int subl_size = subl.size();
    for (int i = 0; i < l_size - subl_size;++i){
        vector<int> curr(l.begin()+i, l.begin() + min(i+subl_size, l_size-1));
        bool  res = true;
        for(int i = 0; i < curr.size();i++)
            {
                if(curr[i]!=subl[i])
                    res = false;
            }
        if(res == true)
            return true;
    }
    return false;

}

bool is_valid_position(int board_size,pair<int,int> pos){
    int i = pos.first;
    int j = pos.second;
    return i>=0 && i<board_size && j>=0 && j<board_size;
}

vector<int> expand_area(int size, vector<int> idxs){
    vector<int> area_idxs(idxs);
    for(int i = 0;i < size;++i){
        for(int j = 0; j < size; ++j){
            if (!idxs[i,j])
                continue;
            vector<int> direction[4] ={{1,0},{0,1},{1,1},{1,-1}};
            for(int k = 0; k < 4;++k){
                int di = direction[k][0];
                int dj = direction[k][1];
                vector<int> side{1,-1};
                for(auto s:side){
                    int ni = i + di*s;
                    int nj = j + dj*s;
                    if (!is_valid_position(size,{ni,nj}))
                        continue;
                    area_idxs[ni,nj] = true;

                }
            }
        }
    }
    vector<int> res;
    for (size_t i = 0; i < area_idxs.size(); i++)
    {
        res.push_back(area_idxs[i]^idxs[i]);
    }
    

}




class BoardState{

    private:
        vector<vector<int>> values;
        int size;
        Piece color;
        int last_move;
        int winner;
    public:
        BoardState(){

        }
        BoardState(int size,vector<vector<int>> values = {},Piece color = white){
            if (!values.empty())
                this->values = values;
            else {
                for (size_t i = 0; i < size; i++)
                {
                    vector<int> row;
                    for (size_t i = 0; i < size; i++)
                    {
                        row.push_back (empty);
                    }
                    
                    this->values.push_back(row);
                }
                
            }
            this->size =size;
            this->color = color;
            this->last_move = 0;
            this->winner = 0;
        }

        vector<int> value(int pos){
            return this->values[pos];
        }

        bool is_valid_position(int pos){
            return this->values[pos].empty(); 
        }

        vector<int> legal_moves(){
            vector<int> prev_move_idxs;
            for (size_t i = 0; i < size; i++)
            {
                bool res = true;
                for(int j = 0; j < size;++j)
                    if(this->values[i][j]==empty)
                        res = false;
                if(!res)
                    prev_move_idxs.push_back(i);
            }
            vector<int> area_idxs =  expand_area(this->size,prev_move_idxs);

            
        }

        BoardState next(int pos){
            BoardState next_state = BoardState(this->size,this->values,
            this->color);
            next_state.last_move = pos;
            return next_state;
        }

        bool is_terminal(){
            pair<bool,Piece> res = check_five_in_a_row();
            bool is_win = res.first;
            Piece color = res.second;
            bool is_full = this->is_full();
            if (is_full)
                return true;
            return is_win;
        }

        pair<bool,Piece> check_five_in_a_row(){
            vector<int> pattern{1,1,1,1,1};
            for_each(pattern.begin(),pattern.end(),[](int &a){a*=black;});
            int black_win = check_pattern(pattern);
            for_each(pattern.begin(),pattern.end(),[](int &a){ a/=black;a*=white;});
            int white_win =  check_pattern(pattern);
            
            if (black_win){
                this->winner = black;
                return make_pair(true,black);
            }
            if (white_win){
                this->winner = white;
                return make_pair(true,white);
            }
            return make_pair(false,empty);
        }

        bool is_full(){
            bool res = false;
            for (int i = 0; i < size; i++)
            {
                if(values[i].empty())
                    res = true;
            }
            return !res;
        }

        int check_pattern(vector<int> pattern){
            int cnt = 0;
            auto lines = this->get_lines();
            for(auto line:lines){
                if (issub(line,pattern))
                    cnt++;
            }
            return cnt;
        }

        vector<vector<int>> get_lines(){
            vector<vector<int>> l;
            for(int  i = 0 ; i < size; ++i){
                l.push_back(vector<int>(values.begin()+i,values.end()));
                l.push_back(vector<int>(values.begin(),values.begin()+i));
            }

            for(int i = -size+5;i<size-4;++i){
                vector<int> v;
                for(int j = 0;j<size;++j){
                    v.push_back(values[j][j+i]);
                }
                for(int j = 0;j<size;++j){
                    v.push_back(values[size-j][j+i]);
                }

            }
            return l;
        }

};