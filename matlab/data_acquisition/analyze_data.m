% Create figures for presentation of bioreactor data

% Ted Lutkus

% Data acquisition frequency with arduino
data_freq = 41; % [Hz]

% Baseline bioreactor pressure
data_baseline = load('pressure_data_baseline.csv');
baseline = mean(data_baseline);

%% Single Waveform
% Pull data for single wave
data_wave = load('white_push_in_CV_1.csv');
data_wave = data_wave(342:454);
data_wave = data_wave - baseline;
time_wave = ((0:length(data_wave)-1) * 1/data_freq)';

% Plot single wave data
figure;
plot(time_wave, data_wave, 'r-o', 'LineWidth', 2);
xlim([0, time_wave(end)]);
xlabel('Time [s]');
ylabel('Post-Valve Pressure [mmHg]');
title('Bioreactor Physiological Waveform');

%% 60 BPM 20 Over 10
data_60 = load('black_sine1hz_CV_1plus0.55.csv');
data_60 = data_60(10:257) - 28;
time_60 = ((0:length(data_60)-1) * 1/data_freq)';
figure;
plot(time_60, data_60, 'r-o', 'LineWidth', 2);
xlim([0, time_60(end)]);
xlabel('Time [s]');
ylabel('Post-Valve Pressure [mmHg]');
title('Bioreactor 20 Over 10 Waveform (60BPM)');

%% Low Pressure Waveform
data_low = load('white_sine0.05hz_MV_1.csv');
data_low = data_low(data_low > -100) - baseline; % Removing some bad reads from the serial port
time_low = ((0:length(data_low)-1) * 1/data_freq)';
figure;
plot(time_low, data_low, 'r-o');
xlim([0, time_low(end)]);
xlabel('Time [s]');
ylabel('Post-Valve Pressure [mmHg]');
title('Bioreactor Low Pressure Waveform');

%% 120 BPM 20 Over 10
data_120 = load('120_bpm_p2.csv');
data_120 = data_120 - baseline;
time_120 = ((0:length(data_120)-1) * 1/data_freq)';
figure;
plot(time_120, data_120, 'r-o', 'LineWidth', 2);
xlim([0, time_120(end)]);
xlabel('Time [s]');
ylabel('Post-Valve Pressure [mmHg]');
title('Bioreactor Running at 120 Beats Per Minute');