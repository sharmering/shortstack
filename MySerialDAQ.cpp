#include "MySerialDAQ.h"
#include "MyDatabase.h"

//This function is not used because of control strategy
thread usrSerialCollectStart(int port)
{
    /*
    //Modbus_RtuSerialPortConf conf;
    //conf.isEnabled = 1;
    //conf.portName = "asdfasd";
    //conf.speed = 115200;
    //conf.dataBits = 8;
    //conf.parity = "E";
    //conf.stopbBits = 1;
    //conf.collectPeriod = 5;
    //conf.portNum = 1;
    //RtuDevice device;
    //device.stationAddress = 1;
    //device.IsEnabled = 1;
    //device.DeviceName = "Iamgood";
    //conf.Devices.push_back(device);
    //string jsonStr = "";
    //JsonHelper::ObjectToJson(conf, jsonStr);
    //cout << jsonStr << endl;
    //ofstream out("Port1.json");
    //out << jsonStr << endl;
    //out.close();
    */

    MySerialDAQ* serial = new MySerialDAQ(port);
    if (serial == nullptr)
    {
        cout<< "initial MyserialDAQ fail" << endl;
        //return nullptr;
    }
    thread t1 = serial->thread_start();
    return t1;
}


MySerialDAQ::MySerialDAQ(int portNum)
{
    isCanceled = false;
    strJsonFileName = "Port" + to_string(portNum) + ".json";
    portnum = portNum;
    if (readConfFile() != -1)
    {
        cout << "read Port" << portNum << ".json file successfully, set serial port ok."
             << endl;
    }
    else
    {
        /*
        int rc = -1;
        ctx = modbus_new_rtu(strPort
            conf.baudrate,
            serialConf.parity,
            serialConf.dataBits,
            serialConf.stopBits);

        rc = modbus_connect(ctx);
        */
        cout << "Port" << portNum << ".json file doesn't exist." << endl;
    }
}

