#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class Vehicles: represents buses or trains
class Vehicles {
    protected:
        string route;     // Route name
        int capacity;     // Maximum passenger capacity
        bool status;      // Operating status (true = on-time, false = full)

    public:
        // Constructor: initialize route, capacity, status
        Vehicles(string _route, int _capacity, bool _status): route(_route), capacity(_capacity), status(_status) {}

        // Getter functions
        string getRoute() { return route; }
        int getCapacity() { return capacity; }
        bool getStatus() { return status; }

        // Setter functions
        void setRoute(string _route) { route = _route; }
        void setCapacity(int _capacity) { capacity = _capacity; }
        void setStatus(bool _status) { status = _status; }

        // Calculate travel time (hours) with bus speed = 50 km/h
        virtual double calculateTravelTime(double distance) {
            return distance / 50;
        }
};

// Class ExpressBus: inherits from Vehicles, represents express buses
class ExpressBus : public Vehicles {
    private:
        double speed;  // Speed of the express bus

    public:
        // Constructor: initialize speed, route, capacity, status (calls base constructor)
        ExpressBus(double _speed, string _route, int _capacity, bool _status): speed(_speed), Vehicles(_route, _capacity, _status) {}

        // Override travel time calculation using express bus speed
        double calculateTravelTime(double distance) override {
            return distance / speed;
        }
};

// Class Schedule: represents the schedule of a bus or train
class Schedule {
    private:
        string route;       // Route name
        string timeArrival; // Arrival time at a station

    public:
        // Constructor
        Schedule(string _route, string _timeArrival) : route(_route), timeArrival(_timeArrival) {}

        // Getter functions
        string getRoute() { return route; }
        string getTimeArrival() { return timeArrival; }

        // Setter functions
        void setRoute(string _route) { route = _route; }
        void setTimeArrival(string _timeArrival) { timeArrival = _timeArrival; }
};

// Class Schedule_ExpressBus: Represents the schedule of an express bus
class Schedule_ExpressBus {
    private:
        string route; // Name of the route the express bus serves
        string timeArrival; // Arrival time of the express bus at a station

    public:
        // Constructor: initialize route and arrival time
        Schedule_ExpressBus(string _route, string _timeArrival): route(_route), timeArrival(_timeArrival) {}

        // Getter functions
        string getRoute() { return route; }
        string getTimeArrival() { return timeArrival; }

        // Setter functions
        void setRoute(string _route) { route = _route; }
        void setTimeArrival(string _timeArrival) { timeArrival = _timeArrival; }
};

// Class Station: represents a bus stop or an MRT station
class Station {
    private:
        string name; // Station name
        string location; // Station location
        string type; // Station type (Bus or Train)
        vector<Schedule> scheduledArrivals; // Arrival schedules for buses/trains
        vector<Schedule_ExpressBus> scheduledArrivals_ExpressBus; // Arrival schedules for express buses

    public:
        // Constructor: initialize name, location, type, and schedules for buses/trains
        Station(string _name, string _location, string _type, vector<Schedule> _scheduledArrivals)
        : name(_name), location(_location), type(_type), scheduledArrivals(_scheduledArrivals) {}

        // Constructor: initialize name, location, type, schedules for buses/trains, and express buses
        Station(string _name, string _location, string _type, vector<Schedule> _scheduledArrivals, vector<Schedule_ExpressBus> _scheduledArrivals_ExpressBus)
        : name(_name), location(_location), type(_type), scheduledArrivals(_scheduledArrivals), scheduledArrivals_ExpressBus(_scheduledArrivals_ExpressBus) {}

        // Getter functions
        string getName() { return name; }
        string getLocation() { return location; }
        string getType() { return type; }
        vector<Schedule> getScheduledArrivals() { return scheduledArrivals; }
        vector<Schedule_ExpressBus> getScheduledArrivals_ExpressBus() {
            return scheduledArrivals_ExpressBus;
        }

