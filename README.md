# Ostiary

Ostiary is an access control system based on the ATMEL platform.

In Ancient Roman times, all members of the upper class employed an ostiarius, or ostiary, whose duty it was to stand
guard over the main entrance of the house.

The Ostiary system is a NFC/RFID compatible access control system which uses an ATmega2560 microcontroller and a PN532
NFC controller. It is compatible with any 13.56MHz RFID or NFC tag, Type 1 thru 4, and even MiFare tags.

Ostiary is compatible with virtually any door strike and can be retrofitted to most existing systems with ease. The
only thing that is required is a 5V power connection for the unit itself. The system is fail-proof, meaning in the
case of a power outage, the door strike will remain closed. The Ostiary also has support for various types of exit
switches, like Exit PIRs and push buttons.

###HOW IT WORKS

Ostiary is comprised of 3 main components: a MySQL database, an NFC reader and a webserver. The reader sends the
scanned NFC tag to a webserver which checks it against a database. If the tag exists in the database then it sends an
open command to the reader. When the door opens, an entry is created in the log table of the database with a timestamp
and the tag ID which opened the door.

###HOW TO SET IT UP

Create your MySQL database with the file "1-MakeDB.sql". Then configure your webserver and place the file "check.php"
in a folder named "ostiary". Download the Arduino sketch file, and change the ip, username, password, and port to
reflect your configuration. Then save and compile the sketch an upload it to your Arduino.