void MySerialDAQ::start()
{
    {
        struct timeval TmStart = { 0 }, TmEnd = { 0 };
        string strBuf;
        char buf[MAXBUF];
        bool bFileExist = conf_file_exist(strJsonFileName);
        bool commFlag[MAX_RTU_NUM_PER_SERIAL_PORT] = { true };
        int commTries[MAX_RTU_NUM_PER_SERIAL_PORT] = { 0 };
        while (isCanceled == false)
        {
            if (bFileExist == false)
            {
                bFileExist = conf_file_exist(strJsonFileName);
                if (bFileExist)
                {
                    //重新发现文件，加载配置
                    if (readConfFile() == -1)
                    {
                        cout << "read port configuration file fail." << endl;
                        bFileExist = false;
                        this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }
                    else
                    {
                        memset(commFlag, 0, sizeof(commFlag));
                        memset(commTries, 0, sizeof(commTries));
                    }
                }
                else
                {
                    this_thread::sleep_for(std::chrono::milliseconds(3000));
                }
            }
            if (bFileExist)
            {
                //start to collect
                cout << "thread of " << this_thread::get_id() << endl;
                gettimeofday(&TmStart, NULL);

                if(conf == NULL)
                {
                    if (readConfFile() == -1)
                    {
                        cout << "read port configuration file fail." << endl;
                        bFileExist = false;
                        this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }
                    else
                    {
                        memset(commFlag, 0, sizeof(commFlag));
                        memset(commTries, 0, sizeof(commTries));
                    }
                }
                //poll process
                for (size_t d = 0; d < conf.Devices.size(); d++)
                {
                    RtuDevice device = conf.Devices[d];
                    if (device.IsEnabled > 0)
                    {
                        if(device.collectPeriod == 0)
                            device.collectPeriod = 15;
                        if (TmEnd.tv_sec % device.collectPeriod == 0 && TmStart.tv_sec != TmEnd.tv_sec)
                        {
                            CDbService::DbEntry* entries = new
                            CDbService::DbEntry[device.vecCommands.size()];
                            for (size_t c = 0; c < device.vecCommands.size(); c++)
                            {
                                //assambly the command
                                ModbusCmdOut cmd = device.vecCommands[c];
                                int regNum = cmd.vecOutData[cmd.vecOutData.size() - 1].offset +
                                             get_length_by_datatype(cmd.functionCode,
                                                                    cmd.vecOutData[cmd.vecOutData.size() - 1].dataType);
                                strBuf = GetReadCommand(device.stationAddress, cmd.functionCode,
                                                        cmd.registerStartAddr, regNum);
                                //flush the recv buffer
                                tcflush(port_fd, TCIFLUSH);
                                int len = write(port_fd, strBuf.c_str(), (int)strBuf.size());
                                cout << "Tx: " << strBuf << endl;
                                if (len < 0)
                                {
                                    cout << "write data error: " << __LINE__ << endl;
                                }
                                len = readRev(buf);
                                //check validation of data
                                if (len > 0 && validate_return_data(
                                            device.stationAddress, cmd.functionCode, regNum, buf,len))
                                {
                                    //parse_return_data(buf, len);
                                    int count = cmd.vecOutData.size();
                                    for (int r = 0; r < count; r++)
                                    {
                                        ModbusDataParse* dp = &cmd.vecOutData[r];
                                        //遥信处理
                                        if (dp->dataType & DataType::dtCoil)
                                        {
                                            int byteNum = dp->offset / 8;
                                            int bitNum = dp->offset % 8;
                                            if (byteNum == buf[2])
                                                break;
                                            int value = (buf[3 + byteNum] >> bitNum) & 0x01;
                                            if (dp->dataType & DataType::dtBitReverse)
                                            {
                                                if (value > 0)
                                                    value = 0;
                                                else
                                                    value = 1;
                                            }
                                            cout << "dp->innerId=" << dp->innerId << ": " << value << endl;
                                            //update database
                                            CDbService::DbEntry& dbEntry = entries[r];
                                            dbEntry.innerId = dp->innerId;
                                            dbEntry.dataType = 1;   //coil or discrete input
                                            dbEntry.time = TmStart.tv_sec;
                                            dbEntry.sDigiValue = value;
                                            dbEntry.divider = 1;
                                        }
                                        //遥测转遥信处理
                                        else if (dp->dataType & DataType::dtHolding2Coil)
                                        {
                                            //telemetry to telesignaling
                                            unsigned int value = 0;
                                            if (dp->len == 1)
                                                value = buf[3];
                                            else if (dp->len == 2)
                                            {
                                                value = buf[3];
                                                value <<= 8;
                                                value += buf[4];
                                            }
                                            else if (dp->len == 4)
                                            {
                                                value = buf[3];
                                                value <<= 8;
                                                value += buf[4];
                                                value <<= 8;
                                                value += buf[5];
                                                value <<= 8;
                                                value += buf[6];
                                            }
                                            std::vector<int> innerIdList(dp->h2cInnerIdList);
                                            int listSize = innerIdList.size();
                                            if ( listSize > 0 && (dp->len * 8) >= listSize)
                                            {
                                                CDbService::DbEntry* h2cEntries = new CDbService::DbEntry[innerIdList.size()];
                                                for (size_t l = 0; l < innerIdList.size(); l++)
                                                {
                                                    CDbService::DbEntry& dbEntry = h2cEntries[r];
                                                    dbEntry.innerId = dp->h2cInnerIdList[l];
                                                    dbEntry.dataType = 1;   //coil or discrete input
                                                    dbEntry.time = TmStart.tv_sec;
                                                    dbEntry.sDigiValue = (value >> l) & 0x01;
                                                    dbEntry.divider = 1;
                                                }
                                                DbService.ModbusMasterUpdate(h2cEntries, innerIdList.size());
                                                delete[]h2cEntries;
                                            }
                                        }
                                        //遥测处理
                                        else if(dp->offset + dp->len <= cmd.totalByteNum)
                                        {
                                            uint8_t tmp[8] = {0};
                                            long long value = 0;
                                            for(int index = 0; index < dp->len; index++)
                                            {
                                                if(dp->dataType & DataType::dtByteOrder)
                                                {
                                                    const int off = (dp->byteOrder >> (index * 4)) & 0x0F;
                                                    tmp[index] = buf[dp->offset + off];
                                                }
                                                else if(dp->dataType & DataType::dtLittleEndian)
                                                {
                                                    tmp[dp->len - index -1] = buf[dp->offset + index];
                                                }
                                                else
                                                {
                                                    tmp[index] = buf[dp->offset + index];
                                                }
                                            }
                                            switch (dp->dataType & 0xFF)
                                            {
                                            case DataType::dtChar:
                                            case DataType::dtInt16:
                                            case DataType::dtInt32:
                                            case DataType::dtInt64:
                                            {
                                                switch (dp->len)
                                                {
                                                case 1:
                                                    if (dp->dataType & DataType::dtBitReverse)
                                                        value = (~(*(char*)tmp)) & 0xff;
                                                    else
                                                        value = *(char*)tmp;
                                                    break;

                                                case 2:
                                                    if (dp->dataType & DataType::dtBitReverse)
                                                        value = (~(*(short*)tmp)) & 0xffff;
                                                    else
                                                        value = *(short*)tmp;
                                                    break;

                                                case 3:
                                                case 4:
                                                    if (dp->dataType & DataType::dtBitReverse)
                                                        value = (~(*(int*)tmp)) & 0xffffffff;
                                                    else
                                                        value = *(int*)tmp;
                                                    break;

                                                case 8:
                                                    if (dp->dataType & DataType::dtBitReverse)
                                                        value = ~(*(long long*)tmp);
                                                    else
                                                        value = *(long long*)tmp;
                                                    break;

                                                default:
                                                    value = 0;
                                                    break;
                                                }
                                            }
                                            break;
                                            case DataType::dtUchar:
                                            case DataType::dtUint16:
                                            case DataType::dtUint32:
                                            case DataType::dtUint64:
                                            switch (dp->len)
                                                    {
                                                    case 1:
                                                        if (dp->dataType & DataType::dtBitReverse)
                                                            value = (~(*(unsigned char*)tmp)) & 0xff;
                                                        else
                                                            value = *(unsigned char*)tmp;
                                                        break;

                                                    case 2:
                                                        if (dp->dataType & DataType::dtBitReverse)
                                                            value = (~(*(unsigned short*)tmp)) & 0xffff;
                                                        else
                                                            value = *(unsigned short*)tmp;
                                                        break;

                                                    case 3:
                                                    case 4:
                                                        if (dp->dataType & DataType::dtBitReverse)
                                                            value = (~(*(unsigned int*)tmp)) & 0xffffffff;
                                                        else
                                                            value = *(unsigned int*)tmp;
                                                        break;

                                                    case 8:
                                                        if (dp->dataType & DataType::dtBitReverse)
                                                            value = ~(*(unsigned long long*)tmp);
                                                        else
                                                            value = *(unsigned long long*)tmp;
                                                        break;

                                                    default:
                                                        value = 0;
                                                        break;
                                                    }
                                            break;

                                            case DataType::dtFloat:
                                            {
                                                if (dp->len == sizeof(float))
                                                {
                                                    float val = (double)ByteToFloat(tmp);
                                                    //memcpy(&val, tmp, sizeof(float));
                                                    //binvert((char*)&val, sizeof(val));
                                                    //dvalue =
                                                    val -= dp->deviation;
                                                    value = val * dp->coef;
                                                }
                                            }
                                            break;
                                            case DataType::dtDouble:
                                            {
                                                if (dp->len == sizeof(double))
                                                {
                                                    double val = ByteToDouble(tmp);
                                                    //memcpy(&val, tmp, sizeof(double));
                                                    //binvert((char*)&val, sizeof(val));
                                                    val -= dp->deviation;
                                                    value = (val * dp->coef);
                                                }
                                            }
                                            break;
                                            }

                                            if (dp->dataType & DataType::dtBCD)
                                            {
                                                value = BCD_TO_BIN64(value);
                                            }

                                            //update the database
                                            cout << "dp->innerId=" << dp->innerId << ": " << value << endl;
                                            CDbService::DbEntry& dbEntry = entries[r];
                                            dbEntry.innerId = dp->innerId;
                                            dbEntry.time = TmStart.tv_sec;
                                            dbEntry.dataType = 0;
                                            dbEntry.dbValue = (value - dp->deviation) * dp->coef;
                                            if (abs(CDbService::GetInstance()->GetInnerIdValue(dp->innerId) - dbEntry.dbValue) < dp->interval)
                                                dbEntry.dbValue = CDbService::GetInstance()->GetInnerIdValue(dp->innerId);
                                            dbEntry.divider = 1;
                                        }
                                    }
                                    DbService.ModbusMasterUpdate(entries, device.vecCommands.size());
                                    if (commFlag[d] == false)
                                    {
                                        commFlag[d] = true;
                                        //update database
                                        CDbService::DbEntry* pEntry = new CDbService::DbEntry();
                                        pEntry->innerId = device.InnerIdBase;
                                        pEntry->divider = 1;
                                        pEntry->dataType = 1;
                                        pEntry->sDigiValue = 1;
                                        pEntry->time = TmStart.tv_sec;
                                        DbService.ModbusMasterUpdate(pEntry, 1);
                                        delete pEntry;
                                    }
                                    commTries[d] = 0;
                                }
                                else
                                {
                                    commTries[d]++;
                                    if (commTries[d] > 5)
                                    {
                                        if (commFlag[d])
                                        {
                                            commFlag[d] = false;
                                            //update database
                                            CDbService::DbEntry* pEntry = new CDbService::DbEntry();
                                            pEntry->innerId = device.InnerIdBase;
                                            pEntry->divider = 1;
                                            pEntry->dataType = 1;
                                            pEntry->sDigiValue = 0;
                                            pEntry->time = TmStart.tv_sec;
                                            DbService.ModbusMasterUpdate(pEntry, 1);
                                            delete pEntry;
                                        }
                                        commTries[d] = 0;
                                    }
                                    cout << "Rx: invalid data: " << byte_array_to_string(buf, len) << endl;
                                }
                                //recv error
                            }
                            delete[]entries;
                        }
                    }
                }
                //delay 100ms
                this_thread::sleep_for(std::chrono::milliseconds(conf.speed));
                gettimeofday(&TmEnd, NULL);
                //ready to send control command
                int vecCount = (int)vecControls.size();
                if (vecCount > 0)
                {
                    std::lock_guard<std::mutex> lockGuard(mutexWrite);
                    for (int i = 0; i < vecCount; i++)
                    {
                        string strCmd = vecControls[i];
                        int len = write(port_fd, strCmd.c_str(), (int)strCmd.size());
                        if (len < 0)
                        {
                            //write failure
                            //  cout << __FILE__ ": " << __LINE__ << ":write command error" << endl;
                            this_thread::sleep_for(chrono::milliseconds(100));
                        }
                        else
                        {
                            len = readRev(buf);
                            this_thread::sleep_for(chrono::milliseconds(50));
                        }
                        //log the sent data and received data
                        char* px = (char*)(strCmd.c_str());
                        cout << "Port" << portnum << " Tx: " ;
                        for (size_t t = 0; t < strCmd.size(); t++)
                        {
                            //unsigned char tv = px[t];
                            cout << hex << (unsigned int)(unsigned char)px[t];
                        }
                        cout << endl;
                        if(len >0)
                        {
                            cout << "Port" << portnum << " Rx: ";
                            for(int k = 0; k < len; k++)
                            {
                                cout << hex << buf[k];
                            }
                            cout << endl;
                        }
                        //cout << this_thread::get_id() << "write command:" << strCmd.c_str() << endl;
                    }
                    vecControls.clear();
                }
            }
            else
            {
                conf = NULL;
            }
        }
        //close the serial port
        if (port_fd != -1)
            close(port_fd);
    }
}