        // Setter functions
        void setName(string _name) { name = _name; }
        void setLocation(string _location) { location = _location; }
        void setType(string _type) { type = _type; }
        void setScheduledArrivals(vector<Schedule> _scheduledArrivals) {
            scheduledArrivals = _scheduledArrivals;
        }
        void setScheduledArrivals_ExpressBus(
            vector<Schedule_ExpressBus> _scheduledArrivals_ExpressBus) {
            scheduledArrivals_ExpressBus = _scheduledArrivals_ExpressBus;
        }

        // Function to add a new route to the current station
        void addRoute(bool isBus, vector<pair<Station, double>> &allStations) {
            cout << "ADD NEW ROUTE:\n";

            int choice;
            // If it’s a bus, ask for the bus type
            if (isBus) {
                cout << "Choose bus type:\n";
                cout << "1. Bus\n";
                cout << "2. Express Bus\n";
                cout << "Choose: ";
                cin >> choice;
                // Validate the entered value
                if (choice < 1 || choice > 2) {
                    cout << "Invalid\n";
                    return; // Exit the function if not valid
                }
            }

            // Input the route name
            cout << "Input route name: ";
            cin.ignore(); // Clear the remaining '\n' in the buffer
            string route;
            getline(cin, route);

            // Input arrival time at the current station
            cout << "Input arrival time: ";
            cin.ignore(); // Clear any previous '\n'
            string timeArrival;
            cin >> timeArrival;

            // Notify success after entering information
            cout << "Add new route successful!\n";
            cout << "========================\n";
            cout << "Route: " << route << endl;
            cout << "Station list of " << route << ":\n";

            // Save route info into the appropriate list
            if (isBus) {
                // For regular bus
                if (choice == 1) scheduledArrivals.emplace_back(route, timeArrival);
                // For express bus
                else scheduledArrivals_ExpressBus.emplace_back(route, timeArrival);
            } else { 
                // For trains
                scheduledArrivals.emplace_back(route, timeArrival);
            }

            // Iterate over all stations to find stations belonging to the added route
            for (auto p : allStations) {
                Station s = p.first; // Extract Station object from allStations
                // Print the station name and arrival time for each case
                if (choice == 1 || !isBus) { // Bus or train case
                    for (auto sc : s.getScheduledArrivals()) {
                        if (sc.getRoute() == route) {
                            cout << "Station: " << s.getName() << endl;
                            cout << "Arrival Time: " << sc.getTimeArrival() << endl;
                            cout << endl;
                        }
                    }
                } else if (choice == 2) { // Express bus case
                    for (auto sc : s.getScheduledArrivals_ExpressBus()) {
                        if (sc.getRoute() == route) {
                            cout << "Station: " << s.getName() << endl;
                            cout << "Arrival Time: " << sc.getTimeArrival() << endl;
                            cout << endl;
                        }
                    }
                }
            }
        }
};

// Class Ticket: represents a ticket purchased by a passenger
class Ticket {
    private:
        string routeName; // Name of the bus/train route
        string type; // Type of vehicle
        string firstStop; // Departure station
        string finalStop; // Destination station
        string departureTime; // Departure time
        string arrivalTime; // Arrival time
        double timeTravel; // Travel duration (unit: hours)

    public:
        // Constructor: create a ticket with full trip information
        Ticket(string _routeName, string _type, string _firstStop, string _finalStop, string _departureTime, string _arrivalTime, double _timeTravel)
        : routeName(_routeName), type(_type), firstStop(_firstStop), finalStop(_finalStop), departureTime(_departureTime), arrivalTime(_arrivalTime), timeTravel(_timeTravel) {}

        // Getter functions
        string getRouteName() { return routeName; }
        string getType() { return type; }
        string getFirstStop() { return firstStop; }
        string getFinalStop() { return finalStop; }
        string getDepartureTime() { return departureTime; }
        string getArrivalTime() { return arrivalTime; }

        // Setter functions
        void setRouteName(string _routeName) { routeName = _routeName; }
        void setType(string _type) { type = _type; }
        void setFirstStop(string _firstStop) { firstStop = _firstStop; }
        void setFinalStop(string _finalStop) { finalStop = _finalStop; }
        void setDepartureTime(string _departureTime) { departureTime = _departureTime; }
        void setArrivalTime(string _arrivalTime) { arrivalTime = _arrivalTime; }

