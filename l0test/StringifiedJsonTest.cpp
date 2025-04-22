#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;
using ::testing::IsFalse;
using ::testing::Test;

const auto kJson = "{\"a\":\"{\\\"b\\\":\\\"c\\\"}\"}";
const auto kQuoted = "\"{\\\"b\\\":\\\"c\\\"}\"";
const auto kUnquoted = "{\"b\":\"c\"}";

class AStringifiedJson : public Test {
protected:
    JsonValue json;
    void SetUp() override
    {
        json = JsonObject(kJson)["a"];
    }
};

TEST_F(AStringifiedJson, TypeIsSTRING)
{
    EXPECT_THAT(json.Content(), Eq(Core::JSON::Variant::type::STRING));
}

TEST_F(AStringifiedJson, StringIsQuoted)
{
    EXPECT_THAT(json.String(), Eq(kQuoted));
}

TEST_F(AStringifiedJson, ObjectIsEmpty)
{
    EXPECT_THAT(json.Object().Variants().Next(), IsFalse());
}

TEST_F(AStringifiedJson, JsonStringIsQuoted)
{
    EXPECT_THAT(Core::JSON::String(json.String()).Value(), Eq(kQuoted));
}

TEST_F(AStringifiedJson, JsonStringFromStringIsUnquoted)
{
    Core::JSON::String jsonString;
    jsonString.FromString(json.String());
    EXPECT_THAT(jsonString.Value(), Eq(kUnquoted));
}

TEST_F(AStringifiedJson, JsonObjectIsEmpty)
{
    EXPECT_THAT(JsonObject(json.String()).Variants().Next(), IsFalse());
}

TEST_F(AStringifiedJson, JsonObjectFromStringIsEmpty)
{
    JsonObject jsonObject;
    jsonObject.FromString(json.String());
    EXPECT_THAT(JsonObject(json.String()).Variants().Next(), IsFalse());
}
