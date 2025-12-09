#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures (unchanged)
typedef struct {
    int bus_id;
    char bus_name[50];
    char route[100];
    int total_seats;
    int available_seats;
    char departure_time[10];
    char arrival_time[10];
} Bus;

typedef struct {
    int user_id;
    char name[50];
    char email[50];
    char password[20];
} Passenger;

typedef struct {
    int reservation_id;
    int bus_id;
    int user_id;
    int seat_number;
    char reservation_date[20];
} Reservation;

// Function Prototypes (MODIFIED: Added getBusDetails)
void adminMenu();
void passengerMenu(int user_id);
void addBus();
void viewBuses();
void bookSeat(int user_id);
void viewReservations(int user_id);
int authenticateUser(char *email, char *password);
void registerUser();
void saveBus(Bus bus);
void saveReservation(Reservation reservation);
int generateReservationID();
int generateUserID();
int isBusAvailable(int bus_id);
void updateBusAvailability(int bus_id, int increment);
int isSeatAlreadyReserved(int bus_id, int seat_number, char *date);
int isValidSeatNumber(int bus_id, int seat_number);
// NEW PROTOYPE
void getBusDetails(int bus_id, char *bus_name, char *route, char *dep_time, char *arr_time);


// Main Function (unchanged)
int main() {
    int choice, user_id;
    char email[50], password[20];

    while (1) {
        printf("\n--- Bus Reservation System ---\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Register as Passenger\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                printf("Enter Email: ");
                scanf("%s", email);
                printf("Enter Password: ");
                scanf("%s", password);
                user_id = authenticateUser(email, password);
                if (user_id != -1) {
                    passengerMenu(user_id);
                } else {
                    printf("Invalid credentials. Try again.\n");
                }
                break;
            case 3:
                registerUser();
                break;
            case 4:
                printf("Thank you for using the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Admin Menu (unchanged)
void adminMenu() {
    int choice;

    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Bus\n");
        printf("2. View Buses\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                viewBuses();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Passenger Menu (unchanged)
void passengerMenu(int user_id) {
    int choice;

    while (1) {
        printf("\n--- Passenger Menu ---\n");
        printf("1. View Buses\n");
        printf("2. Book a Seat\n");
        printf("3. View My Reservations\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBuses();
                break;
            case 2:
                bookSeat(user_id);
                break;
            case 3:
                viewReservations(user_id);
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Add Bus (unchanged from your last provided code, includes input fixes)
void addBus() {
    Bus bus;
    int c;

    // Clear buffer before first scanf
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Bus ID: ");
    if (scanf("%d", &bus.bus_id) != 1) return;
    while ((c = getchar()) != '\n' && c != EOF); // Clear after scanf

    printf("Enter Bus Name: ");
    fgets(bus.bus_name, sizeof(bus.bus_name), stdin);
    bus.bus_name[strcspn(bus.bus_name, "\n")] = 0; // Remove newline

    printf("Enter Route: ");
    fgets(bus.route, sizeof(bus.route), stdin);
    bus.route[strcspn(bus.route, "\n")] = 0; // Remove newline
    
    printf("Enter Total Seats (e.g., 50): "); 
    if (scanf("%d", &bus.total_seats) != 1) return;
    bus.available_seats = bus.total_seats;
    while ((c = getchar()) != '\n' && c != EOF); // Clear after scanf

    printf("Enter Departure Time (e.g., 10:00AM): ");
    fgets(bus.departure_time, sizeof(bus.departure_time), stdin);
    bus.departure_time[strcspn(bus.departure_time, "\n")] = 0;

    printf("Enter Arrival Time (e.g., 03:00PM): ");
    fgets(bus.arrival_time, sizeof(bus.arrival_time), stdin);
    bus.arrival_time[strcspn(bus.arrival_time, "\n")] = 0;

    saveBus(bus);
    printf("Bus added successfully!\n");
}

// Save Bus to File (unchanged)
void saveBus(Bus bus) {
    FILE *file = fopen("buses.dat", "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&bus, sizeof(Bus), 1, file);
    fclose(file);
}

// View Buses (unchanged)
void viewBuses() {
    FILE *file = fopen("buses.dat", "rb");
    if (!file) {
        printf("No buses available.\n");
        return;
    }

    Bus bus;
    printf("\n--- Available Buses ---\n");
    while (fread(&bus, sizeof(Bus), 1, file)) {
        printf("Bus ID: %d | Name: %s | Route: %s | Seats: %d/%d | Departure: %s | Arrival: %s\n",
               bus.bus_id, bus.bus_name, bus.route, bus.available_seats, bus.total_seats, bus.departure_time, bus.arrival_time);
    }
    fclose(file);
}

// Book Seat (unchanged)
void bookSeat(int user_id) {
    int bus_id, seat_number;
    char date[20];
    int c;

    printf("Enter Bus ID: ");
    if (scanf("%d", &bus_id) != 1) return;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Reservation Date (DD-MM-YYYY): ");
    if (scanf("%s", date) != 1) return;
    while ((c = getchar()) != '\n' && c != EOF);

    if (!isBusAvailable(bus_id)) {
        printf("Invalid Bus ID or no available seats.\n");
        return;
    }

    printf("Enter Seat Number: ");
    if (scanf("%d", &seat_number) != 1) return;
    while ((c = getchar()) != '\n' && c != EOF);

    // 1. Check if seat number is valid (e.g., 1 to 50)
    if (!isValidSeatNumber(bus_id, seat_number)) {
        printf("Invalid Seat Number. Please choose a seat between 1 and the total number of seats.\n");
        return;
    }

    // 2. Check if the seat is already reserved for this bus on this date
    if (isSeatAlreadyReserved(bus_id, seat_number, date)) {
        printf("Seat %d is already reserved for bus %d on %s. Please choose another seat.\n", seat_number, bus_id, date);
        return;
    }
    
    // 3. Proceed with reservation
    Reservation reservation = {generateReservationID(), bus_id, user_id, seat_number, ""};
    strcpy(reservation.reservation_date, date);

    saveReservation(reservation);
    updateBusAvailability(bus_id, -1); // Decrement available seats count
    printf("Reservation successful! Reservation ID: %d\n", reservation.reservation_id);
}

// Save Reservation to File (unchanged)
void saveReservation(Reservation reservation) {
    FILE *file = fopen("reservations.dat", "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&reservation, sizeof(Reservation), 1, file);
    fclose(file);
}

// NEW FUNCTION: Bus ID এর ভিত্তিতে বাসের বিবরণ খুঁজে বের করে
void getBusDetails(int bus_id, char *bus_name, char *route, char *dep_time, char *arr_time) {
    FILE *file = fopen("buses.dat", "rb");
    if (!file) {
        strcpy(bus_name, "N/A");
        strcpy(route, "N/A");
        strcpy(dep_time, "N/A");
        strcpy(arr_time, "N/A");
        return;
    }

    Bus bus;
    int found = 0;
    while (fread(&bus, sizeof(Bus), 1, file)) {
        if (bus.bus_id == bus_id) {
            strcpy(bus_name, bus.bus_name);
            strcpy(route, bus.route);
            strcpy(dep_time, bus.departure_time);
            strcpy(arr_time, bus.arrival_time);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        strcpy(bus_name, "Unknown Bus");
        strcpy(route, "Unknown Route");
        strcpy(dep_time, "N/A");
        strcpy(arr_time, "N/A");
    }
}


// View Reservations (MODIFIED: Now shows Bus Details)
void viewReservations(int user_id) {
    FILE *file = fopen("reservations.dat", "rb");
    if (!file) {
        printf("No reservations found.\n");
        return;
    }

    Reservation reservation;
    char bus_name[50], route[100], dep_time[10], arr_time[10];

    printf("\n--- My Reservations ---\n");
    printf("%-10s | %-15s | %-20s | %-10s | %-10s | %-8s | %-12s\n", 
           "Res ID", "Bus Name", "Route", "Dept Time", "Arr Time", "Seat", "Date");
    printf("------------------------------------------------------------------------------------------\n");

    while (fread(&reservation, sizeof(Reservation), 1, file)) {
        if (reservation.user_id == user_id) {
            // Get bus details using the reservation's bus_id
            getBusDetails(reservation.bus_id, bus_name, route, dep_time, arr_time);

            printf("%-10d | %-15s | %-20s | %-10s | %-10s | %-8d | %-12s\n",
                   reservation.reservation_id, 
                   bus_name, 
                   route, 
                   dep_time, 
                   arr_time,
                   reservation.seat_number, 
                   reservation.reservation_date);
        }
    }
    fclose(file);
}

// Authenticate User (unchanged)
int authenticateUser(char *email, char *password) {
    FILE *file = fopen("users.dat", "rb");
    if (!file) {
        printf("No users found.\n");
        return -1;
    }

    Passenger user;
    while (fread(&user, sizeof(Passenger), 1, file)) {
        if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return user.user_id;
        }
    }
    fclose(file);
    return -1;
}

// Register User (unchanged)
void registerUser() {
    Passenger user;
    user.user_id = generateUserID();

    printf("Enter Name: ");
    scanf("%s", user.name);
    printf("Enter Email: ");
    scanf("%s", user.email);
    printf("Enter Password: ");
    scanf("%s", user.password);

    FILE *file = fopen("users.dat", "ab");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&user, sizeof(Passenger), 1, file);
    fclose(file);
    printf("Registration successful! Your User ID is %d\n", user.user_id);
}

// Generate Unique IDs (unchanged)
int generateReservationID() { return rand() % 10000; }
int generateUserID() { return rand() % 10000; }


// Check Bus Availability (unchanged)
int isBusAvailable(int bus_id) {
    FILE *file = fopen("buses.dat", "rb");
    if (!file) return 0;

    Bus bus;
    while (fread(&bus, sizeof(Bus), 1, file)) {
        if (bus.bus_id == bus_id && bus.available_seats > 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


// Check if Seat is Already Reserved (unchanged)
int isSeatAlreadyReserved(int bus_id, int seat_number, char *date) {
    FILE *file = fopen("reservations.dat", "rb");
    if (!file) return 0;

    Reservation res;
    while (fread(&res, sizeof(Reservation), 1, file)) {
        if (res.bus_id == bus_id && res.seat_number == seat_number && strcmp(res.reservation_date, date) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Check if Seat Number is valid (unchanged)
int isValidSeatNumber(int bus_id, int seat_number) {
    FILE *file = fopen("buses.dat", "rb");
    if (!file) return 0; 

    Bus bus;
    while (fread(&bus, sizeof(Bus), 1, file)) {
        if (bus.bus_id == bus_id) {
            fclose(file);
            if (seat_number > 0 && seat_number <= bus.total_seats) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    fclose(file);
    return 0;
}


// Update Bus Availability (unchanged)
void updateBusAvailability(int bus_id, int increment) {
    FILE *file = fopen("buses.dat", "rb+");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    Bus bus;
    long current_pos;

    while (fread(&bus, sizeof(Bus), 1, file)) {
        if (bus.bus_id == bus_id) {
            bus.available_seats += increment;
            
            fseek(file, -sizeof(Bus), SEEK_CUR);
            
            fwrite(&bus, sizeof(Bus), 1, file);
            break;
        }
    }
    fclose(file);
}