long int align_eval(vector<int> line, int color, bool curr){
    int evaluated = 0;
    int size = line.size();
    int con = 0;
    int aligned = 2;
    bool isEmpty = false;
    for(int i = 0; i < line.size(); i++){
        int value = line[i];
        if(value == color){
            con += 1;
        }
        else if (value == EMPTY and con > 0){
            if (!isEmpty && i < size-1 && line[i+1] == color){
                isEmpty = true;
            }
            else{
                evaluated += calculate(con, aligned-1, curr, isEmpty);
                con = 0;
                aligned = 1;
                isEmpty = false;
            }
        }
        
        else if (value == EMPTY){
            aligned = 1;
        }
        else if (con > 0){
            evaluated += calculate(con, aligned, curr);
            con = 0;
            aligned = 2;
        }
        else{
            aligned = 2;
        }
    }
    if (con>0){
        evaluated += calculate(con, aligned, curr);
    }
    return evaluated;
}
