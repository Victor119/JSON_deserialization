// #include <gtest/gtest.h>
// #include <fstream>
// #include <sstream>
// #include <cstdio>
// #include <cstdlib>

#include <gtest/gtest.h>
#include <fstream>
#include <string>

extern int main_json(int, char**); // Declare the main function to be used in the tests

std::string runMainWithArgs(const std::string& filePath, const std::string& secondArg) {
    // Redirect standard output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    // Prepare arguments
    const char* argv[] = {"json_exec", filePath.c_str(), secondArg.c_str()};
    main_json(3, const_cast<char**>(argv));

    // Restore standard output
    std::cout.rdbuf(old);

    return buffer.str();
}

std::string getLastLine(const std::string& output) {
    // Start from the end of the string and move backward
    size_t pos = output.size();

    // Trim any trailing newlines or empty spaces
    while (pos > 0 && (output[pos - 1] == '\n' || output[pos - 1] == '\r')) {
        --pos;
    }

    // Find the last newline before the last non-empty line
    size_t lastNewline = output.rfind('\n', pos - 1);
    if (lastNewline == std::string::npos) {
        return output.substr(0, pos); // Return everything if there's no newline
    }

    return output.substr(lastNewline + 1, pos - lastNewline - 1);
}


class JsonValidationTests : public ::testing::Test {
protected:
    std::string tempFileName = "temp_input.txt";

    void SetUp() override {
        // No specific setup needed before each test
    }

    void TearDown() override {
        std::remove(tempFileName.c_str());
    }

    void writeToTempFile(const std::string& content) {
        std::ofstream outFile(tempFileName);
        outFile << content;
        outFile.close();
    }
};

const std::string JSON_VALIDATED_MESSAGE = "JSON validated";

// Test case for: key with null value
TEST_F(JsonValidationTests, KeyWithNullValue) {
    writeToTempFile("{\"x\": null, \"y\": null}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "null");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "null");
}

// Test case for: key with bool value true
TEST_F(JsonValidationTests, KeyWithBoolValueTrue) {
    writeToTempFile("{\"x\": true, \"y\": true}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "true");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "true");
}

// Test case for: key with bool value true and key with bool value false
TEST_F(JsonValidationTests, KeyWithBoolValueTrueAndFalse) {
    writeToTempFile("{\"x\": true, \"y\": false}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "true");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "false");
}

// Test case for: 2 different keys but inside have 1 common key name to access value
TEST_F(JsonValidationTests, KeysWithCommonSubKey) {
    writeToTempFile("{\"x\": {\"b\": \"123\"}, \"y\": {\"b\": \"123\"}}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"b\": \"123\"}");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"b\": \"123\"}");

    output = runMainWithArgs(tempFileName, "x.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"123\"");

    output = runMainWithArgs(tempFileName, "y.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"123\"");
}

// Test case for: value key using inside string escaped \" and characters [ ]
TEST_F(JsonValidationTests, ValueKeyWithEscapedCharacters) {
    writeToTempFile("{\"x\": {\"b\": \"1[2]7\\\"3\"}, \"y\": {\"b\": \"123\"}}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"b\":\"1[2]7\\\"3\"");

    output = runMainWithArgs(tempFileName, "x.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"1[2]7\\\"3\"");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"b\":\"123\"");

    output = runMainWithArgs(tempFileName, "y.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"123\"");
}

// Test case for: value key with negative integer
TEST_F(JsonValidationTests, ValueKeyWithNegativeInteger) {
    writeToTempFile("{\"x\": -789, \"a\": {\"b\": [1, 2, {\"c\": \"test\"}, [11, 12]]}, \"y\": -999}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "-789");

    output = runMainWithArgs(tempFileName, "a");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"b\":[1,2,{\"c\":\"test\"},[11,12]]}");

    output = runMainWithArgs(tempFileName, "a.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[1,2,{\"c\":\"test\"},[11,12]]");

    output = runMainWithArgs(tempFileName, "a.b[0]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "1");

    output = runMainWithArgs(tempFileName, "a.b[1]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "2");

    output = runMainWithArgs(tempFileName, "a.b[2]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"c\":\"test\"}");

    output = runMainWithArgs(tempFileName, "a.b[3]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[11, 12]");

    output = runMainWithArgs(tempFileName, "a.b[2].c");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"test\"");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "-999");
}

// Test case for: value key with double values
TEST_F(JsonValidationTests, ValueKeyWithDoubleValues) {
    writeToTempFile("{\"x\": -789.235, \"a\": {\"b\": [1, 2, 3, 4, {\"c\": \"test\"}, [11, 12]]}, \"y\": 999.999}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "-789.235");

    output = runMainWithArgs(tempFileName, "a");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"b\":[1,2,3,4,{\"c\":\"test\"},[11,12]]}");

    output = runMainWithArgs(tempFileName, "a.b");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[1,2,3,4,{\"c\":\"test\"},[11,12]]");

    output = runMainWithArgs(tempFileName, "a.b[0]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "1");

    output = runMainWithArgs(tempFileName, "a.b[1]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "2");

    output = runMainWithArgs(tempFileName, "a.b[2]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "3");

    output = runMainWithArgs(tempFileName, "a.b[3]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "4");

    output = runMainWithArgs(tempFileName, "a.b[4]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "{\"c\":\"test\"}");

    output = runMainWithArgs(tempFileName, "a.b[5]");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[11,12]");

    output = runMainWithArgs(tempFileName, "a.b[4].c");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "\"test\"");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "999.999");
}

// Test case for: invalid JSON structure
TEST_F(JsonValidationTests, InvalidJsonStructure) {
    writeToTempFile("{\"x\": 789, \"a\": [\"b\": [1, 2, {\"c\": \"te[s]\"\\t\"}, [11, 12]]], \"y\": 999}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a[0].b");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a[0].b[0]");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a[0].b[1]");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a[0].b[2]");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "x.a[0].b[3]");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find("JSON-ul nu este valid.") != std::string::npos);
}

// Test case for: array type value with only one element
TEST_F(JsonValidationTests, ArrayTypeWithSingleValue) {
    writeToTempFile("{\"x\": [789], \"y\": [999]}");

    std::string output = runMainWithArgs(tempFileName, "x");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[789]");

    output = runMainWithArgs(tempFileName, "y");
    ASSERT_TRUE(output.find(JSON_VALIDATED_MESSAGE) == 0);
    ASSERT_EQ(getLastLine(output), "[999]");
}