int MySerialDAQ::readConfFile()
{
    strPort = ("/dev/ttymxc") + to_string(portnum);
    //read port1.json file
    if (conf_file_exist(strJsonFileName) == false)
    {
        return -1;
    }
    ifstream inJson(strJsonFileName);
    if (!inJson.is_open())
    {
        cout << "error opening file of " << strJsonFileName << endl;
        return -1;
    }

    string strJson((std::istreambuf_iterator<char>(inJson)),
                   std::istreambuf_iterator<char>());
    inJson.close();

    //remove \r & \t
    strJson.erase(std::remove(strJson.begin(), strJson.end(), '\r'), strJson.end());
    strJson.erase(std::remove(strJson.begin(), strJson.end(), '\t'), strJson.end());
    //string to object

    bool check = JsonHelper::JsonToObject(conf, strJson);
    if (check == false)
    {
        cout << "convert json file of " << strJsonFileName <<
             " to PortConf object failed." << endl;
        return -1;
    }
    if (conf.portNum == portnum && conf.isEnabled)
    {
        port_fd = open(strPort.c_str(), O_RDWR | O_NOCTTY);
        if (port_fd < 0)
        {
            perror("open port error\n");
            cout << "open port of " + to_string(portnum) + " failed." << endl;
            return -1;
        }
        return set_serial(port_fd, conf.speed, (char)conf.parity.c_str()[0],
                          conf.dataBits, conf.stopbBits);
    }
    else
        return 0;
}

