% This script will load necessary data to setup the parameters of the
% bioreactor and then pull up the GUI

% Ted Lutkus
% 1/13/2020

% Load lab user data from excel sheet
[~,sheet_names] = xlsfinfo('gui_data/lab_user_settings.xlsx');
for i = 1:length(sheet_names)
    
    % Load lab member's sheet to loop through experiments they have setup
    lab_sheet = readcell('gui_data/lab_user_settings.xlsx', 'Sheet', sheet_names{i});
    
    % Allocate memory to a struct to pass into the gui
    lab_data.users(i) = sheet_names(i);
    lab_data.experiments(i,:) = lab_sheet(1,2:end);
    lab_data.peak_pressures(i,:) = lab_sheet(2,2:end);
    lab_data.min_pressures(i,:) = lab_sheet(3,2:end);
    lab_data.forward_pulse_time(i,:) = lab_sheet(4,2:end);
    lab_data.backpressure_time(i,:) = lab_sheet(5,2:end);
    lab_data.rest_time(i,:) = lab_sheet(6,2:end); %later bpm!!
    lab_data.acq_freq(i,:) = lab_sheet(7,2:end);
    lab_data.save_loc = lab_sheet(8,2:end);
end

% Run the bioreactor and pass in the lab's data
bioreactor_gui(lab_data);