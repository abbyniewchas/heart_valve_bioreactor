% https://www.mathworks.com/matlabcentral/fileexchange/51037-zcshiner-dynamixel-mx64-matlab
% https://www.mathworks.com/help/matlab/ref/serialport.read.html
% http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/library_setup/matlab_linux/#matlab-linux
%% Read value from Arduino serial port and send position command

% Setup Dynamixel
COM_port = 31;
baud = 1000000;
Dynamixel = MX64(COM_port,baud);

angle = 50;
Dynamixel.position(ID,angle);

% If using read from serial port
s = serialport("COM3",9600);
data = read(s,5,"uint32");