int MySerialDAQ::set_serial(int fd, int nSpeed, int nBits, char nEvent,
                            int nStop)
{
    struct termios newttys1, oldttys1;

    /*保存原有串口配置*/
    if (tcgetattr(fd, &oldttys1) != 0)
    {
        perror("Setupserial 1");
        return -1;
    }
    bzero(&newttys1, sizeof(newttys1));
    newttys1.c_cflag |= (CLOCAL |
                         CREAD); /*CREAD 开启串行数据接收，CLOCAL并打开本地连接模式*/

    newttys1.c_cflag &= ~CSIZE;/*设置数据位*/
    /*数据位选择*/
    switch (nBits)
    {
    case 7:
        newttys1.c_cflag |= CS7;
        break;
    case 9:
    ////newttys1.c_cflag |= CS9;
    default:
        newttys1.c_cflag |= CS8;
    }
    /*设置奇偶校验位*/
    switch (nEvent)
    {
    case '0':  /*奇校验*/
        newttys1.c_cflag |= PARENB;/*开启奇偶校验*/
        newttys1.c_iflag |= (INPCK |
                             ISTRIP);/*INPCK打开输入奇偶校验；ISTRIP去除字符的第八个比特  */
        newttys1.c_cflag |= PARODD;/*启用奇校验(默认为偶校验)*/
        break;
    case 'E':/*偶校验*/
        newttys1.c_cflag |= PARENB; /*开启奇偶校验  */
        newttys1.c_iflag |= (INPCK |
                             ISTRIP);/*打开输入奇偶校验并去除字符第八个比特*/
        newttys1.c_cflag &= ~PARODD;/*启用偶校验*/
        break;
    case 'N': /*无奇偶校验*/
        newttys1.c_cflag &= ~PARENB;
        break;
    }
    /*设置波特率*/
    switch (nSpeed)
    {
    case 2400:
        cfsetispeed(&newttys1, B2400);
        cfsetospeed(&newttys1, B2400);
        break;
    case 4800:
        cfsetispeed(&newttys1, B4800);
        cfsetospeed(&newttys1, B4800);
        break;
    case 9600:
        cfsetispeed(&newttys1, B9600);
        cfsetospeed(&newttys1, B9600);
        break;
    case 115200:
        cfsetispeed(&newttys1, B115200);
        cfsetospeed(&newttys1, B115200);
        break;
    default:
        cfsetispeed(&newttys1, B9600);
        cfsetospeed(&newttys1, B9600);
        break;
    }
    /*设置停止位*/
    if (nStop ==
            1)/*设置停止位；若停止位为1，则清除CSTOPB，若停止位为2，则激活CSTOPB*/
    {
        newttys1.c_cflag &= ~CSTOPB;/*默认为一位停止位； */
    }
    else if (nStop == 2)
    {
        newttys1.c_cflag |= CSTOPB;/*CSTOPB表示送两位停止位*/
    }

    /*设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
    newttys1.c_cc[VTIME] = 0;/*非规范模式读取时的超时时间；*/
    newttys1.c_cc[VMIN] = 0; /*非规范模式读取时的最小字符数*/
    tcflush(fd,
            TCIFLUSH);/*tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */

    /*激活配置使其生效*/
    if ((tcsetattr(fd, TCSANOW, &newttys1)) != 0)
    {
        perror("com set error");
        return -1;
    }

    return 0;
}

