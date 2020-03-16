%% Connect Arduino
clear s;
s = serialport(serialportlist, 1000000)
flush(s);

%% Collect Data
flush(s);
a = cell(10000,1);
for i = 1:100000
   a{i} = readline(s);
   disp(i);
end

%% Extract data

data = a(~cellfun('isempty', a));

pressure = zeros(length(data), 1);
for i = 1:length(data)
    data_split = split(data{i}, ', ');
    if length(data_split) == 4
        pressure(i) = str2double(data_split(3));
    end
end

pressure = pressure * 0.750062 - 766;

%% Plot data

figure;
%plot(pressure(1:end)*0.750062 - 766 - 21, '-o');

% Baseline pressure
baseline = 28.3510;
%pressure_plot = pressure;
pressure_plot = pressure(pressure > -5);
plot(pressure_plot(1:end) - baseline, '-o');

%LOW PRESSURE: pressure*0.750062 - 766 - 21
%% Save data
% naming: ring - wave - valve - version
% all displacement = 500 servo increments
writematrix(pressure, 'black_sine1hz_CV_2010_almost.csv');