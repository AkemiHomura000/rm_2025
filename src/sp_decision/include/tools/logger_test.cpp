#include "tools/logger.hpp"
int main(int argc, char **argv)
{
    tools::logger::Ptr logger = std::make_shared<tools::logger>();
    spdlog::set_level(spdlog::level::debug);
    std::stringstream ss;
    ss << "This is a test message.";
    logger->logInfo(ss);
    spdlog::info(ss.str());
    spdlog::debug(ss.str());
    spdlog::error(ss.str());
    spdlog::critical(ss.str());
    return 0;
}