int MySerialDAQ::readRev(char* revBuf)
{
    //使用select设置阻塞时间
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(port_fd, &rfds);
    timeval timeout;
    timeout.tv_sec = 0;  //秒
    timeout.tv_usec = 500 * 1000;  //微秒
    int retval = select(port_fd + 1, &rfds, NULL, NULL, &timeout);

    if (retval <= 0)
    {
        cout << ("No data receive from port, select error") << endl;
        return -1;  //"noData";
    }
    else
    {
        return (int)read(port_fd, revBuf, MAXBUF);
    }
}

int MySerialDAQ::add_cmd_to_queue(string cmd)
{
    lock_guard<std::mutex> lockGuard(mutexWrite);
    vecControls.push_back(cmd);
    return vecControls.size();
}

string MySerialDAQ::GetReadCommand(int addr, int functionCode, int regStart,
                                   int regNum)
{
    string cmd;
    unsigned char temp[10] = {0};
    temp[0] = (unsigned char)addr;
    temp[1] = (unsigned char)functionCode;
    temp[2] = (unsigned char)(regStart >> 8) & 0xFF;
    temp[3] = (unsigned char)regStart & 0xFF;
    temp[4] = (unsigned char)(regNum >> 8) & 0xFF;
    temp[5] = (unsigned char)regNum & 0xFF;
    unsigned int crc = crc16(temp, 6);
    temp[6] = crc & 0xFF;
    temp[7] = (crc >> 8) & 0xFF;
    for (int i = 0; i < 8; i++)
    {
        cmd.push_back(temp[i]);
    }
    return cmd;
}

