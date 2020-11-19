#include <iostream>
#include <stdio.h>
#include <array>
#include <QString>

#include "networkworker.h"
#include <QCoreApplication>


double pinger(const char* addr, QString& res) // returns average time
{
    std::array<char, 128> buffer;
    std::string result;

    // std::cout << "Opening reading pipe" << std::endl;
    FILE* pipe = popen(addr, "r");
    if (!pipe)
    {
        std::cerr << "Couldn't start command." << std::endl;
        return 0;
    }
    while (fgets(buffer.data(), 128, pipe) != nullptr)
    {
        // std::cout << "Pinging... " << std::endl;
        result += buffer.data();
    }
    auto returnCode = pclose(pipe);

    // std::cout << result << std::endl;
    // std::cout << "Pinger renurned code: " << returnCode << std::endl;


    std::string resume((result.begin() + result.find("---")), result.end());

    std::cout << "Resume: " << resume << '\n';


    short slashes = 0;
    std::string avg_time = "0.0";
    bool time_exist_sw = false;
    for (std::size_t end = resume.size(); slashes < 3 && end > 0; --end)
    {
        if(resume[end] == '/') ++slashes;
        if (slashes == 2)
        {
            if (!time_exist_sw)
            {
                time_exist_sw = true;
                avg_time.clear();
            }
            if (!std::isspace(resume[end]))
                avg_time += resume[end];
        }
    }

    std::string avg_time_result;

    for (std::size_t end = avg_time.size() - 1; end > 0; --end)
        avg_time_result += avg_time[end];

    double d_result = 0.0;
    d_result = std::stod(avg_time_result);

    if (d_result < 1) return 0.0;

    res = QString::fromStdString(resume);

    return d_result;
}


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    QString resume;
    networkworker sender;

    double res_time = 4.0;

    while (res_time < 7.5)
    {
        res_time = pinger("ping 8.8.8.8 -c 3", resume);
        if (res_time == 0.0) break;
    }

    system("tshark -a duration:120");
    sender.goUrl(resume + "\n Сниффер включен!");


    return a.exec();
}












