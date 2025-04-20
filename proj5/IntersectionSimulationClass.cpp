// File: IntersectionSimulationClass.cpp
// programmer: Yiwei Gui
// date: 4/20/2025
// purpose: The implementation of the IntersectionSimulationClass.

#include "IntersectionSimulationClass.h"

using namespace std;

void IntersectionSimulationClass::readParametersFromFile(
      const string &paramFname) {
    bool success = true;;
    ifstream paramF;

    paramF.open(paramFname.c_str());

    //Check that the file was able to be opened...
    if (paramF.fail()) {
        success = false;
        cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
    }
    else {
      //Now read in all the params, according to the specified format of
      //the text-based parameter file.
      if (success) {
          paramF >> randomSeedVal;
          if (paramF.fail() || randomSeedVal < 0) {
              success = false;
              cout << "ERROR: Unable to read/set random generator seed" << endl;
          }
      }

      if (success) {
          paramF >> timeToStopSim;
          if (paramF.fail() || timeToStopSim <= 0) {
              success = false;
              cout << "ERROR: Unable to read/set simulation end time" << endl;
          }
      }

      if (success) {
          paramF >> eastWestGreenTime >> eastWestYellowTime;
          if (paramF.fail() || eastWestGreenTime <= 0 || 
            eastWestYellowTime <= 0) {
              success = false;
              cout << "ERROR: Unable to read/set east-west times" << endl;
          }
      }

      if (success) {
          paramF >> northSouthGreenTime >> northSouthYellowTime;
          if (paramF.fail() || northSouthGreenTime <= 0 || 
            northSouthYellowTime <= 0) {
              success = false;
              cout << "ERROR: Unable to read/set north-south times" << endl;
          }
      }

      if (success) {
          paramF >> eastArrivalMean >> eastArrivalStdDev;
          if (paramF.fail() || eastArrivalMean <= 0 || eastArrivalStdDev < 0) {
              success = false;
              cout << "ERROR: Unable to read/set east arrival distribution" 
                   << endl;
          }
      }

      if (success) {
          paramF >> westArrivalMean >> westArrivalStdDev;
          if (paramF.fail() || westArrivalMean <= 0 || westArrivalStdDev < 0) {
              success = false;
              cout << "ERROR: Unable to read/set west arrival distribution" 
                   << endl;
          }
      }

      if (success) {
          paramF >> northArrivalMean >> northArrivalStdDev;
          if (paramF.fail() || northArrivalMean <= 0 || northArrivalStdDev < 0){
              success = false;
              cout << "ERROR: Unable to read/set north arrival distribution" 
                << endl;
          }
      }

      if (success) {
          paramF >> southArrivalMean >> southArrivalStdDev;
          if (paramF.fail() || southArrivalMean <= 0 || southArrivalStdDev < 0){
              success = false;
              cout << "ERROR: Unable to read/set south arrival distribution" 
                   << endl;
          }
      }

      if (success) {
          paramF >> percentCarsAdvanceOnYellow;
          if (paramF.fail() || percentCarsAdvanceOnYellow < 0 ||
              percentCarsAdvanceOnYellow > 100) {
              success = false;
              cout << "ERROR: Unable to read/set percentage yellow advance" 
                   << endl;
          }

          //Use the specified seed to seed the random number generator
          setSeed(randomSeedVal);
      }

      paramF.close();
    }

    //Let the caller know whether things went well or not by printing the
    if (!success) {
        cout << "ERROR: Parameter file was NOT read in successfully, so the " 
             << "simulation is NOT setup properly!" << endl;
        isSetupProperly = false;
    }
    else {
        cout << "Parameters read in successfully - simulation is ready!" 
             << endl;
        isSetupProperly = true;
    }
}

