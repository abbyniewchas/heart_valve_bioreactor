% https://www.mathworks.com/matlabcentral/fileexchange/51037-zcshiner-dynamixel-mx64-matlab
% https://www.mathworks.com/help/matlab/ref/serialport.read.html
% http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/library_setup/matlab_linux/#matlab-linux
%% Read value from Arduino serial port and send position command

% Setup Dynamixel
%COM_port = 31;
%baud = 1000000;
%Dynamixel = MX64("ttyACM0",baud);

%angle = 50;
%Dynamixel.position(ID,angle);

% If using read from serial port
%s = serialport("/dev/ttyACM0",9600);
for i = 1:0.01:100
    data = read(s,1,"string")
end