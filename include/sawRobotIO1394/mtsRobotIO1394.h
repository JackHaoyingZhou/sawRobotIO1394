/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s):  Zihan Chen, Peter Kazanzides
  Created on: 2011-06-10

  (C) Copyright 2011-2013 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef __mtsRobotIO1394_H__
#define __mtsRobotIO1394_H__

#include <ostream>
#include <iostream>
#include <vector>

#include <cisstMultiTask/mtsTaskPeriodic.h>

class FirewirePort;
class AmpIO;

class mtsRobotIO1394 : public mtsTaskPeriodic {

    CMN_DECLARE_SERVICES(CMN_DYNAMIC_CREATION_ONEARG, CMN_LOG_ALLOW_DEFAULT);
public:
    enum { MAX_BOARDS = 16 };

protected:

    class RobotInternal;
    class DigitalInInternal;

    FirewirePort * Port;                      // Pointer to IEEE-1394 port handler
    std::ostream * MessageStream;             // Stream provided to the low level boards for messages, redirected to cmnLogger
    std::vector<RobotInternal *> RobotList;   // List of robots (provided interfaces)
    std::vector<DigitalInInternal *> DigitalInList; // List of digital inputs (provided interfaces)
    AmpIO *BoardList[MAX_BOARDS];             // List of boards

///////////// Public Class Methods ///////////////////////////
public:
    // Constructor & Destructor
    mtsRobotIO1394(const std::string &name, double period, int port_num);
    mtsRobotIO1394(const mtsTaskPeriodicConstructorArg & arg); // TODO: add port_num
    virtual ~mtsRobotIO1394();

    void Init();

    void Configure(const std::string &filename);
    void Startup(void);
    void Run(void);
    void Cleanup(void);
    void GetNumberOfDigitalInputs(int &num) const;

protected:

    void GetNumberOfBoards(int &num) const;
    void GetNumberOfRobots(int &num) const;

    void GetRobotNames(std::vector<std::string> &result) const;
    void GetNumberOfActuatorPerRobot(vctIntVec &result) const;

    void GetDigitalInputNames(std::vector<std::string> &result) const;
    void GetName(std::string &result) const;


////////////// Private Class Methods /////////////////////////////
private:
    // Make uncopyable
    mtsRobotIO1394(const mtsRobotIO1394 &);
    mtsRobotIO1394 &operator=(const mtsRobotIO1394 &);
};

CMN_DECLARE_SERVICES_INSTANTIATION(mtsRobotIO1394);


#endif  //__mtsRobotIO1394_H__
