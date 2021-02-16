int calculate(int con, int aligned, bool isCurr, bool emptyFound = false){
    if(aligned == 2 && con < 5){
        return 0;
    }
    
    else{
        if(con >= 5){
            if(emptyFound){
                return 8000;
            }
            return 100000;
        }
        vector<int> conScore {2, 5, 1000, 10000};
        vector<double> blockCountScore {0.5, 0.6, 0.01, 0.25};
        vector<double> notCurrScore {1, 1, 0.2, 0.15};
        vector<double> emptySpaceScore {1, 1.2, 0.9, 0.4};
        
        int conID = con-1;
        double value = conScore[conID];
        if(aligned == 1){
            value *= blockCountScore[conID];
        }
        if (!isCurr){
            value *= notCurrScore[conID];
        }
        if (emptyFound){
            value *= emptySpaceScore[conID];
        }
        int ret_val = value;
        return ret_val;
    }
}
