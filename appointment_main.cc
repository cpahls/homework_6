/**
 *   @file: homework_6.cc
 * @author: Christian Pahls
 *   @date: 04/12/24
 *  @brief: This program has multiple functions to change input
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Helper function
string trim(const string& str, const string& whitespace = "/t"){
    // Removes leading/following spaces
    const auto strBegin = str.find_first_not_of(whitespace);
    if(strBegin == string::npos)
    return "";
    
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}// End of trim function

string militaryToStandard(int time){
    // Example converts 1830 to "6:30PM"
    int timeLen;
    string hr, min, aorp, sTime, standard;
    // Converts to string
    sTime = to_string(time);
    // Gets string length
    timeLen = sTime.length();
    // Determins hr and min based on length
    if(timeLen == 2){
        // Lenth of 3 will be AM (midnight)
        hr = "12";
        min = sTime.substr(0,2);
        aorp = "AM";
    } else if(timeLen == 3){
        // Length of 3 will be AM
        hr = sTime.substr(0,1);
        min = sTime.substr(1,2);
        aorp = "AM";
    } else{
        // Lenght of 4 will vary AM/PM
        min = sTime.substr(2,2);
        // If less than 12000 hrs (specifically 10 Am and 11 AM)
        if(stoi(sTime.substr(0,2)) < 12){
            hr = sTime.substr(0,2);
            aorp = "AM";
            // If equal to 1200 hrs
        } else if(sTime.substr(0,2) == "12"){
            hr = "12";
            aorp = "PM";
            // If greater than 1200 hrs
        } else{
            hr = to_string(stoi(sTime.substr(0,2)) - 12);
            aorp = "PM";
        }
    }
    // Create time in standard format hh:MM AM/PM
    standard = hr + ":" + min + " " + aorp;
    return standard;
} // End militaryToStandard() function

int standardToMilitary(string time){
    
    int seperator, military;
    string hr, min, aorp;
 // Convert to lower case (helper to simplify AM vs PM)
    for(int i = 0; i < time.length(); i++){
        if(time[i] >= 'A' && time[i] <= 'Z'){
            time[i] = time[i] + 32;
        }
    }
 // Get hr and min
    seperator = time.find(":");
    hr = time.substr(0, seperator);
    min = time.substr(seperator + 1,2);
   
    // Determin AM or PM
    if(time.find("a") != string::npos){
        aorp = "am";
    } else{
        aorp = "pm";
    }

    // Convert to military time
    if(aorp == "am"){
        if(hr == "12"){
            // Handles midnight
            military = stoi(to_string(stoi(hr) + 12) + min); 
        } else{
            // Handles other morning hours
            military = stoi(hr + min);
        }
    } else{
        if(hr == "12"){
            // Handles noon hours
            military = stoi(hr + min);
        } else{
            // Handles afternoon hours
            military = stoi(to_string(stoi(hr) + 12) + min);
        }
    }
    return military;
} // End standardToMilitary() function

class Appointment{
    public: // Make available outside of Appointment.h

    // Default Constructor
    Appointment() : getTitle("N/A"), getYear(1), getMonth(1), getDay(1),
    getTime(0), getDuration(1){}

    // Constructor takes appointment string as an input
    // Extracts tilte, year, month, day , time, and duration
    Appointment(string appData){
        sAppt = trim(appData);
        // GetTitle
        iPos = 0;
        iLen = sAppt.find("|", iPos) - iPos;
        getTitle = trim(sAppt.substr(iPos,iLen));
        // GetYear
        iPos = iLen + 2;
        iLen = sAppt.find("|", iPos) - iPos;
        getYear = stoi(trim(sAppt.substr(iPos,iLen)));
        // GetMonth
        iPos = iPos + iLen + 1;
        iLen = sAppt.find("|", iPos) -iPos;
        getMonth = stoi(trim(sAppt.substr(iPos, iLen)));
        // GetDay
        iPos = iPos + iLen + 1;
        iLen = sAppt.find("|", iPos) - iPos;
        getDay = stoi(trim(sAppt.substr(iPos, iLen)));
        // GetTime
        iPos = iPos + iLen +1;
        iLen = sAppt.find("|", iPos) - iPos;
        getTime = standardToMilitary(trim(sAppt.substr(iPos, iLen)));
        // GetDuration
        iPos = iPos + iLen + 1;
        iLen = sAppt.length() - iPos;
        getDuration = stoi(trim(sAppt.substr(iPos, iLen)));
    }

    // Member function that prints the stored string
    void printAppt(){
        cout << "Appointment input: " << sAppt << "\n\n";
        cout << "getTitle: " << getTitle << "\n";
        cout << "getYear: " << getYear << "\n";
        cout << "getMonth: " << getMonth << "\n";
        cout << "getDay: " << getDay << "\n";
        cout << "getTime: " << getTime << "\n";
        cout << "getDuration: " << getDuration << "\n";
    }

    // Member function that returns appointment status message
    string returnMessage(){
        if(getYear < 0){
            message = "Error: Year must be a positive value.";
        } else if(getMonth < 1 || getMonth > 12){
            message = "Error: Month must be between 1 and 12.";
        } else if(getDay < 1 || getDay > 31){
            message = "Error: Day must be between 1 and 31.";
        } else if(getTime > 2359){
            message = "Error: Time must be between 1 - 2359 (in Military time).";
        } else if(getDuration < 1){
            message = "Error: Duration must be greater than 0 min.";
        } else {
            message = "appointment successfully recorded.";
        }
        return message;
    }

    //Variables used in class
    private:
        string sAppt, getTitle, getDate, getStandardTime, message;
        int iPos, iLen, getYear, getMonth, getDay, getTime, getDuration;
        void setTitle(string newTitle);
        void setYear(int newYear);
        void setMonth(int newMonth);
        void setDay(int newDAy);
        void setTime(int newTime); // Military time
        void setDuration(int newDuration);
        void setDate(int newYear, int newMonth, int newDay);
}; // End of Appointment class

int main() {

    // Define variables(used for testing functions)
    string sTime;
    int iTime;

    // Create an instande of Appointment class with string input
    Appointment apptObj("Meeting with Bob | 2023 |6 |23 |8:30aM | 15");

    // Returns message to indicate if any errors
    cout << apptObj.returnMessage() << endl;

    // Prints appointment details
    apptObj.printAppt();

    return 0;
} // End of main

