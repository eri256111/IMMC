#include <bits/stdc++.h>
using namespace std;

const int N = 3, M = 12;

const double error = 0.0001;

class Weight{
private:
    const double DOUBLE_MIN = -1e9,
                 DOUBLE_MAX = 1e9;
                 
    double x[N][M], Max[M], Min[M], Sum[M], p[N][M],
           e[M], d[M], sum_d, w[M];
public:
    void Input(){
        ifstream infile;
        infile.open("C:/Users/user/Desktop/IMMC_Weight/Data.txt", ios::in);
        assert(infile);
        for(int i = 0 ; i < N ; i++){
            for(int j = 0 ; j < M ; j++){
                infile >> x[i][j];
            }
        }
        infile.close();
    }
    void Output(){
        ofstream outfile;
        outfile.open("C:/Users/user/Desktop/IMMC_Weight/Weight.txt", ios::out);
        assert(outfile);
        for(int j = 0 ; j < M ; j++){
            outfile << w[j] << ' ';
        }
        outfile.close();
    }
    void Normalization(){
        fill(Max, Max + M, DOUBLE_MIN);
        fill(Min, Min + M, DOUBLE_MAX);
        for(int j = 0 ; j < M ; j++){
            for(int i = 0 ; i < N ; i++){
                Max[j] = max(Max[j], x[i][j]);
                Min[j] = min(Min[j], x[i][j]);
            }
        }
        for(int j = 0 ; j < M ; j++){
            Sum[j] = 0;
            for(int i = 0 ; i < N ; i++){
                x[i][j] = (x[i][j] - Min[j]) / (Max[j] - Min[j]);
                Sum[j] += x[i][j];
            }
        }
    }
    void check_0(){
        for(int j = 0 ; j < M ; j++){
            for(int i = 0 ; i < N ; i++){
                if(x[i][j] > (-1) * error and x[i][j] < error){
                    for(int k = 0 ; k < N ; k++){
                        x[k][j] += 1;
                        Sum[j] += N;
                    }
                    continue;
                }
            }
        }
    }
    void Proportion(){
        for(int j = 0 ; j < M ; j++){
            for(int i = 0 ; i < N ; i++){
                p[i][j] = x[i][j] / Sum[j];
            }
        }
    }
    void Entropy(){
        double k = 1 / log(N);
        for(int j = 0 ; j < M ; j++){
            double tmp = 0;
            for(int i = 0 ; i < N ; i++){
                tmp += p[i][j] * log(p[i][j]);
            }
            e[j] = (-1) * k * tmp;
        }
    }
    void Redundancy(){
        sum_d = 0;
        for(int j = 0 ; j < M ; j++){
            d[j] = 1 - e[j];
            sum_d += d[j];
        }
    }
    void _Weight(){
        for(int j = 0 ; j < M ; j++){
            w[j] = d[j] / sum_d;
        }
    }
};

int main(){
    Weight weight;
    weight.Input();
    weight.Normalization();
    weight.check_0();
    weight.Proportion();
    weight.Entropy();
    weight.Redundancy();
    weight._Weight();
    weight.Output();
    return 0;
}