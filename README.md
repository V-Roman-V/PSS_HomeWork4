# PSS_HomeWork4
The task is to implement a backend for the WEndex.Taxi.

## Program features
### first version
- The program stores all information about people in a database.
- A person's age is automatically calculated from today's date by their date of birth.
- People have passports, phone numbers, and more. 
- The database is organized so that there is no duplicate information.
- When you save the address, you can specify its abbreviation
- A system of communication between the user and the driver has been implemented.
- Implemented system allows to test all features manually.
- Control menus have been implemented for interaction with the user and with the driver. 
- In the console you can select the option by typing the whole word or its number.
- You can go back at any time during the interaction with the system.
- A nice input with the ">" symbol has been implemented :)
- The text in the console is automatically erased for convenience, so you don't have to scroll much.
- Incorrectly entered text is also erased so as not to clutter up the console.
- You can only log in by entering a phone number from the database.
- All information is saved when you close program
- I implemented my own class enum, which allows me to conveniently display its text.
### second version
- Implemented admin Gateway
- Admin can block passengers to create orders, and can also block drivers to take orders. He can also unblock them.
- Admin can find out information about any user
- Multiple mobile devices for all is provided by storing all information in a database.
- Drivers can now have many cars and take orders, for all types of cars he has.
- A driver cannot use an unverified car, but may have it.
- An admin interface has also been added, so that you can use it to test the program.

## How to open the code
 For this project the qmake build system was used.  
 The ".pro" file is located in the directory:
 > PSS_HomwWork4

### Where the source code is located
  main.cpp and other classes are located in the directory:
 > PSS_HomwWork4

## Where the database is located
 For this project the excele database was used.  
 The ".xlsx" file is located in the directory:
 > build-PSS_HomeWork4-Desktop_Qt_5_12_5_MinGW_64_bit-Release\release\DataBase
 
### How to execute the code
  Compiled and ready to run .exe file is located in the directory:
 > build-PSS_HomeWork4-Desktop_Qt_5_12_5_MinGW_64_bit-Release\release
  
  The runnability test was done under Windows x64 without Qt, the .exe file ran successfully.
  

## How to test the code
**Important**: The current version of the program does not support multiple entries in the database, but it saves all data after closing. Therefore, you have to start the program again when you switch between people. 
Testing my program can be done entirely through communicating with my system in the console.
![image](https://user-images.githubusercontent.com/48117438/116116794-bcc9de80-a6e5-11eb-855b-89d4c53f864a.png)
Your options are written in curly brackets. You can enter either the whole word or a short character in brackets to the left.   
To log in you must enter a phone number, all numbers are stored in a database.  
For example, the phone number of the **passenger**: 89959280771, the **driver**: 333221234, the **admin**:3377722.
