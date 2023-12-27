#include <vector>
#include <ctime>
using namespace std;

enum VehicleType {TRUCK , CAR , BIKE};

class Ticket{
    private:
        Vehicle vehicle;
        Slot slot;
        int startTime;
        int endTime;
        bool isPaid;
    public:
        Ticket(){}
        Ticket (Slot s,Vehicle v)
        {
            isPaid = false;
            slot = s;
            vehicle = v;
            // Scope to improve on how to get the current time
            startTime = time(NULL);
        }
        void markTicketAsPaid()
        {
            isPaid = true;
        }
        void markEndTime()
        {   
            // Scope to improve on how to get the current time
            endTime = time(NULL);
        }
};

class Vehicle{
    private:
        Ticket ticket;
        VehicleType vehicleType;
    public:
        Vehicle(){}
        Vehicle(VehicleType vt)
        {
            vehicleType = vt;
        }
        void attachTicketToVehicle(Ticket ticket)
        {
            this->ticket = ticket;
        }
};

class Slot{
    private:
        Floor floor;
        VehicleType vehicleType;
        bool isOccupied;
        int slotId;
        // double hourlyRate; think about adding this feature when adding payments to parking lot
    public:
        Slot(){}
        Slot(Floor floor, VehicleType vehicleType, int slotId)
        {
            this->floor = floor;
            this->vehicleType = vehicleType;
            this->slotId  = slotId;
            isOccupied = false;
        }
        bool isSlotOccupied(){
            return isOccupied;
        }
};


class Floor{
    private:
        vector<Slot> slots;
        EntranceGate entranceGate;
        ExitGate exitGate;
        int floorId;
    public:
        Floor(){}
        vector<Slot> getFreeSlotsForVehicleOnFloor(Vehicle vehicle) {}
        Slot addSlotForVehicleType(VehicleType vehicleType) {}
};

class EntranceGate{
    private:
        Floor floor;
    public:
        EntranceGate(){}
        EntranceGate(Floor floor)
        {
            this->floor = floor;
        }
        Ticket createParkingTicket(Vehicle vehicle){}
};

class ExitGate{
    private:
        Floor floor;
    public:
        ExitGate(){}
        ExitGate(Floor floor)
        {
            this->floor = floor;
        }
        void unparkVehicle(Vehicle vehicle){}
};

// Used singleton design pattern to ensure that always only one ParkingLotService exists
class ParkingLotSerivce{
    private:
        vector<Floor> floors;
        static ParkingLotSerivce* instance; // NOTE only for pointers it is possible to have initial value NULL in CPP (unlike in Python)
        ParkingLotSerivce() {}
    public:
        static ParkingLotSerivce* getParkingLotInstance()
        {
            if(instance == NULL)
            {
                instance = new ParkingLotSerivce();
            }
            return instance;
        }
        Floor addFloor(){}
        Slot getFreeParkingSlotForVehicle(Vehicle vehicle){}
        void parkVehicle(Vehicle vehicle){}
        void unparkVehicle(Vehicle vehicle){}
};

// TODO Add startegy object which will decide on how to pick the first empty parking slot for a vehicle.