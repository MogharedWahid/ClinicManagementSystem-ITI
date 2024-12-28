# Clinic Management System

This is a simple C-based **Clinic Management System** that allows an administrator to manage patient records, including adding new patients, editing records, reserving and canceling appointment slots. A user can view their own patient record and check their reservation status.

## Features

- **Admin Mode**:
  - Add a new patient.
  - Edit existing patient records.
  - Reserve an appointment slot.
  - Cancel a reservation.

- **User Mode**:
  - View personal patient record.
  - View today's reservation (if any).

## Prerequisites

- C compiler (e.g., GCC) to compile and run the code.
- Basic understanding of C programming (structures, enums, arrays, and functions).

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/MogharedWahid/ClinicManagementSystem-ITI.git
   cd ClinicManagementSystem-ITI
2. **Compile the code:** If you're using GCC, compile the code with the following command:
   ```bash
   gcc -o clinic.c
   ```
3. **Run the program:** After compiling, you can run the program with:
   ```bash
   ./clinic

## Code Walkthrough

### Structures

- **Patient Structure**:  The `Patient` structure holds information about each patient, including:
  - `name`: The patient's name (up to 20 characters).
  - `gender`: The patient's gender (either 'm' for male or 'f' for female).
  - `age`: The patient's age.
  - `id`: The patient's unique identification number.
  - `slot`: The reserved slot for the patient's appointment. If there is no reservation, it's set to `-1`.

### Enums
* **Mode:** Defines the operating mode of the system (`ADMIN_MODE` or `USER_MODE`).
* **AdminChoice:** Defines the options available in the admin mode (Add, Edit, Reserve, Cancel).
* **UserChoice:** Defines the options available in the user mode (View Record, View Reservations).

### Functions
* **choose_mode():** Prompts the user to choose between Admin and User mode.
* **check_password():** Validates the admin's password with a maximum of 3 attempts.
* **check_add_id():** Checks whether the patient ID is already in use before adding a new patient.
* **check_id():** Checks whether the given ID exists in the system (for editing or viewing records).
* **admin_choices():** Displays options for the admin (add, edit, reserve, or cancel a patient record).
* **add_patient():** Adds a new patient to the system.
* **edit_patient_record():** Edits the details of an existing patient.
* **reserve_slot():** Reserves an appointment slot for a patient.
* **cancel_reservation():** Cancels a patient's reservation.
* **user_choices():** Displays options for the user (view record or view reservation).
* **view_patient_record():** Displays the patient's personal details.
* **view_todays_reservation():** Displays the patient's current reservation status.

### Slots
There are 5 available time slots for reservations:
* From 2:00 PM to 2:30 PM
* From 2:30 PM to 3:00 PM
* From 3:00 PM to 3:30 PM
* From 4:00 PM to 4:30 PM
* From 4:30 PM to 5:00 PM

These slots can be reserved by patients, and the system ensures that each slot can only be reserved by one patient at a time.

### Error Handling
* **Invalid Password:** Admin must enter the correct password. After 3 attempts, the system will lock.
* **Duplicate IDs:** Admin cannot add a patient with an existing ID.
* **Slot Reservation:** Admin or patient cannot reserve an already occupied time slot.
* **Patient Not Found:** Admin or user must provide a valid patient ID when editing records or viewing patient information.

## Usage

1.**Admin Mode:**
* Enter the correct admin password.
* Choose from the following admin actions:
  * Add a new patient.
  * Edit an existing patient record.
  * Reserve an appointment slot.
  * Cancel a reservation.

2.**User Mode:**
* Choose a user action:
  * View patient record: Displays the user's personal details.
  * View today's reservation: Displays the user's current reservation slot.
 
## Example
Here’s an example of the flow in **Admin Mode**:

1. Admin logs in by entering the correct password.
2. Admin chooses to Add a new patient.
3. The program prompts for the patient's details (name, age, gender).
4. The patient is added to the system.
5. Admin can then choose to Reserve an appointment slot for the patient.

In **User Mode**, the user can:

1. View their personal patient record.
2. Check their current appointment reservation.


## Limitations
* The system is limited to managing up to 20 patients (MAX_PATIENTS).
* Only 5 appointment slots are available for reservation at any given time.
* The admin password is hardcoded (set to 1234).

## Future Enhancements
* Use a database to store patient records permanently.
* Implement more sophisticated user authentication.
* Extend functionality to support multiple doctors and their respective schedules.
* Add more user-friendly error messages and improve input validation.