        // Display ticket information
        // Print all trip details on the screen, converting travel time to minutes
        void displayTicketInfo() {
            cout << "     TICKET INFO:\n";
            cout << "Route: " << routeName << endl;
            cout << "Type: " << type << endl;
            cout << "First Stop: " << firstStop << endl;
            cout << "Final Stop: " << finalStop << endl;
            cout << "Departure Time: " << departureTime << endl;
            cout << "Arrival Time: " << arrivalTime << endl;
            cout << "Travel Time: " << timeTravel * 60 << " minutes" << endl;
        }
};

// Class Passengers: represents a passenger
class Passengers {
    private:
        string name; // Passenger's full name
        string ID; // Passenger's ID
        int balance; // Passenger's account balance
        vector<Ticket> bookedTickets; // List of tickets the passenger has booked

    public:
        // Constructor: initialize name, ID, and the list of booked tickets
        Passengers(string _name, string _ID, vector<Ticket> _bookedTickets)
        : name(_name), ID(_ID), bookedTickets(_bookedTickets) {}

        // Getter functions
        string getName() { return name; }
        string getID() { return ID; }
        vector<Ticket> getBookedTickets() { return bookedTickets; }

        // Setter functions
        void setName(string _name) { name = _name; }
        void setID(string _ID) { ID = _ID; }
        void setBookedTickets(vector<Ticket> _bookedTickets) {bookedTickets = _bookedTickets;}

        // Display the passenger's information (name and ID)
        void displayInfo() {
            cout << "Name: " << name << endl;
            cout << "ID: " << ID << endl;
        }

        // Function to deposit money into the account
        void deposit() {
            cout << "Balance: " << balance << endl; // Show current balance

            // Enter the amount to deposit
            cout << "Input money you want to deposit: ";
            int money;
            cin >> money;

            // Validate the entered amount
            if (money >= 0) {
                cout << "Deposit successful\n"; // Notify successful deposit
                balance += money; // Add to balance
                cout << "Balance: " << balance << endl; // Show updated balance
            } else cout << "Invalid\n"; // Show error if amount is not valid
        }

        // Display the passenger's ticket booking history
        void displayBookedTickets() {
            cout << "TICKET BOOKING HISTORY\n\n";
            for (int i = 0; i < bookedTickets.size(); i++) {
                cout << "Ticket " << i + 1 << ":\n";
                bookedTickets[i].displayTicketInfo();
                cout << endl;
            }
        }

