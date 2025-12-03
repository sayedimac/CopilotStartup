#include "handlers.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace webservice::handlers::tests {

class HandlersTest : public ::testing::Test {
protected:
    httplib::Request req_;
    httplib::Response res_;
};

TEST_F(HandlersTest, HealthHandlerReturnsHealthyStatus) {
    handleHealth(req_, res_);
    
    EXPECT_EQ(res_.status, 200);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("healthy"));
    EXPECT_THAT(res_.body, ::testing::HasSubstr("cpp-webservice"));
}

TEST_F(HandlersTest, RootHandlerReturnsHtmlPage) {
    handleRoot(req_, res_);
    
    EXPECT_EQ(res_.status, 200);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("C++ Web Service"));
    EXPECT_THAT(res_.body, ::testing::HasSubstr("Available Endpoints"));
}

TEST_F(HandlersTest, EchoHandlerReturnsReceivedData) {
    req_.body = R"({"message": "test"})";
    
    handleEcho(req_, res_);
    
    EXPECT_EQ(res_.status, 200);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("received"));
    EXPECT_THAT(res_.body, ::testing::HasSubstr("test"));
}

TEST_F(HandlersTest, EchoHandlerReturnsErrorOnEmptyBody) {
    req_.body = "";
    
    handleEcho(req_, res_);
    
    EXPECT_EQ(res_.status, 400);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("error"));
}

TEST_F(HandlersTest, EchoHandlerReturnsErrorOnInvalidJson) {
    req_.body = "not valid json";
    
    handleEcho(req_, res_);
    
    EXPECT_EQ(res_.status, 400);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("valid JSON"));
}

TEST_F(HandlersTest, TimeHandlerReturnsValidTime) {
    handleTime(req_, res_);
    
    EXPECT_EQ(res_.status, 200);
    EXPECT_THAT(res_.body, ::testing::HasSubstr("time"));
    EXPECT_THAT(res_.body, ::testing::HasSubstr("UTC"));
    // Check for ISO 8601 format pattern (e.g., 2024-12-03T10:59:38Z)
    EXPECT_THAT(res_.body, ::testing::MatchesRegex(".*[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}Z.*"));
}

} // namespace webservice::handlers::tests
