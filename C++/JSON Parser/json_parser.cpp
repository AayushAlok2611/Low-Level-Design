#include <iostream>
#include <map>
#include <string>
#include <vector>
 using namespace std;


/*
In CPP , there is no generic return type that i can set fr the getValue function of JSONElement , so I am always returning strings only

*/

// ======== Declaring JSON data types ===============

class JSONElement{ // interface for JSONElements
    protected:
    JSONElement(){} // protected constructor and destructor ensure that this class can't be instantiated and/or destroyed anywhere other than in the class and its subclasses
    ~JSONElement(){}

    public:
    virtual string getValue() = 0; // pure virtual function (Abstract class)
};
// Here JSONElement is a template where T can take any dataType

class JSONString : public JSONElement{
    private:
    string str;

    public:
    JSONString(string str):str(str){}

    string getValue(){
        return str;
    }
};

class JSONNumber: public JSONElement{
    private:
    double number;

    public:
    JSONNumber(double number):number(number){}

    string getValue(){
        return to_string(number);
    }
};

class JSONBoolean: public JSONElement {
    private:
    bool val;

    public:
    JSONBoolean(bool val):val(val){}

    string getValue(){
        return val? "true": "false";
    }
};

class JSONArray: public JSONElement{
    private:
    vector<JSONElement*> elements;

    public:
    JSONArray(vector<JSONElement*> & elements):elements(elements){}

    string getValue(){
        string result = "[";
        for (auto element : elements) {
            result += element->getValue() + ", ";
        }
        if (!elements.empty()) {
            result.pop_back(); // Remove last comma
            result.pop_back(); // Remove space
        }
        result += "]";
        return result;
    }
};

class JSONObject: public JSONElement {
    private:
    map<string,JSONElement*> jsonObject;

    public:
    JSONObject(map<string,JSONElement*> &parsedJson):jsonObject(parsedJson){}

    string getValue(){
        string result = "{";
        for (auto entry : jsonObject) {
            result += "\"" + entry.first + "\": " + entry.second->getValue() + ", ";
        }
        if (!jsonObject.empty()) {
            result.pop_back(); // Remove last comma
            result.pop_back(); // Remove space
        }
        result += "}";
        return result;
    }
};


// ======================== JSON Parser ====================================

class JSONParser{
    private:
    string jsonString;
    int idx;
    const char OPEN_CURLY_BRACE = '{';
    const char CLOSE_CURLY_BRACE = '}';
    const char COMMA = ',';
    const char COLON = ':';
    const char DECIMAL = '.';
    const char OPEN_SQAURE_BRACE = '[';
    const char CLOSE_SQUARE_BRACE = ']';
    const char DOUBLE_QUOTE = '"';
    
    JSONElement* parseValue()
    {
        char currentChar = jsonString[idx];
        if(currentChar == OPEN_CURLY_BRACE)
        {
            return parseObject();
        }
        else if(currentChar == OPEN_SQAURE_BRACE)
        {
            return parseArray();
        }
        else if (currentChar == DOUBLE_QUOTE) 
        {
            return parseString();
        } 
        else if (isdigit(currentChar) || currentChar == '-') 
        {
            return parseNumber();
        } 
        else if (currentChar == 't' || currentChar == 'f') 
        {
            return parseBoolean();
        } 
        else if (currentChar == 'n') 
        {
            return parseNull();
        }

        throw new exception("Invalid JSON");

    }
    JSONObject* parseObject()
    {
        skipWhitespaces(); // skip whit spaces between { and first key's double quote
        map<string,JSONElement*> properties;

        consume(OPEN_CURLY_BRACE); // move idx

        while(idx<jsonString.size() && jsonString[idx]!=CLOSE_CURLY_BRACE)
        {
            string key = parseString()->getValue();
            skipWhitespaces();

            consume(COLON);

            JSONElement* value = parseValue();
            properties[key] = value;

            skipWhitespaces();

            // Check for a comma, indicating more properties
            if (jsonString[idx] == COMMA) {
                consume(COMMA);
                skipWhitespaces();
            }
        }
        consume(CLOSE_CURLY_BRACE); // move idx ahead of closing curly brace
        return new JSONObject(properties);
    }

    JSONArray* parseArray()
    {
        consume(OPEN_SQAURE_BRACE); // move idx ahead of opening square brace
        skipWhitespaces();

        vector<JSONElement*> elements;
        while(idx<jsonString.size() && jsonString[idx]!=CLOSE_SQUARE_BRACE)
        {
            // Parse array element
            JSONElement* element = parseValue();
            elements.push_back(element);

            skipWhitespaces();

            // Check for a comma, indicating more elements
            if (jsonString[idx] == COMMA) {
                consume(COMMA);
                skipWhitespaces();
            }
        }
        consume(CLOSE_SQUARE_BRACE); // move idx ahead of closing sqaure brace
        return new JSONArray(elements);
    }

    JSONNumber* parseNumber()
    {
        int startIndex = idx;

        // Consume digits and optional decimal point
        while (isdigit(jsonString[idx]) || jsonString[idx] == '.') {
            idx++;
        }

        string numberStr = jsonString.substr(startIndex, idx);
        return new JSONNumber(stod(numberStr));
    }

    JSONBoolean* parseBoolean() {
        string boolStr = "";

        while(idx<jsonString.size() && isalpha(jsonString[idx]))
        {
            boolStr.push_back(jsonString[idx++]);
        }

        if (boolStr == "true") {
            return new JSONBoolean(true);
        } else if (boolStr == "false") {
            return new JSONBoolean(false);
        }

        throw new exception("Invalid boolean value");
    }

    JSONElement* parseNull() {
        string nullStr = "";
        while(idx<jsonString.size() && isalpha(jsonString[idx]))
        {
            nullStr.push_back(jsonString[idx++]);
        }
        return NULL;
    }

    JSONString* parseString()
    {
        consume(DOUBLE_QUOTE); // move idx ahead of starting double quote
        skipWhitespaces();

        string key="";
        while(idx< jsonString.size() && jsonString[idx]!=DOUBLE_QUOTE)
        {
            key.push_back(jsonString[idx++]);
        }
        consume(DOUBLE_QUOTE); // move idx ahead of ending double quote
        return new JSONString(key);
    }

    void skipWhitespaces()
    {
        while(idx < jsonString.size() && jsonString[idx]==' ')idx++;
    }

    void consume(char ch)
    {
        while(idx < jsonString.size() && jsonString[idx]==ch)idx++;
    }

    public:

    JSONParser(string jsonString):jsonString(jsonString){
        idx = 0;
    }

    JSONElement* parse() 
    {   
        skipWhitespaces(); // skipping whitespaces between start of jsonString and 1st {
        return parseValue();
    }

};