        // Function that allows a passenger to book a ticket
        void bookTicket(vector<Vehicles> allVehicles, vector<ExpressBus> allExpressBus, vector<pair<Station, double>> allStations) {
            cout << "BOOK TICKET \n";

            // Choose a route
            cout << "Choose routes:\n";
            for (int i = 0; i < allVehicles.size(); i++) {
                cout << i + 1 << ". " << allVehicles[i].getRoute() << " " << endl;
            }
            cout << "Choose: ";
            int n1;
            cin >> n1;
            if (n1 <= 0 || n1 > allVehicles.size()) { // Validate input
                cout << "Invalid\n";
                return;
            }
            cout << endl;
            string chooseRoute = allVehicles[n1 - 1].getRoute(); // Save the selected route name

            // Determine the type of vehicle
            int m;
            vector<Station> availableStation; // List of stations on the route
            string vehicleType;
            int chooseIdx = 0; // Index of the corresponding Express Bus

            // If the route is for Bus or Express Bus
            if (allVehicles[n1 - 1].getRoute().find("(MRT)") == -1) {
                int maxOption = 1;
                cout << "Choose type of bus:\n";
                cout << "1. Bus ";
                // Show the vehicle's status
                if (allVehicles[n1 - 1].getStatus()) cout << "(On-time)\n";
                else cout << "(Full)\n";

                // Check if there is an Express Bus on this route
                for (int i = 0; i < allExpressBus.size(); i++) {
                    if (allExpressBus[i].getRoute() == chooseRoute) {
                        maxOption = 2;
                        chooseIdx = i;

                        cout << "2. Express Bus ";
                        // Show the vehicle's status
                        if (allExpressBus[i].getStatus()) cout << "(On-time)\n";
                        else cout << "(Full)\n";
                        break;
                    }
                }

                cout << "Choose: ";
                cin >> m;
                cout << endl;

                // If the user selects Bus
                if (m == 1) {
                    if (allVehicles[n1 - 1].getStatus()) {
                        vehicleType = "Bus";
                        // Get the list of stations that serve this route
                        for (int i = 0; i < allStations.size(); i++) {
                            vector<Schedule> arrivals =
                                allStations[i].first.getScheduledArrivals();
                            for (auto &a : arrivals) {
                                if (a.getRoute() == chooseRoute) {
                                    availableStation.push_back(allStations[i].first);
                                    break;
                                }
                            }
                        }
                    } else {
                        // Case when the bus is full
                        cout << "The bus is full\n";
                        return;
                    }

                // If the user selects Express Bus
                } else if (m == 2 && m == maxOption) {
                    if (allExpressBus[chooseIdx].getStatus()) {
                        vehicleType = "Express Bus";
                        // Get the list of stations that serve this route
                        for (int i = 0; i < allStations.size(); i++) {
                            vector<Schedule_ExpressBus> arrivals =
                                allStations[i].first.getScheduledArrivals_ExpressBus();
                            for (auto &a : arrivals) {
                                if (a.getRoute() == chooseRoute) {
                                    availableStation.push_back(allStations[i].first);
                                    break;
                                }
                            }
                        }
                    } else {
                        // Case when the express bus is full
                        cout << "The express bus is full\n";
                        return;
                    }

                } else { // Invalid selection
                    cout << "Invalid\n";
                    return;
                }
            }
            // If the user selects MRT
            else {
                vehicleType = "Train";
                for (int i = 0; i < allStations.size(); i++) {
                    vector<Schedule> arrivals = allStations[i].first.getScheduledArrivals();
                    for (auto &a : arrivals) {
                        if (a.getRoute() == chooseRoute) {
                            availableStation.push_back(allStations[i].first);
                            break;
                        }
                    }
                }
            }

            // Choose the departure station
            vector<string> timeList;
            cout << "Choose first stop:\n";
            for (int i = 0; i < availableStation.size() - 1; i++) {
                // Display station
                cout << i + 1 << ". " << availableStation[i].getName();

                // Print arrival time at the station for Bus or MRT
                if (vehicleType == "Bus" || vehicleType == "Train") {
                    vector<Schedule> arrivals = availableStation[i].getScheduledArrivals();
                    for (auto &a : arrivals) {
                        if (a.getRoute() == chooseRoute) {
                            cout << "  Arrival Time: " << a.getTimeArrival() << endl;
                            timeList.push_back(a.getTimeArrival());
                            break;
                        }
                    }
                } else { // For Express Bus
                    vector<Schedule_ExpressBus> arrivalsExp =
                        availableStation[i].getScheduledArrivals_ExpressBus();
                    for (auto &a : arrivalsExp) {
                        if (a.getRoute() == chooseRoute) {
                            cout << "  Arrival Time: " << a.getTimeArrival() << endl;
                            timeList.push_back(a.getTimeArrival());
                            break;
                        }
                    }
                }
            }

            cout << "Choose: ";
            int k1;
            cin >> k1;
            cout << endl;
            if (k1 <= 0 || k1 > availableStation.size()) { // Validate the choice
                cout << "Invalid\n";
                return;
            }
            string firstStop = availableStation[k1 - 1].getName(); // Departure station name
            string departureTime = timeList[k1 - 1];               // Departure time

            // List of arrival times corresponding to available destination stops
            vector<string> finalTimes;

            cout << "Choose final stop:\n"; // Display the list of destination stops

            // Iterate over stops after the departure stop (k1) to the end of the route
            for (int i = k1; i < availableStation.size(); i++) {
                // Print the index and stop name
                cout << i - k1 + 1 << ". " << availableStation[i].getName();

                // If the vehicle is a Bus or MRT, get the arrival time from the regular schedule
                if (vehicleType == "Bus" || vehicleType == "Train") {
                    for (auto &a : availableStation[i].getScheduledArrivals()) {
                        if (a.getRoute() == chooseRoute) {
                            cout << "  Arrival Time: " << a.getTimeArrival() << '\n';
                            finalTimes.push_back(a.getTimeArrival());   // Save the arrival time
                            break;
                        }
                    }
                } else {
                    // Otherwise, if the vehicle is an Express Bus, get the time from the express schedule
                    for (auto &a : availableStation[i].getScheduledArrivals_ExpressBus()) {
                        if (a.getRoute() == chooseRoute) {
                            cout << "  Arrival Time: " << a.getTimeArrival() << '\n';
                            finalTimes.push_back(a.getTimeArrival());
                            break;
                        }
                    }
                }
            }

            cout << "Choose: ";
            int k2;
            cin >> k2; // Enter the destination stop selection
            cin.ignore();

            // Validate the user's choice
            if (k2 <= 0 || k2 > finalTimes.size()) {
                cout << "Invalid\n";
                return;
            }
            cout << "Booking ticket sucessful!\n\n";

            // Save the destination stop name & corresponding arrival time
            string finalStop  = availableStation[k1 - 1 + k2].getName();
            string arrivalTime = finalTimes[k2 - 1];

            // Calculate the distance between the two stops
            int startIdx = 0, endIdx = 0;
            int n = allStations.size();

            // Find the position of the departure stop in the full station list
            for (int i = 0; i < n; i++) {
                if (allStations[i].first.getName() == firstStop) {
                    startIdx = i;
                    break;
                }
            }
            // Find the position of the destination stop (iterate backward to ensure the correct one)
            for (int i = n - 1; i >= 0; i--) {
                if (allStations[i].first.getName() == finalStop) {
                    endIdx = i;
                    break;
                }
            }

            // Compute the total distance between the two stops
            double distance = 0;
            for (int i = startIdx; i < endIdx; i++) {
                distance += allStations[i].second;
            }

            // Calculate the expected travel time
            double timeTravel;
            if (vehicleType == "Bus" || vehicleType == "Train") timeTravel = allVehicles[n1 - 1].calculateTravelTime(distance);
            else timeTravel = allExpressBus[chooseIdx].calculateTravelTime(distance);

            // Create, display & save the ticket
            Ticket newTicket(chooseRoute, vehicleType, firstStop, finalStop, departureTime, arrivalTime, timeTravel);

            // Display the ticket information to the user
            newTicket.displayTicketInfo();

            // Save the ticket into the passenger's booked ticket list
            bookedTickets.push_back(newTicket);
        }

