%% Sample for actual pressure waveform
time = [0 0.25 0.4 1 1.1];
y = [0 30 20 0 0];

xx = 0:0.01:time(end);

yy = pchip(time, y, xx);
clf;
plot(xx, yy)
hold on
plot(time, y, 'o')

%% Waveform Test

x = [0 0.2 0.6 0.65 0.8];
y = [0 50 -10 0 0];

xx = 0:0.001:x(end);

yy = pchip(x, y, xx);

clf;
plot(x, y, 'o')
hold on
plot(xx, yy)
legend({'data', 'pchip'})
title('Waveform Sample')