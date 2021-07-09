#include <iostream>
#include <fstream>
#include <string>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>

using namespace std;
using namespace boost::random;

mt19937 generator;

int random_uniform_int_generator(){
    boost::random::uniform_int_distribution<int> distribution(1, 20); // 1-20 interval
    return distribution(generator);
}

double random_exponential_generator(){
    boost::random::exponential_distribution<> distribution(3.5); // I don't know it is 3.5
    return distribution(generator);
}

int random_poisson_generator(){
    boost::random::poisson_distribution<int> distribution(5); // mean = 5
    return distribution(generator);
}

void display(string file_name){
    ifstream read_the_file(file_name);
    string line;
    while (getline(read_the_file, line))
        cout << line << endl;
    read_the_file.close();
}

int *howmany(string fileName){
    int number;
    ifstream read_the_file(fileName); // open for reading

    string line;
    int *statics_array = (int *) calloc(21, sizeof(int));
    while (getline(read_the_file, line)){ // read to file line by line
        number = stoi(line); // string to integer cast
        statics_array[number] = statics_array[number] + 1; // increase the elements that we have
    }
    read_the_file.close();
    return statics_array;
}

//fileName is the reading file
//outputName is the writing file
void writestat(string fileName,string outputName){
    int *a = howmany(fileName);
    ofstream write_file1(outputName);
    for (int i = 0; i < 21; i++)
        write_file1 << i << "\t" << a[i] << endl;
    write_file1.close(); // Once the loop is finished, writing process will finish.
    free(a);
}

int main(){
    ofstream write_file("random_int.txt"); // write to file
    for (int i = 0; i < 1000; i++)
        write_file << random_uniform_int_generator() << endl;
    write_file.close();
    //display("random_int.txt");
    writestat("random_int.txt", "howmany_int.dat");

    ofstream write_file1("random_exponential.txt");
    for (int i = 0; i < 2; i++)
        write_file1 << random_exponential_generator() << endl;
    write_file1.close();
    //display("random_exponential.txt");

    ofstream write_file2("random_poisson.txt");
    for (int i = 0; i < 1000; i++)
        write_file2 << random_poisson_generator() << endl;
    write_file2.close();
    writestat("random_poisson.txt", "howmany_poisson.dat");
    //display("random_poisson.txt");

   return 0;
}