        // Function to cancel a booked ticket
        void cancelTicket() {
            displayBookedTickets(); // Display all booked tickets so the user can choose
            cout << "Choose ticket to cancel:\n";
            cout << "Choose: ";
            int n;
            cin >> n;

            // Check if the chosen ticket number is valid
            if (n > 0 && n <= bookedTickets.size()) {
                cout << "Delete successful!\n";  // Notify that the ticket was successfully canceled
                displayBookedTickets();          // Display the list of tickets again after deletion
            } else cout << "Invalid\n"; // Show an error if the choice is not valid
        }
};

int main() {
    // Initialize initial data
    vector<Vehicles> allVehicles; // List of buses and trains
    vector<ExpressBus> allExpressBus; // List of express buses
    vector<pair<Station, double>> allStations; // List of stations and the distance to the next station (km)

    // Initialize vehicle/train routes
    // MRT route
    allVehicles.emplace_back("MRT Line 1 (MRT)", 200, true);

    // Bus A route (also has express bus)
    allVehicles.emplace_back("Bus A", 50, true);
    allExpressBus.emplace_back(80, "Bus A", 40, true);

    // Bus B route
    allVehicles.emplace_back("Bus B", 50, true);

    // Bus C route
    allVehicles.emplace_back("Bus C", 50, false);

    // Create the list of stations
    // 4 MRT stations
    Station s1("Central MRT", "Zone 1", "MRT", { Schedule("MRT Line 1 (MRT)", "08:00") });
    Station s2("North MRT",   "Zone 2", "MRT", { Schedule("MRT Line 1 (MRT)", "08:10") });
    Station s3("East MRT",    "Zone 3", "MRT", { Schedule("MRT Line 1 (MRT)", "08:20") });
    Station s4("South MRT",   "Zone 4", "MRT", { Schedule("MRT Line 1 (MRT)", "08:30") });

    // 7 bus stations (some are served by express buses)
    Station s5("City Center", "Zone 1", "Bus",
    { Schedule("Bus A","08:05"), Schedule("Bus B","08:15"), Schedule("Bus C","08:25") },
    { Schedule_ExpressBus("Bus A","08:05") });

    Station s6("Green Park", "Zone 1", "Bus",
    { Schedule("Bus A","08:12"), Schedule("Bus B","08:2") });  

    Station s7("Airport", "Zone 2", "Bus",
    { Schedule("Bus A","08:20"), Schedule("Bus C","08:40") },
    { Schedule_ExpressBus("Bus A","08:14") });

    Station s8("University", "Zone 2", "Bus",
    { Schedule("Bus B","08:28"), Schedule("Bus C","08:50") }); 

    Station s9("Old Town", "Zone 3", "Bus",
    { Schedule("Bus A","08:30"), Schedule("Bus B","08:35") },
    { Schedule_ExpressBus("Bus A","08:20") });

    Station s10("Stadium", "Zone 3", "Bus",
    { Schedule("Bus B","08:42"), Schedule("Bus C","09:00") }); // No express bus

    Station s11("Harbor", "Zone 4", "Bus",
    { Schedule("Bus A","08:50"), Schedule("Bus C","09:10") },
    { Schedule_ExpressBus("Bus A","08:33") });

    // Add stations to allStations with the distance to the next station (km)
    // For MRT
    allStations.push_back({s1, 8.33});
    allStations.push_back({s2, 8.33});
    allStations.push_back({s3, 8.33});
    allStations.push_back({s4, 0});

    // For Bus & Express Bus
    allStations.push_back({s5, 5.8});
    allStations.push_back({s6, 6.7});
    allStations.push_back({s7, 8.3});
    allStations.push_back({s8, 0});
    allStations.push_back({s9, 16.7});
    allStations.push_back({s10,0});
    allStations.push_back({s11,0});

    // Menu to choose user role
    cout << "Choose your role:\n";
    cout << "1. Passenger\n";
    cout << "2. Administrator\n";
    cout << "Choose: ";
    int n; cin >> n;
    cout << "===================\n";

    // If user is a passenger
    if (n == 1) {
        // Create a sample passenger (name, ID, no booked tickets)
        Passengers p("Nguyen Khanh Hung", "P001", {});
        p.displayInfo(); // Display passenger information
        cout << endl;

        // Passenger menu
        cout << "Choose function:\n";
        cout << "1. View ticket booking history\n";
        cout << "2. Book ticket\n";
        cout << "3. Cancel ticket\n";
        cout << "4. Deposit\n";
        cout << "Choose: ";
        int m; cin >> m;
        cout << "=================================\n";

        switch(m) {
            case 1: // View booked ticket history
                p.displayBookedTickets();
                break;

            case 2: // Book a new ticket
                p.bookTicket(allVehicles, allExpressBus, allStations);
                break;

            case 3: // Cancel a booked ticket
                p.cancelTicket();
                break;

            case 4: // Deposit money into account
                p.deposit();
                break;

            default:
                // Invalid choice
                cout << "Invalid\n";
                break;
        }
    }
    // If user is an administrator
    else if (n == 2) {
        cout << "Choose function:\n";
        cout << "1. Add route\n";
        cout << "Choose: ";
        int m; cin >> m;

        if (m == 1) {
            // Choose the type of vehicle to add a route for
            cout << "Choose vehicle type:\n";
            cout << "1. Bus\n";
            cout << "2. Train\n";
            cout << "Choose: ";
            int k; cin >> k;

            // Adding a route for Bus
            if (k == 1) {
                bool isBus = true;
                bool firstStation = false;
                int startIdx;
                int numberOfBusStation = 0;

                // Display list of bus stations
                cout << "Choose station:\n";
                for (int i = 0; i < allStations.size(); i++) {
                    if (allStations[i].first.getName().find("MRT") == -1) {
                        if (!firstStation) {
                            startIdx = i;
                            firstStation = true;
                        }
                        cout << i + 1 << ". " << allStations[i].first.getName() << endl;
                        numberOfBusStation++;
                    }
                }

                // Select station to add a route
                cout << "Choose: ";
                int c; cin >> c;
                if (c >= 1 && c <= numberOfBusStation) {
                    allStations[startIdx + c - 1].first.addRoute(isBus, allStations);
                } else cout << "Invalid\n";

            }
            // Adding a route for Train (MRT)
            else if (k == 2) {
                bool isBus = false;
                int numberOfTrainStation = 0;
                cout << "Choose station:\n";
                for (int i = 0; i < allStations.size(); i++) {
                    if (allStations[i].first.getName().find("MRT") != -1) {
                        cout << i + 1 << ". " << allStations[i].first.getName() << endl;
                        numberOfTrainStation++;
                    }
                }

                cout << "Choose: ";
                int c; cin >> c;
                if (c >= 1 && c <= numberOfTrainStation) {
                    allStations[c - 1].first.addRoute(isBus, allStations);
                } else cout << "Invalid\n";
            }
            else cout << "Invalid\n";
        }
        else cout << "Invalid\n";
    }
    // If the role input is invalid
    else cout << "Invalid\n";
}
/*
  ALL TEST CASES
- Test case 1:
+ Input:
  1
  2
  2
  1
  1
  2
+ Output:
    Choose your role:
    1. Passenger
    2. Administrator
    Choose: 1
    ===================
    Name: Nguyen Khanh Hung
    ID: P001

    Choose function:
    1. View ticket booking history
    2. Book ticket
    3. Cancel ticket
    4. Deposit
    Choose: 2
    =================================
    BOOK TICKET
    Choose routes:
    1. MRT Line 1 (MRT)
    2. Bus A
    3. Bus B
    4. Bus C
    Choose: 2

    Choose type of bus:
    1. Bus (On-time)
    2. Express Bus (On-time)
    Choose: 1

    Choose first stop:
    1. City Center  Arrival Time: 08:05
    2. Green Park  Arrival Time: 08:12
    3. Airport  Arrival Time: 08:20
    4. Old Town  Arrival Time: 08:30
    Choose: 1

    Choose final stop:
    1. Green Park  Arrival Time: 08:12
    2. Airport  Arrival Time: 08:20
    3. Old Town  Arrival Time: 08:30
    4. Harbor  Arrival Time: 08:50
    Choose: 2
    Booking ticket sucessful!

        TICKET INFO:
    Route: Bus A
    Type: Bus
    First Stop: City Center
    Final Stop: Airport
    Departure Time: 08:05
    Arrival Time: 08:20
    Travel Time: 15 minutes

- Test case 2:
+ Input:
    1
    2
    4
    1
+ Output:
    Choose your role:
    1. Passenger
    2. Administrator
    Choose: 1
    ===================
    Name: Nguyen Khanh Hung
    ID: P001

    Choose function:
    1. View ticket booking history
    2. Book ticket
    3. Cancel ticket
    4. Deposit
    Choose: 2
    =================================
    BOOK TICKET
    Choose routes:
    1. MRT Line 1 (MRT)
    2. Bus A
    3. Bus B
    4. Bus C
    Choose: 4

    Choose type of bus:
    1. Bus (Full)
    Choose: 1

    The bus is full
*/

