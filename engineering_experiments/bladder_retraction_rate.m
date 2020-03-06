% Use ode to determine fill rate of bladder

[t, V]=ode45('bladder_diffeqn',[0 2], 0);
A = 4.0079e-05;

figure;
plot(t, V/A)