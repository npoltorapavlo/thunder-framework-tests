#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

using namespace Thunder;

using ::testing::Eq;

namespace {
const uint32_t kNumber = 464258508;
}

TEST(DecUInt32, FromStringNumberIsNumber)
{
    Core::JSON::DecUInt32 decUInt32;
    decUInt32.FromString(std::to_string(kNumber));
    EXPECT_THAT(decUInt32.Value(), Eq(kNumber));
}

TEST(DecUInt32, FromStringQuotedNumberIsNumber)
{
    Core::JSON::DecUInt32 decUInt32;
    decUInt32.FromString("\"" + std::to_string(kNumber) + "\"");
    EXPECT_THAT(decUInt32.Value(), Eq(kNumber));
}

TEST(JsonValue, FromStringNumberIsNumber)
{
    JsonValue jsonValue;
    jsonValue.FromString(std::to_string(kNumber));
    EXPECT_THAT(jsonValue.Number(), Eq(kNumber));
}

TEST(JsonValue, FromStringQuotedNumberIs0)
{
    JsonValue jsonValue;
    jsonValue.FromString("\"" + std::to_string(kNumber) + "\"");
    EXPECT_THAT(jsonValue.Number(), Eq(0));
}

TEST(DecUInt32, ToStringIsStringNumber)
{
    string str;
    Core::JSON::DecUInt32(kNumber).ToString(str);
    EXPECT_THAT(str, Eq(std::to_string(kNumber)));
    Core::JSON::DecUInt32 decUInt32;
    decUInt32 = kNumber;
    decUInt32.ToString(str);
    EXPECT_THAT(str, Eq(std::to_string(kNumber)));
    decUInt32.FromString(std::to_string(kNumber));
    decUInt32.ToString(str);
    EXPECT_THAT(str, Eq(std::to_string(kNumber)));
    decUInt32.FromString("\"" + std::to_string(kNumber) + "\"");
    decUInt32.ToString(str);
    EXPECT_THAT(str, Eq(std::to_string(kNumber)));
}
