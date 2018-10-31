#include <iostream>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>

/* Xhanti Singatha
* SNGXHA002 ML Lab 4
*/

using namespace std;
int count = 0;

vector<string> split_string(std::string str);
int perceptron(int x, int y, vector<double> weight);
vector<double> adjustWeights(string filename, vector<double> vecWeight);

vector<string> split_string(std::string str){
               int len = str.size();
               vector<string> data;
               
               std::string str1 = "";
               std::string item = "";
               
               int counter = 0;
               for (int i = 0; i < len; i++){
                    item = str.at(i);
                    if (item.compare(" ") == 0){
                       data.push_back(str1);
                       str1 = "";
                       counter++;
                    }
                   
                    else if (counter == 2){
                        data.push_back(str.substr(i,len));
                        break;
                    }
                   
                    else {
                        str1 += item;
                    }
                   
               }         
               
               return data;
               
}

int perceptron(int x, int y, vector<double> weight){
    double output =  (x * weight[1]) + (y * weight[2]);
    if (output > weight[0]){ // weight[0] is the threshold
       return 1;
    }
    
    else {
      return 0;
    }

}

vector<double> adjustWeights(string filename, vector<double> vecWeight){
               vector<double> temp;
               double learningRate = 0.2;
               double dxWeight, dyWeight, dweightZero;
               
               ifstream myfile;
               myfile.open(filename.c_str());
   
               string line = "";
               string x, y, t;
               if (myfile.is_open()){
                  while (!myfile.eof()){
                        getline(myfile, line);
                        
                        vector<string> input = split_string(line);
                       
                        x = input[0];
                        y = input[1];
                        t = input[2];
                       
                        int o = perceptron(atoi(x.c_str()), atoi(y.c_str()), vecWeight);
             
                        if (o != atoi(t.c_str())){
                            dxWeight = (learningRate)*(atoi(t.c_str()) - (o))*(atoi(x.c_str()));
                            dyWeight = (learningRate)*(atoi(t.c_str()) - (o))*(atoi(y.c_str()));
                            dweightZero = (learningRate)*(atoi(t.c_str()) - (o))*(atoi(x.c_str()));
                  
                            temp.push_back(vecWeight[0]+dweightZero);
                            temp.push_back(vecWeight[1]+dxWeight);
                            temp.push_back(vecWeight[2]+dyWeight);
                         }
             
                         else {
                            count++; // do nothing on weights
                         }
                   }
                   myfile.close();
                   
   
               }
   
               else {
                    cout << "Error opening file" << "\n";
               }
               temp.push_back(count);
               
               return temp;
}

int main(){ 

   cout << "Hello There !" << "\n"; 
   vector<double> weights = {2.5,3.0,2.0};
   
   while (count != 4){
         cout << "General Kenobi !" << "\n";
         vector<double> copy = adjustWeights("training_example.txt", weights);
         weights[0] = copy[0];
         weights[1] = copy[1];   
         weights[2] = copy[2];
 
    }
   
   cout << "W0 :" << weights[0] << "\n";
   cout << "x weight:" << weights[1] << "\n";
   cout << "y weight:" << weights[2] << "\n";
 
}