"# capstone-hcs-files" 
To interface with Arduino, an additional library needs to be installed:
https://www.mathworks.com/matlabcentral/fileexchange/40312-simulink-support-package-for-arduino-hardware

Once this is installed and the setup is complete, connect the (master) Arduino Uno to the controlling PC via USB-B

Master Arduino should be able to power the (slave) Arduino Nano, which is used to update the LCD. 

Please find the master simulation file in the 'FINAL PROJECT SLX' folder.

If .ino scripts need to be uploaded to Arduino, the 'simulinkInterface' ought to be uploaded to the Uno board and the 'slaveSimulinkClock' is for the Uno.