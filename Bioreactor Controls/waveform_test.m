%% Sample for actual pressure waveform
time = [0 0.25 0.4 1 1.1];
y = [0 30 20 0 0];

xx = 0:0.01:time(end);

yy = pchip(time, y, xx);
clf;
plot(xx, yy)
hold on
plot(time, y, 'o')