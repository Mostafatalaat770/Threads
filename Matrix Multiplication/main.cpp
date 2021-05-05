#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <ctime>

using namespace std;
using namespace std::chrono;

void multiplyElement(vector <vector<vector<int> > >  arrays, vector<vector<int> > &output, int i, int j)
{
    int result = 0;
    for(int x = 0; x < arrays[1].size() ; x++)
    {
        result += arrays[0][i][x] * arrays[1][x][j];
    }
    output[i][j] = result;
}
void multiplyRow(vector <vector<vector<int> > >  arrays, vector<vector<int> > &output, int i)
{
    int result = 0;
    for(int y = 0; y < arrays[1].size(); y++)
    {
        result = 0;
        for(int x = 0; x < arrays[1].size() ; x++)
        {
            result += arrays[0][i][x] * arrays[1][x][y];
        }
        output[i][y] = result;
    }
}
void writeOutput(vector<vector<int> > array, double timeTaken1, double timeTaken2)
{
    FILE *output = fopen("output.txt", "w");
    for(int n = 0; n < 2; n++)
    {

        for(int i = 0; i < array.size(); i++)
        {
            for(int j = 0; j < array[0].size(); j++)
            {
                fprintf(output, "%d ",array[i][j]);
            }
            fprintf(output,"\n");
        }
        double time;
        time = n == 0 ? timeTaken1 : timeTaken2;
        fprintf(output, "%s\tTime elapsed: %f\n", n == 0 ? "END1" : "END2", time);
    }
}
vector <vector<vector<int> > > readArrays()
{
    FILE *input = fopen("input.txt", "r");
    int currentArray = 0;
    vector <vector<vector<int> > > arrays(2);
    int i = 0,j = 0;
    while(!feof(input))
    {
        fscanf(input,"%d %d", &i,&j);
        arrays[currentArray].resize(i);

        for(int x = 0; x < i; x++)
        {

            for(int y = 0; y < j; y++)
            {
                int number;
                fscanf(input, "%d", &number);
                arrays[currentArray][x].push_back(number);
            }
            fscanf(input,"\n");
        }
        currentArray++;
    }
    fclose(input);
    return arrays;

}

int main()
{
    struct timespec start, finish;
    vector <vector<vector<int> > > arrays = readArrays();
    vector <vector<int> > output(arrays[0].size(), vector<int>(arrays[1][0].size()));

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i = 0; i < output.size(); i++)
    {
        for(int j = 0; j < output[i].size(); j++)
        {
            thread th(multiplyElement,arrays, ref(output), i, j);
            th.join();
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double time_taken1 = finish.tv_sec - start.tv_sec;
    time_taken1 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "time element: " << time_taken1 << " - ";

    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i = 0; i < output.size(); i++)
    {
        thread th(multiplyRow,arrays, ref(output), i);
        th.join();

    }


    clock_gettime(CLOCK_MONOTONIC, &finish);
    double time_taken2 = finish.tv_sec - start.tv_sec;
    time_taken2 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    cout << "time row: " << time_taken2<< endl;

    for(int j = 0; j < output.size(); j++)
    {
        for(int k = 0; k < output[j].size(); k++)
        {
            cout << output[j][k] << " ";
        }
        cout << endl;
    }
    writeOutput(output,time_taken1,time_taken2);

    return 0;
}
