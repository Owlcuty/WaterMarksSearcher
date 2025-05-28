#include <iostream>

#include "Application.h"
#include "ConsoleLogger.h"


int main(int argc, char** argv)
{
    try
    {
        Application app;
        /*
        app.set..Factory(); <->
        */
        std::shared_ptr<ILogger> logger = std::make_shared<ConsoleLogger>(ILogger::LogLevel::Debug);
        app.setLogger(std::move(logger));
        app.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << ":: Main failed" << std::endl;
        return -1;
    }
    catch (...)
    {
        return -2;
    }
    return 0;
}