int MySerialDAQ::get_length_by_datatype(int code, int datatype)
{
    if(code == 1 || code == 2)
        return 1;
    else
    {
        switch(datatype)
        {
        case 0:
        case 1:
            return 2;
        case 3:
        case 4:
        case 6:
            return 4;
        default:
            return 8;
        }
    }
}

unsigned int MySerialDAQ::crc16(unsigned char* updata, unsigned int len)
{
    unsigned char uchCRCHi = 0xff;
    unsigned char uchCRCLo = 0xff;
    unsigned int  uindex;
    while (len--)
    {
        uindex = uchCRCHi ^ *updata++;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uindex];
        uchCRCLo = auchCRCLo[uindex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

string MySerialDAQ::byte_array_to_string(char* key, int length)
{
    char* p = new char[length];
    memcpy(p, key, length);
    p[length] = 0;
    string str(p);
    return str;
}


bool MySerialDAQ::validate_return_data(int stationNum, int functionCode,
                                       int regNum, char* buf, int len)
{
    if (buf[0] != stationNum || buf[1] != functionCode) return false;
    switch (functionCode)
    {
    case 1:
    case 2:
        if ((regNum % 8) == 0)
        {
            if (buf[2] != regNum / 8) return false;
        }
        else
        {
            if (buf[2] != (int(regNum / 8) + 1)) return false;
        }
        break;
    case 3:
    case 4:
        if (buf[2] != regNum * 2) return false;
        break;
    default:
        break;
    }
    return true;
}

long long MySerialDAQ::BCD_TO_BIN64(long long bcd)
{
    return ((bcd & 0xf) * 1) +
        (((bcd & 0xf0) >> 4) * 10ULL) +
        (((bcd & 0xf00) >> 8) * 100ULL) +
        (((bcd & 0xf000) >> 12) * 1000ULL) +
        (((bcd & 0xf0000) >> 16) * 10000ULL) +
        (((bcd & 0xf00000) >> 20) * 100000ULL) +
        (((bcd & 0xf000000) >> 24) * 1000000ULL) +
        (((bcd & 0xf0000000) >> 28) * 10000000ULL) +
        (((bcd & 0xf00000000) >> 32) * 100000000ULL) +
        (((bcd & 0xf000000000) >> 36) * 1000000000ULL) +
        (((bcd & 0xf0000000000) >> 40) * 10000000000ULL) +
        (((bcd & 0xf00000000000) >> 44) * 100000000000ULL) +
        (((bcd & 0xf000000000000) >> 48) * 1000000000000ULL) +
        (((bcd & 0xf0000000000000) >> 52) * 10000000000000ULL) +
        (((bcd & 0xf00000000000000) >> 56) * 100000000000000ULL) +
        (((bcd & 0xf000000000000000) >> 60) * 1000000000000000ULL);
}
