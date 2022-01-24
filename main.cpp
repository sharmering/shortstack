#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <streambuf>
#include <memory>
#include <atomic>
#include <ctime>
#include <ratio>
#include <functional>


#include "AIGCJson/AIGCJson.hpp"
#include "JsonFileModel.h"
#include "picojson.h"
#include "MySerialDAQ.h"
#include "MyDatabase.h"

using namespace std;
using namespace aigc;


void f2(int n)
{
    for(int i=0;i< 10; i++)
    {
        cout<< "Thread of " << n << "executing" <<endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main()
{
    cout << "Welcome to ZTDQ ZT643!" << endl;
/*
    //test thread usage
    thread t1(f2, 5);
    thread t2(f2, 10);
    t1.join();
    t2.join();
*/
/*
    //Json serialization
    MainConf mainConf;
    mainConf.name = "new station";
    mainConf.masterSerialPorts.push_back(1);
    mainConf.masterSerialPorts.push_back(2);
    string strMainConf;
    //Json Object to string
    JsonHelper::ObjectToJson(mainConf, strMainConf);
    ofstream outFile("device.json");
    outFile << strMainConf << endl;
    outFile.close();
    //string to Json Object
    mainConf.name = "old station";
    JsonHelper::ObjectToJson(mainConf, strMainConf);
    cout << strMainConf << endl;
*/
    std::map<int, MySerialDAQ*> mapMasterSerialPort;
    MySerialDAQ* masterSerialPortObj[4];
    thread masterSerialPortThread[4];
    MainConf conf;
    string strMainConfFile = "device.json";
    if(MySerialDAQ::conf_file_exist(strMainConfFile))
    {
        ifstream fileStream(strMainConfFile);
        string strJson((istreambuf_iterator<char>(fileStream)),
                       istreambuf_iterator<char>());
        strJson.erase(remove(strJson.begin(), strJson.end(), '\t'));
        strJson.erase(remove(strJson.begin(), strJson.end(), '\r'));

        if(JsonHelper::JsonToObject(conf, strJson))
        {
            for(size_t i = 0; i < conf.masterSerialPorts.size(); i++)
            {
                masterSerialPortObj[i] = new MySerialDAQ(conf.masterSerialPorts[i]);
                masterSerialPortThread[i] = masterSerialPortObj[i]->thread_start();
                mapMasterSerialPort.insert(pair<int, MySerialDAQ*>(conf.masterSerialPorts[i], masterSerialPortObj[i]));
            }
        }
    }
    else
    {
        cout << "device.json file doesn't exist! Program aborts." << endl;
    }

    //wait for master collection thread to finish
    for(size_t i = 0; i < conf.masterSerialPorts.size(); i++)
    {
        masterSerialPortThread[i].join();
    }

    //to end the program
    int i =0;
    cin >> i;
    return 0;
}
