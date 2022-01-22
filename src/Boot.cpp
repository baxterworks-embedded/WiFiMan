#include <Arduino.h>
#include "Boot.h"

void reboot()
{
    ESP.restart();
}

bool clear()
{

    if(LittleFS.begin())
    {
        if(!LittleFS.exists("/config.json"))
            return true;

        if(LittleFS.remove("/config.json"))
            return true;
        else
            return false;
    }
    else
    {
        DEBUG_MSG("#>< Clear : LittleFS Error!\n");
        return false;
    }
}

bool makeBootFlag()
{
    if(LittleFS.begin())
    {
        File configFile = LittleFS.open("/boot.conf", "w");
        if (!configFile) 
        {
            DEBUG_MSG("#>< makeBootFlag : LittleFS Error! Cannot open /boot.conf\n");
            LittleFS.end();
            return false;
        }
        else
        {
            configFile.print("skip-auto-connect");
            configFile.close();
            LittleFS.end();
            return true;
        }
    }
    else
    {
        DEBUG_MSG("#>< makeBootFlag : LittleFS Error!\n");
        return false;
    }
}

bool clearBootFlag()
{
    if(LittleFS.begin())
    {
        if (LittleFS.exists("/boot.conf")) 
        {
            LittleFS.remove("/boot.conf");
            LittleFS.end();
            return true;
        }
        else
        {
            LittleFS.end();
            return true;
        }
    }
    else
    {
        DEBUG_MSG("#>< clearBootFlag : LittleFS Error!\n");
        return false;
    }
}

bool getBootFlag()
{
    if(LittleFS.begin())
    {
        if (LittleFS.exists("/boot.conf")) 
        {
            LittleFS.end();
            return true;
        }
        else
        {
            LittleFS.end();
            return false;
        }
    }
    else
    {
        DEBUG_MSG("#>< getBootFlag : LittleFS Error!\n");
        return false;
    }
}

// ------------------------------------------------------ 

bool getBootMode()
{
    if(getBootFlag())
    {
        //remove the boot flag
        clearBootFlag();
        return true;
    }
    return false;
}

bool rebootToApMode()
{
    //make boot flag
    makeBootFlag();
    //then reboot
    reboot();
    return false;
}