void IntersectionSimulationClass::printParameters() const {
    cout << "===== Begin Simulation Parameters =====" << endl;
    if (!isSetupProperly) {
        cout << "  Simulation is not yet properly setup!" << endl;
    }
    else {
        cout << "  Random generator seed: " << randomSeedVal << endl;
        cout << "  Simulation end time: " << timeToStopSim << endl;

        cout << "  East-West Timing -" <<
                " Green: " << eastWestGreenTime << 
                " Yellow: " << eastWestYellowTime <<
                " Red: " << getEastWestRedTime() << endl;

        cout << "  North-South Timing -" <<
                " Green: " << northSouthGreenTime << 
                " Yellow: " << northSouthYellowTime <<
                " Red: " << getNorthSouthRedTime() << endl;

        cout << "  Arrival Distributions:" << endl;
        cout << "    East - Mean: " << eastArrivalMean << 
                " StdDev: " << eastArrivalStdDev << endl;
        cout << "    West - Mean: " << westArrivalMean << 
                " StdDev: " << westArrivalStdDev << endl;
        cout << "    North - Mean: " << northArrivalMean << 
                " StdDev: " << northArrivalStdDev << endl;
        cout << "    South - Mean: " << southArrivalMean << 
                " StdDev: " << southArrivalStdDev << endl;

        cout << "  Percentage cars advancing through yellow: " <<
                percentCarsAdvanceOnYellow << endl;
    }
    cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(const string &travelDir) {
    // cout << "THIS FUNCTION NEEDS TO BE IMPLEMENTED" << endl;
    //This function should include a print statement for lines such as:
    //Time: 29 Scheduled [Event Type: West-Bound Arrival Time: 41]

    int arrivalTime = currentTime;
    double mean = 0.0, standardDev = 0.0;
    int eventType = 0;

    // East direction:
    if (travelDir == EAST_DIRECTION) {
        mean = eastArrivalMean;
        standardDev = eastArrivalStdDev;
        eventType = EVENT_ARRIVE_EAST;
    }

    // South direction:
    else if (travelDir == SOUTH_DIRECTION) {
        mean = southArrivalMean;
        standardDev = southArrivalStdDev;
        eventType = EVENT_ARRIVE_SOUTH;
    }

    // West direction:
    else if (travelDir == WEST_DIRECTION) {
        mean = westArrivalMean;
        standardDev = westArrivalStdDev;
        eventType = EVENT_ARRIVE_WEST;    
    }

    // North direction:
    else if (travelDir == NORTH_DIRECTION) {
        mean = northArrivalMean;
        standardDev = northArrivalStdDev;
        eventType = EVENT_ARRIVE_NORTH;
    }

    int timeIncrement = getPositiveNormal(mean, standardDev);
    arrivalTime += timeIncrement;

    EventClass newEvent(arrivalTime, eventType);
    eventList.insertValue(newEvent);
    
    cout << "Time: " << currentTime << " Scheduled " << newEvent << endl;

    // Over the simutime will not create event;
}

void IntersectionSimulationClass::scheduleLightChange() {
    // cout << "THIS FUNCTION NEEDS TO BE IMPLEMENTED" << endl;
    //This function should include a print statement for lines such as:
    //Time: 29 Scheduled [Event Type: Light Change to EW Green Time: 32]
    
    // My code is here:
    int eventTime = 0;
    EventClass singleEvent;

    switch (currentLight) {
    case LIGHT_GREEN_EW:
        eventTime  = currentTime + eastWestGreenTime;
        singleEvent = EventClass(eventTime, EVENT_CHANGE_YELLOW_EW);
        break;

    case LIGHT_YELLOW_EW:
        eventTime  = currentTime + eastWestYellowTime;
        singleEvent = EventClass(eventTime, EVENT_CHANGE_GREEN_NS);
        break;

    case LIGHT_GREEN_NS:
        eventTime  = currentTime + northSouthGreenTime;
        singleEvent = EventClass(eventTime, EVENT_CHANGE_YELLOW_NS);
        break;

    case LIGHT_YELLOW_NS:
        eventTime  = currentTime + northSouthYellowTime;
        singleEvent = EventClass(eventTime, EVENT_CHANGE_GREEN_EW);
        break;

    default:
        return;
    }

    eventList.insertValue(singleEvent);
    cout << "Time: " << currentTime << " Scheduled " << singleEvent << endl;
}

bool IntersectionSimulationClass::handleNextEvent(){
    // cout << "THIS FUNCTION NEEDS TO BE IMPLEMENTED" << endl;
    //This function is where most of your new code should go.
    //Any output observed in the sample output that is not
    //provided to you in posted source code i(or mentioned
    //above in the previous two functions) should be 
    //printed iduring this function's execution.

    // My code is here:
    // Check whether the list is empty or not;

    // if (eventList.getNumElems() == 0)
    // {
    //     return false;
    // }

    // Get the next event from the event list;
    EventClass nextEvent;
    eventList.removeFront(nextEvent);
    currentTime = nextEvent.getTimeOccurs();

    // Over the simutime, return F;
    // if (nextEvent.getTimeOccurs() >= timeToStopSim)
    // {
    //     cout << "Next event occurs AFTER the simulation end time (" 
    //          << nextEvent 
    //          << ")!" 
    //          << endl;
    //     return false;
    // }

    if (currentTime <= timeToStopSim) {
        cout << endl;
        cout << "Handling " << nextEvent << endl;
    

        // Deal with the car arrival event;
        if (nextEvent.getType() == EVENT_ARRIVE_EAST) {
            CarClass newCar(EAST_DIRECTION, currentTime);
            eastQueue.enqueue(newCar);

            // Renew the maximum length;
            if (eastQueue.getNumElems() > maxEastQueueLength) {
                maxEastQueueLength = eastQueue.getNumElems();
            }

            cout << "Time: " << currentTime << " Car id: " << newCar.getId() 
              << " Travel dir: " << EAST_DIRECTION << " Arrived at: "
              << currentTime << " - new queue length: " 
              << eastQueue.getNumElems() << endl;
            
            scheduleArrival(EAST_DIRECTION);

        }
        else if (nextEvent.getType() == EVENT_ARRIVE_SOUTH) {
            CarClass newCar(SOUTH_DIRECTION, currentTime);
            southQueue.enqueue(newCar);

            // Renew the maximum length;
            if (southQueue.getNumElems() > maxSouthQueueLength) {
                maxSouthQueueLength = southQueue.getNumElems();
            }

            cout << "Time: " << currentTime << " Car id: " << newCar.getId()
                << " Travel dir: " << SOUTH_DIRECTION << " Arrived at: "
                << currentTime << " - queue length: " 
                << southQueue.getNumElems() << endl;
            
            scheduleArrival(SOUTH_DIRECTION);

        }
        else if (nextEvent.getType() == EVENT_ARRIVE_WEST) {
            CarClass newCar(WEST_DIRECTION, currentTime);
            westQueue.enqueue(newCar);

            // Renew the maximum length;
            if (westQueue.getNumElems() > maxWestQueueLength) {
                maxWestQueueLength = westQueue.getNumElems();
            }

            cout << "Time: " << currentTime << " Car id: " << newCar.getId()
                << " Travel dir: " << WEST_DIRECTION << " Arrived at: "
                << currentTime  << " - new queue length: " 
                << westQueue.getNumElems() << endl;
            
            scheduleArrival(WEST_DIRECTION);

        }
        else if (nextEvent.getType() == EVENT_ARRIVE_NORTH) {
            CarClass newCar(NORTH_DIRECTION, currentTime);
            northQueue.enqueue(newCar);
            
            if (northQueue.getNumElems() > maxNorthQueueLength) {
                maxNorthQueueLength = northQueue.getNumElems();
            }
            
            cout << "Time: " << currentTime << " Car id: " << newCar.getId() 
                << " Travel dir: " << NORTH_DIRECTION << " Arrived at: " 
                << currentTime << " - queue length: " 
                << northQueue.getNumElems() << endl;
            
            scheduleArrival(NORTH_DIRECTION);
        }
        
        
        // Handling traffic light change events;
        else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
            currentLight = LIGHT_YELLOW_EW;

            cout << "Advancing cars on east-west green!" << endl;
            cout << "  East-bound queue length before advancing: "
              << eastQueue.getNumElems() << endl;
            cout << "  West-bound queue length before advancing: " 
              << westQueue.getNumElems() << endl;

            // Record the number of car;
            int numEast = 0, numWest = 0;

            // Remove car from East;
            for (int i = 0; i < eastWestGreenTime && 
                  eastQueue.getNumElems() > EMPTY_LIST; i++) {
                CarClass car;
                eastQueue.dequeue(car);
                numEast++; // Increase # of passing car;
                numTotalAdvancedEast++; // Increase # of whole passing car;

                cout << "  Car #" << car.getId()
                  << " advances east-bound on green" << endl;
            }

            if (eastQueue.getNumElems() == EMPTY_LIST && 
                numEast == EMPTY_LIST) {
                cout << "  No cars in east-bound queue waiting to advance!" 
                    << endl;
            }

            // Remove car from West;
            for (int j = 0; j < eastWestGreenTime && 
                  westQueue.getNumElems() > EMPTY_LIST; j++) {
                CarClass car;
                westQueue.dequeue(car);
                numWest++; // Increase # of passing car;
                numTotalAdvancedWest++; // Increase # of whole passing car;

                cout << "  Car #" << car.getId() 
                  << " advances west-bound on green" << endl;
            }

            if (westQueue.getNumElems() == EMPTY_LIST && 
                numWest == EMPTY_LIST) {
                cout << "  No cars in west-bound queue waiting to advance!" 
                    << endl;
            }

            cout << "  At time " << currentTime  << ", " << numEast 
              << " east-bound cars advanced on green,"
              << " remaining queue length: " << eastQueue.getNumElems() << endl;
            cout << "  At time " << currentTime << ", " << numWest 
              << " west-bound cars advanced on green,"
              << " remaining queue length: " << westQueue.getNumElems() << endl;

            scheduleLightChange();
        }


        else if (nextEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
            currentLight = LIGHT_YELLOW_NS;

            cout << "Advancing cars on north-south green" 
                << endl;
            cout << "  North-bound queue length before advancing: "
                << northQueue.getNumElems()
                << endl;
            cout << "  South-bound queue length before advancing: "
                << southQueue.getNumElems()
                << endl;

            int numNorth = 0, numSouth = 0;

            for (int i = 0; i < northSouthGreenTime &&
                  northQueue.getNumElems() > EMPTY_LIST; i++) {
                CarClass car;
                northQueue.dequeue(car);
                numNorth++;
                numTotalAdvancedNorth++;

                cout << "  Car #" << car.getId() 
                  << " advances north-bound on green" << endl;
            }

            if (northQueue.getNumElems() == EMPTY_LIST && 
              numNorth == EMPTY_LIST) {
                cout << "  No cars in north-bound queue waiting to advance!"
                    << endl;
            }

            // Remove car from South;
            for (int j = 0; j < northSouthGreenTime &&
                  southQueue.getNumElems() > EMPTY_LIST; j++) {
                CarClass car;
                southQueue.dequeue(car);
                // Increasing the passing car;
                numSouth++;
                numTotalAdvancedSouth++;

                cout << "  Car #"
                    << car.getId()
                    << " advances south-bound on green"
                    << endl;
            }

            if (southQueue.getNumElems() == 0 && numSouth == 0) {
                cout << "  No cars in south-bound queue waiting to advance!"
                    << endl;
            }

            cout << "  At time "
                << currentTime
                << ", "
                << numNorth
                << " north-bound cars advanced on green,"
                << " remaining queue length: "
                << northQueue.getNumElems()
                << endl;
            cout << "  At time "
                << currentTime
                << ", "
                << numSouth
                << " south-bound cars advanced on green,"
                << " remaining queue length: "
                << southQueue.getNumElems()
                << endl;
        
            scheduleLightChange();
        }


        else if (nextEvent.getType() == EVENT_CHANGE_GREEN_NS) {
            currentLight = LIGHT_GREEN_NS;

            cout << "Advancing cars on east-west yellow" 
                << endl;

            cout << "  East-bound queue length before advancing: " 
                << eastQueue.getNumElems() 
                << endl;
            cout << "  West-bound queue length before advancing: " 
                << westQueue.getNumElems() 
                << endl;

            int numEast = 0, numWest = 0;
            // Mark whether to stop eastbound vehicles;
            bool stopEast = false;

            while (eastQueue.getNumElems() > EMPTY_LIST &&
                numEast < eastWestYellowTime && !stopEast) {
                // if (numEast == 0)
                // {
                //     cout << "  Next car will advance east-bound on yellow"
                //          << endl;
                // }

                int random = getUniform(RANDOM_MIN, RANDOM_MAX);
                if (random > percentCarsAdvanceOnYellow) {
                    cout << "  Next car will NOT advance east-bound on yellow" 
                        << endl;
                    stopEast = true;
                }
                else {
                    if (numEast == EMPTY_LIST) {
                        cout << "  Next car will advance east-bound on yellow"
                            << endl;
                    }

                    CarClass car;
                    eastQueue.dequeue(car);
                    numEast++;
                    numTotalAdvancedEast++;
                    
                    cout << "  Car #" 
                            << car.getId() 
                            << " advances east-bound on yellow" 
                            << endl;
                    if (eastQueue.getNumElems() > EMPTY_LIST && 
                        numEast < eastWestYellowTime) {
                        cout << "  Next car will advance east-bound on yellow" 
                        << endl;
                    }
                }
            }

            if (eastQueue.getNumElems() == 0 && numEast == 0) {
                cout << "  No cars in east-bound queue waiting to advance!" 
                << endl;
            }


            bool stopWest = false;

            while (westQueue.getNumElems() > EMPTY_LIST &&
                numWest < eastWestYellowTime && !stopWest) {
                // if (numWest == 0)
                // {
                //     cout << "  Next car will advance west-bound on yellow"
                //          << endl;
                // }
                int random = getUniform(RANDOM_MIN, RANDOM_MAX);

                if (random > percentCarsAdvanceOnYellow) {
                    cout << "  Next car will NOT advance west-bound on yellow" 
                        << endl;
                    stopWest = true;
                }
                else {
                    if (numWest == EMPTY_LIST){
                        cout << "  Next car will advance west-bound on yellow"
                            << endl;
                    }
                    CarClass car;
                    westQueue.dequeue(car);
                    numWest++;
                    numTotalAdvancedWest++;
                    
                    cout << "  Car #" 
                            << car.getId() 
                            << " advances west-bound on yellow" 
                            << endl;

                    if (westQueue.getNumElems() > EMPTY_LIST && 
                        numWest < eastWestYellowTime) {
                        cout << "  Next car will advance west-bound on yellow" 
                             << endl;
                    }
                }
            }
            
            if (westQueue.getNumElems() == EMPTY_LIST && numWest == EMPTY_LIST){
                cout << "  No cars in west-bound queue waiting to advance!" 
                    << endl;
            }

            cout << "  At time "
                << currentTime
                << ", "
                << numEast
                << " east-bound cars advanced on yellow,"
                << " remaining queue length: "
                << eastQueue.getNumElems()
                << endl;
            cout << "  At time "
                << currentTime
                << ", "
                << numWest
                << " west-bound cars advanced on yellow,"
                << " remaining queue length: "
                << westQueue.getNumElems()
                << endl;

            scheduleLightChange();
        }

        
        else if (nextEvent.getType() == EVENT_CHANGE_GREEN_EW) {
            currentLight = LIGHT_GREEN_EW;

            cout << "Advancing cars on north-south yellow" << endl;
            cout << "  North-bound queue length before advancing: " 
              << northQueue.getNumElems() << endl;
            cout << "  South-bound queue length before advancing: " 
              << southQueue.getNumElems() << endl;

            int numNorth = 0, numSouth = 0;
            // Mark whether to stop northbound vehicles;
            bool stopNorth = false;

            while (northQueue.getNumElems() > EMPTY_LIST &&
                numNorth < northSouthYellowTime && !stopNorth) {
                // if (numNorth == 0)
                // {
                //     cout << "  Next car will advance north-bound on yellow"
                //          << endl;
                // }

                int random = getUniform(RANDOM_MIN, RANDOM_MAX);
                if (random > percentCarsAdvanceOnYellow) {
                    cout << "  Next car will NOT advance north-bound on yellow" 
                        << endl;
                    stopNorth = true;
                }
                else {
                    if (numNorth == EMPTY_LIST) {
                        cout << "  Next car will advance north-bound on yellow"
                             << endl;
                    }
                    CarClass car;
                    northQueue.dequeue(car);
                    numNorth++;
                    numTotalAdvancedNorth++;
                    
                    cout << "  Car #" 
                            << car.getId() 
                            << " advances north-bound on yellow" 
                            << endl;
                    if (northQueue.getNumElems() > EMPTY_LIST && 
                        numNorth < northSouthYellowTime) {
                        cout << "  Next car will advance north-bound on yellow" 
                             << endl;
                    }
                }
            }

            if (northQueue.getNumElems() == EMPTY_LIST && 
                numNorth == EMPTY_LIST) {
                cout << "  No cars in north-bound queue waiting to advance!" 
                    << endl;
            }

            // Mark whether to stop southbound vehicles;
            bool stopSouth = false;

            while (southQueue.getNumElems() > EMPTY_LIST &&
                numSouth < northSouthYellowTime && !stopSouth) {
                // if (numSouth == 0)
                // {
                //     cout << "  Next car will advance south-bound on yellow"
                //          << endl;
                // }

                int random = getUniform(RANDOM_MIN, RANDOM_MAX);
                if (random > percentCarsAdvanceOnYellow) {
                    cout << "  Next car will NOT advance south-bound on yellow" 
                        << endl;
                    stopSouth = true;
                }
                else {
                    if (numSouth == EMPTY_LIST) {
                        cout << "  Next car will advance south-bound on yellow"
                             << endl;
                    }
                    CarClass car;
                    southQueue.dequeue(car);
                    numSouth++;
                    numTotalAdvancedSouth++;
                    
                    cout << "  Car #" 
                            << car.getId() 
                            << " advances south-bound on yellow" 
                            << endl;
                    if (southQueue.getNumElems() > EMPTY_LIST && 
                        numSouth < northSouthYellowTime) {
                        cout << "  Next car will advance south-bound on yellow" 
                             << endl;
                    }
                }
            }

            if (southQueue.getNumElems() == EMPTY_LIST && 
              numSouth == EMPTY_LIST) {
                cout << "  No cars in south-bound queue waiting to advance!" 
                    << endl;
            }

            cout << "  At time "
                << currentTime
                << ", "
                << numNorth
                << " north-bound cars advanced on yellow,"
                << " remaining queue length: "
                << northQueue.getNumElems() 
                << endl;
            cout << "  At time "
                << currentTime
                << ", "
                << numSouth
                << " south-bound cars advanced on yellow,"
                << " remaining queue length: "
                << southQueue.getNumElems()
                << endl;

            scheduleLightChange();

        }
        return true;
    }
    
    cout << endl;
    cout << "Next event occurs AFTER the simulation end time "
         << "("
         << nextEvent
         << ")!"
         << endl;
    return false;

}

void IntersectionSimulationClass::printStatistics() const {
    cout << "===== Begin Simulation Statistics =====" << endl;
    cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
    cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
    cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
    cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
    cout << "  Total cars advanced east-bound: " <<
            numTotalAdvancedEast << endl;
    cout << "  Total cars advanced west-bound: " <<
            numTotalAdvancedWest << endl;
    cout << "  Total cars advanced north-bound: " <<
            numTotalAdvancedNorth << endl;
    cout << "  Total cars advanced south-bound: " <<
            numTotalAdvancedSouth << endl;
    cout << "===== End Simulation Statistics =====" << endl;
}
