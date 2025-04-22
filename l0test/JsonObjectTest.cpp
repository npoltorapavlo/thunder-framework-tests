#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;
using ::testing::IsTrue;
using ::testing::Test;

const auto kJson = "{\"a\":{\"b\":\"c\"}}";
const auto kQuoted = "\"{\\\"b\\\":\\\"c\\\"}\"";
const auto kUnquoted = "{\"b\":\"c\"}";

class AJsonObject : public Test {
protected:
    JsonValue json;
    void SetUp() override
    {
        json = JsonObject(kJson)["a"];
    }
};

TEST_F(AJsonObject, TypeIsOBJECT)
{
    EXPECT_THAT(json.Content(), Eq(Core::JSON::Variant::type::OBJECT));
}

TEST_F(AJsonObject, StringIsUnquoted)
{
    EXPECT_THAT(json.String(), Eq(kUnquoted));
}

TEST_F(AJsonObject, ObjectIsNotEmpty)
{
    EXPECT_THAT(json.Object().Variants().Next(), IsTrue());
}

TEST_F(AJsonObject, JsonStringIsUnquoted)
{
    EXPECT_THAT(Core::JSON::String(json.String()).Value(), Eq(kUnquoted));
}

TEST_F(AJsonObject, JsonStringFromStringIsUnquoted)
{
    Core::JSON::String jsonString;
    jsonString.FromString(json.String());
    EXPECT_THAT(jsonString.Value(), Eq(kUnquoted));
}

TEST_F(AJsonObject, JsonObjectIsNotEmpty)
{
    EXPECT_THAT(JsonObject(json.String()).Variants().Next(), IsTrue());
}

TEST_F(AJsonObject, JsonObjectFromStringIsNotEmpty)
{
    JsonObject jsonObject;
    jsonObject.FromString(json.String());
    EXPECT_THAT(JsonObject(json.String()).Variants().Next(), IsTrue());
}

TEST_F(AJsonObject, ToQuotedStringIsQuoted)
{
    EXPECT_THAT(Core::ToQuotedString('\"', json.String()), Eq(kQuoted));
}
