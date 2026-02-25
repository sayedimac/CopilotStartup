#include "server.h"
#include <gtest/gtest.h>

namespace webservice::tests {

class ServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Use a different port for testing to avoid conflicts
        server_ = std::make_unique<Server>("localhost", 8081);
    }

    void TearDown() override {
        if (server_ && server_->isRunning()) {
            server_->stop();
        }
    }

    std::unique_ptr<Server> server_;
};

TEST_F(ServerTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(server_->getHost(), "localhost");
    EXPECT_EQ(server_->getPort(), 8081);
    EXPECT_FALSE(server_->isRunning());
}

TEST_F(ServerTest, ConstructorThrowsOnInvalidPort) {
    EXPECT_THROW(Server("localhost", -1), std::invalid_argument);
    EXPECT_THROW(Server("localhost", 0), std::invalid_argument);
    EXPECT_THROW(Server("localhost", 65536), std::invalid_argument);
}

TEST_F(ServerTest, ServerNotRunningInitially) {
    EXPECT_FALSE(server_->isRunning());
}

TEST_F(ServerTest, GettersReturnCorrectValues) {
    Server server("127.0.0.1", 9000);
    EXPECT_EQ(server.getHost(), "127.0.0.1");
    EXPECT_EQ(server.getPort(), 9000);
}

TEST_F(ServerTest, MoveConstructorWorks) {
    Server server1("localhost", 8082);
    EXPECT_FALSE(server1.isRunning());
    
    Server server2(std::move(server1));
    EXPECT_EQ(server2.getHost(), "localhost");
    EXPECT_EQ(server2.getPort(), 8082);
    EXPECT_FALSE(server2.isRunning());
    
    // Moved-from object should be in a valid state (not running)
    EXPECT_FALSE(server1.isRunning());
}

TEST_F(ServerTest, MoveAssignmentWorks) {
    Server server1("localhost", 8082);
    Server server2("127.0.0.1", 8083);
    
    server2 = std::move(server1);
    EXPECT_EQ(server2.getHost(), "localhost");
    EXPECT_EQ(server2.getPort(), 8082);
    EXPECT_FALSE(server2.isRunning());
    
    // Moved-from object should be in a valid state (not running)
    EXPECT_FALSE(server1.isRunning());
}

} // namespace webservice::tests
